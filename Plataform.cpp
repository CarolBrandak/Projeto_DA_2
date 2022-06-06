//
// Created by Carol on 14/05/2022.
//

#include "Plataform.h"
#include "fulkersongraph.h"

Plataform::Plataform() {
    this->graph = new Graph<int>;
}

void Plataform::FileMenu(){
    cout << "Qual ficheiro quer ler: (1-10)"<< endl;
    std::cin >> fich;
    while (fich < 0 || fich > 10){
        cout << "Erro! Qual ficheiro quer ler: (1-10)"<< endl;
        std::cin >> this->fich;
    }
    if(fich==10) {
        file ="../Tests/in"+ std::to_string(fich) +".txt";
        ReadDataset(file);
    }
    else {
        this->file="../Tests/in0"+ std::to_string(fich) +".txt";
        ReadDataset(file);
    }
    initialMenu();
}
void Plataform::initialMenu(){
    int op;
    cout<< "----------------------------------------------------" <<endl;
    cout << "Choose an option:" << endl;
    cout << "1. Lista de viagens" << endl;
    cout << "2. Cenario 1" << endl;
    cout << "3. Cenario 2" << endl;
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
                Menu1();
                break;
            case 3:
                Menu2();
                break;
            default:
                cout<<"Invalid option, enter again!\n\n";
                initialMenu();
                break;
        }
    }
}

void Plataform::Menu1() {
    int op;
    cout<< "----------------------------------------------------" <<endl;
    cout << "Choose an option:" << endl;
    cout << "1. Case 1.1" << endl;
    cout << "2. Case 1.2" << endl;
    cout << "0. Voltar ao menu anterior" << endl;
    std::cin>>op;
    switch (op) {
        case 0:
            initialMenu();
            break;
        case 1:
            MaxGroupDimension();
            break;
        case 2:
            MaxDimMinTrans();
            break;
        default:
            cout << "Invalid option, enter again!\n\n";
            Menu1();
            break;
    }
}

void Plataform::Menu2() {
    int op;
    cout<< "----------------------------------------------------" <<endl;
    cout << "Choose an option:" << endl;
    cout << "1. Case 2.1" << endl;
    cout << "2. Case 2.2"<<endl;
    cout << "3. Case 2.3"<<endl;
    cout << "4. Case 2.4"<<endl;
    cout << "0. Voltar ao menu anterior" << endl;
    std::cin>>op;
    switch (op) {
        case 0:
            initialMenu();
            break;
        case 1:
            case_2_1();
            break;
        case 2:
            case_2_2();
            break;
        case 3:
            Case_2_3();
            break;
        case 4:
            Case_2_4();
            break;
        default:
            cout << "Invalid option, enter again!\n\n";
            Menu2();
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
    Menu1();
}



void Plataform::MaxDimMinTrans() {
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

    graph->dijkstraMaxCapacity(o);

    vector<int> vec = graph->getPath(o, d);
    if(vec.size() == 0){
        cout << "Caminho Inexistente\n";
    }else {
        cout << "Rota com maior capacidade:" << endl;
        for (int v = 0; v < vec.size(); v++) {
            if (v != vec.size() - 1)
                cout << vec[v] << " --> ";
            else
                cout << vec[v];
        }
        cout << endl;
    }

    graph->dijkstraShortestPath(o);

    vector<int> vec2 = graph->getPath(o, d);
    if(vec.size() == 0){
        cout << "Caminho Inexistente\n";
    }else {
        cout << "Rota com menos transbordos:" << endl;
        for (int v = 0; v < vec2.size(); v++) {
            if (v != vec2.size() - 1)
                cout << vec2[v] << " --> ";
            else
                cout << vec2[v];
        }
        cout << endl;
    }
    Menu1();
}

void Plataform::case_2_1() {
    int d,o,cap;

    printCaseMenu(o,d,cap);

    FulkersonGraph rgraph = FulkersonGraph(this->file);
    vector<FulkersonGraph::Path> aux =rgraph.fordFulkerson(o,d);
    int max_flow = 0;
    for(auto e: aux){
        max_flow+=e.flow;
    }
    if(cap > max_flow){
        cout<<"Impossivel transportar esse numero de pessoas!"<<endl;
        Menu2();
    }
    else if (cap == max_flow){
        printPath(aux);
        Menu2();
    }
    else{
        FulkersonGraph graph = FulkersonGraph(this->file);
        vector<FulkersonGraph::Path> res = graph.fordFulkerson2_1(o,d,cap);
        printPath(res);
    }

    Menu2();
}

void Plataform::case_2_2() {
    int o,d,cap;

    printCaseMenu(o,d,cap);

    FulkersonGraph rgraph = FulkersonGraph(this->file);
    vector<FulkersonGraph::Path> aux =rgraph.fordFulkerson(o,d);
    int max_flow = 0;
    for(auto e: aux){
        max_flow+=e.flow;
    }
    if(cap > max_flow){
        cout<<"Impossivel transportar esse numero de pessoas!"<<endl;
        Menu2();
    }
    else if (cap == max_flow){
        printPath(aux);
        Menu2();
    }

    else {
        FulkersonGraph graph = FulkersonGraph(this->file);
        vector<FulkersonGraph::Path> res = graph.fordFulkerson2_1(o, d, cap);
        printPath(res);

        max_flow -= cap;
        int option, newpassengers;
        cout << "Deseja adicionar passageiros?(1->sim / 0->nao)" << endl;
        cin >> option;
        if (option == 0) {
            Menu2();
        }
        cout << "Quantos?" << endl;
        cin >> newpassengers;

        if (newpassengers > max_flow){
            cout << "Impossivel transportar esse numero de pessoas!" << endl;
            Menu2();
        }
        res = graph.fordFulkerson2_1(o,d,newpassengers);
        printPath(res);
    }
}

void Plataform::Case_2_3() {
    int o,d;

    cout << "Origem:" << endl;
    std::cin >> o;
    while (!graph->findVertex(o)){
        cout << "Essa origem não existe.\n";
        cout << "Origem:" << endl;
        std::cin >> o;
    }

    cout << "Destino:" << endl;
    std::cin >> d;
    while (!graph->findVertex(d)){
        cout << "Esse destino não existe.\n";
        cout << "Destino:" << endl;
        std::cin >> d;
    }
    cout << endl;

    FulkersonGraph graph = FulkersonGraph(this->file);
    vector <FulkersonGraph::Path> paths = graph.fordFulkerson(o,d);
    cout<<"Encaminhamento:"<<endl;

    int max_flow =0;
    for(auto i: paths){
        for(int j=0; j<i.path.size(); j++){
            if (j != i.path.size() - 1)
                cout << i.path[j] << " --> ";
            else
                cout << i.path[j];
        }
        cout<<"    Numero de pessoas :"<<i.flow<<endl;
        max_flow+=i.flow;
    }
    cout<<"Maximo flow:"<<max_flow<<endl;
}

void Plataform::Case_2_4() {
    int o,d,cap,duration = 0;

    printCaseMenu(o,d,cap);

    FulkersonGraph graph = FulkersonGraph(this->file);
    vector<FulkersonGraph::Path> paths =graph.fordFulkerson2_1(o,d,cap);
    graph.pathduration(paths);
    sort(paths.begin(), paths.end(), desDuration);

    /*for(int i =0; i<paths.size();i++){
        cout<<paths[i].duration<<endl;
    }*/
    cout<<"Duration:"<<paths[0].duration<<endl;
    Menu2();
}

void Plataform::printPath(vector<FulkersonGraph::Path> paths) {
    cout<<"Encaminhamento:"<<endl;
    for (auto i: paths){
        for(int j=0; j< i.path.size();j++){
            cout<<i.path[j]<<"->";
        }
        cout<<"Nº de pessoas:"<<i.flow<<endl;
    }
}

void Plataform::printCaseMenu(int &o, int &d, int &c) {

    cout << "Origem:" << endl;
    std::cin >> o;
    while (!graph->findVertex(o)){
        cout << "Essa origem não existe.\n";
        cout << "Origem:" << endl;
        std::cin >> o;
    }

    cout << "Destino:" << endl;
    std::cin >> d;
    while (!graph->findVertex(d)){
        cout << "Esse destino não existe.\n";
        cout << "Destino:" << endl;
        std::cin >> d;
    }
    cout << "Capacity:" << endl;
    std::cin >> c;
}


bool Plataform::desDuration(FulkersonGraph::Path p1, FulkersonGraph::Path p2) {
    return (p1.duration < p2.duration);
}
