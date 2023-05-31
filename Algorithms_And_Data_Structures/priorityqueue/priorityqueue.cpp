
#include "fibonacciheap.h"
#include <fstream>
int main(int argc, char * argv[]) {

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cout << argv[1];
        return 2;
    }
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        return 3;
    }
    char com[13]{0};
    int x;
    int y;
    Node<int> * pushList[70003];
    int numCom = 0;
    FibonacciHeap<int> A;
    while(inFile >> com){
        ++numCom;
        switch (com[0]) {
            case 'p':
                inFile >> x;
                pushList[numCom] = A.insert(x);
                break;
            case 'e':
                if(A.isEmpty()){
                    outFile << "*\n";
                }else{
                    outFile << A.extractMin() << "\n";
                }
                break;
            case 'd':
                inFile >> x >> y;
                A.decreaseKey(pushList[x], y);
                break;
            default:
                std::cout << "Bad things";
        }
    }
    return 0;
}
