#ifndef billstruct_h
#define billstruct_h
struct billItem{
    int medId;
    char name[50];
    float price;
    int quantity;
    float total;
};
struct bill{
    int billNo;
    billItem items[50];
    int itemCount;
    float total;
    float discount;
    float finalAmount;

};
#endif