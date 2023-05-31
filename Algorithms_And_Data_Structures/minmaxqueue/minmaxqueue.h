//
// Created by Alexander on 31.05.2023.
//

#ifndef MINMAXQUEUE_MINMAXQUEUE_H
#define MINMAXQUEUE_MINMAXQUEUE_H

#include <iostream>
#include <fstream>

struct Triple{
    int data = 0;
    int min = 0;
    int max = 0;
};

//стек на массивах(мы заранее знаем размер), храним инимум и максимум каждого элеманта ниже
class Stack{
    Triple *arr;
    int len;
public:

    Stack(int maxLen){
        arr = new Triple[maxLen];
        len = 0;
    }

    ~Stack(){
        delete[]arr;
    }

    void push(int A){
        if(empty()) {
            arr[0].data = A;
            arr[0].max = A;
            arr[0].min = A;
            ++len;
        }else{
            arr[len].data = A;
            arr[len].min = std::min(arr[len - 1].min, A);
            arr[len].max = std::max(arr[len - 1].max, A);
            ++len;
        }
    }

    int pop(){
        if(empty()) {
            throw "Stack is empty";
        }
        --len;
        return arr[len].data;
    }

    bool empty() const{
        return len == 0;
    }

    int min(){
        if(empty()) {
            throw "Stack is empty";
        }
        return arr[len - 1].min;
    }

    int max() {
        if (empty()) {
            throw "Stack is empty";
        }
        return arr[len - 1].max;
    }
};




//Очередь на двух стеках. Левый для пуша, правый для попа
class Queue{
    Stack *left;
    Stack *right;
public:

    explicit Queue(int maxLen){
        left = new Stack(maxLen);
        right = new Stack(maxLen);
    }

    ~Queue(){
        delete left;
        delete right;
    }

    void push(int A){
        left->push(A);
    }

    void pop(){
        if(empty()){
            throw "Queue is empty";
        }
        if(right->empty()){
            while(!left->empty()){
                right->push(left->pop());
            }
        }
        right->pop();
    }

    bool empty(){
        return left->empty() and right->empty();
    }

    int min(){
        if(empty()){
            throw "Queue is empty";
        }
        if(left->empty()){
            return right->min();
        }
        if(right->empty()){
            return left->min();
        }
        return std::min(left->min(), right->min());
    }
    int max(){
        if(empty()) {
            throw "Queue is empty";
        }
        if(left->empty()){
            return right->max();
        }
        if(right->empty()){
            return left->max();
        }
        return std::max(left->max(), right->max());
    }
};
#endif //MINMAXQUEUE_MINMAXQUEUE_H
