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

	// Произвести все необходимые операции над файлом
	void Process(string strFileInName, string strFileOutName); //exception
private:
	string m_strWantedWord;
	// Рабочие файлы
	ifstream m_ifsFileIn;
	ofstream m_ofsFileOut;
private:
	// Открыть файлы для чтения и записи
	void _OpenFiles(string strFileInName, string strFileOutName); //exception
	// Проверить готовность файлов
	bool _FilesAreReady() noexcept;
	// Проверить, совпадает ли переданное слово c искомым
	bool _IsWanted(const string strCurWord, const bool bEndingPunctSign) noexcept;
	// Закрыть все открытые файлы
	void _CloseFiles() noexcept;
};

