//
// Created by Alexander on 15.05.2023.
//

#ifndef MST_SORT_H
#define MST_SORT_H
#include "disjointset.h"

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void QuickSortS(Node M[], int Len,int start) {

    int N = Len;
    int size = 1;
    while (N > 0) {
        N >>= 1; // N = N >> 1; // N /= 2; // N = N / 2;
        ++size;
    }

    int* StackLeft = new int[size];
    int* StackRight = new int[size];
    int topInStack = -1;
    ++topInStack;
    StackLeft[topInStack] = start + 0;
    StackRight[topInStack] = start + Len-1;

    while (topInStack>-1) {
        int left = StackLeft[topInStack];
        int right = StackRight[topInStack];
        --topInStack;
        /* Упорядочить относительно центрального элемента*/
        int i = left;
        int j = right;
        int pindex = i + (j - i) / 2;
        int p = M[pindex].weight;

        while (i < j) {
            while (M[i].weight < p) {
                ++i;
            }
            while (p < M[j].weight) {
                --j;
            }
            if (i < j) {
                swap(M[i], M[j]);
            }
            if(i <= j) {
                ++i;
                --j;
            }
        }

        /* Запомнить неотсортированые участки*/
        if (pindex < i) { // Правая часть меньше, чем левая
            // Значит сортируем сначала то, что справа, а значит сначала на стеке запомнить то, что слева
            if (j > left) {
                ++topInStack;
                StackLeft[topInStack] = left;
                StackRight[topInStack] = j; }
            if (i < right) { ++topInStack;
                StackLeft[topInStack] = i;
                StackRight[topInStack] = right; }
        }
        else { // Левая часть меньше, чем правая
            if (i < right) { ++topInStack;
                StackLeft[topInStack] = i;
                StackRight[topInStack] = right; }
            if (j > left) { ++topInStack;
                StackLeft[topInStack] = left;
                StackRight[topInStack] = j; }
        }
    }
    delete[] StackLeft;
    delete[] StackRight;
}
#endif //MST_SORT_H
