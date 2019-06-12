//
//  ListaEstatica.hpp
//  proyect
//
//  Created by Oscar Sandoval on 3/2/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef ListaEstatica_h
#define ListaEstatica_h
#include <stdexcept>//Para pode lanzar excepciones
#include <iostream>
using namespace std;
template <typename T>//Declaracion de plantilla
class ListaEstatica{
public:
    //index(0) asigna 0 al atributo index
    ListaEstatica<T>() : index(0){}
    bool empty()const;
    bool full();
    size_t size();
    void insert(const T& elem);
    void print();
    bool find(const T& elem);
    void remove(size_t idx);
    T& operator[](size_t idx);
private:
    //size_t es un entero sin signo
    static const size_t CAPACITY = 30;
    T elements[CAPACITY];
    size_t index;
    
};
template<typename T>
bool ListaEstatica<T>::empty()const{
    return index==0;
}
template<typename T>
bool ListaEstatica<T>::full(){
    return index==CAPACITY;
}
template<typename T>
size_t ListaEstatica<T>::size(){
    return index;
}
template<typename T>
void ListaEstatica<T>::insert(const T &elem){
    if(full())
        throw invalid_argument("full list");
    elements [index]=elem;
    index++;
}
template<typename T>
void ListaEstatica<T>::print(){
    for(int i=0;i<index;i++){
        std::cout<<elements[i]<<endl;
    }
}
template<typename T>
bool ListaEstatica<T>::find(const T &elem){
    int i=0;
    while(i<index){
        if(elem==elements[i]){
            return true;
        }
        i++;
    }
    return false;
}
template<typename T>
void ListaEstatica<T>::remove(size_t idx){
    if(idx>index){
        throw invalid_argument("poscision  invalida");
    }
    for(size_t i=idx;i<index-1;i++){
        elements[i]=elements[i+1];
        
    }
    index--;
}
template<typename T>
T& ListaEstatica<T>::operator[](size_t idx){
    if(empty())
        throw invalid_argument("[] on empty list");
    if(idx>=index)
        throw invalid_argument("[] on invalid position ");
    return elements[idx];
}
#endif /* ListaEstatica_h */
