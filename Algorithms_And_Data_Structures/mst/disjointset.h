//
// Created by Alexander on 15.05.2023.
//

#ifndef MST_DISJOINTSET_H
#define MST_DISJOINTSET_H

struct Node{
    int vertex1;
    int vertex2;
    int weight;
    void set(int a, int b, int c){
        vertex1 = a;
        vertex2 = b;
        weight = c;
    };
};


//непересекающиеся множества на массиве
struct DisjointSet{
    int *id;
    DisjointSet(int size){
        id = new int[size];
        for (int i = 0; i < size; ++i) {
            id[i] = -1;  // каждый корень хранит число элементов по модулю
        }
    }
    ~DisjointSet(){
        delete[]id;
    }
    int find(int key) const {
        // Поиск корня множества
        int root = key;
        while (id[root] > -1) {
            root = id[root];
        }

        // Сжатие пути
        int next;
        while (key != root) {
            next = id[key];
            id[key] = root;
            key = next;
        }
        return root;
    }

    bool unionSet(int f, int s) const {
        int rootX = find(f);
        int rootY = find(s);
        if (rootX == rootY) {
            return false;  // элементы уже находятся в одном множестве
        }

        if (id[rootX] > id[rootY]) {
            id[rootX] = rootY;
            --id[rootY];
        } else{
            id[rootY] = rootX;
            --id[rootX];
        }
        return true;
    }

};
#endif //MST_DISJOINTSET_H
