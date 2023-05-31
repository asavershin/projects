#include "minmaxqueue.h"


int main(int argc, char* argv[]) {

    std::ifstream inFile(argv[1]);
    if(!inFile){
        std::cout << "inFile is not open";
        return 1;
    }

    std::ofstream outFile(argv[2]);
    if(!outFile){
        std::cout << "outFile is not open";
        return 2;
    }

    char ch;
    int num;

    inFile >> num;
    try {
        Queue queue(num);
        while (inFile >> ch) {
            switch (ch) {
                case '+':
                    inFile >> num;
                    queue.push(num);
                    break;
                case '-':
                    queue.pop();
                    break;
                case '?':
                    outFile << (queue.max() - queue.min()) << std::endl;
                    break;
                default:
                    throw "Unknown command";
            }
        }
    }
    catch(const char* error){
        std::cout << error;
    }
    outFile.close();
    inFile.close();
    return 0;
}
