//
// Created by muhammet on 11/22/20.
//

#include "IncidenceMatrix.h"
#include "vector"
#include "iostream"
#include "algorithm"

bool IncidenceMatrix::subset_check(std::vector<int> subset_1, const std::vector<int> &subset_2) {
    bool subset = true;
    for(const int & i: subset_2){
        if (!std::count(subset_1.begin(), subset_1.end(), i))
            subset = false;
    };
    return subset;
}

std::vector<std::vector<int>> IncidenceMatrix::getIncidenceMatrix(const std::vector<std::vector<int>> &klets,
                                                                  const std::vector<std::vector<int>> &columns) {
    std::vector<std::vector<int>> IncidenceArray;

    for(int i=0; i<klets.size(); i++){
        std::vector<int> temp_row;
        for(int j=0; j< columns.size(); j++){
            if(subset_check(klets[i],columns[j])){
                temp_row.push_back(true);
            }
            else{
                temp_row.push_back(false);
            }
        }
        IncidenceArray.push_back(temp_row);
    }

    return IncidenceArray;
}

std::vector<std::vector<int>> IncidenceMatrix::getSets(std::vector<std::vector<int>> incidence_matrix) {
    std::vector<std::vector<int>> sol;
    for(auto & i : incidence_matrix){
        std::vector<int> row;
        for(int j=0; j< i.size();j++){
            if(i[j]){
                row.push_back(j+1);
            }
        }
        sol.push_back(row);
    }
    return sol;
}
