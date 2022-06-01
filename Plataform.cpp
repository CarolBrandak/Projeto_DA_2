//
// Created by Carol on 14/05/2022.
//

#include "Plataform.h"

Plataform::Plataform() {
    this->graph = new Graph<int>;
}

void Plataform::FileMenu(){
    cout << "Qual ficheiro quer ler: (1-10)"<< endl;
    int fich;
    std::cin >> fich;
    while (fich < 0 || fich > 10){
        cout << "Erro! Qual ficheiro quer ler: (1-10)"<< endl;
        std::cin >> fich;
    }
    if(fich==10) ReadDataset("../Tests/in"+ std::to_string(fich) +".txt");
    else ReadDataset("../Tests/in0"+ std::to_string(fich) +".txt");
    initialMenu();
}
void Plataform::initialMenu(){
    int op;
    cout<< "----------------------------------------------------" <<endl;
    cout << "Choose an option:" << endl;
    cout << "1. Lista de viagens" << endl;
    cout << "2. Calcular rota de grupos que nao se separam" << endl;
    cout << "0. Exit" << endl;
    std::cin>>op;
    while (stateApplication){
        switch (op) {
            case 0:
                stateApplication=false;
                break;
            case 1 :
                ReadGraph();
                break;
            case 2 :
                MenuRota();
                break;
            default:
                cout<<"Invalid option, enter again!\n\n";
                initialMenu();
                break;
        }
    }
}

void Plataform::MenuRota() {
    int op;
    cout << "1. Maximizar a dimensao" << endl;
    cout << "2. Maximizar a dimensao e minimizar o numero de transbordos"<<endl;
    cout << "3. Voltar ao menu anterior" << endl;
    std::cin >> op;
    switch (op) {
        case 1:
            MaxGroupDimension();
            break;
        case 2:
            MaxDimMinTrans();
            break;
        case 3:
            initialMenu();
            break;
        default:
            cout << "Invalid option, enter again!\n\n";
            MenuRota();
            break;
    }
}

void Plataform::ReadDataset(const string& fileName) {
    ifstream file(fileName);
    string line;
    if(!file.is_open()){
        cerr<<"ERROR: file could not be open"<<endl;
        return;
    }

    int numNodes, numTravels;
    file >> numNodes >> numTravels;

    for (int i = 0; i < numNodes; ++i) {
        this->graph->addVertex(i+1);
    }
    getline(file, line);
    int cnt = 0;
    int o, d, ca, du;
    while(cnt < numTravels){
        cnt++;
        file >> o >> d >> ca >> du;
        this->graph->addEdge(cnt, o, d, ca, du);
        getline(file, line);
    }
}

void Plataform::ReadGraph(){
    for (auto i:graph->getVertexSet()) {
        cout << "Origin->  " << i->getId() << endl;
        cout << "Travels: " << endl;
        for (auto j : i->getEdges()) {
            cout << "Travel ID: " << j.getId() << "  Destination: " << j.getDestId() << "  Capacity: " << j.getCapacity() << "  Duration: " << j.getDuration() << endl;
        }
        cout << endl << endl;
    }
    initialMenu();
}

void Plataform::MaxGroupDimension() {
    int o, d;
    cout << "Origin:" << endl;
    std::cin >> o;
    while (!graph->findVertex(o)){
        cout << "Essa origem nao existe.\n";
        cout << "Origin:" << endl;
        std::cin >> o;
    }
    cout << "Destination:" << endl;
    std::cin >> d;
    while (!graph->findVertex(d)){
        cout << "Esse destino nao existe.\n";
        cout << "Destination:" << endl;
        std::cin >> d;
    }
    cout << endl;

    graph->dijkstraMaxCapacity(o);

    vector<int> vec = graph->getPath(o, d);
    if(vec.size() == 0){
        cout << "Caminho Inexistente\n";
    }else {
        cout << "Rota:" << endl;
        for (int v = 0; v < vec.size(); v++) {
            if (v != vec.size() - 1)
                cout << vec[v] << " --> ";
            else
                cout << vec[v];
        }
        cout << endl;
    }
    MenuRota();
}

void Plataform::MaxDimMinTrans() {
    int o, d, dim;
    cout << "Origin:" << endl;
    std::cin >> o;
    while (!graph->findVertex(o)){
        cout << "Essa origem nao existe.\n";
        cout << "Origin:" << endl;
        std::cin >> o;
    }
    cout << "Destination:" << endl;
    std::cin >> d;
    while (!graph->findVertex(d)){
        cout << "Esse destino nao existe.\n";
        cout << "Destination:" << endl;
        std::cin >> d;
    }

    graph->dijkstraCapTrans(o);

    vector<int> vec = graph->getPath(o, d);
    if(vec.size() == 0){
        cout << "Caminho Inexistente\n";
    }else {
        cout << "Rota:" << endl;
        for (int v = 0; v < vec.size(); v++) {
            if (v != vec.size() - 1)
                cout << vec[v] << " --> ";
            else
                cout << vec[v];
        }
        cout << endl;
    }

    MenuRota();
}


