//
//  nodeHuffman.hpp
//  proyect
//
//  Created by Oscar Sandoval on 5/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef nodeHuffman_h
#define nodeHuffman_h
#include <exception>
#include <iostream>
typedef std::pair<int,std::string> binary;
typedef std::pair<char,binary> data;

class NodeHuffmanException : public std::exception {
private:
    std::string msg;
public:
    explicit NodeHuffmanException(const char* message) : msg(message) {}
    explicit NodeHuffmanException(const std::string& message) :msg(message) {}
    virtual ~NodeHuffmanException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

template <class T>
class NodeHuffman {
public:
    NodeHuffman<T>();
    NodeHuffman<T>(const T&);
    NodeHuffman<T>(NodeHuffman<T>*);
    ~NodeHuffman<T>();
    
    T& getData();
    T* getDataPtr();
    
    NodeHuffman <T>* getPrev();
    NodeHuffman<T>* getNext();
    
    NodeHuffman<T>* getRight();
    NodeHuffman<T>* getLeft();
    
    void setData(const T&);
    void setDataPtr(T*);
    
    void setPrev(NodeHuffman<T>*);
    void setNext(NodeHuffman<T>*);
    
    void setRight(NodeHuffman<T>*);
    void setLeft(NodeHuffman<T>*);
    
    void unique();
private:
    T* dataPtr;
    NodeHuffman<T>* prev;
    NodeHuffman<T>* next;
    NodeHuffman<T>* right;
    NodeHuffman<T>* left;
};

template <class T>
NodeHuffman<T>::NodeHuffman() {
    prev = nullptr;
    next = nullptr;
    dataPtr = nullptr;
    right = nullptr;
    left = nullptr;
}

template <class T>
NodeHuffman<T>::NodeHuffman(const T& e) : NodeHuffman() {
    dataPtr = new T(e);
    if(dataPtr == nullptr) {
        throw NodeHuffmanException("Memoria no disponible al crear nodo");
    }
}

template <class T>
NodeHuffman<T>::~NodeHuffman() {
    delete dataPtr;
}

template <class T>
T& NodeHuffman<T>::getData() {
    return *dataPtr;
}

template <class T>
T* NodeHuffman<T>::getDataPtr() {
    return dataPtr;
}

template <class T>
NodeHuffman<T>* NodeHuffman<T>::getPrev() {
    return prev;
}

template <class T>
NodeHuffman<T>* NodeHuffman<T>::getLeft(){
    return left;
}

template <class T>
NodeHuffman<T>* NodeHuffman<T>::getRight(){
    return right;
}

template <class T>
NodeHuffman<T>* NodeHuffman<T>::getNext() {
    return next;
}

template <class T>
void NodeHuffman<T>::setData(const T& e) {
    if(dataPtr == nullptr) {
        dataPtr = new T(e);
        if(dataPtr == nullptr) {
            NodeHuffmanException("Error en SET DATA");
        }
        return;
    }
    
    *dataPtr = e;
}
template <class T>
void NodeHuffman<T>::setDataPtr(T* ptr) {
    dataPtr = ptr;
}

template <class T>
void NodeHuffman<T>::setPrev(NodeHuffman<T>* ptr) {
    prev = ptr;
}

template <class T>
void NodeHuffman<T>::setNext(NodeHuffman<T>* ptr) {
    next = ptr;
}

template <class T>
void NodeHuffman<T>::setRight(NodeHuffman<T> *ptr){
    right = ptr;
}

template <class T>
void NodeHuffman<T>::setLeft(NodeHuffman<T>* ptr){
    left = ptr;
}
template <class T>
void NodeHuffman<T>::unique(){
    next=nullptr;
    prev=nullptr;
}

#endif /* nodeHuffman_h */
