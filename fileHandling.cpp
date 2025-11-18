#include "medicineStruct.h"
#include <iostream>
#include <fstream>
using namespace std;

bool sameText(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

bool biggerText(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] > b[i]) return true;
        if (a[i] < b[i]) return false;
        i++;
    }
    return a[i] != '\0';
}
bool isFileEmpty(const char* filename){
    ifstream f(filename, ios::binary);
    if(!f) return true;
    f.seekg(0, ios::end);
    return f.tellg() == 0;
}

medicine* loadFromBinary(const char* filename, int& size){
    if(isFileEmpty(filename)){
        size = 0;
        return nullptr;
    }

    ifstream fin(filename, ios::binary);
    fin.read((char*)&size, sizeof(int));

    medicine* arr = new medicine[size];
    fin.read((char*)arr, sizeof(medicine) * size);
    fin.close();

    return arr;
}

void saveToBinary(const char* filename, medicine* arr, int size){
    ofstream fout(filename, ios::binary);
    fout.write((char*)&size, sizeof(int));
    fout.write((char*)arr, sizeof(medicine) * size);
    fout.close();
}

void exportToText(const char* filename, medicine* arr, int size) {
    ofstream fout(filename);
    fout << "====== PHARMACY INVENTORY REPORT ======\n";
    for (int i = 0; i < size; i++) {
        fout << "ID: " << arr[i].id << "\n";

        fout<<"Name :"<<arr[i].name<<"\n";

        fout << "Price: " << arr[i].price << "\n";

        fout<<"Quantity : "<<arr[i].quantity<<"\n";
        
    }
    fout.close();
}



void appendLog(const char* filename, const char* msg){
    ofstream fout(filename, ios::app);
    fout << msg << "\n";
    fout.close();
}

int getInt(const char* msg){
    int x;
    cout << msg;
    cin >> x;
    cin.ignore(1000, '\n');
    return x;
}


float getFloat(const char* msg){
    float x;
    cout << msg;
    cin >> x;
    cin.ignore(1000, '\n');
    return x;
}


void getString(const char* msg, char arr[], int size){
    cin.ignore(1000, '\n');
    cout << msg;
    cin.getline(arr, size);
}


const char STAFF_PASSWORD[] = "Pharma123";

const int NAME_SIZE = 50;
void addStaffToFile(const char* filename) {
    char name[NAME_SIZE];
    char role[NAME_SIZE];

    cin.ignore(); 
    cout << "Enter staff name: ";
    cin.getline(name, NAME_SIZE);

    cout << "Enter staff role: ";
    cin.getline(role, NAME_SIZE);

    ofstream fout(filename, ios::app); 
    fout << "Name: " << name << "\n";
    fout << "Role: " << role << "\n";
   
    fout.close();

    cout << "Staff added successfully!\n";
}


bool openStaffReportWithPassword(const char* password) {
    int i = 0;
    while (STAFF_PASSWORD[i] != '\0' || password[i] != '\0') {
        if (STAFF_PASSWORD[i] != password[i]) return false;
        i++;
    }
    return true;
}

void displayStaffReport(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Staff report file not found.\n";
        return;
    }

    char line[256];
    cout << "\n====== STAFF REPORT ======\n";
    while (fin.getline(line, 256)) {
        cout << line << endl;
    }
    fin.close();
}


void exportStaffReport(const char* filename, const char staff[][50], const char roles[][50], int count) {
    ofstream fout(filename);
    fout << "      STAFF REPORT      \n";

    for (int i = 0; i < count; i++) {
        fout << "Name: " << staff[i] << "\n";
        fout << "Role: " << roles[i] << "\n";
       
    }

    fout.close();
    cout << "Staff report exported to " << filename << endl;
}

void displayStaffFromFile(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Staff file not found.\n";
        return;
    }

    char line[256];
    cout << "\n      STAFF LIST      \n";
    while (fin.getline(line, 256)) {
        cout << line << endl;
    }
    fin.close();
}

bool openStaffReportWithPassword(const char* password) {
    return sameText(password, STAFF_PASSWORD);
}

void displayStaffReport(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Staff report file not found.\n";
        return;
    }
    char line[256];
    cout << "\n====== STAFF REPORT ======\n";
    while (fin.getline(line, 256)) {
        cout << line << endl;
    }
    fin.close();
}

void addStaff(char staff[][50], char roles[][50], int& count) {
    int n;
    cout << "How many staff members do you want to add? ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nEnter staff name: ";
        cin.getline(staff[count], 50);

        cout << "Enter staff role: ";
        cin.getline(roles[count], 50);

        count++;
    }
    cout << "Staff added successfully.\n";
}

void saveStaffToFile(const char* filename, char staff[][50], char roles[][50], int count) {
    ofstream fout(filename);
    fout << "====== STAFF REPORT ======\n\n";
    for (int i = 0; i < count; i++) {
        fout << "Name: " << staff[i] << "\n";
        fout << "Role: " << roles[i] << "\n";
        fout << "------------------------\n";
    }
    fout.close();
    cout << "Staff report saved.\n";
}
