
#include "hashtable.h"
#include <cmath>


int main(int arc, char* argv[]) {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        return 2;
    }

    std::ofstream outFile(argv[2]);
    if (!outFile) {
        return 3;
    }

    int max;
    inFile >> max;
    char command;
    int num;
    HashTable HT(max);

    for(int i = 0; i < max; ++i){
        inFile >> command;
        inFile >> num;
        switch (command) {
            case '+':
                HT.insert(num);
                break;
            case '-':
                HT.remove(num);
                break;
            case '?':
                outFile << (HT.search(num) != -1 ? "true" : "false")<< '\n';
                break;
            default:
                return 4;
        }
    }
    return 0;
}

