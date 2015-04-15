#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include "Graph.h"
template <typename Item>
class WeightedGraph:public Graph<Item>{
private:
    int** _weights;
    //Gets the minimum distance
    int minD(int distance[], bool spt[]){
        int min = INT_MAX, m;
        for(int i = 0; i < Graph<Item>::size(); ++i){
            if(!spt[i] && distance[i] <= min){
                min = distance[i];
                m = i;
            }
        }
        return m;
    }

public:
    WeightedGraph(std::size_t size = 0):Graph<Item>(size){
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
    //Gets a set of the shortest distances from the vertex to every other vertex
    std::set<int> shortestDistance(std::size_t start){
        int distance[Graph<Item>::size()];
        bool spt[Graph<Item>::size()];
        for(std::size_t i = 0; i < Graph<Item>::size(); ++i){
            distance[i] = INT_MAX;//infinite
            spt[i] = false;
        }
        distance[start] = 0;
        for(int i = 0; i < Graph<Item>::size() - 1; ++i){
            int min = minD(distance,spt);
            spt[min] = true;
            for(int j = 0; j < Graph<Item>::size(); ++j){
                if(!spt[j] && Graph<Item>::isEdge(min,j) && distance[min] != INT_MAX &&
                        distance[min] + _weights[min][j] < distance[j]){
                    distance[j] = distance[min] + _weights[min][j];
                }
            }
        }
        std::set<int> s;
        for(std::size_t i = 0; i < Graph<Item>::size(); ++i){
            s.insert(distance[i]);
        }
        return s;

    }
};
#endif // WEIGHTEDGRAPH_H
