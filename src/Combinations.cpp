//
// Created by muhammet on 11/22/20.
//
#include <iostream>
#include "vector"
#include "algorithm"
#include "Combinations.h"


std::vector<std::vector<int>> Combinations::combs(int n, int r) {
    std::vector<bool> v(n);
    std::fill(v.end() - r, v.end(), true);
    std::vector<std::vector<int>> sol;
    do {
        std::vector<int> row;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                row.push_back(i+1);
            }
        }
        sol.push_back(row);
    } while (std::next_permutation(v.begin(), v.end()));
    return sol;
}
