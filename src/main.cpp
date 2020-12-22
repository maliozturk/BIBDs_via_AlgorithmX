#include <iostream>
#include "vector"
#include "Combinations.h"
#include "IncidenceMatrix.h"
#include "fstream"
#include <pthread.h>
#include <cstdlib>
#include "Graph.h"
#include "AlgorithmX.h"


int main() {
    std::vector<std::vector<int>> todo_list;
    // Add values {v,k}s to solve them.
    todo_list.push_back({13,4});
    todo_list.push_back({7,3});
    todo_list.push_back({8,3});
    todo_list.push_back({13,9});
    todo_list.push_back({9,3});
    todo_list.push_back({7,4});

    for(auto& todo:todo_list){
        SOLUTION_COUNT = 0;
        AlgorithMX::solve_design_problem(todo);
        std::ofstream myFile;
        myFile.open("results.txt", std::ios_base::app);
        myFile << SOLUTION_COUNT << " solutions found for " <<"("<<todo[0]<<","<<todo[1]<<",1)"<<" design.\n";
        myFile.close();
        std::cout << SOLUTION_COUNT << " solutions found for " <<"("<<todo[0]<<","<<todo[1]<<",1)"<<" design."<<std::endl;
    }



    // Testing graph with seven point plane example:
    /*
    std::vector<int> P = {0,1,2,3,4,5,6};
    std::vector<std::vector<int>> B = {{0,1,3},{1,2,4},{2,3,5},{3,4,6},{4,5,0},{5,6,1},{6,0,2}};

    std::vector<Vertice> vertices;
    for(auto i:P){
        Vertice a;
        a.id = i;
        vertices.push_back(a);
    }
    Graph graph_adj_to_nodes = Graph(vertices,B);

    std::cout << "Vertices in graph:";
    for(const auto& vertice: graph_adj_to_nodes.Vertices){
        std::cout << vertice.id << ",";
    }
    std::cout << "\nEdges in graph (Not Directed):\n";
    for(auto edge: graph_adj_to_nodes.Edges){
        for(int i:edge){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
     */
    return 0;
}

[[maybe_unused]] void getDesign_of_Solution(const std::vector<int> &nds, std::vector<std::vector<int>> design, int k) {
    for (int i: nds) {
        std::cout << "[";
        for (int j = 0; j < k; j++) {
            if (j == k - 1)
                std::cout << design[i][j];
            else
                std::cout << design[i][j] << ",";
        }
        std::cout << "]," << std::endl;
    }
}

/*
    void plus_Sol_Count()
    {


        ofstream myfile;
        myfile.open("7-3-1_results.txt", std::ios_base::app);
        std::vector<struct Node*>::iterator i;
        for(i = solutions.begin(); i!=solutions.end(); i++) {
            myfile << (*i)->rowID << " ";
        }
        myfile<<"\n";


    }
*/