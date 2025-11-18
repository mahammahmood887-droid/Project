#include <iostream>
#include <fstream>

using namespace std;

struct medicine {
    int id;
    char name[50];
    float price;
    int quantity;
    int expDay, expMonth, expYear;
};

struct retailer {
    int id;
    char name[50];
    char phone[20];
    char address[80];
};

struct billItem {
    int medId;
    char name[50];
    float price;
    int quantity;
    float total;
};

struct bill {
    int billNo;
    billItem items[50];
    int itemCount;
    float total;
    float discount;
    float finalAmount;
};

// -------------------- STRING REPLACEMENTS (NO strcmp) --------------------
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

// -------------------- FILE HANDLING --------------------
bool isFileEmpty(const char* filename) {
    ifstream f(filename, ios::binary);
    if (!f) return true;
    f.seekg(0, ios::end);
    return f.tellg() == 0;
}

medicine* loadFromBinary(const char* filename, int& size) {
    if (isFileEmpty(filename)) {
        size = 0;
        return nullptr;
    }
    ifstream fin(filename, ios::binary);
    if (!fin) {
        size = 0;
        return nullptr;
    }
    fin.read((char*)&size, sizeof(int));
    if (size <= 0) {
        fin.close();
        size = 0;
        return nullptr;
    }
    medicine* arr = new medicine[size];
    fin.read((char*)arr, sizeof(medicine) * size);
    fin.close();
    return arr;
}

void saveToBinary(const char* filename, medicine* arr, int size) {
    ofstream fout(filename, ios::binary);
    fout.write((char*)&size, sizeof(int));
    if (size > 0 && arr != nullptr)
        fout.write((char*)arr, sizeof(medicine) * size);
    fout.close();
}

void exportToText(const char* filename, medicine* arr, int size) {
    ofstream fout(filename);
    fout << "====== PHARMACY INVENTORY REPORT ======\n";
    for (int i = 0; i < size; i++) {
        fout << "ID: " << arr[i].id << "\n";
        fout << "Name: " << arr[i].name << "\n";
        fout << "Price: " << arr[i].price << "\n";
        fout << "Quantity: " << arr[i].quantity << "\n";
        fout << "Expiry: " << arr[i].expDay << "/" << arr[i].expMonth << "/" << arr[i].expYear << "\n";
        fout << "--------------------------\n";
    }
    fout.close();
}

// -------------------- LOGGING --------------------
void appendLog(const char* filename, const char* msg) {
    ofstream fout(filename, ios::app);
    fout << msg << "\n";
    fout.close();
}

// -------------------- STAFF --------------------
const char STAFF_PASSWORD[] = "Pharma123";

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
    cout << "Staff report saved .\n";
}

// -------------------- MEDICINE FUNCTIONS --------------------
void displayMedicine(const medicine& m) {
    cout << "ID: " << m.id << endl;
    cout << "Name: " << m.name << endl;
    cout << "Price: " << m.price << endl;
    cout << "Quantity: " << m.quantity << endl;
    cout << "Expiry: " << m.expDay << "/" << m.expMonth << "/" << m.expYear << endl;
}

void displayAllMedicines(medicine* arr, int size) {
    cout<<endl;
    if (size == 0) {
        cout << "No medicines.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        displayMedicine(arr[i]);
        cout << "--------------------\n";
    }
}

int searchByID(medicine* arr, int size, int id) {
    for (int i = 0; i < size; i++)
        if (arr[i].id == id) return i;
    return -1;
}

int searchByName(medicine* arr, int size, const char name[]) {
    for (int i = 0; i < size; i++)
        if (sameText(arr[i].name, name)) return i;
    return -1;
}

int generateID(medicine* arr, int size) {
    int max = 0;
    for (int i = 0; i < size; i++)
        if (arr[i].id > max) max = arr[i].id;
    return max + 1;
}

// ---------- ADD/UPDATE/DELETE WITH FILE HANDLING ----------
void addMedicine(medicine*& arr, int& size, const char* DATAFILE, const char* REPORTFILE) {
    medicine m;
    m.id = generateID(arr, size);

    cin.ignore();
    cout << "Enter name: ";
    cin.getline(m.name, 50);

    cout << "Enter price: ";
    cin >> m.price;

    cout << "Enter quantity: ";
    cin >> m.quantity;

    cout << "Enter expiry (day month year): ";
    cin >> m.expDay >> m.expMonth >> m.expYear;

    medicine* temp = new medicine[size + 1];
    for (int i = 0; i < size; i++) temp[i] = arr[i];
    temp[size] = m;

    delete[] arr;
    arr = temp;
    size++;

    cout << "Medicine added.\n";

    // Save immediately to files
    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

void Updateprice(medicine* arr, int size, int id, const char* DATAFILE, const char* REPORTFILE) {
    int idx = searchByID(arr, size, id);
    if (idx == -1) { cout << "Not found\n"; return; }
    cout << "Enter new price: ";
    cin >> arr[idx].price;

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

void UpdateQuantityByID(medicine* arr, int size, int id, const char* DATAFILE, const char* REPORTFILE) {
    int idx = searchByID(arr, size, id);
    if (idx == -1) { cout << "Not found\n"; return; }
    cout << "Enter new quantity: ";
    cin >> arr[idx].quantity;

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

void deleteByID(medicine*& arr, int& size, int id, const char* DATAFILE, const char* REPORTFILE) {
    int index = searchByID(arr, size, id);
    if (index == -1) { cout << "Not found\n"; return; }

    medicine* temp = new medicine[size - 1];
    int j = 0;
    for (int i = 0; i < size; i++)
        if (i != index) temp[j++] = arr[i];

    delete[] arr;
    arr = temp;
    size--;

    cout << "Deleted.\n";

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

void sortByName(medicine* arr, int size, const char* DATAFILE, const char* REPORTFILE) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (biggerText(arr[j].name, arr[j + 1].name))
                swap(arr[j], arr[j + 1]);

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

void sortByPrice(medicine* arr, int size, const char* DATAFILE, const char* REPORTFILE) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j].price > arr[j + 1].price)
                swap(arr[j], arr[j + 1]);

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

// -------------------- EXPIRY --------------------
bool isExpired(const medicine& m, int d, int mth, int y) {
    if (m.expYear < y) return true;
    if (m.expYear == y && m.expMonth < mth) return true;
    if (m.expYear == y && m.expMonth == mth && m.expDay < d) return true;
    return false;
}

void listOfExpiredMeds(medicine* arr, int size) {
    int d, m, y;
    cout << "Enter today (day month year): ";
    cin >> d >> m >> y;

    bool found = false;
    for (int i = 0; i < size; i++)
        if (isExpired(arr[i], d, m, y)) {
            displayMedicine(arr[i]);
            found = true;
        }

    if (!found) cout << "No expired medicines.\n";
}

void removeExpired(medicine*& arr, int& size, const char* DATAFILE, const char* REPORTFILE) {
    int d, m, y;
    cout << "Enter today (day month year): ";
    cin >> d >> m >> y;

    int newSize = 0;
    for (int i = 0; i < size; i++)
        if (!isExpired(arr[i], d, m, y)) newSize++;

    medicine* temp = new medicine[newSize];
    int j = 0;
    for (int i = 0; i < size; i++)
        if (!isExpired(arr[i], d, m, y))
            temp[j++] = arr[i];

    delete[] arr;
    arr = temp;
    size = newSize;

    cout << "Expired removed.\n";

    saveToBinary(DATAFILE, arr, size);
    exportToText(REPORTFILE, arr, size);
}

// -------------------- MISSING FUNCTIONS --------------------
int generateInvoiceNumber() {
    static int invoiceCounter = 1;
    return invoiceCounter++;
}

void calculateTotal(bill& b) {
    b.total = 0;
    for (int i = 0; i < b.itemCount; i++) {
        b.total += b.items[i].total;
    }
}

void discount(bill& bill, float percent) {
    bill.discount = (bill.total * percent) / 100.0;
    bill.finalAmount = bill.total - bill.discount;
}

void applyDiscount(bill& b, float percent) {
    discount(b, percent);
}

void showNearExpiry(medicine* arr, int size) {
    int todayD, todayM, todayY;
    cout << "Enter today's date (day month year): ";
    cin >> todayD >> todayM >> todayY;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].expYear == todayY) {
            if (arr[i].expMonth == todayM || arr[i].expMonth == todayM + 1) {
                displayMedicine(arr[i]);
                found = true;
            }
        }
        else if (arr[i].expYear == todayY + 1 && todayM == 12 && arr[i].expMonth == 1) {
            displayMedicine(arr[i]);
            found = true;
        }
    }

    if (!found) cout << "No medicines near expiry.\n";
}

void blockSale(medicine& m, int d, int mth, int y) {
    if (isExpired(m, d, mth, y)) {
        cout << "Sale blocked: medicine " << m.name << " is expired!\n";
    }
    else {
        cout << "Medicine " << m.name << " is valid for sale.\n";
    }
}

// -------------------- BILLING --------------------
void addItemToBill(bill& bill, medicine* arr, int size) {
    int id, qty;
    cout << "Enter medicine ID: ";
    cin >> id;
    int index = searchByID(arr, size, id);
    if (index == -1) {
        cout << "Medicine not found!" << endl;
        return;
    }

    cout << "Enter quantity to buy: ";
    cin >> qty;
    if (qty > arr[index].quantity) {
        cout << "Not enough stock" << endl;
        return;
    }

    billItem item;
    item.medId = arr[index].id;
    for (int i = 0; i < 50; i++) {
        item.name[i] = arr[index].name[i];
        if (arr[index].name[i] == '\0') break;
    }

    item.price = arr[index].price;
    item.quantity = qty;
    item.total = qty * item.price;

    bill.items[bill.itemCount++] = item;
    cout << "Item added to bill." << endl;
}

void printBill(bill bill) {
    cout << "BILL" << endl;
    for (int i = 0; i < bill.itemCount; i++) {
        cout << bill.items[i].name << " x " << bill.items[i].quantity
            << " = " << bill.items[i].total << endl;
    }
    cout << "Total: " << bill.total << endl;
    cout << "Discount: " << bill.discount << endl;
    cout << "Final Amount: " << bill.finalAmount << endl;
}

void reduceStock(medicine* arr, int size, bill bill) {
    for (int i = 0; i < bill.itemCount; i++) {
        int id = bill.items[i].medId;
        int index = searchByID(arr, size, id);

        if (index != -1) {
            arr[index].quantity -= bill.items[i].quantity;
        }
    }
}

void saveBillToFile(bill bill) {
    ofstream out("bills.txt", ios::app);

    out << "Bill #" << bill.billNo << endl;
    for (int i = 0; i < bill.itemCount; i++) {
        out << bill.items[i].name << " "
            << bill.items[i].quantity << " "
            << bill.items[i].total << endl;
    }
    out << "Total: " << bill.total << endl;
    out << "Discount: " << bill.discount << endl;
    out << "Final: " << bill.finalAmount << endl;
    out << "--------------------------\n";

    out.close();
}

//BACKUP INVENTORY
void backupInventory(const char* mainfile, const char* backupfile) {
    ifstream input(mainfile, ios::binary);
    if (!input) {
        cout << "Inventory file not found! Nothing to backup!\n";
        return;
    }
    ofstream output(backupfile, ios::binary);
    if (!output) {
        cout << "Failed to create backup file!\n";
        return;
    }
    output << input.rdbuf();
    input.close();
    output.close();
    cout << "\nBACKUP SUCCESSFULLY STORED!\n";
}

//TOTAL INVENTORY
void showtotalinventory(medicine* arr, int size) {
    float totalvalue = 0;
    for (int i = 0; i < size; i++) {
        totalvalue += arr[i].price * arr[i].quantity;
    }
    cout << "TOTAL INVENTORY VALUE: Rs." << totalvalue << "\n";
}

//STOCK ALERT
void showlowstock(medicine* arr, int size) {
    int limit;
    bool found = false;
    cout << "ENTER LOWSTOCK LIMIT: ";
    cin >> limit;
    for (int j = 0; j < size; j++) {
        if (arr[j].quantity <= limit) {
            displayMedicine(arr[j]);
            cout << "----------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "NO MEDICINES BELOW STOCK LIMIT!\n";
    }
}

//SEARCH MEDICINE BY STARTING LETTER
void searchbyletter(medicine* arr, int size) {
    char letter;
    cout << "Enter Starting Letter: ";
    cin >> letter;
    bool found = false;
    for (int k = 0; k < size; k++) {
        if (arr[k].name[0] == letter) {
            displayMedicine(arr[k]);
            cout << "----------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "NO MEDICINE FOUND WITH THIS LETTER!\n";
    }
}

void purchaseMedicine(medicine* arr, int size, const char* datafile, const char* reportfile) {
    bill b;
    b.billNo = generateInvoiceNumber();
    b.itemCount = 0;

    int choice;
    do {
        cout << "\n1. Add item to bill\n2. Finish bill\nChoice: ";
        cin >> choice;
        if (choice == 1)
            addItemToBill(b, arr, size);
    } while (choice != 2);

    calculateTotal(b);
    applyDiscount(b, 5); 
    printBill(b);
    saveBillToFile(b);
    reduceStock(arr, size, b);

    saveToBinary(datafile, arr, size);
    exportToText(reportfile, arr, size);

    cout << "Purchase completed.\n";
}

//-------------RETAILER FUNCTION-----------//
void addretailer(retailer* list, int& count) {
    cin.ignore();

    cout << "Enter Retailer name: ";
    cin.getline(list[count].name, 50);
    cout << "Enter phone number: ";
    cin.getline(list[count].phone, 20);
    cout << "Enter address: ";
    cin.getline(list[count].address, 80);
    list[count].id = count + 1;
    cout << "Retailer added! ID=" << list[count].id << "\n";
    count++;
}

void showretailer(retailer* list, int count) {
    if (count == 0) {
        cout << "NO RETAILERS ADDED!\n";
        return;
    }
    cout << "----------RETAILER LIST-------- \n";

    for (int j = 0; j < count; j++) {
        cout << "ID: " << list[j].id << "\n";
        cout << "NAME: " << list[j].name << "\n";
        cout << "PHONE: " << list[j].phone << "\n";
        cout << "ADDRESS: " << list[j].address << "\n";
        cout << "----------------------------\n";
    }
}

void searchretailerbyname(retailer* list, int count) {
    char name[50];
    cin.ignore();
    cout << "Enter retailer name to search: ";
    cin.getline(name, 50);
    bool found = false;
    for (int k = 0; k < count; k++) {
        if (sameText(list[k].name, name)) {
            cout << "Retailer found!\n";
            cout << "ID: " << list[k].id << "\n";
            cout << "NAME: " << list[k].name << "\n";
            cout << "PHONE: " << list[k].phone << "\n";
            cout << "ADDRESS: " << list[k].address << "\n";
            cout << "----------------------------------\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "NO RETAILER FOUND WITH GIVEN NAME!\n";
    }
}

void updateretailer(retailer* list, int count) {
    int rid;
    cout << "ENTER RETAILER ID TO UPDATE: ";
    cin >> rid;
    cin.ignore();
    for (int i = 0; i < count; i++) {
        if (list[i].id == rid) {
            cout << "Enter NEW Retailer name: ";
            cin.getline(list[i].name, 50);
            cout << "Enter phone number: ";
            cin.getline(list[i].phone, 20);
            cout << "Enter address: ";
            cin.getline(list[i].address, 80);
            cout << "Retailer updated!\n";
            return;
        }
    }
    cout << "RETAILER ID NOT FOUND!\n";
}

void deleteretailer(retailer* list, int& count) {
    int rid;
    cout << "ENTER RETAILER ID TO DELETE: ";
    cin >> rid;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (list[i].id == rid) {
            found = true;
            for (int j = i; j < count - 1; j++) {
                list[j] = list[j + 1];
            }
            count--;
            cout << "RETAILER DELETED SUCCESSFULLY!\n";
            break;
        }
    }
    if (!found) {
        cout << "RETAILER ID NOT FOUND!";
    }
}


int main() {
    const char* SYSTEM_PASSWORD = "Admin123";  // Password for management system
    const char* DATAFILE = "inventory.dat";
    const char* REPORTFILE = "report.txt";
    const char* STAFFFILE = "staff.txt";
    const char* BACKUPFILE = "pharmacybackup.dat";

    char staff[50][50];
    char roles[50][50];
    int staffCount = 0;

    retailer* retailers = new retailer[50];
    int retailercount = 0;

    int size = 0;
    medicine* inventory = loadFromBinary(DATAFILE, size);

    char inputPass[50];
    bool loggedIn = false;

    while (!loggedIn) {
        cout << "Enter system password: ";
        cin.getline(inputPass, 50);

        if (sameText(inputPass, SYSTEM_PASSWORD)) {
            loggedIn = true;
            cout << "Login successful!\n";
        }
        else {
            cout << "Incorrect password! Try again.\n";
        }
    }

    // --------- Main Menu ---------
    int mainChoice;
    do {
        cout << "\n====== PHARMACY MANAGEMENT SYSTEM ======\n";
        cout << "1. Medicine Management\n";
        cout << "2. Billing\n";
        cout << "3. Staff Management\n";
        cout << "4. Search / Update Medicine\n";
        cout << "5. Expiry Management\n";
          cout<<"6. Inventry management"<<"\n";
         cout<<"7. Retialler management"<<"\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;
        cin.ignore();

        if (mainChoice == 1) { // Medicine Management
            int sub;
            cout << "\n--- Medicine Management ---\n";
            cout << "1. Display all medicines\n2. Add medicine\n3. Delete medicine\n4. Sort by name\n5. Sort by price\n0. Back\n";
            cout << "Choice: "; cin >> sub;

            if (sub == 1) displayAllMedicines(inventory, size);
            else if (sub == 2) addMedicine(inventory, size, DATAFILE, REPORTFILE);
            else if (sub == 3) { int id; cout << "ID: "; cin >> id; deleteByID(inventory, size, id, DATAFILE, REPORTFILE); }
            else if (sub == 4) sortByName(inventory, size, DATAFILE, REPORTFILE);
            else if (sub == 5) sortByPrice(inventory, size, DATAFILE, REPORTFILE);
        }
        else if (mainChoice == 2) { // Billing
            cout << "\n--- Billing ---\n";
            purchaseMedicine(inventory, size, DATAFILE, REPORTFILE);
        }
        else if (mainChoice == 3) { // Staff Management
            int sub;
            cout << "\n--- Staff Management ---\n";
            cout << "1. Add Staff\n2. View Staff Report (Password Required)\n0. Back\n";
            cout << "Choice: "; cin >> sub;
            cin.ignore();

            if (sub == 1) {addStaff(staff, roles, staffCount);
            saveStaffToFile(STAFFFILE, staff, roles, staffCount);}
    
            else if (sub == 2) {

                   char pass[50]; 
                    cout<<"Password: "; cin.getline(pass,50); if(openStaffReportWithPassword(pass)) displayStaffReport(STAFFFILE); else cout<<"Denied.\n"; 
            }
        }
        else if (mainChoice == 4) { // Search / Update Medicine
            int sub;
            cout << "\n--- Search / Update Medicine ---\n";
            cout << "1. Search by ID\n2. Search by Name\n3. Update Price\n4. Update Quantity\n0. Back\n";
            cout << "Choice: "; cin >> sub;
            cin.ignore();

            if (sub == 1) {
                int id; cout << "ID: "; cin >> id;
                int i = searchByID(inventory, size, id);
                if (i != -1) displayMedicine(inventory[i]);
                else cout << "Not found\n";
            }
            else if (sub == 2) {
                char n[50]; cout << "Name: "; cin.getline(n, 50);
                int i = searchByName(inventory, size, n);
                if (i != -1) displayMedicine(inventory[i]);
                else cout << "Not found\n";
            }
            else if (sub == 3) { int id; cout << "ID: "; cin >> id; Updateprice(inventory, size, id, DATAFILE, REPORTFILE); }
            else if (sub == 4) { int id; cout << "ID: "; cin >> id; UpdateQuantityByID(inventory, size, id, DATAFILE, REPORTFILE); }
        }
        else if (mainChoice == 5) { // Expiry Management
            int sub;
            cout << "\n--- Expiry Management ---\n";
            cout << "1. List expired medicines\n2. Remove expired medicines\n3. Show near expiry\n4. Block sale if expired\n0. Back\n";
            cout << "Choice: "; cin >> sub;

            if (sub == 1) listOfExpiredMeds(inventory, size);
            else if (sub == 2) removeExpired(inventory, size, DATAFILE, REPORTFILE);
            else if (sub == 3) showNearExpiry(inventory, size);
            else if (sub == 4) {
                int id, d, m, y;
                cout << "ID: "; cin >> id;
                int i = searchByID(inventory, size, id);
                cout << "Today's date (dd mm yyyy): "; cin >> d >> m >> y;
                if (i != -1) blockSale(inventory[i], d, m, y);
                else cout << "Not found\n";
            }
        }
        else if (mainChoice == 6) { //inventry 
            int sub;

        cout << "1. Inventory backup\n";
        cout << "2. Total inventory\n";
        cout << "3. Low stock\n";
        cout << "4. Search by first letter\n";
        cin>>sub;
            if (sub == 1){
            backupInventory(DATAFILE, BACKUPFILE);
        }
        else if (sub == 2) {
            if (size == 0) {
                cout << "Inventory is empty!\n";
            }
            else {
                showtotalinventory(inventory, size);
            }
        }
        else if (sub == 3) {
            if (size == 0) {
                cout << "Inventory is empty!\n";
            }
            else {
                showlowstock(inventory, size);
            }
        }
        else if (sub == 4){
            if (size == 0) {
                cout << "Inventory is empty!\n";
            }
            else {
                searchbyletter(inventory, size);
            }
           }   }
           
        else if (mainChoice == 7) { // relaillrer;
            int sub;
             cout << "1. Add Retailer!\n";
        cout << "2. Show Retailers!\n";
        cout << "3. Search Retailers\n";
        cout << "4. Update retailer\n";
        cout << "5. Delete retailer\n";
        cin>>sub;
        if (sub == 1){
            addretailer(retailers, retailercount);
        }
        else if (sub == 2) {
            showretailer(retailers, retailercount);
        }
        else if (sub == 3) {
            searchretailerbyname(retailers, retailercount);
        }
        else if (sub == 4) {
            updateretailer(retailers, retailercount);
        }
        else if (sub == 5) {
            deleteretailer(retailers, retailercount);
        }
    }
        else if (mainChoice == 0) cout << "Exiting system...\n";
        else cout << "Invalid choice\n";

    } while (mainChoice != 0);

    delete[] inventory;
    delete[] retailers;
    return 0;
}