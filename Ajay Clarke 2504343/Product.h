#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include "Storable.h"

// Abstract superclass for all items sold in the stadium shop
class Product : public Storable {
protected:
    int productId;
    std::string name;
    double price;
    int stock;

public:
    static constexpr double GCT_RATE = 0.15; // 15% General Consumption Tax

    Product();
    Product(int id, const std::string& productName, double productPrice, int initialStock);
    virtual ~Product() {}

    // Accessors
    int getProductId() const;
    std::string getName() const;
    double getPrice() const;
    int getStock() const;

    // Mutators with validation
    void setProductId(int id);
    void setName(const std::string& newName);
    void setPrice(double newPrice);
    void setStock(int newStock);
    void addStock(int quantity);
    void reduceStock(int quantity);

    // Tax calculation
    virtual double calculateTax(int quantity = 1) const;
    virtual double calculateTotal(int quantity = 1) const;

    // Pure virtual methods
    virtual void describe() const = 0;
    virtual std::string getProductType() const = 0;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // PRODUCT_H
