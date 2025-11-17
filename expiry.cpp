#include "medicineStruct.h"
#include "inventory.h"
#include <iostream>
using namespace std;

// check if medicine is expired

bool isExpired(medicine m,int cDay,int cMonth,int cYear){
    if(m.expYear<cYear){
        return true;
    }
    if(m.expYear==cYear && m.expMonth<cMonth){
        return true;
    }
    if(m.expYear==cYear && m.expMonth==cMonth&& m.expDay<cDay){
        return true;
    }
    return false;
}

// list of all expired medicines

void listOfExpiredMeds(medicine *arr,int size){
    int cDay,cMonth,cYear;
    cout<<" enter today's day: "<<endl;
    cin>>cDay;
    cout<<" enter today's month: "<<endl;
    cin>>cMonth;
    cout<<" enter today's year: "<<endl;
    cin>>cYear;

    cout<<"Expired medicines are : "<<endl;
    bool found=false;
    for(int i=0;i<size;i++){
        if(isExpired(arr[i],cDay,cMonth,cYear)){
            found =true;

             cout<<"ID: "<<arr[i].id<<endl;
    cout<<"Name: "<<arr[i].name<<endl;
    cout<<"Expired on : "<<arr[i].expDay<<"/"<<arr[i].expMonth<<"/"<<arr[i].expYear<<endl;
   
        }
    }

}

// remove expired medicines
void removeExpired(medicine*&arr,int &size){
      int cDay,cMonth,cYear;
    cout<<" enter today's day: "<<endl;
    cin>>cDay;
    cout<<" enter today's month: "<<endl;
    cin>>cMonth;
    cout<<" enter today's year: "<<endl;
    cin>>cYear;

    int newSize=0;
    for(int i=0;i<size;i++){
        if(!isExpired(arr[i],cDay,cMonth,cYear)){
            newSize++;
        }
    }

    if(newSize==size){cout<<"no expired medicine to remove!"<<endl;
    return;}

    medicine *temp =new medicine[newSize];
    int index=0;
    for(int i=0;i<size;i++){
          if(!isExpired(arr[i],cDay,cMonth,cYear)){
            temp[index++]=arr[i];
          }
    }
    delete []arr;
    arr=temp;
    size=newSize;
    cout<<"expired medicines removed successfully"<<endl;

}

// near to expire medicines
bool isNearExpiry(const medicine &m,int cDay,int cMonth,int cYear,int check){
int expT=m.expYear*12+m.expMonth;
int currT=cYear*12+cMonth;
return (expT-currT)<=check&& (expT >= currT);
}
void showNearExpiry(medicine*arr,int size){
       int cDay,cMonth,cYear,check;
    cout<<" enter today's day: "<<endl;
    cin>>cDay;
    cout<<" enter today's month: "<<endl;
    cin>>cMonth;
    cout<<" enter today's year: "<<endl;
    cin>>cYear;
cout<<"enter number of months to check(e.g 3): "<<endl;
cin>>check;

cout<<"Medicine near to expiry are: "<<endl;
bool found=false;
for(int i=0;i<size;i++){
    if(isNearExpiry(arr[i],cDay,cMonth,cYear,check)){
        displayMedicine(arr[i]);
        found =true;
    }
}
if(!found){
    cout<<"no medicines near expiry "<<endl;
}
}


bool blockSale(medicine &m,int cDay,int cMonth,int cYear){
    if(isExpired(m,cDay,cMonth,cYear)){
        cout<<"sales blocked "<<endl;
        cout<<m.name<<" is expired "<<endl;
        return true;
    }
    return false;
}