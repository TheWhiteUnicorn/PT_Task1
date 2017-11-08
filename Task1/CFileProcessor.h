#pragma once
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

class CFileProcessor
{
public: // конструктор и деструктор
	CFileProcessor();
	~CFileProcessor();
public:
	// Обозначить искомое слово
	void SetWantedWord(string strWanted);
	// Произвести все необходимые операции над файлом
	// Парам.: имена файла ввода и вывода
	void Process(string strFileInName, string strFileOutName); //exception
private:
	// Искомое слово
	string m_strWantedWord;
	// Рабочие файлы
	ifstream m_ifsFileIn;
	ofstream m_ofsFileOut;
	
private:
	// Открыть файлы для чтения и записи
	void _OpenFiles(string strFileInName, string strFileOutName); //exception
	// Проверить готовность файлов
	bool _FilesAreReady();
	// Проверить, совпадает ли переданное слово c искомым
	bool _IsWanted(const string strCurWord, const bool bEndingPunctSign);
	// Закрыть все открытые файлы
	void _CloseFiles();
};

