#ifndef DA_PROJECT_GRAPH_FORD_FULKERSON_H
#define DA_PROJECT_GRAPH_FORD_FULKERSON_H

#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include "MaxHeap.h"
#include <queue>
#include "MinHeap.h"

using namespace std;
class FulkersonGraph {
    struct Edge {
        int dest;   // Destination node
        int flow;
        int capacity; // An integer weight
        bool active;
    };
    struct Node {
        int dist;
        int cap;
        int grau;
        int parent;
        bool visited;
        vector<Edge*> adj;
        vector<Edge*> residual;
    };
    int size;              // Graph size (vertices are numbered from 1 to n)
    std::vector<Node> nodes; // The list of nodes being represented
public:

    explicit FulkersonGraph(int size) : size(size) {
        for (int i = 0; i <= size; i++) {
            add_node(i);
        }
    }

    explicit FulkersonGraph(string file) {
        ifstream infile(file);
        if (!infile.is_open()){
            cerr<<"Cannot open the file!"<<endl;
        }

        int noNodes, noEdges;
        infile >> noNodes >> noEdges;
        size = noNodes;

        *this = FulkersonGraph(noNodes);

        int src, dest, cap, dur;
        while (infile >> src) {
            infile >> dest >> cap >> dur;
            add_edge(src, dest, cap);
        }
    }

    void add_node(int val) {
        if (nodes.size() == size + 1) return;
        Node node;
        node.dist=0;
        node.adj.clear();
        nodes.push_back(node);
    }

    void add_edge(int src, int dest, int capacity = 1) {
        if (src < 1 || src > size || dest < 1 || dest > size)
            return;

        nodes[src].adj.push_back(new Edge{dest, 0, capacity, true});
        nodes[dest].residual.push_back(new Edge{src, 0, 0, true});
    }

    int getSize() const{
        return size;
    }

    pair <int,vector<int>> bfs(int v, int dest) {

        map<int,int> distToV;
        vector<int> path;
        distToV[v] = 0;

        for (int i = 1; i<= size;i++){
            nodes[i].visited = false;
            nodes[i].parent = -1;
        }
        nodes[v].parent = v;
        queue<int> q ;
        q.push(v);
        nodes[v].visited = true;

        while(!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto e : nodes[u].adj){
                int w = e->dest ;

                if(nodes[w].visited== false && e->capacity >0){
                    distToV[w] = distToV[u] + 1;
                    nodes[w].parent = u;
                    nodes[w].grau +=1;
                    q.push(w);
                    nodes[w].visited=true;
                }
                if(distToV.find(dest) != distToV.end()){
                    int pred = dest;
                    path.push_back(dest);
                    while(pred != v){
                        pred = nodes[pred].parent;
                        path.insert(path.begin(),pred);
                    }
                    return {distToV[dest], path};
                }
            }
        }
        return{-1,{}};
    }

    pair<vector<int>,vector<vector<int>>> fordFulkerson(int s, int t) {
        pair<int,vector<int>> res;
        vector<vector<int>> paths;
        vector<int> path_flows;
        int max_flow=0, status=0;

        while(status != -1){
            res= bfs (s,t);
            if((status = res.first) == -1){
                break;
            }
            else{
                int path_flow = INT_MAX;
                for(int i = 0; i< res.second.size() -1 ; i++){
                    int src = res.second[i];
                    int dest = res.second[i+1];
                    int srcdest_flow=0;
                    for(auto e: nodes[src].adj){
                        if(e->dest == dest && e->capacity > srcdest_flow){
                            srcdest_flow = e->capacity;
                        }
                    }
                    if(srcdest_flow < path_flow)
                        path_flow = srcdest_flow;
                }
                for(int i = 0; i<res.second.size()-1;i++){
                    int src = res.second[i];
                    int dest = res.second[i+1];

                    int numrep = 0;
                    for(int i = 0; i<nodes[src].adj.size();i++){

                        if(nodes[src].adj[i]->dest == dest) {
                            numrep++;
                            if (nodes[src].adj[i]->capacity >= path_flow) {
                                nodes[src].adj[i]->capacity -= path_flow;
                            } else {
                                continue;
                            }
                            int numreturn = 0;
                            for (int j = 0; j < nodes[dest].adj.size(); j++) {
                                if (nodes[dest].residual[j]->dest == src) {
                                    numreturn++;
                                    if (numrep == numreturn) {
                                        nodes[dest].residual[j]->capacity += path_flow;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                max_flow += path_flow;
                path_flows.push_back(path_flow);
                paths.push_back(res.second);
            }
        }
       return {path_flows,paths};
    }

    pair<vector<int>,vector<vector<int>>> fordFulkerson2_1(int s, int t, int capacity) {
        pair<int,vector<int>> res;
        vector<vector<int>> paths;
        vector<int> path_flows;
        int max_flow=0, status=0;

        while(capacity > 0 && status !=-1){
            res= bfs (s,t);
            if((status = res.first) == -1){
                break;
            }
            else{
                int path_flow = INT_MAX;
                for(int i = 0; i< res.second.size() -1 ; i++){
                    int src = res.second[i];
                    int dest = res.second[i+1];
                    int srcdest_flow=0;
                    for(auto e: nodes[src].adj){
                        if(e->dest == dest && e->capacity > srcdest_flow){
                            srcdest_flow = e->capacity;
                        }
                    }
                    if(srcdest_flow < path_flow)
                        path_flow = srcdest_flow;
                }
                for(int i = 0; i<res.second.size()-1;i++){
                    int src = res.second[i];
                    int dest = res.second[i+1];

                    int numrep = 0;
                    for(int i = 0; i<nodes[src].adj.size();i++){

                        if(nodes[src].adj[i]->dest == dest) {
                            numrep++;
                            if (nodes[src].adj[i]->capacity >= path_flow) {
                                nodes[src].adj[i]->capacity -= path_flow;
                            } else {
                                continue;
                            }
                            int numreturn = 0;
                            for (int j = 0; j < nodes[dest].adj.size(); j++) {
                                if (nodes[dest].residual[j]->dest == src) {
                                    numreturn++;
                                    if (numrep == numreturn) {
                                        nodes[dest].residual[j]->capacity += path_flow;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                capacity -= path_flow;
                if(capacity < 0 ){
                    path_flows.push_back(capacity+=path_flow);
                }
                path_flows.push_back(path_flow);
                paths.push_back(res.second);
            }
        }
        return {path_flows,paths};
    }
};



#endif
