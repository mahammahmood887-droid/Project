#include <iostream>
#include <fstream>
using namespace std;

struct Medicine {
    int id;
    char name[50];
    float price;
    int quantity;
};


bool isFileEmpty(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) return true;

    file.seekg(0, ios::end);
    long size = file.tellg();
    return size == 0;
}

Medicine* loadFromBinary(const char* filename, int &size) {
    if (isFileEmpty(filename)) {
        size = 0;
        return nullptr;
    }

    ifstream fin(filename, ios::binary);
    fin.read((char*)&size, sizeof(int));

    if(size < 0 || size > 10000) { 
        size = 0;
        return nullptr;
    }

    Medicine* arr = new Medicine[size];
    fin.read((char*)arr, sizeof(Medicine) * size);

    fin.close();
    return arr;
}

void saveToBinary(const char* filename, Medicine* arr, int size) {
    ofstream fout(filename, ios::binary);
    fout.write((char*)&size, sizeof(int));
    fout.write((char*)arr, sizeof(Medicine) * size);
    fout.close();
}

void exportToText(const char* filename, Medicine* arr, int size) {
    ofstream fout(filename);
    fout << "     PHARMACY INVENTORY REPORT     \n";

    for (int i = 0; i < size; i++) {
        fout << "ID:" << arr[i].id << "\n";
        fout << "Name: " << arr[i].name << "\n";
        fout << "Price: " << arr[i].price << "\n";
        fout << "Quantity: " << arr[i].quantity << "\n\n";
    }

    fout.close();
}

void appendLog(const char* filename, const char* message) {
    ofstream fout(filename, ios::app);
    fout << message << "\n";
    fout.close();
}


int getInt(const char* msg) {
    int x;
    while (true) {
        cout << msg;
        cin >> x;

        if (cin.fail() || x < 0) {
            cout << "Invalid input! Enter a positive number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            return x;
        }
    }
}

float getFloat(const char* msg) {
    float x;
    while (true) {
        cout << msg;
        cin >> x;

        if (cin.fail() || x < 0) {
            cout << "Invalid input! Enter a positive price.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            return x;
        }
    }
}

void getString(const char* msg, char arr[], int size) {
    cout << msg;

    if(cin.peek() == '\n') cin.ignore();

    cin.getline(arr, size);

    while (arr[0] == '\0') {
        cout << "Name cannot be empty! Enter again: ";
        cin.getline(arr, size);
    }
}

int main() {
    int size = 0;
    Medicine* medicines = loadFromBinary("medicine.dat", size);

    if (medicines == nullptr) {
        cout << "No records found yet.\n";
    }

    size++;
    Medicine newMed;
    newMed.id = getInt("Enter medicine ID: ");
    getString("Enter medicine name: ", newMed.name, 50);
    newMed.price = getFloat("Enter medicine price: ");
    newMed.quantity = getInt("Enter quantity: ");

    
    Medicine* temp = new Medicine[size];
    for (int i = 0; i < size - 1; i++) {
        temp[i] = medicines[i];
    }
    temp[size - 1] = newMed;

    delete[] medicines;
    medicines = temp;

    saveToBinary("medicine.dat", medicines, size);
    exportToText("report.txt", medicines, size);
    appendLog("log.txt", "Added new medicine record.");

    cout << "\nMedicine added successfully!\n";

    delete[] medicines;
    return 0;
}
