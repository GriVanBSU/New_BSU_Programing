#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<windows.h>

using namespace std;

const int maxNameLength = 10;

struct employee {
	int num;
	char name[maxNameLength];
	double hours;
};

int main() {
	string binFileName;
	int numRecords;
	cout << "Enter the name of binary file : ";
	cin >> binFileName;
	cout << "Enter the num of records : ";
	cin >> numRecords;

	STARTUPINFO siCreator = { 0 };
	PROCESS_INFORMATION piCreator = { 0 };

	wstring CommandLine = (L"Creator.exe " + wstring(binFileName.begin(), binFileName.end()) + L" " + to_wstring(numRecords));
	LPWSTR LCommandLine = &CommandLine[0];
	CreateProcess(NULL, LCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siCreator, &piCreator);

	WaitForSingleObject(piCreator.hProcess, INFINITY);

	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);

	ifstream finBin(binFileName, ios::binary);
	employee human;



	string reportFileName;
	int payPerHour;
	cout << "Enter the name report file ";
	cin >> reportFileName;
	cout << "Enter pay per hour : ";
	cin >> payPerHour;

	STARTUPINFO siReporter = { 0 };
	PROCESS_INFORMATION piReporter = { 0 };

	wstring reporterCommandLine = (L"REeporter.exe " + wstring(reportFileName.begin(), reportFileName.end()) + L" " + to_wstring(payPerHour) + L" " + wstring(binFileName.begin(), binFileName.end()));
	LPWSTR RCommandLine = &reporterCommandLine[0];
	CreateProcess(NULL, RCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siReporter, &piReporter);

	WaitForSingleObject(piReporter.hProcess, INFINITY);
	CloseHandle(piReporter.hThread);
	CloseHandle(piCreator.hProcess);

	ifstream finRep(reportFileName);
	string line;

	while (getline(finRep, line))
	{
		cout << line << "\n";
	}

	finBin.close();
	finRep.close();
	return 0;
}