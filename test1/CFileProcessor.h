#pragma once
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

class CFileProcessor
{
public: 
	CFileProcessor();
	~CFileProcessor();
public:
	
	void SetWantedWord(string strWanted) noexcept;

	// ���������� ��� ����������� �������� ��� ������
	void Process(string strFileInName, string strFileOutName); //exception
private:
	string m_strWantedWord;
	// ������� �����
	ifstream m_ifsFileIn;
	ofstream m_ofsFileOut;
private:
	// ������� ����� ��� ������ � ������
	void _OpenFiles(string strFileInName, string strFileOutName); //exception
	// ��������� ���������� ������
	bool _FilesAreReady() noexcept;
	// ���������, ��������� �� ���������� ����� c �������
	bool _IsWanted(const string strCurWord, const bool bEndingPunctSign) noexcept;
	// ������� ��� �������� �����
	void _CloseFiles() noexcept;
};

