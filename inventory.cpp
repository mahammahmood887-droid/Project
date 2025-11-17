#include "medicineStruct.h"
#include <iostream>
#include <cstring>
using namespace std;

// display medicine info
void displayMedicine(const medicine&m){
    cout<<"ID: "<<m.id<<endl;
    cout<<"Name: "<<m.name<<endl;
    cout<<"Price: "<<m.price<<endl;
    cout<<"Quantity: "<<m.quantity<<endl;}


    // display all medicines

void displayAllMedicines( medicine *arr,int size){
    if(size==0){
      cout<<  "No medicine present in inventory"<<endl;
    }

    else{
        for(int i=0;i<size;i++){
            displayMedicine(arr[i]);

        }

    }

}

// search medicine by id
int searchByID(medicine*arr,int size,int id){

    for(int i=0;i<size;i++){
        if(arr[i].id==id){
            return i;
        }
    }
    return -1;
}

// search by name 



int searchByName(medicine *arr, int size, char name[]) {
    for (int i = 0; i < size; i++) {
    
        int j = 0;
        while (arr[i].name[j] && name[j]) {
            if (tolower(arr[i].name[j]) != tolower(name[j])) {
                break;  
            }
            j++;
        }

    
        if (arr[i].name[j] == '\0' && name[j] == '\0') {
            return i;
        }
    }
    return -1;
}


// update price of medicine by id

void updatePrice(medicine *arr,int size,int id){
    int index=searchByID(arr,size,id);
    if(index==-1){
        cout<<"medicine not found"<<endl;
    }
    else{
        cout<<"enter price to update"<<endl;
        int price;
        cin>>price;
        arr[index].price=price;
        cout<<"price updated successfully"<<endl;
    }
}

// update quantity by id
void UpdateQuantityByID(medicine *arr,int size,int id){
 int index=searchByID(arr,size,id);
    if(index==-1){
        cout<<"medicine not found"<<endl;
    }
    else{
        cout<<"enter quantity to update"<<endl;
        int quantity;
        cin>>quantity;
        arr[index].quantity=quantity;
        cout<<"quantity updated successfully"<<endl;
    }
}

// delete a medicine by id

void deleteByID(medicine*&arr,int& size,int id){
    int index=searchByID(arr,size,id);
    if(index==-1){
        cout<<"medicine not found"<<endl;
    }
    else{

        for(int i=index;i<size-1;i++){
            arr[i]=arr[i+1];

        }
        size--;
        medicine *temp=new medicine[size];

        for(int i=0;i<size;i++){
            temp[i]=arr[i];
        }
        delete[]arr;
        arr=temp;
        cout<<"Medcine deleted successfulyy"<<endl;
        
    }

}

// generate new unique id
int generateID(medicine *arr,int size){
    int max=0;
    for(int i=0;i<size;i++){
        if(arr[i].id>max){
            max=arr[i].id;
        }
    }
    return max+1;
}

// add medicine




void addMedicine(medicine *&arr, int &size)
{
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

    medicine *temp = new medicine[size + 1];
    for (int i = 0; i < size; i++)
        temp[i] = arr[i];
    temp[size] = m;

    delete[] arr;
    arr = temp;
    size++;

    cout << "Medicine added.\n";
}

// sort by name
void sortByName(medicine* arr, int size) {
    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(strcmp(arr[j].name, arr[j+1].name) > 0) {
                medicine temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "Medicines sorted by name.\n";
}

// sort by price
void sortByPrice(medicine* arr, int size) {
    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(arr[j].price> arr[j+1].price)  {
                medicine temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "Medicines sorted by price"<<endl;
}
