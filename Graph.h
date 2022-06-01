//
// Created by Carol on 14/05/2022.
//

#ifndef PROJETO_DA_2_GRAPH_H
#define PROJETO_DA_2_GRAPH_H

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    //T & info;
    int id;
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int lastEdge = 0;

    bool visited = false;		// auxiliary field

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
    int capacity;
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
    std::vector<T> getPath(int origin, int dest) const;
    std::vector<int> getEdgePath(const T &origin, const T &dest) const;

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
    std::for_each(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex){vertex->dist = INF; vertex->visited = false; vertex->path = NULL; vertex->lastEdge = 0;});
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

template<class T>
void Graph<T>::dijkstraMaxCapacity(int origin) {
    auto v = findVertex(origin);
    std::vector<Vertex<T> *> vertexSetCopy = vertexSet;
    std::for_each(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * vertex){vertex->dist = 0; vertex->visited = false; vertex->path = NULL; vertex->lastEdge = 0;});
    v->dist = 1;
    std::sort(vertexSetCopy.begin(), vertexSetCopy.end(), [](Vertex<T> * v1, Vertex<T> * v2){return v1->dist > v2->dist;});
    for(int i = 0; i < vertexSet.size(); ++i) {
        Vertex<T> * nextV = vertexSetCopy.front();
        for (auto edge : nextV->adj){
            if (!edge.dest->visited) {
                if(nextV->dist + edge.capacity > edge.dest->dist || edge.dest->dist == INF) {
                    edge.dest->dist = nextV->dist + edge.capacity;
                    edge.dest->path = nextV;
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


#endif //PROJETO_DA_2_GRAPH_H
