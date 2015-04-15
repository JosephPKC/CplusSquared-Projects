#ifndef LABELLEDGRAPH_H
#define LABELLEDGRAPH_H
#include "Graph.h"
template <typename Item, typename Label>
class LabelledGraph : public Graph<Item>{
private:
    Label** _edgeLabels;
public:
    //Constructors
    LabelledGraph(std::size_t size = 0):Graph<Item>(size){
        Graph<Item>::allocate2D(_edgeLabels,size);
    }
    //Add an edge with a label
    void addEdge(std::size_t source, std::size_t target, const Label& label){
        Graph<Item>::addEdge(source,target);
        _edgeLabels[source][target] = label;
    }
    //Output
    friend std::ostream& operator <<(std::ostream& out, const LabelledGraph<Item,Label>& G){
            out << "   ";
            for(std::size_t i = 0; i < G.size(); ++i){
                out << G.Graph<Item>::_labels[i] << "|";
            }
            out  << std::endl;
            for(std::size_t i = 0; i < G.size(); ++i){
                out << G._labels[i] << ":|";
                for(std::size_t j = 0; j < G.size(); ++j){
                    if(G._edges[i][j])
                        out << G._edgeLabels[i][j] << "|";
                    else
                        out << " " << "|";
                }
                out << std::endl;
            }

            return out;
    }
};
#endif // LABELLEDGRAPH_H
