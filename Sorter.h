#ifndef SORTER_H
#define SORTER_H

#include "Product.h"
#include <vector>
#include <iostream>
#include <functional>
#include <chrono>
#include <iomanip>

class Sorter {
private:
    void siftDown(std::vector<Product>& a, int n, int i, const std::function<bool(const Product&, const Product&)>& less, bool verbose, int& pass) {
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && less(a[largest], a[left])) largest = left;
            if (right < n && less(a[largest], a[right])) largest = right;
            if (largest == i) break;

            std::swap(a[i], a[largest]);

            if (verbose) {
                std::cout << "\n  [Step " << ++pass << "] Sift-Down Swap (Price "
                          << std::fixed << std::setprecision(2) << a[largest].getPrice() << " moved down)\n";
                printTable(a);
            }
            i = largest;
        }
    }

    void printTable(const std::vector<Product>& v) const {
        std::cout << "  +-----+--------------+------------+-------+-------+\n";
        std::cout << "  | ID  | Name         | Price(MWK) | Stock | Sales |\n";
        std::cout << "  +-----+--------------+------------+-------+-------+\n";
        for (const auto& p : v) {
            std::cout << "  | " << p << " |\n";
        }
        std::cout << "  +-----+--------------+------------+-------+-------+\n";
    }

public:
    void heapSort(std::vector<Product>& a, std::function<bool(const Product&, const Product&)> less, bool verbose = false) {
        int n = (int)a.size();
        int pass = 0;

        for (int i = n / 2 - 1; i >= 0; --i) {
            siftDown(a, n, i, less, verbose, pass);
        }

        if (verbose) {
            std::cout << "\n  >>> Heap built successfully. Largest price is at the root. <<<\n";
            printTable(a);
            std::cout << "\n  >>> Starting Extraction Phase (Moving max to the end) <<<\n";
        }

        for (int end = n - 1; end > 0; --end) {
            std::swap(a[0], a[end]);
            if (verbose) {
                std::cout << "\n  [Pass " << (n - end) << "] Extract Max (Swapped root to end of unsorted section)\n";
                printTable(a);
            }
            siftDown(a, end, 0, less, verbose, pass);
        }
    }

    void sortByPrice(std::vector<Product>& a, bool verbose = false) {
        heapSort(a, [](const Product& x, const Product& y) { return x.getPrice() < y.getPrice(); }, verbose);
    }

    void sortByID(std::vector<Product>& a) {
        heapSort(a, [](const Product& x, const Product& y) { return x.getProductID() < y.getProductID(); });
    }

    void sortBySales(std::vector<Product>& a) {
        heapSort(a, [](const Product& x, const Product& y) { return x.getSalesCount() < y.getSalesCount(); });
    }

    template <typename SortFn>
    double timeSort(SortFn fn) {
        auto start = std::chrono::high_resolution_clock::now();
        fn();
        auto stop = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(stop - start).count();
    }
};

#endif