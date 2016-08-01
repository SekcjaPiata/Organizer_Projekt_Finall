#include <Windows.h>
#include "Defines.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class MenuView {
protected:
	int iMenuState = 0; // Aktualnie wybrane menu.
	int iMenuSelectedOption = 0; // Pozycje na liscie menu.
	string sHidePassword = ""; // Gwiazdki hasla ...
	string sErrorMessage = ""; // Buffor tekstu bledu
	int iCharToDisplayNick = 0; // Dlugosc loginu do wyswietlenia

	void PrintMenu(const string &sLoginBuffor, const string &sPasswordBuffor, const bool &bWritingStatus, const int iNumberOfUsers, const string *sUserList) { // Menu glowne

		if (iMenuState == 0) { // Menu glowne.
			PrintButton("\t\t\t", " Zaloguj sie  ", iMenuSelectedOption == 0 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", " Stworz konto ", iMenuSelectedOption == 1 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", "     Wyjdz    ", iMenuSelectedOption == 2 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", "  Usun Konto  ", iMenuSelectedOption == 3 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR); // do ewentualnej zmiany
		}
		else if (iMenuState == 1 || iMenuState == 2 || iMenuState == 4) { //	Menu logowania lub tworzenia konta.

			PrintUserList(iNumberOfUsers, sUserList); // Wyswietlenie lisy userow

			sHidePassword = HideString(sPasswordBuffor); // zastepowanie hasla '*'

			if (sErrorMessage != "") // Jesli error msg nie pusty to wypisz
				PrintButton("\t\t", "  " + sErrorMessage + "  ", ERROR_TEXT_COLOR); // Komunikat bledu

			
			if (sLoginBuffor.length() > 10) // Przesowanie nicku podczas pisania
				iCharToDisplayNick = sLoginBuffor.length() - 10;
			else
				iCharToDisplayNick = 0;


			PrintButton("\t\t\t", "    Nick:  " + sLoginBuffor.substr(iCharToDisplayNick, 10), iMenuSelectedOption == 0 ? (bWritingStatus ? ACTIVE_TEXT_COLOR : MAIN_MENU_SELECTED) : DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", "   Haslo:  " + sHidePassword.substr(0, 10), iMenuSelectedOption == 1 ? (bWritingStatus ? ACTIVE_TEXT_COLOR : MAIN_MENU_SELECTED) : DEFAULT_TEXT_COLOR);

			if (iMenuState == 1) // Stan menu == 1 LOGOWANIE
				PrintButton("\t\t\t", "   Zaloguj ", iMenuSelectedOption == 2 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			else if(iMenuState == 2) // Stan menu == 2 REJESTRACJA																				// Zmodyfikowane 
				PrintButton("\t\t\t", "   Stworz  ", iMenuSelectedOption == 2 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			else if(iMenuState == 4)
				PrintButton("\t\t\t", "   Usun  ", iMenuSelectedOption == 2 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);

			cout << "\n";
			PrintButton("\t\t\t", "   Cofnij  ", iMenuSelectedOption == 3 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
		}
		else  if (iMenuState == 3) { // Potwierdzenie wyjscia.
			PrintButton("\t\t\t", "   Czy wyjsc   ", DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", "      TAK      ", iMenuSelectedOption == 0 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
			PrintButton("\t\t\t", "      NIE      ", iMenuSelectedOption == 1 ? MAIN_MENU_SELECTED : DEFAULT_TEXT_COLOR);
		}

	}

	void PrintUserList(const int iNumberOfUsers, const string *sUserList) { // Wypisanie listy userow
		if (iMenuState == 1) {  // W logowaniu tylko
			if (iNumberOfUsers > 0) { // jesli wiecej niz 0
				PrintButton("\t\t\t", " Uzytkownicy ", DEFAULT_TEXT_COLOR);
				for (int i = 0; i < iNumberOfUsers; i++) {
					if (i % 4 == 0)
						cout << "\t  ";

					if (sUserList[i].length() <= 7) // Przycinanie nazwy bo za dluga
						cout << "  " << sUserList[i] << "    ";
					else
						printf("  %.6s.. ", sUserList[i].c_str());

					if (((i + 1) % 4) == 0)
						cout << endl;
					if (i + 1 == MAX_NUMBER_OF_USERS)
						break;
				}
				cout << endl;
			}
			else {
				PrintButton("\t\t   ", " Brak uzytkownikow ", DEFAULT_TEXT_COLOR);
			}
		}
		cout << endl;
	}

	string HideString(const string sText) { // Zastepowanie * itd itp
		sHidePassword = "";
		for (unsigned int i = 0; i < sText.length(); i++) // '*' zamiasta hasla
			sHidePassword += '*';
		return sHidePassword;
	}

	// Rysowanie przycisku i ramki przycisku ....
	void PrintButton(string sAlignment, string sText, unsigned int iColor) {
		ButtonBorder(sAlignment, sText, iColor); // Gorna ramka przycisku

		cout << sAlignment; // Wyrownaine przycisku
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), iColor); // Kolor przycisku aktywny lub domyslny
		cout << "|" << sText << "|" << endl; // Tekst przycisku

		ButtonBorder(sAlignment, sText, iColor); // Dolna ramka przycisku
	}
	void ButtonBorder(string sAlignment, string sText, unsigned int iColor) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR); // Ustawienie koloru na domyslny
		cout << sAlignment; // Wyrownaine przycisku
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), iColor); // Kolor przycisku aktywny lub domyslny

		cout << "+";										//					//
		for (unsigned int i = 0; i < sText.length(); i++)	// Ramka przycisku  //
			cout << "-";									//					//
		cout << "+" << endl;								//					//

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_TEXT_COLOR); // Ustawienie koloru na domyslny
	}

};
