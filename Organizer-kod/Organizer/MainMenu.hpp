#include "MainMenu_Model.hpp"
#include "MainMenu_View.hpp"
#include <iostream>

using namespace std;

class MainMenu : protected MenuModel, protected MenuView {
private:
	bool bExit = false; // Czy wyjsc z menu

public:
	MainMenu(File_Guardian *fNewFile) {
		fFile = fNewFile;
	}

	string Menu() {
		sLoginBuffor = ""; // Buffor loginu
		sPasswordBuffor = ""; // Bufor hasla
		iMenuState = 0; // stan menu 

		do {
			CLEAR; // Czyszczenie ekranu
			PrintMenu(sLoginBuffor, sPasswordBuffor, bWritingStatus, fFile->NumberOfUsers(), fFile->getUsers()); // Ryswanie menu na podstawie danych
			bExit = ExecuteInput(GetInput(), iMenuState, iMenuSelectedOption, sErrorMessage); // Pobranie przycisku zwraca czy wyjsc ... mozna pozbyc sie zmiennej 
		} while (!bExit);

		CLEAR;
		return sLoginBuffor; // Zwrocenie loginu lub pustego napisu
	}
};
