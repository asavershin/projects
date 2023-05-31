#include "hashtableforisbtree.h"


bool checkKeyOrder(HashTable &HT, int node, int minKey, int maxKey) {
    int next;
    int n = HT.cells[node].numChildren;
    if(minKey > HT.cells[node].keys[0] or maxKey < HT.cells[node].keys[HT.cells[node].numKeys - 1]){
        return false;
    }

    // Проверка ключей в потомках узла
    for (int i = 0; i < n; i++) {
        int childMinKey = (i == 0) ? minKey : HT.cells[node].keys[i - 1];
        int childMaxKey = (i == n - 1) ? maxKey : HT.cells[node].keys[i];

        next = HT.search(HT.cells[node].children[i]);
        if(next == -1){
            return false;
        }

        if (!checkKeyOrder(HT, next, childMinKey, childMaxKey)) {
            return false;
        }
    }

    return true;
}

bool lastCheck(HashTable &HT) {
    int minKey = -2147483648;
    int maxKey = 2147483647;

    return checkKeyOrder(HT, HT.root, minKey, maxKey);
}


int main(int arc, char* argv[]) {

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        return 2;
    }

    int max;
    int t;
    int tmp;
    inFile >> max >> t >> tmp;
    char type[8]{0};
    int num;
    int keys;
    int children;
    char trash;

    HashTable HT(max);
    int cell;


    inFile >> type >> trash >> trash;
    inFile >> num >> trash;
    cell = HT.insert(num);
    HT.root = cell;

    inFile >> keys >> trash;
    if(keys < 1 or keys > 2*t - 1){
        std::cout << "no";
        return 0;
    }
    HT.cells[cell].numKeys = keys;
    HT.cells[cell].keys = new int[keys];
    inFile >> HT.cells[cell].keys[0];
    for (int k = 1; k < keys; ++k){
        inFile >> HT.cells[cell].keys[k];
        if(HT.cells[cell].keys[k] < HT.cells[cell].keys[k - 1]){
            std::cout << "no";
            return 0;
        }
    }

    inFile >> trash;
    if(type[0] == 'b') {
        inFile >> trash >> children >> trash;
        if (children < 2 or children > 2 * t or keys + 1 != children) {
            std::cout << "no";
            return 0;
        }
        HT.cells[cell].numChildren = children;
        HT.cells[cell].children = new int[children];
        for (int k = 0; k < children; ++k) {
            inFile >> HT.cells[cell].children[k];
        }

        inFile >> trash;
    }
    for(int i = 1; i < max; ++i){
        inFile >> type >> trash >> trash;
        inFile >> num >> trash;
        if(HT.search(num) != -1){
            std::cout << "no";
            return 0;
        }
        cell = HT.insert(num);
        inFile >> keys >> trash;
        if(keys < t - 1 or keys > 2*t - 1){
            std::cout << "no";
            return 0;
        }
        HT.cells[cell].keys = new int[keys];
        HT.cells[cell].numKeys = keys;
        inFile >> HT.cells[cell].keys[0];
        for (int k = 1; k < keys; ++k){
            inFile >> HT.cells[cell].keys[k];
            if(HT.cells[cell].keys[k] < HT.cells[cell].keys[k - 1]){
                std::cout << "no";
                return 0;
            }
        }
        inFile >> trash;
        if (type[0] == 'b') {
            inFile >> trash >> children >> trash;
            if(children < t or children > 2 * t or keys + 1 != children){
                std::cout << "no";
                return 0;
            }
            HT.cells[cell].children = new int[children];
            HT.cells[cell].numChildren = children;
            for (int k = 0; k < children; ++k) {
                inFile >> HT.cells[cell].children[k];
                if(HT.cells[HT.root].adress == HT.cells[cell].children[k]){
                    std::cout << "no";
                    return 0;
                }
            }
            inFile >> trash;
        }
    }


    if(lastCheck(HT)){
        std::cout << "yes";
    }else{
        std::cout << "no";
    }

    return 0;
}
