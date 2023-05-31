
#ifndef _hashtable_H_
#define _hashtable_H_

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
class HashTable{

    int m;
    int m_1;

    int h1(int k) const{
        return k % m;
    }

    int h2(int k) const{
        return 1 + (k % m_1);
    }

    struct Cell{
        char status;// 0 -- Nil, 1 -- Occupied, -1 -- deleted
        int data;
        Cell(){
            status = 0;
            data = 0;
        }
    };


    Cell *cells;
public:


    HashTable(int size){
        m = findPrimeNumber(size);
        m_1 = m - 1;
        cells = new Cell[m];
    }


    ~HashTable(){
        delete []cells;
    }

    int insert(int k){
        int j;
        for(int i = 0; i < m; ++i){
            j = std::abs((h1(k) + i * h2(k)) % m);
            if(cells[j].status == 0 or cells[j].status == -1){
                cells[j].data = k;
                cells[j].status = 1;
                return j;
            }
        }
        return -1;
    }


    int search(int k){

        int i = 0;
        int j = std::abs((h1(k) + i * h2(k)) % m);
        for(; i < m and cells[j].status != 0; ++i, j = std::abs((h1(k) + i * h2(k)) % m)){
            if(cells[j].data == k and cells[j].status != -1){
                return j;
            }
        }
        return -1;
    }


    bool remove(int k){
        int j = search(k);
        if(j != -1){
            cells[j].status = -1;
            return true;
        }
        return false;
    }

};

#endif








