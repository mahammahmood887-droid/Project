#ifndef MEDICINESTRUCT_H
#define MEDICINESTRUCT_H
#include "medicineStruct.h"

bool isExpired(medicine m,int cDay,int cMonth,int cYear);
void listOfExpiredMeds(medicine *arr,int size);
void removeExpired(medicine*&arr,int &size);
bool isNearExpiry(const medicine &m,int cDay,int cMonth,int cYear,int check);
void showNearExpiry(medicine*arr,int size);

#endif