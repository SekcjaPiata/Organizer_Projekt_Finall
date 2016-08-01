#include "User.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;

User::User(string sNewName, File_Guardian *fNewFile) {
	sName = sNewName;
	fFile = fNewFile;
	SetEvent();
}

string User::Get_Name() { // Zwraca nazwe usera
	return sName;
}

int User::Get_NOE() { // Zwraca ilosc eventow
	return  fFile->CountEvents(sName);
}

bool User::ChangePassword(string sNewPassword, string sPassworChange_New) { 

	if (fFile->isLoginDataGood(sName, sNewPassword)) {
		fFile->ChangePassword(sName, fFile->HashString(sPassworChange_New));
		return true;
	}
	return false;
}

void User::SetEvent() {
	eEventList = fFile->ReadEventFile((USERS_CONTAINER + sName + EVENTS_FILE).c_str());
}

bool User::isEvent(int iDayNumber, int iMonthOffset, int iYearOffset,int *counter) {
	SetEvent();

	for (int i = 0; i < fFile->getNoOfElements(); i++) {

		if (iYearOffset == eEventList[i].getYear()) {
			if (iMonthOffset == eEventList[i].getMonth()) {
				if (iDayNumber == eEventList[i].getDay()) {
					*counter = i; 
					return true; // Danego dnia jest event
				}
			}
		}

		if (DayOfWeek(iDayNumber, iMonthOffset, iYearOffset) == (DayOfWeek(eEventList[i].getDay(), eEventList[i].getMonth(), eEventList[i].getYear()))) {
			if (eEventList[i].getPeriod() == co_tydzien) {
				*counter = i; 
				return true;
			}
		}
		else if (eEventList[i].getPeriod() == co_miesiac) {
			if (iDayNumber == eEventList[i].getDay()) {
				*counter = i; 
				return true;
			}
		}

	}
	return false;
}

int User::DayOfWeek(int iDay, int iMonth, int iYear) { // Jakim dniem tygodnia jest dana data
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	iYear -= iMonth < 3;
	return ((iYear + iYear / 4 - iYear / 100 + iYear / 400 + t[iMonth - 1] + iDay) % 7);
}


void User::AddEvent(string sUserName, string sEventName, string sEventDesc, int iEventHour, int iEventMinutes, int iSelectedDay, int iMonthOffset, int iYearOffset, char iSelectedTag, int iEventPrioryty, int iEventFrequency) {
	fFile->AddEvent(sUserName, sEventName, sEventDesc, iEventHour, iEventMinutes, iSelectedDay, iMonthOffset, iYearOffset, iSelectedTag, iEventPrioryty, iEventFrequency);

}

int User::getNoOfElements() {
	return fFile->CountEvents(sName);
}

Event *User::Get_Event_List() {
	SetEvent();
	if (NULL != eEventList) {
		return eEventList;
	}
}



bool User::EditEvent(int ID, string sEventName, string sEventDesc, int iEventHour, int iEventMinutes, int iSelectedDay, int iMonthOffset, int iYearOffset, char iSelectedTag, int iEventPrioryty, int iEventFrequency) {
	char cEventTags[10] = { '.' ,'X' , 'Z' , 'O' , '#' , 'I' , '$' , 'q' , '*' , '|' };
	eEventList[ID].setName(sEventName);
	eEventList[ID].setDescription(sEventDesc);
	eEventList[ID].setHour(iEventHour);
	eEventList[ID].setMinute(iEventMinutes);
	eEventList[ID].setDay(iSelectedDay);
	eEventList[ID].setMonth(iMonthOffset);
	eEventList[ID].setYear(iYearOffset);
	eEventList[ID].setTag(cEventTags[iSelectedTag]);
	eEventList[ID].setPriority(iEventPrioryty);
	eEventList[ID].setPeriod(Period(iEventFrequency));
	fFile->EditEvent(sName, eEventList);
	
	//Dodawanie eventu w aktualnie wczytanej tablicy 'eEventList[ID]' i zapis do pliku 
	return true;
}

bool User::DeleteEvent(int ID) {
	eEventList[ID].setDay(NULL);
	fFile->EditEvent(sName, eEventList);
	// Usuwanie eventu o id ID w aktualnie wczytanej tablicy 'eEventList[ID]'
	return true;
}

