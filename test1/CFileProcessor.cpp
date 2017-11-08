#include "CFileProcessor.h"
#include <stdexcept>

#define SPACE_CHAR ' '
#define FOPEN_ERR_MSG "������ ��� �������� ������"
#define END_OF_SENTENCE_SIGNS ".!?"
#define COMMA_CHAR ','


CFileProcessor::CFileProcessor() {
	m_strWantedWord = "�������";
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
		bool bFoundWanted = false; // ������� � ���, ��� � ������� ����������� ������� ������� �����
		
		while (!m_ifsFileIn.eof()){
			if (!_FilesAreReady()) throw new exception(FOPEN_ERR_MSG);

			m_ifsFileIn >> strCurWord;
			// ����� ������� ����� � �����������
			strCurSentence = strCurSentence + strCurWord + SPACE_CHAR;
			
			bool bEndOfSentence = false; // ������� � ���, ��� ������� ����� �������� ��������� � �����������
			bool bEndingPunctuationMark = false; // ������� � ������� � ����� �������� ����� ����� ����������
			
			if (strCurWord.find_first_of(COMMA_CHAR) != -1)
				bEndingPunctuationMark = true;
			if (strCurWord.find_first_of(END_OF_SENTENCE_SIGNS) != -1) {
				bEndingPunctuationMark = true;
				bEndOfSentence = true;
			}
			bFoundWanted = _IsWanted(strCurWord, bEndingPunctuationMark);
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
	m_ifsFileIn.open(strFileInName);
	m_ofsFileOut.open(strFileOutName);
	if (!_FilesAreReady()) throw new exception(FOPEN_ERR_MSG);
}

bool CFileProcessor::_FilesAreReady() {
	if (m_ifsFileIn.is_open() && m_ofsFileOut.is_open())
		return true;
	else
		return false;
}

bool CFileProcessor::_IsWanted(const string strCurWord, const bool bEndingPunctSign) {
	string strCurTmp(strCurWord);
	strCurTmp[0] = tolower(strCurTmp[0]);
	bool bSizeWithoutSignsEqual = !bEndingPunctSign && strCurTmp.size() == m_strWantedWord.size();
	bool bSizeWithSignsEqueal = bEndingPunctSign && strCurTmp.size() - 1 == m_strWantedWord.size();
	if (strCurTmp.find(m_strWantedWord) != -1 && (bSizeWithSignsEqueal || bSizeWithoutSignsEqual))
		return true;

	return false;
}

void CFileProcessor::_CloseFiles() {
	m_ifsFileIn.close();
	m_ofsFileOut.close();
}