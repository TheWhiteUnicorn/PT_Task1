#include "CFileProcessor.h"
#include <cassert>
#include <ctype.h>

const char SPACE_CHAR = ' ';
const char COMMA_CHAR = ',';
const char FOPEN_ERR_MSG[] = "Ошибка при открытии файлов";
const char END_OF_SENTENCE_SIGNS[] = ".!?";



CFileProcessor::CFileProcessor() {
	m_strWantedWord = "перевод";
}

CFileProcessor::~CFileProcessor() {
}


void CFileProcessor::SetWantedWord(string strWanted) noexcept {
	m_strWantedWord = strWanted;
}

void CFileProcessor::Process(string strFileInName, string strFileOutName) {
	_OpenFiles(strFileInName, strFileOutName);

	string strCurWord;
	string strCurSentence;

	while (!m_ifsFileIn.eof()) {
		bool bFoundWanted = false; // Говорит о том, что в текущем предложении найдено искомое слово
		
		while (!m_ifsFileIn.eof()){
			if (!_FilesAreReady()) throw new exception(FOPEN_ERR_MSG); //exception

			m_ifsFileIn >> strCurWord;
			// Сразу заносим слово в предложение
			strCurSentence = strCurSentence + strCurWord + SPACE_CHAR;
			
			bool bEndOfSentence = false; // Говорит о том, что текущее слово является последним в предложении
			bool bEndingPunctuationMark = false; // Говорит о наличии в конце текущего слова знака пунктуации
			
			if (strCurWord.find_first_of(COMMA_CHAR) != -1)
				bEndingPunctuationMark = true;
			if (strCurWord.find_first_of(END_OF_SENTENCE_SIGNS) != -1) {
				bEndingPunctuationMark = true;
				bEndOfSentence = true;
			}
			if(_IsWanted(strCurWord, bEndingPunctuationMark))
				bFoundWanted = true;

			if (bEndOfSentence) {
				if(bFoundWanted)
					m_ofsFileOut << strCurSentence;
				break;
			}
		}
		strCurWord.clear();
		strCurSentence.clear();
	}
	_CloseFiles();
}

void CFileProcessor::_OpenFiles(string strFileInName, string strFileOutName) {
	assert(strFileInName.size() != NULL && strFileOutName.size() != NULL);
	m_ifsFileIn.open(strFileInName);
	m_ofsFileOut.open(strFileOutName);
	if (!_FilesAreReady()) throw new exception(FOPEN_ERR_MSG); //exception
}

bool CFileProcessor::_FilesAreReady() noexcept {
	return (m_ifsFileIn && m_ofsFileOut);
}


bool CFileProcessor::_IsWanted(const string strCurWord, const bool bEndingPunctSign) noexcept {
	string strCurTmp(strCurWord);
	strCurTmp[0] = tolower(strCurTmp[0]);
	bool bSizeWithoutSignsEqual = !bEndingPunctSign && strCurTmp.size() == m_strWantedWord.size();
	bool bSizeWithSignsEqueal = bEndingPunctSign && strCurTmp.size() - 1 == m_strWantedWord.size();

	return strCurTmp.find(m_strWantedWord) != -1 && (bSizeWithSignsEqueal || bSizeWithoutSignsEqual);
}

void CFileProcessor::_CloseFiles() noexcept {
	m_ifsFileIn.close();
	m_ofsFileOut.close();
}