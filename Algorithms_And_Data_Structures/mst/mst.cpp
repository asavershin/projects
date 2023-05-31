#include <iostream>
#include <fstream>
#include "sort.h"

int main(int argc, char*argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cout << argv[1];
        return 2;
    }
//    std::ofstream outFile(argv[2]);
//    if (!outFile) {
//        return 3;
//    }
    int A;
    int B;
    int weight;
    int numVert;
    int numEdge;


    inFile >> numVert >> numEdge;
    Node *list = new Node[numEdge];
    DisjointSet set(numVert);
    for(int i = 0; i < numEdge; ++i){
        inFile >> A >> B >> weight;
        list[i].set(A, B, weight);
    }
    QuickSortS(list, numEdge, 0);

//    for(int i = 0; i < numEdge; ++i){
//        outFile << list[i].vertex1 << " "<< list[i].vertex2 << std::endl;
//    }

    int stop = 0;
    int max = 0;

    for(int i = 0; i < numEdge; ++i){
        max += set.unionSet(list[i].vertex1, list[i].vertex2)? list[i].weight : 0;
        if(stop == numVert - 1){
            break;
        }
    }
    delete []list;
    std::cout << max;
}
