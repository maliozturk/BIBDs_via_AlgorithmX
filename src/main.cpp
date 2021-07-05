#include <iostream>
#include "vector"
#include "Combinations.h"
#include "IncidenceMatrix.h"
#include "fstream"
#include <cstdlib>
#include "Graph.h"
#include "AlgorithmX.h"


int main() {
    std::vector<std::vector<int>> todo_list;
    /// Add values {v,k}s to todo_list to find {v,k,1}-designs.

    todo_list.push_back({7,3});
    todo_list.push_back({11,4});
    todo_list.push_back({13,4});
    // todo_list.push_back({13,4});

    for(auto& todo:todo_list){
        SOLUTION_COUNT = 0;
        AlgorithMX::solve_design_problem(todo);
        std::cout << SOLUTION_COUNT << " solutions found for " <<"("<<todo[0]<<","<<todo[1]<<",1)"<<" design."<<std::endl;
    }
    
    return 0;
}