//Приоритетная очередь на пирамиде Фиббоначи

#ifndef PRIORITYQUEUE_FIBONACCIHEAP_H
#define PRIORITYQUEUE_FIBONACCIHEAP_H
#include <iostream>
#include "cmath"

template<typename T>
struct Node {
    T key;      // ключ
    Node *parent;  // указатель на родительский узел
    Node *child;   // указатель на один из дочерних узлов
    Node *left;    // указатель на левый узел того же предка
    Node *right;   // указатель на правый узел того же предка
    unsigned char degree;   // степень вершины
    bool mark; // был ли удален в процессе изменения ключа ребенок этой вершины)
    Node(): key(0), parent(nullptr), child(nullptr), left(nullptr), right(nullptr), degree(0), mark(false) {};
    Node(int x): key(x), parent(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false) {};
    ~Node(){
        delete child;
        if(right == this){
            return;
        }
        if(left != nullptr){
            left->right = nullptr;
        }
        delete right;
    }
};

template<typename T>
class FibonacciHeap{
    int size; // количество узлов в текущий момент
    Node<T> *min; // указатель на корень дерева с минимальным ключом


    static void link(Node<T>* y, Node<T>* x);
    void consolidate();

    static void unionLists(Node<T>* a, Node<T>* b); // функция для объединения колцеввых списков двух пирамид
    void merge(FibonacciHeap& x);
    void cut(Node<T>* x, Node<T>* y);
    void cascadingCut(Node<T>* y);


    static void clear(Node<T>* x);
public:

    FibonacciHeap(){
        size = 0;
        min = nullptr;
    }

    ~FibonacciHeap(){
        delete min;
    }

    bool isEmpty() const;
    Node<T>* insert(int x);
    int getMinimum() const;
    int extractMin();
    void decreaseKey(Node<T>* x, T k);
    void deleteNode(Node<T>* x);

};

template<typename T>
Node<T> * FibonacciHeap<T>::insert(int x) {

    auto* newNode = new Node<T>(x);
    if (min == nullptr) {
        min = newNode;
    } else {
        unionLists(newNode, min);
        if (newNode->key < min->key) {
            min = newNode;
        }
    }
    ++size;
    return newNode;
}


template<typename T>
int FibonacciHeap<T>::getMinimum() const {
    return min->key;
}


template<typename T>
void FibonacciHeap<T>::unionLists(Node<T>* a, Node<T>* b){
    if(b == nullptr){
        return;
    }
    if(a != nullptr) {
        a->left->right = b->right;
        b->right->left = a->left;
        b->right = a;
        a->left = b;
    }
}


template<typename T>
void FibonacciHeap<T>::merge(FibonacciHeap<T>& x){
    if(x.size == 0){//вторая пирамида пуста, нечего делать
        return;
    }
    if(size == 0){//первая пирамида пуста, тоже несложно
        min = x.min;
        x.min = nullptr; // на всякий случай
        size = x.size;
        return;
    }
    unionLists(min, x.min);
    size += x.size;
    if(min == nullptr or ((x.min != nullptr) and x.min->key < min->key)){
        min = x.min;
    }
    x.min = nullptr;
}


template<typename T>
void FibonacciHeap<T>::link(Node<T>* y, Node<T>* x){
    {
        // Удаляем узел y из списка корневых узлов
        y->left->right = y->right;
        y->right->left = y->left;
        y->right = y;
        y->left = y;
        // Устанавливаем y как дочерний узел для x
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
        } else {
            unionLists(x->child, y);
        }
        // Увеличиваем степень x
        ++x->degree;

        // Сбрасываем пометку (mark) y
        y->mark = false;
    }
}


template<typename T>
void FibonacciHeap<T>::consolidate() {
    int maxHeight = 64;
    auto ** A = new Node<T>*[maxHeight];
    for(int i = 0; i < maxHeight; ++i){
        A[i] = nullptr;
    }

    Node<T>* x = min;
    Node<T>* y;
    Node<T>* tmp;
    int degree;
    do{
        degree = x->degree;
        if(A[degree] == x){
            break;
        }
        while(A[degree] != nullptr){
            y = A[degree];
            if(x->key > y->key){
                std::swap(x, y);
            }
            if(y == min){
                min = x;
            }
            link(y, x);
            A[degree] = nullptr;
            ++degree;
        }
        A[degree] = x;
        x = x->right;
    } while (true);
    min = nullptr;
    for(int i = 0; i < maxHeight; ++i){
        tmp = A[i];
        if(tmp != nullptr){
            tmp->left->right = tmp->right;
            tmp->right->left = tmp->left;
            tmp->right = tmp;
            tmp->left = tmp;
            if(min == nullptr){
                min = tmp;
            }else{
                unionLists(tmp, min);
                if(A[i]->key < min->key){
                    min = tmp;
                }
            }
        }
    }
    for(int i = 0; i < maxHeight; ++i){
        A[i] = nullptr;
    }
    delete [] A;

}


template<typename T>
void FibonacciHeap<T>::clear(Node<T>* x){
    x->right = nullptr;
    x->parent = nullptr;
    x->child = nullptr;
    x->left = nullptr;
}


template<typename T>
void FibonacciHeap<T>::cut(Node<T>* x, Node<T>* y) {
    if(x->left == x){//нет братьев и сестер
        y->child = nullptr;
    }else{
        x->left->right = x->right;
        x->right->left = x->left;
        if(y->child == x){//меняем на любого другого ребенка, это не важно
            y->child = x->right;
        }
    }

    --y->degree;
    // Добавляем узел x в список корневых узлов
    x->right = x;
    x->left = x;
    unionLists(min, x);

    x->parent = nullptr;//в детдом
    x->mark = false;
}


template<typename T>
void FibonacciHeap<T>::cascadingCut(Node<T>* y) {
    Node<T>* z = y->parent;
    if(z != nullptr){
        if( !y->mark ){
            y->mark = true;
        }else{
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template<typename T>
void FibonacciHeap<T>::decreaseKey(Node<T>* x, T k) {
    if(k > x->key){//ошибка, я просто ничего не делаю и игнорирую
        return;
    }

    x->key = k;
    Node<T>* y = x->parent;
    if(y != nullptr && x->key < y->key){
        //свойство кучи нарушили, выполняем отсечение
        cut(x, y);
        cascadingCut(y);
    }
    if(min != nullptr) {
        if (x->key < min->key) {
            min = x;
        }
    }

}


template<typename T>
int FibonacciHeap<T>::extractMin() {
    if(size == 0){
        throw "Heap is empty";
    }
    int ans = min->key;
    Node<T>* child = nullptr;
    Node<T>* tmp;
    if (min->child != nullptr) {
        child = min->child;
        tmp = child;
        do {
            tmp->parent = nullptr; // Сбрасываем родительский указатель для дочерних узлов
            tmp = tmp->right;
        } while (tmp != child);
    }
    unionLists(min, child);//добавляем детей в список корней
    min->left->right = min->right;//удаляем минимум из списка корней
    min->right->left = min->left;



    if(min->right == min){
        clear(min);
        delete min;
        min = nullptr;
    }else{
        tmp = min->right;
        clear(min);
        delete min;
        min = nullptr;
        min = tmp;
        consolidate();
    }
    --size;
    return ans;
}


template<typename T>
void FibonacciHeap<T>::deleteNode(Node<T> *x) {
    decreaseKey(x, -2147483648);
}

template<typename T>
bool FibonacciHeap<T>::isEmpty() const {
    return size == 0;
}

#endif //PRIORITYQUEUE_FIBONACCIHEAP_H
