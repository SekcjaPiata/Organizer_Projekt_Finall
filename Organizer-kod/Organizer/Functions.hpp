#pragma once
#ifndef funkcje_hpp
#define funkcje_hpp
#include "Event.hpp"
#include <conio.h>
#include <string.h>

//to was nie interesuje//
int sort_iPriority_ros(const void * a, const void * b) {

	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getPriority() < d->getPriority()) return -1;
	else if (c->getPriority() == d->getPriority()) return 0;
	else return 1;

}
int sort_iPriority_mal(const void * a, const void * b) {

	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getPriority() > d->getPriority()) return -1;
	else if (c->getPriority() == d->getPriority()) return 0;
	else return 1;

}
int sort_iName_mal(const void * a, const void * b) {

	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getName() > d->getName()) return -1;
	else if (c->getName() == d->getName()) return 0;
	else return 1;

}
int sort_iName_ros(const void * a, const void * b) {

	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getName() < d->getName()) return -1;
	else if (c->getName() == d->getName()) return 0;
	else return 1;

}
int sort_cTag_mal(const void * a, const void * b) {

	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getTag() > d->getTag()) return -1;
	else if (c->getTag() == d->getTag()) return 0;
	else return 1;

}
int sort_cTag_ros(const void * a, const void * b) {
	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getTag() < d->getTag()) return -1;
	else if (c->getTag() == d->getTag()) return 0;
	else return 1;
}

int sort_date_ros(const void * a, const void * b) {
	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getYear() < d->getYear())
		return -1;
	else if (c->getYear() > d->getYear())
		return 1;


	/* here you are sure the years are equal, so go on comparing the months */

	if (c->getMonth() < d->getMonth())
		return -1;
	else if (c->getMonth() > d->getMonth())
		return 1;

	/* here you are sure the months are equal, so go on comparing the days */

	if (c->getDay() < d->getDay())
		return -1;
	else if (c->getDay() > d->getDay())
		return 1;
	else
		return 0; /* definitely! */

}
int sort_date_mal(const void * a, const void * b) {
	Event *c = (Event*)a;
	Event *d = (Event*)b;
	if (c->getYear() > d->getYear())
		return -1;
	else if (c->getYear() < d->getYear())
		return 1;


	/* here you are sure the years are equal, so go on comparing the months */

	if (c->getMonth() > d->getMonth())
		return -1;
	else if (c->getMonth() < d->getMonth())
		return 1;

	/* here you are sure the months are equal, so go on comparing the days */

	if (c->getDay() > d->getDay())
		return -1;
	else if (c->getDay() < d->getDay())
		return 1;
	else
		return 0; /* definitely! */

}
// a to poniżej już tak, wywolujcie tylko te voidy do sortowania
//asc = rosnaco
//dsc = malejaco
void sort_Date_asc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *)) sort_date_ros);
}
void sort_Date_dsc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *)) sort_date_mal);
}

void sort_iPriority_asc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_iPriority_ros);
}
void sort_iPriority_dsc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_iPriority_mal);
}
void sort_iName_dsc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_iName_mal);
}
void sort_iName_asc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_iName_ros);
}
void sort_cTag_dsc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_cTag_mal);
}
void sort_cTag_asc(Event *tab, int ile) {
	qsort(tab, ile, sizeof(Event), (int(*)(const void *, const void *))sort_cTag_ros);
}

#endif
