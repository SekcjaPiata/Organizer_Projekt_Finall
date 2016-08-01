#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Functions.hpp" 
#include "Defines.hpp"
#include "User.hpp"
#pragma warning(disable : 4996)
using namespace std;

class Callendar_Model {

protected:
	// Ograniczyc ilosc zmiennych ... przeponazywac
	User *uUser;
	string sUserName = "";
	string Event_buff = "";
	int iFirstDay, iLastDay;
	int iSelectedDay = 1;
	int iDayOffset = 0;

	int iMonthSelected = 0;
	int iMonthSelectedBuffor = 0;
	int iMonthOffset = 0;
	int iYearOffset = 0;

	int iYearFix = 0;

	int iDayCurrent = 0;
	int iMonthCurrent = 0;
	int iYearCurrent = 0;

	bool bShowMenu = true;
	bool bShowEvents = false;
	bool SetFirst = true;
	bool _ExitProgram = false;

	int iMenuToDisplay = 0;
	int iCharToDisplay;

	int iEventCreationStage = 0;

	string sEventName = "";
	string sEventDesc = "";
	int iEventHour = 12, iEventMinutes = 30, iSelectedTag = 0;
	int iEventFrequency = 0;
	int iEventPrioryty = 0;

	int iPassworChangeStage = 0, PassBug = 0;
	string sPassworChange_Old = "";
	string sPassworChange_New = "";
	string sPassworChange_New2 = "";
	int iSortType = 0;
	int iEventID = 0;
	// Lista dozwolonych znakow
	char cAllowedChars[74] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','w' ,'q' ,'x','y','z','v'
		,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','W','Q' ,'X','Y','Z','V'
		,'1','2','3','4','5','6','7','8','9','0','_','!','@','#','$','%','^','&','*','?' , '.' ,' ' };

	// TAGI
	char cEventTags[10] = { '.' ,'X' , 'Z' , 'O' , '#' , 'I' , '$' , 'q' , '*' , '|' };

	void ExecuteEvent(char Input) { // Kontrola manu starowanie ,porusznie sie obsluga Inputu
		if (iMenuToDisplay != 2) {

			if (iEventCreationStage == 0 && iMenuToDisplay != 3 && iMenuToDisplay != 4) {
				if (toupper(Input) == EVENT_BUTTON) {
					CLEAR;
					bShowEvents = !bShowEvents;
				}
				else if (toupper(Input) == MENU_BUTTON) {
					bShowMenu = !bShowMenu;
				}
				else if (toupper(Input) == ARROW_UP) {
					if (iSelectedDay > 7)
						iSelectedDay -= 7;
					else {
						iMonthSelected--;
						iSelectedDay = findLastDay(iMonthOffset - 1, iYearOffset) - abs((iSelectedDay - 7));
					}
				}
				else if (toupper(Input) == ARROW_DOWN) {
					if (iSelectedDay <= iLastDay - 7)
						iSelectedDay += 7;
					else {
						iMonthSelected++;
						iSelectedDay = abs(((iSelectedDay + 7) - findLastDay(iMonthOffset, iYearOffset)));
					}
				}
				else if (toupper(Input) == ARROW_LEFT) {
					if (iSelectedDay > 1) iSelectedDay--;
				}
				else if (toupper(Input) == ARROW_RIGHT) {
					if (iSelectedDay < iLastDay) iSelectedDay++;
				}
				else if (toupper(Input) == NEXT_MONTH) {
					iMonthSelected++;
				}
				else if (toupper(Input) == PREVIOUS_MONTH) {
					iMonthSelected--;
				}
			}
			else if (iEventCreationStage == 1) { // Pisanie nazwy wydarzenia
				if (toupper(Input) == ARROW_UP) {
					if (iEventMinutes < 59)
						iEventMinutes++;
					else {
						iEventMinutes = 0;
						if (iEventHour < 23)
							iEventHour++;
						else
							iEventHour = 0;
					}
				}
				else if (toupper(Input) == ARROW_DOWN) {
					if (iEventMinutes > 0)
						iEventMinutes--;
					else {
						iEventMinutes = 59;
						if (iEventHour > 0)
							iEventHour--;
						else
							iEventHour = 23;
					}
				}
				else if (toupper(Input) == ARROW_LEFT) {
					if (iEventHour > 0)
						iEventHour--;
					else
						iEventHour = 23;
				}
				else if (toupper(Input) == ARROW_RIGHT) {
					if (iEventHour < 23)
						iEventHour++;
					else
						iEventHour = 0;
				}
			}
			else if (iEventCreationStage == 2) { // Pisanie nazwy wydarzenia
				if (IsAllowed(Input) && sEventName.length() <= MAX_EVENT_NAME_LENGTH)
					sEventName += Input;
				else if (toupper(Input) == BACKSPACE_BUTTON)
					sEventName = sEventName.substr(0, sEventName.size() - 1);
			}
			else if (iEventCreationStage == 3) { // Pisanie opisu wydarzenia
				if (IsAllowed(Input) && sEventDesc.length() <= MAX_EVENT_DESCRIPTION_LENGTH)
					sEventDesc += Input;
				else if (toupper(Input) == BACKSPACE_BUTTON)
					sEventDesc = sEventDesc.substr(0, sEventDesc.size() - 1);
			}
			else if (iEventCreationStage == 4) { // TAG
				if (toupper(Input) == ARROW_UP) {
					if (iSelectedTag < 10)
						iSelectedTag++;
					else {
						iSelectedTag = 0;
					}
				}
				else if (toupper(Input) == ARROW_DOWN) {
					if (iSelectedTag > 0)
						iSelectedTag--;
					else {
						iSelectedTag = 10;
					}
				}
			}
			else if (iEventCreationStage == 5) { // priorytet
				if (toupper(Input) == ARROW_UP) {
					if (iEventPrioryty < 10)
						iEventPrioryty++;
					else {
						iEventPrioryty = 0;
					}
				}
				else if (toupper(Input) == ARROW_DOWN) {
					if (iEventPrioryty > 0)
						iEventPrioryty--;
					else {
						iEventPrioryty = 10;
					}
				}
			}
			else if (iEventCreationStage == 6) { // czestosc eventow
				if (toupper(Input) == ARROW_UP) {
					if (iEventFrequency < 2)
						iEventFrequency++;
					else {
						iEventFrequency = 0;
					}
				}
				else if (toupper(Input) == ARROW_DOWN) {
					if (iEventFrequency > 0)
						iEventFrequency--;
					else {
						iEventFrequency = 2;
					}
				}
			}
		}

		if (iMenuToDisplay == 3 || iMenuToDisplay == 4) {
			if (toupper(Input) == ARROW_UP) {
				if (iEventID > 0) iEventID--;
			}
			else if (toupper(Input) == ARROW_DOWN) {
				if (iEventID < uUser->Get_NOE() - 1) iEventID++;

			}

		}

		if (iMenuToDisplay == 2) {
			if (iPassworChangeStage == 0) {
				if (IsAllowed(Input) && sPassworChange_Old.length() <= MAX_EVENT_NAME_LENGTH)
					sPassworChange_Old += Input;
				else if (toupper(Input) == BACKSPACE_BUTTON)
					sPassworChange_Old = sPassworChange_Old.substr(0, sPassworChange_Old.size() - 1);
			}
			else if (iPassworChangeStage == 1) {
				if (IsAllowed(Input) && sPassworChange_New.length() <= MAX_EVENT_NAME_LENGTH)
					sPassworChange_New += Input;
				else if (toupper(Input) == BACKSPACE_BUTTON)
					sPassworChange_New = sPassworChange_New.substr(0, sPassworChange_New.size() - 1);
			}
			else if (iPassworChangeStage == 2) {
				if (IsAllowed(Input) && sPassworChange_New2.length() <= MAX_EVENT_NAME_LENGTH)
					sPassworChange_New2 += Input;
				else if (toupper(Input) == BACKSPACE_BUTTON)
					sPassworChange_New2 = sPassworChange_New2.substr(0, sPassworChange_New2.size() - 1);
			}
		}

		if (!bShowEvents) {
			if (toupper(Input) == ENTER_BUTTON) {
				if (iMenuToDisplay == 1) { // Zatwierdzanie w tworzeniu wydarzenia
					if (iEventCreationStage <= 7) iEventCreationStage++;
					// iSelectedDay iMonthOffset  iYearOffset
					if (iEventCreationStage > 7) {
						uUser->AddEvent(sUserName, sEventName, sEventDesc, iEventHour, iEventMinutes, iSelectedDay, iMonthOffset, iYearOffset, GetTag(iSelectedTag), iEventPrioryty, iEventFrequency);
						iMenuToDisplay = 0;
						iEventCreationStage = 0;
						sEventName = "";
						sEventDesc = "";
						iEventHour = 12;
						iEventMinutes = 30;
						iSelectedTag = 0;
						iEventFrequency = 0;
						iEventPrioryty = 0;
					}
				}
				else if (iMenuToDisplay == 2) {
					if (iPassworChangeStage <= 2) iPassworChangeStage++;
					if (iPassworChangeStage > 2) {
						if (sPassworChange_New == sPassworChange_New2) {
							uUser->ChangePassword(sPassworChange_Old, sPassworChange_New);
							iPassworChangeStage = 0;
							sPassworChange_Old = "";
							sPassworChange_New = "";
							sPassworChange_New2 = "";
							iMenuToDisplay = 0;
							PassBug = 0;
						}
						else {
							PassBug = 1;
						}
					}
				}
				else if (iMenuToDisplay == 3) {
					uUser->DeleteEvent(iEventID);
					iEventID = 0;
					iMenuToDisplay = 0;
					CLEAR;

				}
				else if (iMenuToDisplay == 4) {
					CLEAR;
					Event *Event = uUser->Get_Event_List();
					sEventName = Event[iEventID].getName();
					sEventDesc = Event[iEventID].getDescription();;
					iEventHour = (int)Event[iEventID].getHour();
					iEventMinutes = (int)Event[iEventID].getMinute();
					iEventFrequency = (int)Event[iEventID].getPeriod();
					iEventPrioryty = (int)Event[iEventID].getPriority();
					iMenuToDisplay = 5;
				}
				else if (iMenuToDisplay == 5) {
					if (iEventCreationStage <= 7) iEventCreationStage++;
					// iSelectedDay iMonthOffset  iYearOffset
					if (iEventCreationStage > 7) {
						uUser->EditEvent(iEventID, sEventName, sEventDesc, iEventHour, iEventMinutes, iSelectedDay, iMonthOffset, iYearOffset, iSelectedTag, iEventPrioryty, iEventFrequency);

						CLEAR;
						iMenuToDisplay = 5;
						iMenuToDisplay = 0;
						iEventCreationStage = 0;
						sEventName = "";
						sEventDesc = "";
						iEventHour = 12;
						iEventMinutes = 30;
						iSelectedTag = 0;
						iEventFrequency = 0;
						iEventPrioryty = 0;
					}
				}
			}
			else if (toupper(Input) == TAB_BUTTON) {
				if (iMenuToDisplay == 1) { // Zatwierdzanie w tworzeniu wydarzenia
					if (iEventCreationStage >= 0) --iEventCreationStage;
					if (iEventCreationStage == -1) {
						iMenuToDisplay = 0;
						iEventCreationStage = 0;
					}
				}
				else if (iMenuToDisplay == 2) {
					if (iPassworChangeStage > 0) iPassworChangeStage--;
					else if (iPassworChangeStage == 0) {
						sPassworChange_Old = "";
						sPassworChange_New = "";
						sPassworChange_New2 = "";
						iMenuToDisplay = 0;
					}

				}
				else if (iMenuToDisplay == 3) {
					CLEAR;
					iMenuToDisplay = 0;
				}
				else if (iMenuToDisplay == 4) {
					CLEAR;
					iMenuToDisplay = 0;
				}
				else if (iMenuToDisplay == 5) {
					if (iEventCreationStage >= 0) --iEventCreationStage;
					if (iEventCreationStage == -1) {
						CLEAR;

						sEventName = "";
						sEventDesc = "";
						iEventHour = 12;
						iEventMinutes = 30;
						iEventFrequency = 0;
						iEventPrioryty = 0;
						iEventCreationStage = 0;
						iMenuToDisplay = 4;
					}
				}
			}
			else if (toupper(Input) == ADD_EVENT && iMenuToDisplay == 0) {
				// Dodawanie eventu
				if (bShowMenu) {
					iMenuToDisplay = 1;
				}

			}
			else if (toupper(Input) == EDIT_EVENT && iMenuToDisplay == 0) {
				// Usowanie eventu
				if (bShowMenu) {
					CLEAR;
					iMenuToDisplay = 4;
				}
			}
			else if (toupper(Input) == DELETE_EVENT && iMenuToDisplay == 0) {
				// Edycja eventu
				if (bShowMenu) {
					CLEAR;
					iMenuToDisplay = 3;
				}
			}
			else if (toupper(Input) == ABORT_BUTTON || toupper(Input) == CLOSE_PROGRAM) {
				if (bShowMenu) {
					if (iMenuToDisplay == -1) { // Zamykanie
						if (toupper(Input) == ABORT_BUTTON) {
							iMenuToDisplay = 0;
						}
						else {
							_ExitProgram = true;
						}
					}
					else if (iMenuToDisplay == 0) { // Menu glowne
						iMenuToDisplay = -1;
					}
				}
			}
			else if (toupper(Input) == CHANGE_PASS_BUTON && (iMenuToDisplay == 0 || iMenuToDisplay == 2)) {
				if (iMenuToDisplay != 2) {
					iMenuToDisplay = 2;
				}
			}
		}
		else {
			if (Input == NEXT_MONTH) {
				iSortType = 1;
			}
			else if (Input == tolower(NEXT_MONTH)) {
				iSortType = 2;
			}
			else if (Input == DELETE_EVENT) {
				iSortType = 3;
			}
			else if (Input == tolower(DELETE_EVENT)) {
				iSortType = 4;
			}
			else if (Input == PRIORYTY_SORT) {
				iSortType = 5;
			}
			else if (Input == tolower(PRIORYTY_SORT)) {
				iSortType = 6;
			}
		}
	}

	char ReadUserInput() { // Pobieranie wejscia
		return (_ExitProgram == true) ? ' ' : (_getch());
	}

	void FindFirstLastDays() { // Znajdowanie 1 i ostatniego dnia miesiaca aktywnego 

		iDayCurrent = strtol(getDate("%d").c_str(), NULL, 10);
		iMonthCurrent = strtol(getDate("%m").c_str(), NULL, 10);
		iYearCurrent = strtol(getDate("%G").c_str(), NULL, 10);

		iMonthOffset = ((iMonthCurrent + iMonthSelected) % 12);
		iMonthOffset = (iMonthOffset <= 0) ? 12 + iMonthOffset : iMonthOffset;

		iYearFix += (iMonthOffset == 1 && iMonthSelectedBuffor == 12) ? 1 : (iMonthOffset == 12 && iMonthSelectedBuffor == 1) == 1 ? -1 : 0;
		iYearOffset = strtol(getDate("%G").c_str(), NULL, 10) + iYearFix;

		if (iMonthSelected == 0) {
			iFirstDay = findFirstDay(
				strtol(getDate("%d").c_str(), NULL, 10),
				strtol(getDate("%u").c_str(), NULL, 10));
			iLastDay = findLastDay(
				strtol(getDate("%m").c_str(), NULL, 10),
				strtol(getDate("%G").c_str(), NULL, 10));
			if (SetFirst) {
				iSelectedDay = strtol(getDate("%d").c_str(), NULL, 10);
				SetFirst = !SetFirst;
			}
		}
		else {
			iFirstDay = uUser->DayOfWeek(1, iMonthOffset, iYearOffset);
			iLastDay = findLastDay(iMonthOffset, iYearOffset);

		}

		iMonthSelectedBuffor = iMonthOffset;
	}

	int findFirstDay(int iDayOfMonth, int iDayN) { // kiedy jest pierwszy dzien miesiaca
		while (iDayOfMonth - 7 > 1)
			iDayOfMonth -= 7;
		while (iDayOfMonth - 1 != 0) {
			iDayOfMonth--;
			iDayN--;
		}

		return iDayN;
	}

	int findLastDay(int iMonth, int iYear) { // Ilosc dni w miesiacu 

		if (iMonth == 2) { // LUTY 28/29
			if ((iYear % 400 == 0 || iYear % 100 != 0) && (iYear % 4 == 0))
				return 29;
			else return 28;
		}
		else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) { // 30
			return 30;
		}
		else {
			return 31;
		}
	}



	string getDate(char* Mod) { // pobranie parametru czasu w/g MOD
		time_t Time;
		struct tm * Date;
		char Result[80];

		time(&Time);
		Date = localtime(&Time);

		strftime(Result, 80, Mod, Date);
		return Result;
	}

	char GetTag(int i) { // Zwrocenie tagu 
		return cEventTags[i];
	}

	bool IsAllowed(char cChar) { // Sprawdzenie szy klikniety znak jest znakiem dozwolonym (petla foreach() )
		for (char c : cAllowedChars) {
			if (cChar == c) return true;
		}
		return false;
	}

public:
	Callendar_Model() {}
};
