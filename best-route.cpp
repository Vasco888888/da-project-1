#include "csvLoader.cpp"
#include <iostream>
#include "data_structs/Graph.h"
#include "data_structs/MutablePriorityQueue.h"

string mode;
int source, destination;

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {
    auto vertSet = g->getVertexSet();
    for (auto v : vertSet) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<T> *start = g->findVertex(origin);
    if (start == nullptr) return;
    start->setDist(0);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(start);
    while (!q.empty()) {
        auto u = q.extractMin();
        u->setVisited(true);
        for (auto e : u->getAdj()) {
            if (relax(e)) {
                if (!e->getDest()->isVisited()) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
}

void menu() {
    cout << "Mode:";
    cin >> mode;
    if (mode == "exit") {
        return;
    }
    else if (mode == "driving"){
        cout << endl << "Source:";
        cin >> source;
        cout << endl << "Destination:";
        cin >> destination;
        cout << endl;
    }
}

void results() {
    cout << "Source:" << source << endl << "Destination:" << destination << endl;
    cout << "BestDrivingRoute:" << dijkstra() << endl;
}