#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <iomanip>

class Product {
private:
    int productID;
    std::string productName;
    double price;
    int stockQuantity;
    int salesCount;

public:
    Product() : productID(0), productName(""), price(0.0), stockQuantity(0), salesCount(0) {}

    Product(int id, std::string name, double p, int stock, int sales)
        : productID(id), productName(name), price(p), stockQuantity(stock), salesCount(sales) {}

    int getProductID() const { return productID; }
    std::string getProductName() const { return productName; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    int getSalesCount() const { return salesCount; }

    // Formatting for the table
    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << std::setw(3) << p.productID << " | " 
           << std::setw(12) << std::left << p.productName << std::right << " | " 
           << std::setw(10) << std::fixed << std::setprecision(2) << p.price << " | " // Wider column for MWK prices
           << std::setw(5) << p.stockQuantity << " | " 
           << std::setw(5) << p.salesCount;
        return os;
    }
};

#endif