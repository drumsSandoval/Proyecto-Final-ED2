//
//  vertice.cpp
//  proyect
//
//  Created by Oscar Sandoval on 2/21/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#include "vertice.hpp"
using namespace std;
Vertice::Vertice():active(0){
    
}
void Vertice::setData(string  data){
    for(int i=0;i<10;i++)
        this->data[i]='\0';
    for(int i=0;data[i];i++)
        this->data[i]=data[i];
}
void Vertice::setName(std::string data){
    for(int i=0;i<20;i++)
        this->name[i]='\0';
    for(int i=0;data[i];i++)
        this->name[i]=data[i];
}
string Vertice::getName(){
    string a;
    for(int i=0;name[i];i++)
        a+=name[i];
    return a;
}
void Vertice::setActive(int active){
    this->active=active;
}
string Vertice::getData(){
    string a;
    for(int i=0;data[i];i++)
        a+=data[i];
    return a;
}
int& Vertice::getActive(){
    return active;
}
bool Vertice::operator==(Vertice& v)const{
    return strcmp(data,v.data)==0;
}
bool Vertice::operator!=(Vertice &v)const{
    return strcmp(data,v.data)!=0;
}
Vertice Vertice::operator=(const Vertice v){
    for(int i=0;i<10;i++)
        this->data[i]='\0';
    for(int i=0;v.data[i];i++){
        this->data[i]=v.data[i];
    }
    for(int i=0;i<20;i++)
        this->name[i]='\0';
    for(int i=0;v.name[i];i++){
        this->name[i]=v.name[i];
    }
    this->active=v.active;
    return *this;
}
ostream& operator <<(ostream &os,Vertice& c){
    os<<c.getData();
    return os;
}
