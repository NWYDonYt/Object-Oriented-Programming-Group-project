#include "Product.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>

Product::Product() : productId(0), name("Unnamed Product"), price(0.0), stock(0) {}

Product::Product(int id, const std::string& productName, double productPrice, int initialStock) {
    setProductId(id);
    setName(productName);
    setPrice(productPrice);
    setStock(initialStock);
}
int Product::getProductId()  {
    return productId;
}
string Product::getName() {
    return name;
}
double Product::getPrice() {
    return price;
}
int Product::getStock() {
    return stock;
}

void Product::setProductId(int id) {
    if (id < 0) {
        throw InvalidDataException("Product ID cannot be negative.");
    }
    productId = id;
}
void Product::setName(const string& newName) {
    if (newName.empty()) {
        throw InvalidDataException("Product name cannot be empty.");
    }
    name = newName;
}
void Product::setPrice(double newPrice) {
    if (newPrice < 0.0) {
        throw NegativeValueException("Product price cannot be negative. Provided: " + FileManager::toText(newPrice));
    }
    price = newPrice;
}
void Product::setStock(int newStock) {
    if (newStock < 0) {
        throw NegativeValueException("Stock quantity cannot be negative. Provided: " + FileManager::toText(newStock));
    }
    stock = newStock;
}
void Product::addStock(int quantity) {
    if (quantity < 0) {
        throw NegativeValueException("Restock quantity cannot be negative.");
    }
    stock += quantity;
}
void Product::reduceStock(int quantity) {
    if (quantity < 0) {
        throw NegativeValueException("Quantity cannot be negative.");
    }
    if (quantity > stock) {
        throw InvalidDataException("Insufficient inventory: requested " + FileManager::toText(quantity) +
                                   ", but only " + FileManager::toText(stock) + " available.");
    }
    stock -= quantity;
}
double Product::calculateTax(int quantity) const {
    return (price * quantity) * GCT_RATE;
}
double Product::calculateTotal(int quantity) const {
    double subtotal = price * quantity;
    return subtotal + calculateTax(quantity);
}

// Write to file 
string Product::toRecord() const {
    vector<string> fields;

    fields.push_back(getProductType());
    fields.push_back(FileManager::toText(productId));
    fields.push_back(name);
    fields.push_back(FileManager::toText(price));
    fields.push_back(FileManager::toText(stock));

    return FileManager::joinFields(fields);
}

// Read to file
void Product::fromRecord(const string& record) {
    vector<string> fields = FileManager::splitFields(record);

    if (fields.size() < 5) {
        throw FileException("Product record requires at least 5 fields: " + record);
    }

    setProductId(FileManager::toInt(fields[1]));
    setName(fields[2]);
    setPrice(FileManager::toDouble(fields[3]));
    setStock(FileManager::toInt(fields[4]));
}
