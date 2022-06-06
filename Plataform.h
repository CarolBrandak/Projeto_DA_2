//
// Created by Carol on 14/05/2022.
//

#ifndef PROJETO_DA_2_PLATAFORM_H
#define PROJETO_DA_2_PLATAFORM_H

#include "Graph.h"
#include "fulkersongraph.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
#include <algorithm>


class Plataform{
    Graph<int>* graph;
    bool stateApplication=true;
    int fich;
    string file;
    public:
        Plataform();
        void FileMenu();
        void initialMenu();
        void Menu1();
        void Menu2();
        void ReadDataset(const string& fileName);
        void ReadGraph();
        void MaxGroupDimension();
        void MaxDimMinTrans();
        void case_2_1();
        void case_2_2();
        void Case_2_3();
        void Case_2_4();
        void printPath(vector<FulkersonGraph::Path> paths);
        void printCaseMenu(int &o,int &d, int &c);
        static bool desDuration( FulkersonGraph::Path p1, FulkersonGraph::Path p2);
    };

#endif //PROJETO_DA_2_PLATAFORM_H
