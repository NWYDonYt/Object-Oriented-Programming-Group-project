#include "Merchandise.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>

Merchandise::Merchandise()
    :Product(0, "Club Merchandise", 0.0, 0), itemType("Jersey"), size("Standard") {}

Merchandise::Merchandise(int id, const string& name, double price, int stock,
                         const string& type, const string& itemSize)
    :Product(id, name, price, stock) {
    setItemType(type);
    setSize(itemSize);
}

Merchandise::Merchandise(const Merchandise& other)
    :Product(other.productId, other.name, other.price, other.stock),
      itemType(other.itemType), size(other.size) {}

string Merchandise::getItemType() {
    return itemType;
}

string Merchandise::getSize() {
    return size;
}

void Merchandise::setItemType(const string& type) {
    if (type.empty()) {
        throw InvalidDataException("Merchandise item type cannot be empty.");
    }
    itemType = type;
}

void Merchandise::setSize(const string& itemSize) {
    if (itemSize.empty()) {
        throw InvalidDataException("Merchandise size cannot be empty.");
    }
    size = itemSize;
}

void Merchandise::describe() const {
    cout << "[Merchandise] ID: " << productId
              << " | Name: " << name
              << " | Type: " << itemType
              << " | Size: " << size
              << " | Price: $" << std::fixed << std::setprecision(2) << price
              << " (excl. 15% GCT: $" << calculateTax() << ")"
              << " | Stock: " << stock << std::endl;
}

string Merchandise::getProductType() const {
    return "Merchandise";
}

string Merchandise::toRecord() const {
    vector<string> fields;
    fields.push_back("Merchandise");
    fields.push_back(FileManager::toText(productId));
    fields.push_back(name);
    fields.push_back(FileManager::toText(price));
    fields.push_back(FileManager::toText(stock));
    fields.push_back(itemType);
    fields.push_back(size);
    return FileManager::joinFields(fields);
}

void Merchandise::fromRecord(const string& record) {
    vector<string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("Merchandise record requires 7 fields: " + record);
    }
    setProductId(FileManager::toInt(fields[1]));
    setName(fields[2]);
    setPrice(FileManager::toDouble(fields[3]));
    setStock(FileManager::toInt(fields[4]));
    setItemType(fields[5]);
    setSize(fields[6]);
}
