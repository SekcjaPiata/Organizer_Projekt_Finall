#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <thread> 
#include "Defines.hpp"
#include "Callendar_Model.hpp"
#include "User.hpp"
#include "Functions.hpp"

using namespace std;


class Callendar : public Callendar_Model {
private:
	/*Funkcja dodajaca możliwość przemieszczania kursora w dowolne
	miejsce w konsoli.*/
	void gotoxy(const SHORT x, const SHORT y) {
		COORD coord = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	string HideString(const string sText) { // Zastepowanie * itd itp
		string sHidePassword = "";
		for (unsigned int i = 0; i < sText.length(); i++) // '*' zamiasta hasla
			sHidePassword += '*';
		return sHidePassword;
	}


	void MainView(string &dDate, string &dHours, int dMonth, int dYear, string &dDay) { // Glowny widok kalendarza ... tylko widok
		cout << "+---------------------------------------------------------------------+\n";
		cout << "|   Data " << dDate << "    Uzytkownik: ";
		printf("%-15s", uUser->Get_Name().substr((uUser->Get_Name().length() > 15) ? uUser->Get_Name().length() - 15 : 0, 15).c_str());
		cout << "    Godzina " << dHours << "   |\n";
		cout << "+---------------------------------------------------------------------+\n";
		printf("|                  %16s %d                              |\n", MONTH_NAME(dMonth - 1).c_str(), dYear);
		cout << "+---------------------------------------------------------------------+\n";
		cout << "|   Pn    |    Wt   |   Sr    |   Czw   |    Pt   |   Sob   |    Nd   |\n";
		cout << "+---------------------------------------------------------------------+\n";

		int iDayNumber, iDayOffset = 0;

		for (int iWeek = 0; iWeek <= 5; iWeek++) {
			for (int iDay = 1; iDay <= 7; iDay++) {

				//iDayNumber = (iDay + iWeek * 7 - iFirstDay + 1) - 7 + iDayOffset; // Obliczanie numeru dnia iWeek pozycji '1-go' dnia miesiaca

				if (1 <= iFirstDay) {// Elemninacja pustej pierwszej pustej lini w niegtorych dniach
					iDayNumber = (iDay + iWeek * 7 - iFirstDay + 1);
				}
				else {
					iDayNumber = (iDay + iWeek * 7 - iFirstDay + 1) - 7;
				}

				printf("|");
				if (iDayNumber > iLastDay || iDayNumber <= 0) { // Aktualna petla dotyczy: dnia wiekszego niz tzeba ALBO dnia mniejszego-rownego niz zero -> puste pole
					printf("         ");
				}
				else if (iDayCurrent == iDayNumber && (iMonthCurrent == iMonthOffset && iYearCurrent == iYearOffset)) { // Aktualny dzien jest rowny dniowi z aktualnej petli

																														// Dodac zaznaczenia wydarzen - zaznaczony dzien
																														// bool isEvent(int Dzien, int Miesiac, int Rok)
					int counter = 0;																									// Wydarzenie istnieje tego dnia - dzien zaznaczony }
					if (uUser->isEvent(iDayNumber, iMonthOffset, iYearOffset,&counter) == true) { // Event i niedziela

						if (iDay == 7) {
							if (iSelectedDay == iDayNumber)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUNDAY_EVENT);
							else
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TODAY_TEXT_COLOR_2);
							printf(" %4d   %c", iDayNumber,uUser->eEventList[counter].getTag());
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
						}
						else {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_TEXT_COLOR);
							printf(" %4d   %c", iDayNumber, uUser->eEventList[counter].getTag());
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
						}

					}
					else if (iDay == 7 && iDayNumber == iSelectedDay) { // Niedziela
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TODAY_TEXT_COLOR_1);
						printf(" %4d    ", iDayNumber);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
					}
					else if (iDayNumber == iSelectedDay) { // Wybrany dzien jest dniem dzisiejszym
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TODAY_TEXT_COLOR_1);
						printf(" %4d    ", iDayNumber);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
					}
					else { // Wybrano inny dzien niz dzisiejszy
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TODAY_TEXT_COLOR_2);
						printf(" %4d    ", iDayNumber);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
					}

				}
				else {
					int counter = 0;
					// Dodac zaznaczenie wydarzen - pozostałe dni
					// Wydarzenie istnieje tego dnia - dzien nie zaznaczony }
					if (uUser->isEvent(iDayNumber, iMonthOffset, iYearOffset,&counter) == true) { // Event i niedziela
						
						if (iDay == 7) {
							if (iSelectedDay == iDayNumber)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUNDAY_EVENT);
							else
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_TEXT_COLOR);
							printf(" %4d   %c", iDayNumber, uUser->eEventList[counter].getTag());
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
						}
						else {
							if (iSelectedDay == iDayNumber)
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUNDAY_EVENT);
							else
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUB_BORDER_COLOR);
							printf(" %4d   %c", iDayNumber, uUser->eEventList[counter].getTag());
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
						}

					}
					else if (iDayNumber == iSelectedDay) { // Zaznaczono zwykly dzien
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SELECTED_TEXT_COLOR);
						printf(" %4d    ", iDayNumber);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
					}
					else // Zwykly nie-zaznaczony dzien
						if (iDay == 7) { // Niedziela
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_TEXT_COLOR);
							printf(" %4d    ", iDayNumber);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR);
						}
						else
							printf(" %4d    ", iDayNumber);
				}
			}
			cout << "|\n";
		}

		ShowSubMenu();
	}

	void ShowSubMenu() { // menu i event list
		cout << "+---------------------------------------------------------------------+\n";
		cout << "| \x11 " << PREVIOUS_MONTH << ": Poprzedni miesiac                        " << NEXT_MONTH << ": Nastepny miesiac \x10 |\n";
		cout << "+---------------------------------------------------------------------+\n";

		if (!bShowEvents) {
			cout << "|                             " << EVENT_BUTTON << ": Pokaz wydarzenia \x1F                   |\n";
			cout << "+---------------------------------------------------------------------+\n";

			if (!bShowMenu) {
				cout << "|                             " << MENU_BUTTON << ": Pokaz menu \x1F                         |\n";
				cout << "+---------------------------------------------------------------------+\n";
				for (int i = 0; i < 6; i++) cout << "																		";
			}
			else {
				MenuDisplay();
			}
		}
		else {
			CLEAR
				cout << "+---------------------------------------------------------------------+\n";
			cout << "|  Spis Wydarzen:               S - aby wrocic do widoku kalendarza   |\n";
			cout << "|---------------------------------------------------------------------|\n";
			cout << "|  Sortowanie rosnaco w/g:      D - daty   T - priorytetu   N - nazwy |\n";
			cout << "|  Sortowanie malejaco w/g:     d - daty   t - priorytetu   n - nazwy |\n";
			cout << "+---------------------------------------------------------------------+\n"; // 10 lini

			if (uUser->getNoOfElements() == 0) {
				cout << "|                             Brak wydarzen                           |\n";
				cout << "+---------------------------------------------------------------------+\n";
			}
			else {

				Event *Event_buff = uUser->Get_Event_List();

				if (iSortType == 1) {
					sort_iName_dsc(uUser->eEventList, uUser->Get_NOE());
				}
				else if (iSortType == 2) {
					sort_iName_asc(uUser->eEventList, uUser->Get_NOE());
				}
				else if (iSortType == 3) {
					sort_Date_dsc(uUser->eEventList, uUser->Get_NOE());
				}
				else if (iSortType == 4) {
					sort_Date_asc(uUser->eEventList, uUser->Get_NOE());
				}
				else if (iSortType == 5) {
					sort_iPriority_dsc(uUser->eEventList, uUser->Get_NOE());
				}
				else if (iSortType == 6) {
					sort_iPriority_asc(uUser->eEventList, uUser->Get_NOE());
				}

				iSortType = 0;

				for (int i = 0; i < uUser->Get_NOE(); i++) {

					printf("| %-21s", Event_buff[i].getName().c_str()); //Pierwsza linia
					printf(" %42s %2d |\n", "Priorytet:", Event_buff[i].getPriority()); //Pierwsza linia

					printf("| %c", Event_buff[i].getTag()); //Druga linia

					//Formatowanie W drugiej lini zeby dodawalo 0 gdy dzien lub miesiac jest mniejszy od 9
					if (Event_buff[i].getDay() <= 9) {
						if (Event_buff[i].getMonth() <= 9) {
							printf(" Data: 0%d:0%d:%4d", Event_buff[i].getDay(), Event_buff[i].getMonth(), Event_buff[i].getYear()); //Druga linia
						}
						else {
							printf(" Data: 0%d:%d:%4d", Event_buff[i].getDay(), Event_buff[i].getMonth(), Event_buff[i].getYear()); //Druga linia
						}
					}
					else {
						if (Event_buff[i].getMonth() <= 9) {
							printf(" Data: %d:0%d:%4d", Event_buff[i].getDay(), Event_buff[i].getMonth(), Event_buff[i].getYear()); //Druga linia
						}
						else
							printf(" Data: %d:%d:%4d", Event_buff[i].getDay(), Event_buff[i].getMonth(), Event_buff[i].getYear()); //Druga linia
					}

					if (Event_buff[i].getHour() <= 9) {
						if (Event_buff[i].getMinute() <= 9) {
							printf(" Data: 0%d:0%d ", Event_buff[i].getHour(), Event_buff[i].getMinute()); //Druga linia
						}
						else {
							printf(" Data: 0%d:%d ", Event_buff[i].getHour(), Event_buff[i].getMinute()); //Druga linia
						}
					}
					else {
						if (Event_buff[i].getMinute() <= 9) {
							printf(" Data: %d:0%d ", Event_buff[i].getHour(), Event_buff[i].getMinute()); //Druga linia
						}
						else
							printf("  Data: %d:%d ", Event_buff[i].getHour(), Event_buff[i].getMinute()); //Druga linia
					}

					printf("Cyklicznosc: ");
					switch (Event_buff[i].getPeriod()) //Druga linia
					{
					case brak:printf("brak %20s", "|\n"); break;
					case co_tydzien:printf("Co tydzien %14s", "|\n"); break;
					case co_miesiac:printf("Co miesiac %14s", "|\n"); break;
					}

					cout << "| " << "Opis: "; printf("%-61s |\n", Event_buff[i].getDescription().c_str()); //Trzecia linia
					cout << "+---------------------------------------------------------------------+\n";
				}

			}
		}
	}

	void MenuDisplay() { // Pod menusy 
		if (iMenuToDisplay == -1) { // Zamykanie programu
			cout << "|                               Wylogowac?                            |\n";
			cout << "+---------------------------------------------------------------------+\n";
			cout << "|                                                                     |\n";
			cout << "|                        " << CLOSE_PROGRAM << ": Wyloguj                                   |\n";
			cout << "|                                                                     |\n";
			cout << "|                        " << ABORT_BUTTON << ": Anuluj                                    |\n";
			cout << "|                                                                     |\n";
			cout << "|                                                                     |\n";
			cout << "+---------------------------------------------------------------------+\n";
		}
		else if (iMenuToDisplay == 0) { // Domyslne menu
			cout << "|                             " << MENU_BUTTON << ": Ukryj menu \x1F                         |\n";
			cout << "+---------------------------------------------------------------------+\n";
			cout << "|                                                                     |\n";
			cout << "|   " << ADD_EVENT << ": Dodaj wydarzenie                                               |\n";
			cout << "|   " << DELETE_EVENT << ": Usun wydarzenie                                                |\n";
			cout << "|   " << EDIT_EVENT << ": Edytuj wydarzenie                      " << CHANGE_PASS_BUTON << ": Zmien haslo          |\n";
			cout << "|                                             " << CLOSE_PROGRAM << ": Wyloguj              |\n";
			cout << "|                                                                     |\n";
			cout << "+---------------------------------------------------------------------+\n";

		}
		else if (iMenuToDisplay == 1) { // Menu dodawanie wydarzenia

			if (iEventCreationStage == 0)
				cout << "|     ENTER: Zatwierdz              TAB: Anuluj dodawanie             |\n";
			else if (iEventCreationStage == 7)
				cout << "|     ENTER: Dodaj wydarzenie       TAB: Cofnij                       |\n";
			else
				cout << "|     ENTER: Zatwierdz              TAB: Cofnij                       |\n";
			cout << "+---------------------------------------------------------------------+\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 0 ? SUBMITED_FIELD : iEventCreationStage == 0 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Dzien: " << ((iSelectedDay < 10) ? "0" : "") << iSelectedDay << ":" << ((iMonthOffset < 10) ? "0" : "") << iMonthOffset << ":" << iYearOffset;
			SET_COLOR(DEFAULT_TEXT_COLOR);

			cout << "                         ";

			SET_COLOR(iEventCreationStage > 1 ? SUBMITED_FIELD : iEventCreationStage == 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Godzina: ";
			cout << ((iEventHour < 10) ? "0" : "") << iEventHour << ":" << ((iEventMinutes < 10) ? "0" : "") << iEventMinutes;
			SET_COLOR(DEFAULT_TEXT_COLOR);

			/**/ cout << "           |\n";
			////////////////////////////////////////////////////////////////////////////////////////////

			iCharToDisplay = (sEventName.length() > 55) ? sEventName.length() - 55 : 0;

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 2 ? SUBMITED_FIELD : iEventCreationStage == 2 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Nazwa:    ";
			printf("%-55s", sEventName.substr(iCharToDisplay, 55).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			iCharToDisplay = (sEventDesc.length() > 55) ? sEventDesc.length() - 55 : 0;

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 3 ? SUBMITED_FIELD : iEventCreationStage == 3 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Opis:     ";
			printf("%-55s", sEventDesc.substr(iCharToDisplay, 55).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 4 ? SUBMITED_FIELD : iEventCreationStage == 4 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Tag:   " << GetTag(iSelectedTag) << "                                                         ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 5 ? SUBMITED_FIELD : iEventCreationStage == 5 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Priorytet: " << (iEventPrioryty < 10 ? "0" : "") << iEventPrioryty << "                                                    ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 6 ? SUBMITED_FIELD : iEventCreationStage == 6 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Powtarzaj co: ";
			//<< iEventFrequency 
			printf("%-16s", FREQUENCY_NAME(iEventFrequency).c_str());
			cout << "                                   ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "+---------------------------------------------------------------------+\n";
		}
		else if (iMenuToDisplay == 2) { // Domyslne menu
			cout << "|                             " << MENU_BUTTON << ": Ukryj menu \x1F                         |\n";
			cout << "+---------------------------------------------------------------------+\n";

			iCharToDisplay = (sPassworChange_Old.length() > 55) ? sPassworChange_Old.length() - 55 : 0;
			cout << "|  ";
			SET_COLOR(iPassworChangeStage > 0 ? SUBMITED_FIELD : iPassworChangeStage == 0 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Stare haslo:      ";
			printf("%-47s", HideString(sPassworChange_Old.substr(iCharToDisplay, 55)).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|                                                                     |\n";

			iCharToDisplay = (sPassworChange_New.length() > 55) ? sPassworChange_New.length() - 55 : 0;
			cout << "|  ";
			if (PassBug == 0)
				SET_COLOR(iPassworChangeStage > 1 ? SUBMITED_FIELD : iPassworChangeStage == 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			else
				SET_COLOR(iPassworChangeStage == 1 ? SUB_BORDER_COLOR : ERROR_TEXT_COLOR);
			cout << "Nowe haslo:       ";
			printf("%-47s", HideString(sPassworChange_New.substr(iCharToDisplay, 55)).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			iCharToDisplay = (sPassworChange_New2.length() > 55) ? sPassworChange_New2.length() - 55 : 0;
			cout << "|  ";
			if (PassBug == 0)
				SET_COLOR(iPassworChangeStage > 2 ? SUBMITED_FIELD : iPassworChangeStage == 2 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			else
				SET_COLOR(iPassworChangeStage == 2 ? SUB_BORDER_COLOR : ERROR_TEXT_COLOR);
			cout << "Powtorz haslo:    ";
			printf("%-47s", HideString(sPassworChange_New2.substr(iCharToDisplay, 55)).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|                                                                     |\n";

			if (iPassworChangeStage == 0)
				cout << "|     ENTER: Zatwierdz              TAB: Anuluj                       |\n";
			else if (iPassworChangeStage == 3)
				cout << "|     ENTER: Zmien                  TAB: Cofnij                       |\n";
			else
				cout << "|     ENTER: Zatwierdz              TAB: Cofnij                       |\n";

			cout << "+---------------------------------------------------------------------+\n";

		}
		else if (iMenuToDisplay == 3 || iMenuToDisplay == 4) { // Usuwanie wydarzenia
			if (iMenuToDisplay == 3)
				cout << "|                 TAB: Cofnij         ENTER: Usun                     |\n";
			else
				cout << "|                 TAB: Cofnij         ENTER: Edytuj                   |\n";
			cout << "+---------------------------------------------------------------------+\n";
			cout << "|                                                                     |\n";

			Event *Events = uUser->Get_Event_List();
			for (int i = 0; i < uUser->Get_NOE(); i += 2) {

				// RAMKA
				cout << "| ";
				PRINT(iEventID == i ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR, "+-------------------------------+", DEFAULT_TEXT_COLOR);
				cout << " ";
				PRINT(iEventID == i + 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR, "+-------------------------------+", DEFAULT_TEXT_COLOR);

				// DATA GODZINA PRIORYTET 1

				Event_buff = 
					"| " + (string)(Events[i].getDay()<=9?"0":"") + to_string(Events[i].getDay()) +
					":" + (string)(Events[i].getMonth() <= 9 ? "0" : "") + to_string(Events[i].getMonth()) +
					":" + to_string(Events[i].getYear()) + 
					" " + (string)(Events[i].getHour() <= 9 ? "0" : "") + to_string(Events[i].getHour()) +
					":" + (string)(Events[i].getMinute() <= 9 ? "0" : "") + to_string(Events[i].getMinute()) +
					" Priorytet " + (string)(Events[i].getPriority() <= 9 ? "0" : "") + to_string(Events[i].getPriority()) + " |";

				cout << " |\n| ";
				SET_COLOR(iEventID == i ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				printf("%30s", Event_buff.c_str(), DEFAULT_TEXT_COLOR);
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " ";

				// DATA GODZINA PRIORYTET 2
				SET_COLOR(iEventID == i + 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				if (i < uUser->Get_NOE() - 1) {
					Event_buff =
						"| " + (string)(Events[i+1].getDay() <= 9 ? "0" : "") + to_string(Events[i + 1].getDay()) +
						":" + (string)(Events[i + 1].getMonth() <= 9 ? "0" : "") + to_string(Events[i + 1].getMonth()) +
						":" + to_string(Events[i + 1].getYear()) +
						" " + (string)(Events[i + 1].getHour() <= 9 ? "0" : "") + to_string(Events[i + 1].getHour()) +
						":" + (string)(Events[i + 1].getMinute() <= 9 ? "0" : "") + to_string(Events[i + 1].getMinute()) +
						" Priorytet " + (string)(Events[i + 1].getPriority() <= 9 ? "0" : "") +to_string(Events[i + 1].getPriority()) + " |";

					printf("%30s", Event_buff.c_str());
				}
				else {
					printf("+                               +");
				}
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " |\n";

				// NAZWA 1
				cout << "| ";
				SET_COLOR(iEventID == i ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				printf("| %-29s |", (Events[i].getName().substr(0, 29)).c_str());
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " ";


				// NAZWA 2
				SET_COLOR(iEventID == i + 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				if (i < uUser->Get_NOE() - 1) {
					printf("| %-29s |", (Events[i + 1].getName().substr(0, 29)).c_str());
				}
				else {
					printf("+                               +");
				}
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " |\n";

				// OPIS 1
				cout << "| ";
				SET_COLOR(iEventID == i ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				printf("| %-29s |", (Events[i].getDescription().substr(0, 29)).c_str());
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " ";

				// OPIS 2
				SET_COLOR(iEventID == i + 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
				if (i < uUser->Get_NOE() - 1) {
					printf("| %-29s |", (Events[i + 1].getDescription().substr(0, 29)).c_str());
				}
				else {
					printf("+                               +");
				}
				SET_COLOR(DEFAULT_TEXT_COLOR);
				cout << " |\n";

				// RAMKA
				cout << "| ";
				PRINT(iEventID == i ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR, "+-------------------------------+", DEFAULT_TEXT_COLOR);
				cout << " ";
				PRINT(iEventID == i + 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR, "+-------------------------------+", DEFAULT_TEXT_COLOR);
				cout << " |\n";

			}


			//}
			cout << "|                                                                     |\n";
			cout << "+---------------------------------------------------------------------+\n";

		}
		else if (iMenuToDisplay == 5) {

			if (iEventCreationStage == 0)
				cout << "|     ENTER: Zatwierdz              TAB: Anuluj edycje                |\n";
			else if (iEventCreationStage == 7)
				cout << "|     ENTER: Dodaj edycje           TAB: Cofnij                       |\n";
			else
				cout << "|     ENTER: Zatwierdz              TAB: Cofnij                       |\n";
			cout << "+---------------------------------------------------------------------+\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 0 ? SUBMITED_FIELD : iEventCreationStage == 0 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Dzien: " << ((iSelectedDay < 10) ? "0" : "") << iSelectedDay << ":" << ((iMonthOffset < 10) ? "0" : "") << iMonthOffset << ":" << iYearOffset;
			SET_COLOR(DEFAULT_TEXT_COLOR);

			cout << "                         ";

			SET_COLOR(iEventCreationStage > 1 ? SUBMITED_FIELD : iEventCreationStage == 1 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Godzina: ";
			cout << ((iEventHour < 10) ? "0" : "") << iEventHour << ":" << ((iEventMinutes < 10) ? "0" : "") << iEventMinutes;
			SET_COLOR(DEFAULT_TEXT_COLOR);

			 cout << "           |\n";

			iCharToDisplay = (sEventName.length() > 55) ? sEventName.length() - 55 : 0;

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 2 ? SUBMITED_FIELD : iEventCreationStage == 2 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Nazwa:    ";
			printf("%-55s", sEventName.substr(iCharToDisplay, 55).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			iCharToDisplay = (sEventDesc.length() > 55) ? sEventDesc.length() - 55 : 0;

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 3 ? SUBMITED_FIELD : iEventCreationStage == 3 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Opis:     ";
			printf("%-55s", sEventDesc.substr(iCharToDisplay, 55).c_str());
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 4 ? SUBMITED_FIELD : iEventCreationStage == 4 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Tag:   " << GetTag(iSelectedTag) << "                                                         ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 5 ? SUBMITED_FIELD : iEventCreationStage == 5 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Priorytet: " << (iEventPrioryty < 10 ? "0" : "") << iEventPrioryty << "                                                    ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "|  ";
			SET_COLOR(iEventCreationStage > 6 ? SUBMITED_FIELD : iEventCreationStage == 6 ? ACTIVE_FIELD : DEFAULT_TEXT_COLOR);
			cout << "Powtarzaj co: ";

			printf("%-16s", FREQUENCY_NAME(iEventFrequency).c_str());
			cout << "                                   ";
			SET_COLOR(DEFAULT_TEXT_COLOR);
			cout << "  |\n";

			cout << "+---------------------------------------------------------------------+\n";

		}
	}

	std::string MONTH_NAME(int x) { // Nazwa miesiaca
		std::string Months[12] = {
			"Styczen ", "Luty " ,"Marzec ", "Kwiecien ", "Maj ", "Czerwiec ",
			"Lipiec ", "Sierpien ", "Wrzesien ", "Pazdziernik ", "Listopad ",
			"Grudzien "
		};
		return Months[x];
	}

	string FREQUENCY_NAME(int i) { // Nazwa czestotliwosci
		std::string sEventFrequency[NUMBER_OF_PERIODS] = { "Brak", "Co tydzien", "Co miesiac"
		};
		return sEventFrequency[i];
	}

public:
	Callendar(User *uNewUser) {
		uUser = uNewUser;
		sUserName = uUser->Get_Name();
	}

	void RunCalendar() { // Glowna petla kalendarza
		while (!_ExitProgram) {

			MOVETO;   //// Wraca na górę konsoli i nadpisuje wszystko.

			FindFirstLastDays();

			MainView(getDate("%d.%m.%G"),
				getDate("%H:%M"),
				(iMonthOffset),
				(iYearOffset),
				getDate("%d"));

			ExecuteEvent(ReadUserInput());

		}
	}
};
