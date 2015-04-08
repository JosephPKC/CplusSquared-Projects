#include <iostream>
#include "Graph.h"
#include "LabelledGraph.h"
using namespace std;

int main()
{
    Graph<char> G(2);
    G.addVertex('c');
    G.addVertex('b');
    cout << G.size() << endl;
    G.addVertex('f');
    cout << G.size() << endl;
    cout << G << endl;
    G.addEdge(1,0);
    cout << G << endl;
    G.addEdge(1,1);
    cout << G << endl;

    LabelledGraph<char,int> LG(2);
    LG.addVertex('a');
    LG.addVertex('b');
    LG.addVertex('c');
    LG.addVertex('d');
    LG.addEdge(0,0,1);
    LG.addEdge(0,1,13);
    cout << LG << endl;
    return 0;
}

