#include <fstream>
#include <iostream>

//используются один раз для поиска простого числа для размера таблицы
bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }

    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrimeNumber(int A) {
    int current = A + 1;
    while (!isPrime(current)) {
        current++;
    }
    return current;
}

//Таблица с использованием открытой адрессации и двойным хэшированием.
struct HashTable{

    int m;
    int m_1;
    int root;
    int depth;
    int h1(int k) const{
        return k % m;
    }

    int h2(int k) const{
        return 1 + (k % m_1);
    }


    struct Cell{
//        char type; // 0 -- branch, 1 -- leaf
        char status; //0 -- свободно, 1 -- занято
        int adress;
        int numKeys;
        int numChildren;
        int *keys;
        int *children;
        Cell(){
            keys = nullptr;
            children = nullptr;
            numChildren = 0;
            numKeys = 0;
            status = 0;
            adress = 0;
        }
        ~Cell() {
            delete []keys;
            delete []children;
        }
    };

    Cell *cells;

    HashTable(int size){
        depth = 0;
        cells = nullptr;
        m = findPrimeNumber(size);
        m_1 = m - 1;
        cells = new Cell[m];
        root = 0;
    }


    ~HashTable(){
        delete []cells;
    }

    int insert(int k) const{
        int j;
        for(int i = 0; i < m; ++i){
            j = std::abs((h1(k) + i * h2(k)) % m);
            if(cells[j].status == 0){
                cells[j].adress = k;
                cells[j].status = 1;
                return j;
            }
        }
        return -1;
    }


    int search(int k) const{
        int i = 0;
        int j = std::abs(h1(k) + i * h2(k) % m);
        for(; i < m and cells[j].status != 0; ++i, j = std::abs((h1(k) + i * h2(k)) % m)){
            if(cells[j].adress == k){
                return j;
            }
        }
        return -1;
    }

};
