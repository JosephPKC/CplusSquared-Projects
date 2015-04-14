#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <set>
#include <cassert>
struct Path{

};

template <typename Item>
class Graph{
protected:
//    bool edges[MAXIMUM][MAXIMUM];
//    Item labels[MAXIMUM];
//    std::size_t _vertices;
    bool** _edges;
    Item* _labels;
    std::size_t _allocated;
    std::size_t _vertices;
protected:
    void reallocate(std::size_t nSize){
        using namespace std;
//        cout << "Size in reallocate:" << nSize << endl;
        bool** edgeTemp = _edges;
//        for(std::size_t i = 0; i < size(); i++){
//            for(int j = 0; j < size(); j++){
//                cout << "Edge: " <<  edgeTemp[i][j] << endl;
//            }
//        }
//        cout << "edgetemp" << endl;
        Item* labelTemp = _labels;
//        cout << "labeltemp" << endl;
        allocate2D(_edges,nSize);
//        cout << "allocated2d" << endl;
        allocate(_labels,nSize);
//        cout << "allocated" << endl;
        initialize2D(_edges,nSize);
//        cout << "initialized2d" << endl;
//        for(std::size_t i = 0; i < size(); i++){
//            for(int j = 0; j < size(); j++){
//                cout << "Edge: " << edgeTemp[i][j] << endl;
//            }
//        }
//        cout << "Old size: " << size() << endl;
        for(std::size_t i = 0; i < size(); i++){
            copyPtr(edgeTemp[i],_edges[i],size());
        }
//        cout << "for end" << endl;
        copyPtr(labelTemp,_labels,size());
//        cout << "copyied" << endl;
        for(std::size_t i = 0; i < size(); i++){
            delete edgeTemp[i];
        }
        delete edgeTemp;
        delete labelTemp;
        _allocated = nSize;

    }

    void initialize(bool* array, std::size_t size){
        for(std::size_t i = 0; i < size; ++i){
            array[i] = false;
        }
    }
    void initialize2D(bool** array, std::size_t size){
//        std::cout << "Size: " << size << std::endl;
        for(std::size_t i = 0; i < size; ++i){
            initialize(array[i],size);
        }
    }
    template <typename Type>
    void allocate(Type*& array, std::size_t size){
        array = new Type[size];
    }
    template <typename Type>
    void allocate2D(Type**& array, std::size_t size){
        array = new Type*[size];
        for(std::size_t i = 0; i < size; ++i){
            allocate(array[i],size);
        }
    }
    template <typename Type>
    void copyPtr(Type* source, Type* dest, std::size_t size){
        using namespace std;
//        cout << "in copyptr" << endl;
        for(std::size_t i = 0; i < size; ++i){
            dest[i] = source[i];
        }
//        cout << "end copyptr" << endl;
    }

    template <typename Process>
    void dfs(Process f, std::size_t v, bool marked[]){
        std::set<std::size_t> connections = neighbors(v);
        std::set<std::size_t>::iterator it;
        marked[v] = true;
        f(g[v]);
        for(it = connections.begin(); it != connections.end(); ++it){
            if(!marked[*it])
                dfs(f,*it,marked);
        }
    }


public:
//    static const std::size_t MAXIMUM = 30;
    Graph(std::size_t size = 0){
        _vertices = 0;
        _allocated = size;
//        assert(_allocated == 2);
//        std::cout << "Allocated: " << _allocated
//                  << std::endl;
//        reallocate(size);
        allocate2D(_edges,_allocated);
//        assert(_edges);
        initialize2D(_edges,_allocated);

        allocate(_labels,_allocated);
    }

    void addVertex(const Item& label){
        //If size() < MAXIMUM
        //Above should be false
        using namespace std;
//        cout << "Size: " << size() << endl;
        if(_allocated <= size()) resize(_allocated*2);
//        cout << "After resize" << endl;
        std::size_t newVertex = _vertices++;
//        cout << "after new vertex" << endl;
        for(std::size_t other = 0; other < _vertices; ++other){
            _edges[other][newVertex] = false;
            _edges[newVertex][other] = false;
        }
//        cout << "for loop end" << endl;
        _labels[newVertex] = label;
    }

    void addEdge(std::size_t source, std::size_t target){
        //If source < size()
        //If target < size()
        //Above should be false

        _edges[source][target] = true;
    }

    void removeEdge(std::size_t source, std::size_t target){
        //If source < size()
        //If target < size()
        //Above should be false
        _edges[source][target] = false;
    }

    void resize(std::size_t size){
        //If size < allocated
        //Above should be false
        using namespace std;
//        cout << "in resize" << endl;
//        for(std::size_t i = 0; i < _vertices; ++i){
//            delete[] _edges[i];
//        }
//        cout << "for loop end" << endl;
//        delete _edges;
//        cout << "deleted edges" << endl;
//        delete _labels;
//        cout << "deleted labels" << endl;
        reallocate(size);
//        cout << "reallocated" << endl;
    }

    Item& operator [](std::size_t vertex){
        //If vertex < size()
        //Above should be false
        return _labels[vertex];
    }

    std::size_t size() const{
        return _vertices;
    }
    bool isEdge(std::size_t source, std::size_t target) const{
        //If source < size()
        //If target < size()
        //Above should be false

        return _edges[source][target];
    }
    std::set<std::size_t> neighbors(std::size_t vertex) const{
        //If vertex < size()
        //Above should be false
        std::set<std::size_t> adjacents;
        for(std::size_t i = 0; i < size(); ++i)
            if(_edges[vertex][i]) adjacents.insert(i);
        return adjacents;
    }
    Item operator [](std::size_t vertex) const{
        //If vertex < size()
        //Above should be false
        return _labels[vertex];
    }
    friend std::ostream& operator << (std::ostream& out, const Graph<Item> G){
        out << "   ";
        for(std::size_t i = 0; i < G.size(); ++i){
            out << G._labels[i] << "|";
        }
        out  << std::endl;
        for(std::size_t i = 0; i < G.size(); ++i){
            out << G._labels[i] << ":|";
            for(std::size_t j = 0; j < G.size(); ++j){
                out << G._edges[i][j] << "|";
            }
            out << std::endl;
        }

        return out;
    }

    template <typename Process>
    void depthFirst(Process f, std::size_t start){
        bool marked[_allocated];
        assert(start < size());
        std::fill_n(marked,size(),false);
        dfs(f,start,marked);
    }

    template <typename Process>
    void breadthFirst(Process f, std::size_t start){
        bool marked[_allocated];
        std::set<std::size_t> connections;
        std::set<std::size_t>::iterator it;
        std::queue<std::size_t> vQ;
        assert(start < size());
        std::fill_n(maarked,size(),false);
        marked[start] = true;
        f(g[start]);
        vQ.push(start);
        do{
            connections = neighbors(vQ.front());
            vQ.pop();
            for(it = connections.begin(); it != connections.end(); ++it){
                if(!marked[*it]){
                    marked[*it] = true;
                    f(g[*it]);
                    vQ.push(*it);
                }
            }
        } while(!vQ.empty());
    }
};

#endif // GRAPH_H
