#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Event.hpp"
#include "Defines.hpp"

using namespace std;

class File_Guardian {
	int iElements;

public:
	int NumberOfUsers() { // Ilosc userow w pliku 'Users/users.s5'
		string s = USERS_CONTAINER, sLine;
		fstream fUserList;
		fUserList.open(s + USERS_LIST_FILE, fstream::app | fstream::in | fstream::out);

		int i = 0;
		if (fUserList.is_open()) {
			for (; ; i++) {
				sLine = readLine(fUserList);
				if (sLine == "")
					break;
			}
			fUserList.close();
		}
		fUserList.close();
		return i;
	}
	/*/**//*//*/
	int CountEvents(string sUserName) { // Ilosc eventow
		ifstream File;

		string loc = USERS_CONTAINER + sUserName;
		File.open(loc + EVENTS_FILE, fstream::out);

		if (!File.is_open()) {
			printf("Blad otwarcia pliku z danymi");
		}
		int i = 0;
		string buff;
		while (!File.eof())// okresla liczbe linii do wczytania
		{
			getline(File, buff);
			i++;
		}

		i /= 3;
		File.close();
		return i;
	}

	bool UserExists(string sName) { // Sprawdzenie czy dany user istnieje
		string s = USERS_CONTAINER, sLine;
		fstream fUserList;
		fUserList.open(s + USERS_LIST_FILE, fstream::app | fstream::in | fstream::out);

		if (fUserList.is_open()) {

			for (int i = 0; ; i++) {
				sLine = readLine(fUserList);
				if (sLine == sName)
					return true;
				else if (sLine == "")
					break;
			}
			fUserList.close();
		}
		return false;
	}

	bool VerifyUser(string sName, string sPassword) { // sprawdzenie czy dany user isnieje
		string s = USERS_CONTAINER, sLine;
		fstream fUserList;
		fUserList.open(s + sName + DATA_FILE, fstream::app | fstream::in | fstream::out);

		if (fUserList.is_open()) {
			if (readLine(fUserList) == sName)
				if (readLine(fUserList) == HashString(sPassword))
					return true;

			fUserList.close();
		}
		return false;
	}

	string HashString(string Text) {
		return to_string(hash<string>()(Text));
	}

	bool Create(string sNewUserName, string sUserPassword) { // Tworzenie usera

		if (!isLoginDataGood(sNewUserName, sUserPassword)) { // tworzenie usera i struktury katalogow

			string dir = USERS_CONTAINER + sNewUserName;
			CreateDirectoryA(USERS_CONTAINER, NULL);
			CreateDirectoryA(dir.c_str(), NULL);

			createFile(sNewUserName + CONFIG_FILE);
			createFile(sNewUserName + USER_FILE);
			createFile(sNewUserName + EVENTS_FILE);

			fstream fNewUser = createFile(sNewUserName + DATA_FILE);
			writeLine(fNewUser, sNewUserName);
			writeLine(fNewUser, HashString(sUserPassword));
			fNewUser.close();

			string loc = USERS_CONTAINER;
			fNewUser.open(loc + USERS_LIST_FILE, fstream::app);
			writeLine(fNewUser, sNewUserName);
			fNewUser.close();

			return true;
		}
		return false;

	}

	bool Delete(string sName, string sPassword) {  // Usuwania ogolne 

		if (isLoginDataGood(sName, sPassword)) {

			/////////////////////////////////////
			int iN_users = NumberOfUsers(), n = 0;
			string *Users = new string[iN_users];;  // Tablica buforowa, do niej trafiają dane z pliku
			string *N_Users = new string[iN_users]; // Tablica buforowa, do niej trafiają zmienione dane i z niej są przekazywane do pliku. 
			Users = getUsers();


			for (int i = 0; i < iN_users; i++)
			{
				if (!(Users[i] == sName))					// Dopoki łancuch znaku w pliku ( nazwa uzytkownika) jest rozna od nazwy uzytkownika,ktorego chcemy usunac 
				{																// przepisuje 1:1 w momencie,gdy uzytkownik jest kasowany,nastepuje "przesuniecie" calej listy,stad inkrementownik "n"
					if (i + n < iN_users)N_Users[i].insert(0, Users[i + n]);
					else N_Users[i] = "";
				}
				else {
					n++;
					if (i + n < iN_users)N_Users[i].insert(0, Users[i + n]);
					else N_Users[i] = "";
				}
			}


			string s = USERS_CONTAINER, sLine;

			fstream fUserList;
			fUserList.open(s + USERS_LIST_FILE, fstream::out | fstream::trunc);
			for (int i = 0; i < iN_users - 1; i++)
			{
				writeLine(fUserList, N_Users[i]);
			}

			/////////////////////
			fstream del; /// Może być do wywalenia.
			del.open(USERS_CONTAINER + sName + DATA_FILE, fstream::out | fstream::trunc);
			del.close();////////////// TO////////////// TO
			del.open(USERS_CONTAINER + sName + CONFIG_FILE, fstream::out | fstream::trunc);
			del.close();
			del.open(USERS_CONTAINER + sName + USER_FILE, fstream::out | fstream::trunc);
			del.close();
			del.open(USERS_CONTAINER + sName + EVENTS_FILE, fstream::out | fstream::trunc);
			del.close();


			remove((USERS_CONTAINER + sName + DATA_FILE).c_str());
			remove((USERS_CONTAINER + sName + CONFIG_FILE).c_str());
			remove((USERS_CONTAINER + sName + USER_FILE).c_str());
			remove((USERS_CONTAINER + sName + EVENTS_FILE).c_str());
			////////////// TO////////////// T

			//RemoveDirectoryA(USERS_CONTAINER);
			RemoveDirectoryA((USERS_CONTAINER + sName).c_str());
			return true;
			//////////////////////////////////////////////
			delete[] N_Users;
			delete[] Users;
		}

		return false;
	}

	fstream createFile(string sFileName) { // Tworzenie pliku 
		fstream fFileToCreate;
		fFileToCreate.open(USERS_CONTAINER + sFileName, fstream::out);
		return fFileToCreate;
	}

	string readLine(fstream &fFile) {  // Odczytanie lini z pliku
		string sFileLineBuffor;
		fFile >> sFileLineBuffor;
		return sFileLineBuffor;
	}

	void writeLine(fstream &fFile, string sLine) { // Zapisanie do pliku linii
		fFile << sLine << endl;
	}

	bool isLoginDataGood(string &sUserName, string &sUserPassword) { // Tak samo jak 'VerifyUser' zmienic
		fstream fDataFile;
		fDataFile.open(USERS_CONTAINER + sUserName + DATA_FILE, fstream::app | fstream::in | fstream::out);

		if (fDataFile.is_open()) {
			if (readLine(fDataFile) == sUserName && readLine(fDataFile) == HashString(sUserPassword)) {
				fDataFile.close();
				return true;
			}
		}
		return false;
	}

	string *getUsers() { // Pobranie listy userow
		string s = USERS_CONTAINER, sLine;
		string *Users = new string[NumberOfUsers()];

		fstream fUserList;
		fUserList.open(s + USERS_LIST_FILE, fstream::app | fstream::in | fstream::out);

		if (fUserList.is_open()) {

			for (int i = 0; ; i++) {

				sLine = readLine(fUserList);

				if (sLine == "")
					break;
				else
					Users[i] = sLine;

			}
			fUserList.close();
		}
		return Users;
	}

	File_Guardian() { // Konstruktor
		iElements = 0;
	}

	Event *ReadEventFile(string File_name) { // Otwiera plik,tworzy oraz wypelnia Tablice

		ifstream File;
		File.open(File_name);
		if (!File.is_open()) {
			printf("Blad otwarcia pliku z danymi");
		}

		string buff;
		while (!File.eof())// okre?la liczb? linii do wczytania
		{
			getline(File, buff);
			iElements++;
		}

		iElements /= 3;

		int  iDay, iMonth, iYear, iHour, iMinutes, iPrioryty, iFreq;
		string sName, sDescription;
		char cTag;

		Event *eMain_tab = new Event[iElements];// new Event[iElements];
												//Event *eMain_tab = (Event *)malloc(sizeof(Event) * iElements);

		File.clear();
		File.seekg(0, ios::beg);

		for (int i = 0; i < iElements; i++) { // Wype?nianie pól tablicy struktuy

			getline(File, sName);
			getline(File, sDescription);

			//File.getline(sName, 255);
			//File.getline(sDescription, 255);

			File >> iDay;
			File >> iMonth;
			File >> iYear;
			File >> iHour;
			File >> iMinutes;
			File >> cTag;
			File >> iPrioryty;
			File >> iFreq;
			getline(File, buff);

			eMain_tab[i].setName(sName.c_str());
			eMain_tab[i].setDescription(sDescription.c_str());

			eMain_tab[i].setDay(iDay);
			eMain_tab[i].setMonth(iMonth);
			eMain_tab[i].setYear(iYear);
			eMain_tab[i].setHour(iHour);
			eMain_tab[i].setMinute(iMinutes);
			eMain_tab[i].setTag(cTag);
			eMain_tab[i].setPriority(iPrioryty);
			eMain_tab[i].setPeriod((Period)(iFreq));

		}
		File.close();
		return eMain_tab;
	}

	int getNoOfElements() {// Ilosc userow tak samo jak 'Pull_Lines'
		return iElements;
	}

	void AddEvent(string sUserName, string sEventName, string sEventDesc, int iEventHour, int iEventMinutes, int iSelectedDay, int iMonthOffset, int iYearOffset, char cSelectedTag, int iEventPrioryty, int iEventFrequency) { // Dodawanie eventu
		fstream fFile;
		string loc = USERS_CONTAINER + sUserName;
		fFile.open(loc + EVENTS_FILE, fstream::app);

		writeLine(fFile, sEventName);
		writeLine(fFile, sEventDesc);

		string sLine = to_string(iSelectedDay) + " " + to_string(iMonthOffset) + " " + to_string(iYearOffset) + " " + to_string(iEventHour) + " " + to_string(iEventMinutes) + " " + cSelectedTag + " " + to_string(iEventPrioryty) + " " + to_string(iEventFrequency);

		writeLine(fFile, sLine);

		fFile.close();
	}

	void ChangePassword(string sUser, string sPassword) {
		fstream fPassfile;
		fPassfile.open((USERS_CONTAINER + sUser + DATA_FILE).c_str(), fstream::trunc | fstream::out);

		writeLine(fPassfile, sUser);
		writeLine(fPassfile, sPassword);
		fPassfile.close();

	}

	void EditEvent(string sUser, Event *EventTab) {
		int iEventCount = CountEvents(sUser);
		fstream fEventEditFile;
		fEventEditFile.open((USERS_CONTAINER + sUser + EVENTS_FILE).c_str(), fstream::trunc | fstream::out);
		fEventEditFile.close();

		for (int i = 0; i < iEventCount; i++) {
			if (EventTab[i].getDay() != NULL) {
				AddEvent(sUser, EventTab[i].getName(), EventTab[i].getDescription(), EventTab[i].getHour(),
					EventTab[i].getMinute(), EventTab[i].getDay(), EventTab[i].getMonth(),
					EventTab[i].getYear(), EventTab[i].getTag(), EventTab[i].getPriority(), EventTab[i].getPeriod());

			}
		}
	}

};
