
#include <fstream>
#include "aatree.h"


int main(int argc, char *argv[]) {

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
    AATree<int> tree;
    for(int i = 0; i < max; ++i){
        inFile >> command;
        inFile >> num;
        switch (command) {
            case '+':
                tree.insert(num);
                outFile << tree.rootLevel() << '\n';
                break;
            case '-':
                tree.remove(num);
                outFile << tree.rootLevel() << '\n';
                break;
            case '?':
                outFile << (tree.search(num) ? "true" : "false") << '\n';
                break;
            default:
                return 0;
        }
    }
}
