#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include "Graph.h"
template <typename Item>
class WeightedGraph:public Graph<Item>{
private:
    int** _weights;

    int minD(int distance[], bool spt[]){
        int min = INT_MAX, m;
        for(int i = 0; i < size(); ++i){
            if(!spt[i] && distance[i] <= min){
                min = distance[i];
                m = i;
            }
        }
        return m;
    }

public:
    WeightedGraaph(std::size_t size = 0):Graph<Item>(size){
        Graph<Item>::allocate2D(_weights,size);
    }
    void addEdge(std::size_t source, std::size_t target, int weight){
        Graph<Item>::addEdge(source,target);
        _weights[source][target] = weight;
    }
    friend std::ostream& operator <<(std::ostream& out, const WeightedGraph<Item>& G){
            out << "   ";
            for(std::size_t i = 0; i < G.size(); ++i){
                out << G.Graph<Item>::_labels[i] << "|";
            }
            out  << std::endl;
            for(std::size_t i = 0; i < G.size(); ++i){
                out << G._labels[i] << ":|";
                for(std::size_t j = 0; j < G.size(); ++j){
                    if(G._edges[i][j])
                        out << G._weights[i][j] << "|";
                    else
                        out << " " << "|";
                }
                out << std::endl;
            }

            return out;
    }
    std::set<int> shortestDistance(std::size_t start){
//        int distance[size()];
//        std::fill_n(distance,size(),-1); //-1 denotes infinity, 0 denotes the same, -2 denotes impossible
//        distance[start] = 0;
//        std::set<std::size_t> allowed;
//        int allowedSize = 0;
//        for(allowedSize = 1; allowedSize < size(); ++allowedSize){
//            allowed.insert(*neighbors(start).begin());
//        }
        int distance[size()];
        bool spt[size()];
        for(std::size_t i = 0; i < size(); ++i){
            distance[i] = INT_MAX;//infinite
            spt[i] = false;
        }
        distance[start] = 0;
        for(int i = 0; i < size() - 1; ++i){
            int min = minD(distance,spt);
            spt[min] = true;
            for(int j = 0; j < size(); ++j){
                if(!spc[j] && Graph<Item>::isEdge(min,j) && distance[min] != INT_MAX &&
                        distance[min] + _weights[min][j] < distance[j]){
                    distance[j] = distance[min] + _weights[min][j];
                }
            }
        }
        std::set<int> s;
        for(std::size_t i = 0; i < size(); ++i){
            s.insert(distance[i]);
        }
        return s;

    }
}
#endif // WEIGHTEDGRAPH_H
