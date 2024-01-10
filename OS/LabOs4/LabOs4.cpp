#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include<vector>

std::string lineReader(std::string name) {

	std::ifstream in(name, std::ios::binary);
	std::vector<std::string> vectorOfString;

	while (!in.eof()) {
		std::string temp;
		std::getline(in, temp);
		vectorOfString.push_back(temp);
	}

	in.close();
	std::ofstream out(name, std::ios::binary);

	for (size_t i = 1; i < vectorOfString.size(); i++) {
		out << vectorOfString[i] << "\n";
	}
	out.close();

	return vectorOfString[0];
}


int main()
{
	setlocale(LC_ALL, "ru");

	std::cout << "Введите имя бинарного файла(Без расширения) :";
	std::string inputFileName;
	std::cin >> inputFileName;
	inputFileName += ".bin";

	std::cout << "Введите количество записей: ";
	int numOfRecords;
	std::cin >> numOfRecords;

	std::cout << "Введите количество процессов Sender: ";
	int numOfSenders;
	std::cin >> numOfSenders;

	HANDLE hInputSemaphore = CreateSemaphore(NULL, 0, numOfRecords, L"Input Semaphore started");
	if (hInputSemaphore == NULL) {
		return GetLastError();
	}

	HANDLE hOutputSemaphore = CreateSemaphore(NULL, numOfRecords, numOfRecords, L"Output Semaphore started");
	if (hOutputSemaphore == NULL) {
		return GetLastError();
	}

	HANDLE* hEventStarted = new HANDLE[numOfSenders];

	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	LPWSTR lpwstrSenderProcessCommandLine;
	for (int i = 0; i < numOfSenders; i++)
	{
		std::string sender_cmd = "Sender.exe " + inputFileName;
		std::wstring commandLine = std::wstring(sender_cmd.begin(), sender_cmd.end());
		lpwstrSenderProcessCommandLine = &commandLine[0];

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (!CreateProcess(NULL, lpwstrSenderProcessCommandLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			std::cout << "Sender сломали ящеры \n";
			return GetLastError();
		}

		hEventStarted[i] = CreateEvent(NULL, FALSE, FALSE, L"StartProcess");

		CloseHandle(pi.hProcess);
	}

	WaitForMultipleObjects(numOfSenders, hEventStarted, TRUE, INFINITE);

	std::cout << "Введите 1 - хотите вывести глагольню, 0 - хотите закрыть Великорусский процесс Receiver : ";
	int answer;
	std::cin >> answer;
	std::ifstream file(inputFileName, std::ios::binary);
	while (true)
	{
		if (answer == 1)
		{
			WaitForSingleObject(hInputSemaphore, INFINITE);
			ReleaseSemaphore(hOutputSemaphore, 1, NULL);

			char userMessage[20];
			file.read(userMessage, sizeof(userMessage));
			std::cout << "Полученное сообщение: " << lineReader(inputFileName) << "\n";
			std::cout << "Введите 1 - хотите вывести глагольню, 0 - хотите закрыть Великорусский процесс Receiver : ";
			std::cin >> answer;
		}
		else if (answer == 0)
		{
			break;
		}
		else
		{
			std::cout << "Ящерский ввод! Акстись! \n";
			std::cout << "Введите 1 - хотите вывести глагольню, 0 - хотите закрыть Великорусский процесс Receiver : ";
			std::cin >> answer;
		}
	}

	CloseHandle(hInputSemaphore);
	CloseHandle(hOutputSemaphore);
	for (int i = 0; i < numOfSenders; i++)
	{
		CloseHandle(hEventStarted[i]);
	}
	delete[] hEventStarted;	
	file.clear();
	file.close();
	return 0;
}