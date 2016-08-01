#pragma once
#include <iostream>
#include <string>
#include "Event.hpp"
#include "File_Guardian.hpp"
using namespace std;

class User
{
protected:
	string sName; //Nazwa usera
	int iNOE; //Ilosc eventow
	File_Guardian *fFile; // Obsluga pliku

public:
	Event *eEventList; //Tablica eventow usera
	// Deklarzacja metod
	User(string sNewName, File_Guardian *fNewFile);

	string Get_Name(); // Pobieranie nazwy usera
	int Get_NOE(); // Pobierani ilosci eventow
	bool ChangePassword(string sNewPassword ,string sPassworChange_New); 
	void SetEvent(); // Wszytanie eventow z pliku
	//string *GetEvent(unsigned int iID); // Pobranie podanego eventu (id)
	bool isEvent(int iDayNumber, int iMonthOffset, int iYearOffset,int *counter); // czy danego dnia istnieje event
	Event *Get_Event_List();
	void AddEvent(string sUserName, string sEventName, string sEventDesc, int iEventHour, int iEventMinutes, int iSelectedDay, int iMonthOffset, int iYearOffset, char iSelectedTag, int iEventPrioryty, int iEventFrequency);
	int getNoOfElements();
	int DayOfWeek(int iDay, int iMonth, int iYear);

	bool EditEvent(int ID, string sEventName, string sEventDesc, int iEventHour, int iEventMinutes, int iSelectedDay, int iMonthOffset, int iYearOffset, char iSelectedTag, int iEventPrioryty, int iEventFrequency);
	bool DeleteEvent(int ID);
};
