//
// Created by muhammet on 11/22/20.
//

#ifndef BLOCK_DESIGNS_V_ALGORITHMX_INCIDENCEMATRIX_H
#define BLOCK_DESIGNS_V_ALGORITHMX_INCIDENCEMATRIX_H

#include "iostream"
#include <vector>

class IncidenceMatrix {
public:
    static bool subset_check(std::vector<int> subset_1, const std::vector<int>& subset_2);
    static std::vector<std::vector<int>> getIncidenceMatrix(const std::vector<std::vector<int>>& klets, const std::vector<std::vector<int>>& columns);
    static std::vector<std::vector<int>> getSets(std::vector<std::vector<int>> incidence_matrix);
};


#endif //BLOCK_DESIGNS_V_ALGORITHMX_INCIDENCEMATRIX_H
