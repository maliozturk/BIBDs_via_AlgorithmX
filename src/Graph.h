//
// Created by muhammet on 12/20/20.
//

#ifndef DESIGNTOGRAPH_GRAPH_H
#define DESIGNTOGRAPH_GRAPH_H

class Dugum{
public:
    int _id;
    std::vector<std::vector<int>> komsular;
    void komsu_ekle(const std::vector<int>& block){
        komsular.push_back(block);
    };
    explicit Dugum(int id){
        _id = id;
    }
};

void edgeEkle(int d, const std::vector<int>& block){
    Dugum p = Dugum(d);
    p.komsu_ekle(block);
}

bool isIncluding(int p, std::vector<int> B){
    bool included = false;
    for(auto i:B){
        if(i==p){
            included = true;
        }
    }
    return included;
};


struct EdgeMap{
    int node;
    std::vector<int> Block;
};

class Graph{
public:
    std::vector<int> _points;
    std::vector<std::vector<int>> _blocks;
    std::vector<EdgeMap> _edges;
    Graph(std::vector<int> points, std::vector<std::vector<int>> blocks){
        _points = points;
        _blocks = blocks;
    }
    void drawGraph(){
        for(auto point: _points){
            for(auto block: _blocks){
                if(isIncluding(point,block)){
                    edgeEkle(point,block);
                    EdgeMap e;
                    e.node = point;
                    e.Block = block;
                    _edges.push_back(e);
                }
            }
        }
    }
};

#endif //DESIGNTOGRAPH_GRAPH_H
