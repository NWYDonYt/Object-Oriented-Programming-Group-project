#ifndef FOODITEM_H
#define FOODITEM_H

#include "Product.h"
#include <string>
using namespace std;
class FoodItem : public Product {
private:
    bool isBeverage;
    string portionSize;

public:
    FoodItem(){
        isBeverage = false;
        portionSize = "Regular";
    };
    FoodItem(int id, const string& name, double price, int stock, bool beverage, const string& portion = "Regular"){
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
        isBeverage = beverage;
        portionSize = portion;
    };
    FoodItem(const FoodItem& other){
        this->id = other.id;
        this->name = other.name;
        this->price = other.price;
        this->stock = other.stock;
        isBeverage = other.isBeverage;
        portionSize = other.portionSize;
    };
    // Accessors
    bool getIsBeverage(){
        return isBeverage;
    };
    string getPortionSize(){
        return portionSize;
    };
    // Mutators with validation
    void setIsBeverage(bool beverage){
            this->isBeverage = beverage;
    };
    void setPortionSize(const string& portion){
        this->portionSize = portion;
    };


    
    // Polymorphic methods
    virtual void describe() const override;
    virtual string getProductType() const override;

    // Storable interface methods
    virtual string toRecord() const override;
    virtual void fromRecord(const string& record) override;
};

#endif // FOODITEM_H
