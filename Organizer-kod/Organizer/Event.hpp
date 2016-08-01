#pragma once
#include <iostream>
#include <string>
using namespace std;

enum Period { /// 
	brak,
	co_tydzien,
	co_miesiac
};
class Event
{

protected:
	string sName; //nazwa wydarzenia
	string sDescription; // opis wydarzenia
	char cTag; // tag wydarzenia (wartosc z tablicy ASCI)
	size_t iPriority; // priorytet od 1 do 10, 0 oznacza brak priorytetu (uzytkownik nie wprowadzil), size_t to po prostu unsigned int
	size_t iDay, iMonth, iYear, iHour, iMinute; //Dzien, miesiac, rok, godzina, minuta w intach
	Period ePeriod;
public:
	//gettery, zwracaja wartosci pol 
	string getName();
	string getDescription();
	char getTag();
	size_t getPriority();
	size_t getDay();
	size_t getMonth();
	size_t getYear();
	size_t getHour();
	size_t getMinute();
	Period getPeriod();
	//settery, ustawiaja dane pola
	void setName(string n);
	void setDescription(string d);
	void setTag(char t);
	void setPriority(size_t p);
	void setDay(size_t d);
	void setMonth(size_t m);
	void setYear(size_t y);
	void setHour(size_t h);
	void setMinute(size_t m);
	void setPeriod(Period p);
	//konstruktoreły
	Event(string name = "Brak nazwy", size_t day = 1, size_t month = 1, size_t year = 1, size_t hour = 0, size_t minute = 0, char tag = 33, size_t priority = 0, string description = "Brak opisu", Period period = brak);
	//parametryczny, wg kolejnosci zapisu w pliku, mozna podawac mniej argumentow o ile brakuje ich od prawej a nie od lewej
	~Event();//nie ma co niszczyc 
};
