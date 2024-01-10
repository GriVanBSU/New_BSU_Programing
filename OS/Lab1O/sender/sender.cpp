#include<string>
#include<conio.h>
#include<Windows.h>
#include<fstream>
#include <iostream>
#include<vector>
#include<mutex>

const int MAX_MESSAGE_SIZE = 20;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	std::string fileName = argv[1];
	std::fstream binFile;

	HANDLE hStartEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"StartProcess");
	if (hStartEvent == NULL)
	{
		std::cout << "Окаянные ящеры сломали компьютер!\n";
		std::cin.get();
		return GetLastError();
	}

	HANDLE hInputSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"Input Semaphore started");
	if (hInputSemaphore == NULL) {
		return GetLastError();
	}

	HANDLE hOutputSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"Output Semaphore started");
	if (hOutputSemaphore == NULL) {
		return GetLastError();
	}

	SetEvent(hStartEvent);

	int userChoice;
	int numOfRecords = 0;
	std::cout << "Введите 1 - хотите глаголить сообшение, 0 - хотите закрыть Древнерусский процесс Sender : ";
	std::cin >> userChoice;

	while (true) {
		if (userChoice == 1) {
			binFile.open(fileName, std::ios::binary | std::ios::out | std::ios::app);

			char userMessage[22] = {0};
			//userMessage[20] = '\0';
			//userMEssage[21] = '\n'
			std::cout << "Сюда глаголь : ";
			std::cin >> userMessage;
			strcat_s(userMessage, "\n");

			if (ReleaseSemaphore(hInputSemaphore, 1, NULL) != 1) {
				if (numOfRecords != 0) {
					std::cout << "Переполнения процесса Sender, допустимое количество сообщений = " << argv[2] << "\n";
					numOfRecords++;
				}
			}

			WaitForSingleObject(hOutputSemaphore, INFINITE);

			binFile.write(userMessage, sizeof(userMessage));
			ReleaseSemaphore(hInputSemaphore, 1, NULL);

			binFile.close();
			std::cout << "Введите 1 - хотите глаголить сообшение, 0 - хотите закрыть Древнерусский процесс Sender : ";
			std::cin >> userChoice;
		}
		else if (userChoice == 0) {
			return 0;
		}
		else {
			std::cout << "Ящерский ввод, пробуй ещЁ!\n";
			std::cout << "Введите 1 - хотите глаголить сообшение, 0 - хотите закрыть Древнерусский процесс Sender : ";
			std::cin >> userChoice;
		}
	}

	return 0;
}