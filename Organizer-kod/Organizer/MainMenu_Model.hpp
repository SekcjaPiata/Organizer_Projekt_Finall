#include "Defines.hpp"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class MenuModel {
protected:
	File_Guardian *fFile; // Obsluga pliku
	string sLoginBuffor = ""; 
	string sPasswordBuffor = "";
	bool bWritingStatus = false;

	// Dozwolone znaki w menu
	char cAllowedChars[70] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','w' ,'q' ,'x','y','z'
		,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','W','Q' ,'X','Y','Z'
		,'1','2','3','4','5','6','7','8','9','0','_','!','@','#','$','%','^','&','*','?' };

	char GetInput() { // INPUT usera
		return _getch();
	}

	bool ExecuteInput(const char cInput, int &iMenuState, int &iMenuOption, string &sErrorMessage) {
		if ((iMenuState == 1 || iMenuState == 2 || iMenuState == 4) && (iMenuOption == 0 || iMenuOption == 1 || iMenuOption == 3) && bWritingStatus) { // Wpisywanie loginu w tworzeniu konta    // dodano imenstate 4 i imenuoption 3 
			if (toupper(cInput) != ENTER_BUTTON) { // Nie wcisnieto enter
				if (cInput == BACKSPACE_BUTTON) { // Backspace
					if (iMenuOption == 0) // Kasowanie Loginu
						sLoginBuffor = sLoginBuffor.substr(0, sLoginBuffor.size() - 1);
					if (iMenuOption == 1) // Kasowanie hasla
						sPasswordBuffor = sPasswordBuffor.substr(0, sPasswordBuffor.size() - 1);
				}
				else if (IsInArray(cInput)) {// Pominiecie niedozowlonych znakow
					if (iMenuOption == 0) { // Dodawanie poprawnych znaków do bufora
						if (sLoginBuffor.length() < MAX_NICK_LENGTH)
							sLoginBuffor += cInput; // loginu
					}
					else {
						sPasswordBuffor += cInput; // hasla
					}
				}
			}
			else {
				if (bWritingStatus == false)
					sPasswordBuffor = "";
				bWritingStatus = !bWritingStatus;
			}
		}
		else if (iMenuState == 0) { // Menu glowne
			if (toupper(cInput) == ARROW_UP) { // Strzalka do gory
				if (iMenuOption > 0)
					iMenuOption--; // Przesuniecie wyboru do gory
			}
			else if (toupper(cInput) == ARROW_DOWN) { // Strzalka w dol
				if (iMenuOption < 3)										// dodano trzecią opcje (znajduje sie na 4 pozyzcji "usun")
					iMenuOption++; // Przesuniecie wybodu w dol
			}
			else if (toupper(cInput) == ENTER_BUTTON) { // Enter
				if (iMenuOption == 0)
					iMenuState = 1; // Przejscie do Logowania
				else if (iMenuOption == 1)
					iMenuState = 2; // przejscie do rejestracji
				else if (iMenuOption == 2)
					iMenuState = 3;  // Przejscie do wyjscia
				else if (iMenuOption == 3) // Przejscie do usuwania 
					iMenuState = 4;
				iMenuOption = 0;
			}
		}
		else if (iMenuState == 1 || iMenuState == 2 || iMenuState == 4 ) { // Menu logowania i rejestracji				/// Dodano usuwanie iMenuState 4 
			if (toupper(cInput) == ARROW_UP && !bWritingStatus) { // Strzalka do gory
				if (iMenuOption > 0)
					iMenuOption--; // Przesuniecie wyboru do gory
			}
			else if (toupper(cInput) == ARROW_DOWN && !bWritingStatus) { // Strzalka w dol
				if (iMenuOption < 3)
					iMenuOption++; // Przesuniecie wybodu w dol
			}
			else if (toupper(cInput) == ENTER_BUTTON) { // Enter
				if (iMenuOption == 0) {// Zablokowanie widoku na polu login
									   //if (bWritingStatus == false) // Nie kasowac pol przy wchodzeniu
									   //sLoginBuffor = "";
					bWritingStatus = !bWritingStatus;
				}
				else if (iMenuOption == 1) { // Zablokowanie widoku na polu haslo
											 //if (bWritingStatus == false) // Nie kasowac pol przy wchodzeniu
											 //sPasswordBuffor = "";
					bWritingStatus = !bWritingStatus;
				}
				else if (iMenuOption == 2 && iMenuState == 1) { // Przycisk zaloguj

					if (sLoginBuffor.length() < MIN_LENGTH ) {
						sErrorMessage = "Login jest za krotki";
					}
					else if (sPasswordBuffor.length() < MIN_LENGTH) {
						sErrorMessage = "Haslo jest za krotkie";
					}
					else if (fFile->UserExists(sLoginBuffor) &&
						fFile->VerifyUser(sLoginBuffor, sPasswordBuffor)) { // User istnieje (dobrze dla logowania)		
						return true;
					}
					else {
						sErrorMessage = "Nieprawidlowe dane!";
					}
				}
				else if (iMenuOption == 2) { // Przycisk STWORZ w widoku tworzeniu konta

					if (iMenuState == 2) {
						if (sLoginBuffor.length() > MAX_NICK_LENGTH) {
							sErrorMessage = "Login jest za dlugi";
						}
						else if (fFile->NumberOfUsers() < MAX_NUMBER_OF_USERS) { // Jest mniej uzytkownikow niz mozna miec
							if (sLoginBuffor.length() < MIN_LENGTH) {
								sErrorMessage = "Login jest za krotki";
							}
							else if (sPasswordBuffor.length() < MIN_LENGTH) {
								sErrorMessage = "Haslo jest za krotkie";
							}
							else if (!fFile->UserExists(sLoginBuffor)) {// User nie istnieje (dobrze dla tworzenia konta)
								fFile->Create(sLoginBuffor, sPasswordBuffor);
								sErrorMessage = "Uzytkonik stworzony.";
							}
							else {
								sErrorMessage = "Uzytkownik o takim loginie juz istnieje!";
							}
						}
						else { // Limit przekroczony
							sErrorMessage = "Limit uzytkownikow osiagniety!";
						}
					}
					else if (iMenuState == 4) {
						if (sLoginBuffor.length() < MIN_LENGTH) {
							sErrorMessage = "Login jest za krotki";
						}
						else if (sPasswordBuffor.length() < MIN_LENGTH) {
							sErrorMessage = "Haslo jest za krotkie";
						}
						else if (fFile->UserExists(sLoginBuffor) &&
							fFile->VerifyUser(sLoginBuffor, sPasswordBuffor)) { // User istnieje (dobrze dla logowania)		i usuwania 
							if (fFile->Delete(sLoginBuffor, sPasswordBuffor) == true) {
								sErrorMessage = ("Usunieto Konto"); /// 
							}
					}

					return false;
				}
				
				else if(iMenuState == 4) {  // jak dobrze pojdzie to przycisk USUWANIA 
					
				}
					else {
						sErrorMessage = "Nieprawidlowe dane!";
					}
				}
				
				else if (iMenuOption == 3) { // Cofniecie menu
					iMenuOption = 0;
					iMenuState = 0;
					sErrorMessage = "";
					sLoginBuffor = "";
					sPasswordBuffor = "";
				}
			}
		}
		else if (iMenuState == 3) { // Menu wychodzenia
			if (toupper(cInput) == ARROW_UP) { // Strzalka do gory
				if (iMenuOption > 0)
					iMenuOption--; // Przesuniecie wyboru do gory
			}
			else if (toupper(cInput) == ARROW_DOWN) { // Strzalka w dol
				if (iMenuOption < 1)
					iMenuOption++; // Przesuniecie wybodu w dol
			}
			else if (toupper(cInput) == ENTER_BUTTON) { // Enter
				if (iMenuOption == 0) {
					iMenuOption = 0;
					iMenuState = 0;
					return true;
				}
				else if (iMenuOption == 1) {
					iMenuOption = 0;
					iMenuState = 0;
				}
			}
		}
		return false;
	}

	bool IsInArray(char cChar) { // Sprawdzanie czy znak znajduje sie w tablicy dozwolonych znakow
		for (char c : cAllowedChars) {
			if (cChar == c) return true;
		}
		return false;
	}

};
