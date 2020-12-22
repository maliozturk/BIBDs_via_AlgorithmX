//
// Created by muhammet on 12/20/20.
//

#ifndef DESIGNTOGRAPH_GRAPH_H
#define DESIGNTOGRAPH_GRAPH_H
#include "map"

struct Vertice{
    int id;
    std::vector<int> adjs;
};

class Graph{
public:
    std::vector<Vertice> Vertices;
    //std::vector<std::map<Vertice,Vertice>> Edges;
    std::vector<std::vector<int>> Edges;
    void addEdge_between_vertices(Vertice a, int b){
        a.adjs.push_back(b);
        Edges.push_back({a.id,b});
        //Edges.emplace_back(a,b);
    };
    Graph(const std::vector<Vertice>& vertices, std::vector<std::vector<int>> blocks){
        Vertices = vertices;
        std::vector<int> block_ids;
        block_ids.reserve(blocks.size());
        for(int i=0; i<blocks.size(); i++){
            block_ids.push_back(i);
        }
        for(const auto& vertice_a:vertices){
            for(auto vertice_b: blocks[vertice_a.id]){
                addEdge_between_vertices(vertice_a, vertice_b);
            }
        }
    }
};

#endif //DESIGNTOGRAPH_GRAPH_H
