/// TODO Przerobic zmienic nazwy na czytelniejsze ...
#pragma once
#include <string>

// Ustawienia konsoli
#define CONSOLE_SIZE_X 70
#define CONSOLE_SIZE_Y 40
#define REFRESH_SPEED 50

// Nowe kolory (i nazwy)
#define DEFAULT_TEXT_COLOR 112

#define TODAY_TEXT_COLOR_1 142
#define TODAY_TEXT_COLOR_2 126
#define SELECTED_TEXT_COLOR 143
#define ACTIVE_TEXT_COLOR 240
#define ERROR_TEXT_COLOR 124
#define SUB_BORDER_COLOR 113
#define SUBMITED_FIELD 120
#define ACTIVE_FIELD 127
#define SUNDAY_EVENT 132
#define MAIN_MENU_SELECTED 143 


#define SET_COLOR(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x)
#define PRINT(NewColor ,Text ,AfterColor) SET_COLOR(NewColor); printf(Text); SET_COLOR(AfterColor)
// Uzywane przyciski
#define ARROW_UP (char)72
#define ARROW_DOWN (char)80
#define ARROW_LEFT (char)75
#define ARROW_RIGHT (char)77
#define ADD_EVENT 'A'
#define DELETE_EVENT 'D'
#define EDIT_EVENT 'E'
#define CLOSE_PROGRAM 'Q'
#define ABORT_BUTTON 'W'
#define MENU_BUTTON 'O'
#define CHANGE_PASS_BUTON 'I'
#define EVENT_BUTTON 'S'
#define PRIORYTY_SORT 'T'
#define NEXT_MONTH 'N'
#define PREVIOUS_MONTH 'B'
#define ENTER_BUTTON '\r'
#define BACKSPACE_BUTTON '\b'
#define TAB_BUTTON '\t'

// Czyszczenie konsoli
#define MOVETO gotoxy(0,0);  /// Przemieszczanie kursora w dowolne miejsce w konsoli.
#ifdef _WIN32
#define CLEAR system("cls");
#else
#define CLEAR system("clear");
#endif

// Katalogi
#define USERS_CONTAINER "Users/"
#define CONFIG_FILE "/config.ini"
#define DATA_FILE "/data.s5"
#define EVENTS_FILE "/events.s5"
#define USER_FILE "/user.s5"
#define USERS_LIST_FILE "users.s5"

// Limity
#define MAX_NUMBER_OF_USERS 8
#define MAX_NICK_LENGTH 15
#define MIN_LENGTH 4
#define NUMBER_OF_PERIODS 3
#define MAX_EVENT_NAME_LENGTH 20
#define MAX_EVENT_DESCRIPTION_LENGTH 60