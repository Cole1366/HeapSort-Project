#ifndef DATASETGENERATOR_H
#define DATASETGENERATOR_H

#include "Product.h"
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class DatasetGenerator {
private:
    std::mt19937 rng;

    std::vector<Product> buildRandom(int n) {
        std::uniform_int_distribution<int> idDist(1, n * 10);
        std::uniform_real_distribution<double> priceDist(1.0, 1000.0);
        std::uniform_int_distribution<int> stockDist(0, 500);
        std::uniform_int_distribution<int> salesDist(0, 10000);

        std::vector<Product> data;
        data.reserve(n);
        for (int i = 0; i < n; ++i) {
            data.push_back(Product(idDist(rng), "Prod_" + std::to_string(i), priceDist(rng), stockDist(rng), salesDist(rng)));
        }
        return data;
    }

public:
    DatasetGenerator(unsigned seed = 42) : rng(seed) {}

    std::vector<Product> generateRandom(int n) {
        return buildRandom(n);
    }

    std::vector<Product> generateNearlySorted(int n) {
        auto data = buildRandom(n);
        std::sort(data.begin(), data.end(), [](const Product& a, const Product& b) { return a.getPrice() < b.getPrice(); });
        
        int swaps = std::max(1, n / 20); 
        std::uniform_int_distribution<int> idxDist(0, n - 1);
        for (int i = 0; i < swaps; ++i) {
            std::swap(data[idxDist(rng)], data[idxDist(rng)]);
        }
        return data;
    }

    std::vector<Product> generateReverseSorted(int n) {
        auto data = buildRandom(n);
        std::sort(data.begin(), data.end(), [](const Product& a, const Product& b) { return a.getPrice() < b.getPrice(); });
        std::reverse(data.begin(), data.end());
        return data;
    }
};

#endif