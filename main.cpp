#include "Product.h"
#include "DatasetGenerator.h"
#include "Sorter.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

void demonstrateOn10Products() {
    // Realistic MWK prices from the ChatGPT code
    std::vector<Product> demo = {
        {101, "Laptop",       850000.00, 15, 120},
        {102, "Phone",        450000.00, 30, 250},
        {103, "Headphones",    75000.00, 50, 180},
        {104, "Keyboard",      55000.00, 40, 90},
        {105, "Mouse",         25000.00, 60, 300},
        {106, "Monitor",      320000.00, 20, 75},
        {107, "Printer",      280000.00, 12, 65},
        {108, "Tablet",       390000.00, 18, 110},
        {109, "Speaker",       95000.00, 35, 140},
        {110, "Flash Drive",   15000.00, 100, 400}
    };

    std::cout << "\n========================================================================\n";
    std::cout << "  SECTION B: HEAP SORT DEMONSTRATION (10 PRODUCTS, SORT BY PRICE)\n";
    std::cout << "========================================================================\n\n";
    
    std::cout << "INITIAL STATE:\n";
    
    // Print the initial table
    std::cout << "  +-----+--------------+------------+-------+-------+\n";
    std::cout << "  | ID  | Name         | Price(MWK) | Stock | Sales |\n";
    std::cout << "  +-----+--------------+------------+-------+-------+\n";
    for (const auto& p : demo) {
        std::cout << "  | " << p << " |\n";
    }
    std::cout << "  +-----+--------------+------------+-------+-------+\n";

    Sorter s;
    s.sortByPrice(demo, true); // Run with verbose table mode

    std::cout << "\n========================================================================\n";
    std::cout << "FINAL SORTED VECTOR (Lowest Price to Highest):\n";
    std::cout << "========================================================================\n";
    std::cout << "  +-----+--------------+------------+-------+-------+\n";
    std::cout << "  | ID  | Name         | Price(MWK) | Stock | Sales |\n";
    std::cout << "  +-----+--------------+------------+-------+-------+\n";
    for (const auto& p : demo) {
        std::cout << "  | " << p << " |\n";
    }
    std::cout << "  +-----+--------------+------------+-------+-------+\n\n";
}

void runPerformance() {
    DatasetGenerator gen(42);
    Sorter sorter;
    std::ofstream csv("results.csv");
    csv << "datatype,datasetSize,SortCriterion,ExecutionTime(ms)\n";

    std::vector<int> sizes = {5000, 10000, 50000};
    std::vector<std::string> datatypes = {"Random", "NearlySorted", "ReverseSorted"};

    std::cout << "========================================================================\n";
    std::cout << "  SECTION C: PERFORMANCE ANALYSIS (This may take a few seconds...)\n";
    std::cout << "========================================================================\n\n";

    for (int n : sizes) {
        auto randomData  = gen.generateRandom(n);
        auto nearlyData  = gen.generateNearlySorted(n);
        auto reverseData = gen.generateReverseSorted(n);

        struct Entry { const std::string* name; std::vector<Product>* data; };
        Entry entries[3] = {
            {&datatypes[0], &randomData},
            {&datatypes[1], &nearlyData},
            {&datatypes[2], &reverseData}
        };

        std::cout << "--- Dataset Size: " << n << " elements ---\n";
        for (auto& e : entries) {
            std::vector<Product> work;
            std::cout << "  " << std::setw(15) << std::left << *e.name << std::right << " | ";

            work = *e.data;
            double tPrice = sorter.timeSort([&]{ sorter.sortByPrice(work); });
            csv << *e.name << "," << n << ",price," << std::fixed << std::setprecision(4) << tPrice << "\n";
            std::cout << "Price: " << std::setw(7) << std::setprecision(2) << tPrice << " ms | ";

            work = *e.data;
            double tId = sorter.timeSort([&]{ sorter.sortByID(work); });
            csv << *e.name << "," << n << ",productID," << std::setprecision(4) << tId << "\n";
            std::cout << "ID: " << std::setw(7) << std::setprecision(2) << tId << " ms | ";

            work = *e.data;
            double tSales = sorter.timeSort([&]{ sorter.sortBySales(work); });
            csv << *e.name << "," << n << ",salesCount," << std::setprecision(4) << tSales << "\n";
            std::cout << "Sales: " << std::setw(7) << std::setprecision(2) << tSales << " ms\n";
        }
        std::cout << "\n";
    }

    csv.close();
    std::cout << "Results successfully saved to results.csv\n";
    std::cout << "========================================================================\n\n";
}

int main() {
    demonstrateOn10Products();
    runPerformance();
    return 0;
}