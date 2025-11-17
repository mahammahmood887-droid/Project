#ifndef BILLSTRUCT_H
#define BILLSTRUCT_H
#include "medicineStruct.h"
#include "billstruct.h"

void addItemToBill(bill&bill,medicine*arr,int size);
float calculateTotal(bill& bill);
void discount(bill& bill,float percent);
void printBill(bill bill);

void reduceStock(medicine* arr, int size, bill bill);
void saveBillToFile(bill bill);
#endif