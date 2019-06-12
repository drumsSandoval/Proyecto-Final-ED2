//
//  indices.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/14/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "indices.hpp"
#include <fstream>
Indices::Indices(){
    
}
//Setters
void Indices::setAddress(long address){
    this->address=address;
}
void Indices::setKey(int key){
       this->key=key;
}
int Indices::getKey(){
    return key;
}
long Indices::getAddress(){
    return address;
}
bool Indices::operator>(Indices &i)const{
    return key>i.key;
}
bool Indices::operator<(const Indices &i)const{
    return key<i.key;
}
bool Indices::operator<=(const Indices &i)const{
    return key<=i.key;
}
bool Indices::operator>=(const Indices &i)const{
    return key>=i.key;
}
Indices Indices::operator=(const Indices &i){
    key=i.key;
    address=i.address;
    return *this;
}
bool Indices::operator==(const Indices &i)const{
    return key==i.key;
}
void Indices::save(List<Indices>& list){
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Indices.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        archive.write((char*)&list[i],sizeof(Indices));
        i++;
    }
    archive.close();
}


IndiceSecundario::IndiceSecundario(List<IndiceSecundario>&list,List<nodo>& listaInvertida):address(nullptr) {
    fstream archive("/Users/oscarsandoval/Desktop/proyect/ListaInvertida.txt",ios::in|ios::out);
    if(!archive.good()){
        return;
    }
    string myStr;
    nodo aux;
    getline(archive,myStr);
    stringstream stream(myStr);
    while(getline(stream, myStr,'|')){
        aux.first=stoi(myStr);
        listaInvertida.insertData(listaInvertida.getLastPos(),aux);
    }
    getline(archive,myStr);
    stringstream stream2(myStr);
    int i=0;
    while(getline(stream2, myStr,'|')){
        listaInvertida[i].second=listaInvertida.retrieve(stoi(myStr));
        i++;
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/IndiceSecundario.txt");
    getline(archive,myStr);
    stringstream stream3(myStr);
    while(getline(stream3, myStr,'|')){
        setKey(myStr);
        list.insertData(list.getLastPos(),*this);
    }getline(archive,myStr);
    stringstream stream4(myStr);
    i=0;
    while(getline(stream4, myStr,'|')){
        list[i].setAddress(listaInvertida.retrieve(stoi(myStr)));
        i++;
    }
    archive.close();
}
IndiceSecundario::IndiceSecundario(){}

void IndiceSecundario::setAddress(Node<nodo>* a) {
    address=a;
}

void IndiceSecundario::setKey(string name) {
    key=name;
}

Node<nodo>* IndiceSecundario::getAddress() {
    return address;
}

std::string IndiceSecundario::getKey() { 
    return key;
}

bool IndiceSecundario::operator>(IndiceSecundario &z) const {
    return this->key>z.key;
}

bool IndiceSecundario::operator<(const IndiceSecundario &z) const {
    return key<z.key;
}

bool IndiceSecundario::operator>=(const IndiceSecundario &z) const {
    return key>=z.key;
}

bool IndiceSecundario::operator<=(const IndiceSecundario &z) const {
    return key<=z.key;
}

bool IndiceSecundario::operator==(const IndiceSecundario &z) const {
    return key==z.key;
}

IndiceSecundario IndiceSecundario::operator=(const IndiceSecundario &z) {
    key=z.key;
    address=z.address;
    return *this;
}

void IndiceSecundario::save(List<IndiceSecundario> &list,List<nodo>&listaInvertida) {
    ofstream save;
    save.open("/Users/oscarsandoval/Desktop/proyect/IndiceSecundario.txt",ios::out);
    int i=0;
    while(i<=list.size()){
        save<<list[i].getKey()<<"|";
        i++;
    }
    save<<endl;
    i=0;
    while(i<=list.size()){
        save<<listaInvertida[list[i].getAddress()]<<"|";
        i++;
    }
    save<<endl;
    save.close();
    
}
