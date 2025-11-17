#ifndef MEDICINESTRUCT_H
#define MEDICINESTRUCT_H
#include "medicineStruct.h"


void displayMedicine(const medicine& m);
void displayAllMedicines(medicine* arr, int size);

int searchByID(medicine* arr, int size, int id);
int searchByName(medicine* arr, int size, char name[]);

void updatePrice(medicine* arr, int size, int id);
void UpdateQuantityByID(medicine* arr, int size, int id);

void deleteByID(medicine*& arr, int& size, int id);

int generateID(medicine* arr, int size);
void addMedicine(medicine*& arr, int& size);

void sortByName(medicine* arr, int size);
void sortByPrice(medicine* arr, int size);


#endif
