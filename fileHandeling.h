#pragma once
#include "medicineStruct.h"

// File handling functions
bool isFileEmpty(const char* filename);
medicine* loadFromBinary(const char* filename, int& size);
void saveToBinary(const char* filename, medicine* arr, int size);
void exportToText(const char* filename, medicine* arr, int size);
void appendLog(const char* filename, const char* message);
bool openStaffReportWithPassword(const char* password);
void displayStaffReport(const char* filename);
void addStaff(char staff[][50], char roles[][50], int& count);
void saveStaffToFile(const char* filename, char staff[][50], char roles[][50], int count);
bool sameText(const char a[], const char b[]);
bool biggerText(const char a[], const char b[]);

// Safe input functions
int getInt(const char* msg);
float getFloat(const char* msg);
void getString(const char* msg, char arr[], int size);
