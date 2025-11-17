#include "medicineStruct.h"
#include <iostream>
#include "inventory.h"
#include "expiry.h"
#include "billstruct.h"
#include <cstring>
#include <fstream>
using namespace std;


void addItemToBill(bill&bill,medicine*arr,int size){
    int id, qty;
    cout<<"enter medicine id: "<<endl;
    cin>>id;
    int index=searchByID(arr,size,id);
        if(index==-1){
            cout<<"medicine not found!"<<endl;
            return;
        }
    cout<<"enter quantity to buy"<<endl;
    cin>>qty;
    if(qty>arr[index].quantity){
        cout<<"not enough stock"<<endl;
        return;
    }
    billItem item;
    item.medId=arr[index].id;
    strcpy(item.name,arr[index].name);
    item.price=arr[index].price;
    item.quantity=qty;
    item.total=qty*item.price;
    bill.items[bill.itemCount++]=item;
    cout<<"item added to bill "<<endl;

}

float calculateTotal(bill& bill){
    float sum=0;
    for(int i=0;i<bill.itemCount;i++){
        sum+=bill.items[i].total;
       
    }
     bill.total=sum;
        return sum;
}

void discount(bill& bill,float percent)
{
    bill.discount=(bill.total*percent)/100.0;
    bill.finalAmount=bill.total-bill.discount;
}

void printBill(bill bill) {
    cout << "BILL"<<endl;
    for(int i = 0; i < bill.itemCount; i++) {
        cout << bill.items[i].name << " x " << bill.items[i].quantity
             << " = " << bill.items[i].total << endl;
    }
    cout << "Total: " << bill.total << endl;
    cout << "Discount: " << bill.discount << endl;
    cout << "Final Amount: " << bill.finalAmount << endl;
}

void reduceStock(medicine* arr, int size, bill bill) {
    for(int i = 0; i < bill.itemCount; i++) {
        int id = bill.items[i].medId;
        int index = searchByID(arr, size, id);

        if(index != -1) {
            arr[index].quantity -= bill.items[i].quantity;
        }
    }
}

void saveBillToFile(bill bill) {
    ofstream out("bills.txt", ios::app);

    out << "Bill #" << bill.billNo << endl;
    for(int i = 0; i < bill.itemCount; i++) {
        out << bill.items[i].name << " "
            << bill.items[i].quantity << " "
            << bill.items[i].total << endl;
    }
    out << "Total: " << bill.total << endl;
    out << "Discount: " << bill.discount << endl;
    out << "Final: " << bill.finalAmount << endl;
    

    out.close();
}