#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <set>
#include <cassert>
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
        bool** edgeTemp = _edges;
        Item* labelTemp = _labels;
        allocate2D(_edges,nSize);
        allocate(_labels,nSize);
        initialize2D(_edges,nSize);
        for(std::size_t i = 0; i < size(); i++){
            copy(edgeTemp[i],_edges[i],size());
        }
        copy(labelTemp,_labels,size());
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
    void copy(Type* source, Type* dest, std::size_t size){
        for(std::size_t i = 0; i < size; ++i){
            dest[i] = source[i];
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
        if(_allocated <= size()) resize(_allocated*2);
        std::size_t newVertex = _vertices++;
        for(std::size_t other = 0; other < _vertices; ++other){
            _edges[other][newVertex] = false;
            _edges[newVertex][other] = false;
        }
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
        for(std::size_t i = 0; i < _vertices; ++i){
            delete[] _edges[i];
        }
        delete _edges;
        delete _labels;
        reallocate(size);
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

};

#endif // GRAPH_H
