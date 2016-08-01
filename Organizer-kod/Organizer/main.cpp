#include "Callendar.hpp"
#include "MainMenu.hpp"
#pragma warning(disable : 4703)

void SetConsoleSettings() {
	SetConsoleTitle(TEXT("Organizer")); // Nazwa okna 
	SET_COLOR(DEFAULT_TEXT_COLOR); // Domyslne kolory konsoli

	// Rozmiar okna
	SMALL_RECT windowSize = { 0, 0, CONSOLE_SIZE_X, CONSOLE_SIZE_Y };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	// Rozmiar bufora ekranu
	// COORD wCord = { 1 + CONSOLE_SIZE_X ,1 + CONSOLE_SIZE_Y };
	// SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), wCord);
	CLEAR;
}

int main() {

	SetConsoleSettings(); // Ustawienie koloru itd całego okna :)
	string sMMRsult; // 

	// Towrzenie obiektow klass
	File_Guardian *fFile = new File_Guardian();   
	MainMenu *mMenu = new MainMenu(fFile);       
	User *uUser;							    
	Callendar *cCalendar; 

	do { // Glowna petla programu
		if ( (sMMRsult = mMenu->Menu()) != "") { // jesli nie puste <=> userName -- +wyswietlenie menu i obsluga
			uUser = new User(sMMRsult, fFile);    
			cCalendar = new Callendar(uUser); 
			cCalendar->RunCalendar(); // Kalendarz
		}
		else break; // inaczej koniec
	} while (true);
	if (sMMRsult == "")return 0;
	else {//zabezpieczenie przed bledem usuwania czegos, co nie jest zaalokowane
		
		delete cCalendar;
		delete uUser;
		delete mMenu;
		delete fFile;
	}
	return 0;
}
