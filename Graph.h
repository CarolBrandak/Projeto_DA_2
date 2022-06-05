//
// Created by Carol on 14/05/2022.
//

#ifndef PROJETO_DA_2_GRAPH_H
#define PROJETO_DA_2_GRAPH_H

#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include <map>

#include "MaxHeap.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    //T & info;
    int id;
    std::vector<Edge<T>> adj;		// outgoing edges

    double dist = 0;
    int trans = 1;
    Vertex<T> *path = NULL;
    int lastEdge = 0;

    bool visited = false;		// auxiliary field
    int parent = 0;
    int grau=0;

    void addEdge(int id, Vertex<T> *dest, int ca, int du);

public:
    Vertex(int id);
    double getDist() const;
    Vertex *getPath() const;
    std::vector<Edge<T> > getEdges() const;
    int getId() const;

    friend class Graph<T>;
    bool operator<(Vertex<T> & vertex) const;
};


template <class T>
Vertex<T>::Vertex(int id): id(id){}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, int ca, int du) {
    adj.push_back(Edge<T>(id, d, ca, du));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
int Vertex<T>::getId() const{
    return id;
}
/********************** Edge  ****************************/

template <class T>
class Edge {
    int id;
    Vertex<T> * dest;      // destination vertex
    int duration;       // edge duration
    double capacity;
public:
    Edge(int id, Vertex<T> *d, int ca, int du);
    friend class Graph<T>;
    friend class Vertex<T>;
    int getId() const {return id;}
    int getDestId() const {return dest->getId();}
    int getDuration() const {return duration;}
    int getCapacity() const {return capacity;}
};

template <class T>
Edge<T>::Edge(int id, Vertex<T> *d, int ca, int du): id(id), dest(d), capacity(ca), duration(du) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
    //Vertex<T> *findVertex(const T &in) const;
    Vertex<T> *findVertex(int id) const;
    bool addVertex(int id);
    bool addEdge(int id, const int sourc, const int dest, int ca, int du);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void dijkstraShortestPath(int s, int dim);
    void dijkstraMaxCapacity(int origin);
    void dijkstraCapTrans(int origin);
    std::vector<T> getPath(int origin, int dest) const;
    std::vector<int> getEdgePath(const T &origin, const T &dest) const;

    std::pair<int,std::vector<int>> bfs(int v, int dest);
    int fordFulkerson(int s, int t);

};


template<class T>
std::vector <Edge<T>> Vertex<T>::getEdges() const {
    return adj;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
/*template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}*/

template <class T>
Vertex<T> * Graph<T>::findVertex(int id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(int id) {
    if ( findVertex(id) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(id));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(int id, const int sourc, const int dest, int ca, int du) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(id, v2, ca, du);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/


template<class T>
bool myfunction (Vertex<T>* i,Vertex<T>* j) { return (i->getDist() < j->getDist()); }

template<class T>
void Graph<T>::dijkstraShortestPath(int origin, int dim) {
    auto v = findVertex(origin);
    std::vector<Vertex<T> *> vertexSetCopy = vertexSet;
    for (auto vertex: vertexSetCopy){
        vertex->dist = INF;
        vertex->visited = false;
        vertex->path = NULL;
        vertex->lastEdge = 0;
    }
    v->dist = 0;
    std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * v1, Vertex<T> * v2){return v1->dist < v2->dist;});
    for(int i = 0; i < vertexSet.size(); ++i) {
        Vertex<T> * nextV = vertexSetCopy.front();
        for (auto edge : nextV->adj){
            if (!edge.dest->visited && edge.capacity >= dim) {
                if(nextV->dist + edge.duration < edge.dest->dist || edge.dest->dist == 0) {
                    edge.dest->dist = nextV->dist + edge.duration;
                    edge.dest->path = nextV;
                    edge.dest->lastEdge = edge.id;
                }
            }
        }
        nextV->visited = true;
        vertexSetCopy.erase(vertexSetCopy.begin());
        std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex1, Vertex<T> * vertex2){return vertex1->dist < vertex2->dist;});
    }
}

//A testar como nó 2 a 5 e ver que o programa escolhe o cominho 2-5 em vez de 2-4-5 porque tem maior fluxo
template<class T>
void Graph<T>::dijkstraMaxCapacity(int origin) {
    auto v = findVertex(origin);
    std::vector<Vertex<T> *> vertexSetCopy = vertexSet;
    for (auto vertex: vertexSetCopy){
        vertex->dist = 0;
        vertex->visited = false;
        vertex->path = NULL;
    }
    v->dist = INF;

    std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * v1, Vertex<T> * v2){return v1->dist > v2->dist;});
    for(int i = 0; i < vertexSet.size(); ++i) {
        Vertex<T> * nextV = vertexSetCopy.front();
        for (auto edge : nextV->adj){
            double w=std::min(nextV->dist, edge.capacity);
            if (!edge.dest->visited) {
                if(w>edge.dest->dist) {
                    edge.dest->dist = w;
                    edge.dest->path = nextV;
                }
            }
        }
        nextV->visited = true;
        vertexSetCopy.erase(vertexSetCopy.begin());
        std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex1, Vertex<T> * vertex2){return vertex1->dist > vertex2->dist;});
    }
}


//A cada aresta adjacente escolhe a que tem maior capacidade juntamente com o menor numero de transbordos ate esse instante
template<class T>
void Graph<T>::dijkstraCapTrans(int origin) {
    auto v = findVertex(origin);
    std::vector<Vertex<T> *> vertexSetCopy = vertexSet;
    for (auto vertex: vertexSetCopy){
        vertex->dist = 0;
        vertex->visited = false;
        vertex->path = NULL;
        vertex->lastEdge = 0;
    }
    v->dist = 1;
    std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * v1, Vertex<T> * v2){return v1->dist > v2->dist;});
    for(int i = 0; i < vertexSet.size(); ++i) {
        Vertex<T> * nextV = vertexSetCopy.front();
        for (auto edge : nextV->adj){
            if (!edge.dest->visited) {
                if(nextV->dist + (edge.capacity/nextV->trans) > edge.dest->dist) {
                    edge.dest->dist = nextV->dist + (edge.capacity/nextV->trans);
                    edge.dest->path = nextV;
                    edge.dest->trans = nextV->trans + 1;
                    edge.dest->lastEdge = edge.id;
                }
            }
        }
        nextV->visited = true;
        vertexSetCopy.erase(vertexSetCopy.begin());
        std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex1, Vertex<T> * vertex2){return vertex1->dist > vertex2->dist;});
    }
}

template<class T>
std::vector<T> Graph<T>::getPath(int origin, int dest) const {
    std::vector<T> res;
    std::vector<T> res1;
    auto v = findVertex(dest);
    if (v==NULL) return res;
    res.push_back(v->id);
    T destT = dest;
    while (origin != destT) {
        v = v->path;
        if(v == NULL) return res1;
        destT = v->id;
        res.push_back(destT);
    }
    for (int i = res.size()-1; i > -1; i--) {
        res1.push_back(res[i]);
    }
    return res1;
}

template<class T>
std::vector <int> Graph<T>::getEdgePath(const T &origin, const T &dest) const {
    std::vector<int> res;
    std::vector<int> res1;
    auto v = findVertex(dest);
    if (v==NULL) return res;
    res.push_back(v->lastEdge);
    T destT = dest;
    while (origin != destT) {
        v = v->path;
        destT = v->info;
        res.push_back(v->lastEdge);
    }
    for (int i = res.size()-1; i > -1; i--) {
        res1.push_back(res[i]);
    }
    return res1;
}


template<class T>
std::pair<int, std::vector<int>> Graph<T>::bfs(int v, int dest) {
    std::map<int,int> distanceToV;
    std::vector<int> path;
    distanceToV[v]=0;


    for(int i = 0; i< vertexSet.size()  ; i++){
        vertexSet[i]->visited=false;
        vertexSet[i]->parent=-1;
    }
    vertexSet[v]->parent=v;
    std::queue<int> q;
    q.push(v);
    vertexSet[v]->visited=true;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(Edge<T> e : vertexSet[u]->adj){
            int w = e.getDestId()-1;
            if(!vertexSet[w]->visited && e.capacity > 0){
                distanceToV[w]=distanceToV[u]+1;
                vertexSet[w]->grau += 1;
                vertexSet[w]->parent = u;
                q.push(w);
                vertexSet[w]->visited=true;
            }
        }
    }
    if(distanceToV.find(dest) != distanceToV.end()){
        int pred = dest;
        path.push_back(dest);
        while(pred != v){
            pred= vertexSet[pred]->parent;
            path.insert(path.begin(),pred);
        }
        return{ distanceToV[dest], path};
    }

    return {-1,{}};
}

template <class T>
int Graph<T>::fordFulkerson(int s, int t) {
    std::pair<int, std::vector<int>> res;
    int max_flow = 0;
    int status = 0;

    while(status != -1){
        res= bfs(s,t);

        if((status = res.first) != -1) break;

        else{
            int path_flow = INT_MAX;
            for(int i = 0; i<res.second.size()-1 ;i++){
                int src = res.second[i];
                int dest = res.second[i+1];
                int srcdest_flow = 0;
                for(Edge<T> e: vertexSet[src]->adj){
                    if(e.getDestId() == dest && e.capacity > srcdest_flow){
                        srcdest_flow = e.capacity;
                    }
                }
                if(srcdest_flow < path_flow) path_flow = srcdest_flow;
            }

            for(int i = 0; i<res.second.size()-1 ;i++) {
                int src = res.second[i];
                int dest = res.second[i + 1];

                int numrep = 0;
                for (int i = 0; i < vertexSet[src]->adj.size(); i++) {
                    if (vertexSet[src]->adj[i].getDestId() == dest) {
                        numrep++;
                        if (vertexSet[src]->adj[i].capacity >= path_flow) {
                            vertexSet[src]->adj[i].capacity -= path_flow;
                        }
                    } else {
                        continue;
                    }
                    int numreturn = 0;
                    for (int j = 0; j < vertexSet[dest]->adj.size(); j++)
                    {
                        if (vertexSet[dest]->adj[j].getDestId() == src) {
                            numreturn++;
                            if (numrep == numreturn) {
                                vertexSet[dest]->adj[j].capacity += path_flow;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            max_flow += path_flow;
            std::cout << max_flow<< std::endl;
        }
    }

    return max_flow;
}

#endif //PROJETO_DA_2_GRAPH_H
