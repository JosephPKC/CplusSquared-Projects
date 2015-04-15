#include <iostream>
#include "Graph.h"
#include "LabelledGraph.h"
#include "WeightedGraph.h"
using namespace std;
template <typename Item>
bool isConnected(Graph<Item> G, std::size_t start, std::size_t end){

}

int main()
{
    Graph<char> G(2);
    cout << G << endl;
//    cout << "a" << endl;
    G.addVertex('c');
    cout << G << endl;
//    cout << "a" << endl;
    G.addVertex('b');
    cout << G << endl;
//    cout << G.size() << endl;
    G.addVertex('f');
    cout << G << endl;
//    cout << G.size() << endl;
//    cout << G << endl;
    G.addEdge(1,0);
    cout << G << endl;
    G.addEdge(1,1);
    cout << G << endl;

    LabelledGraph<char,int> LG(2);
    LG.addVertex('a');
//    cout << "a" << endl;
    LG.addVertex('b');
//    cout << "b" << endl;
    LG.addVertex('c');
//    cout << "c" << endl;
    LG.addVertex('d');
//    cout << "d" << endl;
    LG.addEdge(0,0,1);
//    cout << "ea" << endl;
    LG.addEdge(0,1,13);
//    cout << "eaa2" << endl;
    cout << LG << endl;

    WeightedGraph<char> WG(2);
    WG.addVertex('a');
//    cout << "a" << endl;
    WG.addVertex('b');
//    cout << "b" << endl;
    WG.addVertex('c');
//    cout << "c" << endl;
    WG.addVertex('d');
//    cout << "d" << endl;
    WG.addEdge(0,0,1);
//    cout << "ea" << endl;
    WG.addEdge(0,1,13);
//    cout << "eaa2" << endl;
    cout << WG << endl;
    return 0;
}

