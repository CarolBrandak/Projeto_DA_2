//
// Created by Carol on 14/05/2022.
//

#ifndef PROJETO_DA_2_PLATAFORM_H
#define PROJETO_DA_2_PLATAFORM_H

#include "Graph.h"

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
    Graph<int>* rgraph;
    bool stateApplication=true;
    int fich;
    public:
        Plataform();
        void FileMenu();
        void initialMenu();
        void MenuRota();
        void ReadDataset(const string& fileName);
        void ReadGraph();
        void MaxGroupDimension();
        void Case_2_3();
        void case_2_1();
        void MaxDimMinTrans();
    };

#endif //PROJETO_DA_2_PLATAFORM_H
