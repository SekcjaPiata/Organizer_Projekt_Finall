#include "Event.hpp"


//gettery:
string Event::getName() {
	return sName;
}
string Event::getDescription() {
	return sDescription;
}
char Event::getTag() {
	return cTag;
}
size_t Event::getPriority() {
	return iPriority;
}
size_t Event::getDay() {
	return iDay;
}
size_t Event::getMonth() {
	return iMonth;
}
size_t Event::getYear() {
	return iYear;
}
size_t Event::getHour() {
	return iHour;
}
size_t Event::getMinute() {
	return iMinute;
}
Period Event::getPeriod() {
	return ePeriod;
}
//settery:
void Event::setName(string n) {
	if (n != "")
		sName = n;
}
void Event::setDescription(string d) {
	if (d != "")
	sDescription = d;
}
void Event::setTag(char t)
{
	cTag = t;
}
void Event::setPriority(size_t p) {
	if (p >= 0 && p < 11)
		iPriority = p;
}
void Event::setDay(size_t d) {
	if (d >= 0 && d < 32)
		iDay = d;
}
void Event::setMonth(size_t m) {
	if (m > 0 && m < 13)
		iMonth = m;
}
void Event::setYear(size_t y) {
	if (y > 1900 && y < 3000)
		iYear = y;
}
void Event::setHour(size_t h) {
	if (h > 0 && h < 24)
		iHour = h;
}
void Event::setMinute(size_t m) {
	if (m > 0 && m < 60)
		iMinute = m;
}
void Event::setPeriod(Period p) {
	if (p >= 0 && p < 4)
		ePeriod = p;
}
//konstruktorely
Event::Event(string name, size_t day, size_t month, size_t year, size_t hour, size_t minute, char tag, size_t priority, string description, Period period)
	:sName(name), iHour(hour), cTag(tag), sDescription(description), ePeriod(period) {
	if (day > 0 && day < 32)iDay = day;
	else iDay = 1;
	if (month > 0 && month < 13)  iMonth = month;
	else iMonth = 1;
	if (year > 1900 && year < 3000) iYear = year;
	else iYear = 1900;
	if (minute >= 0 && minute < 60)iMinute = minute;
	else iMinute = 0;
	if (hour >= 0 && hour < 24)iHour = hour;
	else iHour = 0;
	if (priority >= 0 && priority < 11)iPriority = priority;
	else iPriority = 0;
}


Event::~Event() {}//nie ma co niszczyc
