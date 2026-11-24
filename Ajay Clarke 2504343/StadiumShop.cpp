#include "StadiumShop.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

StadiumShop::StadiumShop()
    : totalRevenue(0.0), totalTaxCollected(0.0), totalItemsSold(0) {}

StadiumShop::~StadiumShop() {
    clearInventory();
}
void StadiumShop::clearInventory() {
    for (size_t i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
}
void StadiumShop::addProduct(Product* product) {
    if (!product) {
        throw InvalidDataException("Cannot add null product to shop.");
    }
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getProductId() == product->getProductId()) {
            throw InvalidDataException("Product with ID " + FileManager::toText(product->getProductId()) + " already exists in shop inventory.");
        }
    }
    inventory.push_back(product);
}
bool StadiumShop::removeProduct(int productId) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getProductId() == productId) {
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    return false;
}
Product* StadiumShop::findProduct(int productId) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getProductId() == productId) {
            return inventory[i];
        }
    }
    return nullptr;
}
const Product* StadiumShop::findProduct(int productId) const {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getProductId() == productId) {
            return inventory[i];
        }
    }
    return nullptr;
}
void StadiumShop::restock(int productId, int quantity) {
    if (quantity <= 0) {
        throw NegativeValueException("Restock quantity must be positive. Provided: " + FileManager::toText(quantity));
    }
    Product* p = findProduct(productId);
    if (!p) {
        throw ProductNotFoundException("Product ID " + FileManager::toText(productId) + " not found in shop inventory.");
    }
    p->addStock(quantity);
}
void StadiumShop::displayInventory() const {
    std::cout << "\n================= KPFL STADIUM SHOP INVENTORY =================\n";
    if (inventory.empty()) {
        std::cout << "No products currently stocked in the stadium shop.\n";
    } else {
        for (size_t i = 0; i < inventory.size(); i++) {
            // Polymorphic call to describe()
            inventory[i]->describe();
        }
    }
    std::cout << "===============================================================\n";
}
const std::vector<Product*>& StadiumShop::getInventory() const {
    return inventory;
}
string StadiumShop::completeSale(int productId, int quantity, double paymentAmount,
                                      double& outSubtotal, double& outTax, double& outTotal, double& outChange) {
    if (quantity <= 0) {
        throw NegativeValueException("Purchase quantity must be positive. Provided: " + FileManager::toText(quantity));
    }
    if (paymentAmount < 0.0) {
        throw NegativeValueException("Payment amount cannot be negative.");
    }

    Product* p = findProduct(productId);
    if (!p) {
        throw ProductNotFoundException("Product ID " + FileManager::toText(productId) + " not found.");
    }

    if (quantity > p->getStock()) {
        throw InvalidDataException("Insufficient stock: Requested " + FileManager::toText(quantity) +
                                   ", but only " + FileManager::toText(p->getStock()) + " available.");
    }

    outSubtotal = p->getPrice() * quantity;
    outTax = outSubtotal * SHOP_GCT_RATE;
    outTotal = outSubtotal + outTax;

    if (paymentAmount < outTotal) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "Payment $" << paymentAmount << " is insufficient for total bill of $" << outTotal
           << " (Short by $" << (outTotal - paymentAmount) << ").";
        throw InsufficientPaymentException(ss.str());
    }

    outChange = paymentAmount - outTotal;

    // Deduct stock
    p->reduceStock(quantity);

    // Update shop financials
    totalRevenue += outTotal;
    totalTaxCollected += outTax;
    totalItemsSold += quantity;

    // Build printed receipt
    std::stringstream receipt;
    receipt << "\n========================================\n";
    receipt << "       KPFL STADIUM SHOP RECEIPT        \n";
    receipt << "========================================\n";
    receipt << "Item:     " << p->getName() << " (" << p->getProductType() << ")\n";
    receipt << "Unit:     $" << std::fixed << std::setprecision(2) << p->getPrice() << "\n";
    receipt << "Quantity: " << quantity << "\n";
    receipt << "----------------------------------------\n";
    receipt << "Subtotal: $" << outSubtotal << "\n";
    receipt << "15% GCT:  $" << outTax << "\n";
    receipt << "TOTAL:    $" << outTotal << "\n";
    receipt << "Paid:     $" << paymentAmount << "\n";
    receipt << "Change:   $" << outChange << "\n";
    receipt << "========================================\n";

    return receipt.str();
}

double StadiumShop::getTotalRevenue() const {
    return totalRevenue;
}
double StadiumShop::getTotalTaxCollected() const {
    return totalTaxCollected;
}
int StadiumShop::getTotalItemsSold() const {
    return totalItemsSold;
}
void StadiumShop::setFinancials(double revenue, double tax, int itemsSold) {
    totalRevenue = revenue;
    totalTaxCollected = tax;
    totalItemsSold = itemsSold;
}

void StadiumShop::displayFinancialSummary() const {
    std::cout << "\n================ SHOP FINANCIAL AUDIT ================\n";
    std::cout << "Total Items Sold:    " << totalItemsSold << "\n";
    std::cout << "Total 15% GCT Tax:   $" << std::fixed << std::setprecision(2) << totalTaxCollected << "\n";
    std::cout << "Total Gross Revenue: $" << totalRevenue << "\n";
    std::cout << "Net Revenue:         $" << (totalRevenue - totalTaxCollected) << "\n";
    std::cout << "======================================================\n";
}
