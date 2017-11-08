#include "CFileProcessor.h"
#include <stdexcept>

#define SPACE_CHAR ' '
#define FOPEN_ERR_MSG "Ошибка при открытии файлов"
#define END_OF_SENTENCE_SIGNS ".!?"
#define COMMA_CHAR ','


CFileProcessor::CFileProcessor() {
	m_strWantedWord = "перевод";
}

CFileProcessor::~CFileProcessor() {
}


void CFileProcessor::SetWantedWord(string strWanted) {
	m_strWantedWord = strWanted;
}

void CFileProcessor::Process(string strFileInName, string strFileOutName) {
	_OpenFiles(strFileInName, strFileOutName);

	string strCurWord;
	string strCurSentence;

	while (!m_ifsFileIn.eof()) {
		while (!m_ifsFileIn.eof()){
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

		}
	}
}

void CFileProcessor::_OpenFiles(string strFileInName, string strFileOutName) {
	m_ifsFileIn.open(strFileInName);
	m_ofsFileOut.open(strFileOutName);
	if (!_FilesAreReady()) throw new exception(FOPEN_ERR_MSG);
}

bool CFileProcessor::_FilesAreReady() {
	if (m_ifsFileIn.is_open() && m_ofsFileOut.is_open)
		return true;
	else
		return false;
}

bool CFileProcessor::_IsWanted(const string strCurWord, const bool bEndingPunctSign) {
	string strCurTmp(strCurWord);
	strCurTmp[0] = tolower(strCurTmp[0]);
	return false;
}

void CFileProcessor::_CloseFiles() {
	m_ifsFileIn.close();
	m_ofsFileOut.close();
}
