//
//  huffman.hpp
//  proyect
//
//  Created by Oscar Sandoval on 5/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef huffman_h
#define huffman_h
#include "nodeHuffman.hpp"
#include "list.hpp"
using namespace std;
class HuffmanException : public std::exception {
private:
    std::string msg;
public:
    explicit HuffmanException(const char* message) : msg(message) {}
    explicit HuffmanException(const std::string& message) :msg(message) {}
    virtual ~HuffmanException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

template <class T>
class Huffman{
private:
    NodeHuffman<T>* header;
    int counter;
    void preOrder(NodeHuffman<T>*,string&,List<T>&);
    void printTree(NodeHuffman<T>*,int,Console&);
    void printTree(NodeHuffman<T>*,int& x, int y,Console&);
public:
    Huffman();
    void preOder();
    int size();
    int findPos(string&);
    ~Huffman();
    void deleteAll(NodeHuffman<T>*);
    
    void generateTree();
    void insertData(NodeHuffman<T>*, T&);
    void sort(NodeHuffman<T>*, NodeHuffman<T>*);
    void remove(NodeHuffman<T>*,NodeHuffman<T>*,NodeHuffman<T>*);
    
    bool isEmpty();
    bool isValidPos(NodeHuffman<T>*);
    bool find(char);
    
    void generateDiccionary(List<T>&);
    
    void printTree();
    
    NodeHuffman<T>* insertTree(NodeHuffman<T>*, T&);
    
    NodeHuffman<T>* lowerData(int);
    NodeHuffman<T>* upperData(int);
    
    NodeHuffman<T>* getLastPos();
    NodeHuffman<T>* getFirstPos();
    NodeHuffman<T>* getNextPos(NodeHuffman<T>*);
    NodeHuffman<T>* getPrevPos(NodeHuffman<T>*);
    
    NodeHuffman<T>* getPos(T&);
    
    void getFrecuency(List<int>&);
    
    
    
    NodeHuffman<T>* retrieve(const int);
    T& operator [](unsigned idx);
    int operator[](NodeHuffman<T>*);
};

template <class T>
Huffman<T>::Huffman():counter(0){
    header = new NodeHuffman<T>();
    
    if(header == nullptr){
        throw HuffmanException("Trono en el constructor");
    }
    header->setNext(header);
    header->setPrev(header);
}

template <class T>
Huffman<T>::~Huffman(){
    deleteAll(header->getNext());
}

template <class T>
void Huffman<T>::deleteAll(NodeHuffman<T>* r){
    if(r==nullptr){
        header->setNext(header);
        header->setLeft(nullptr);
        header->setRight(nullptr);
        header->setPrev(header);
        return;
    }
    deleteAll(r->getLeft());
    deleteAll(r->getRight());
    delete r;
}

template <class T>
int Huffman<T>::size(){
    return counter-1;
}

template <class T>
int Huffman<T>::findPos(string & p){
    if(isEmpty()) {
        return -1;
    }
    
    NodeHuffman<T>* aux = header->getNext();
    int i=0;
    while(aux != header) {
        if(aux->getData().first == p) {
            return i;
        }
        i++;
        aux = aux->getNext();
    }
    return -1;
}

template <class T>
void Huffman<T>::generateTree(){
    //cout<<size()<<endl; cin.get();
    NodeHuffman<T>* h1(header->getNext());
    NodeHuffman<T>* h2(h1->getNext());
    T data;
    /*
     cout<<"h1 : "<<h1->getData().second.first<<endl;
     cin.get();
     cout<<"h2 : "<<h2->getData().second.first<<endl;
     cin.get();
     cout<<h1->getData().second.first+h2->getData().second.first<<endl;
     cin.get();*/
    data.second.first= h1->getData().second.first + h2->getData().second.first;
    data.first = '*';
    NodeHuffman<T>* h3(insertTree(getPos(data), data));
    remove(h3,h1,h2);
}

template <class T>
void Huffman<T>::insertData(NodeHuffman<T> *pos, T & data){
    if(!isValidPos(pos) and pos!=nullptr){
        throw HuffmanException("Posicion no valida para insertar");
    }
    
    NodeHuffman<T>* aux;
    
    try{
        aux = new NodeHuffman<T>(data);
    }catch(NodeHuffmanException& ex){
        throw HuffmanException("Error al insertar");
    }
    
    if(aux == nullptr){
        throw HuffmanException("Error al insertar");
    }
    
    if(pos == nullptr){
        pos = header;
    }
    
    aux->setPrev(pos);
    aux->setNext(pos->getNext());
    
    pos->getNext()->setPrev(aux);
    pos->setNext(aux);
    
    ++counter;
}

template <class T>
void Huffman<T>::sort(NodeHuffman<T>*r, NodeHuffman<T>*l){
    if(r==l){
        return;
    }
    bool band;
    NodeHuffman<T>* i=l;
    NodeHuffman<T>* aux;
    NodeHuffman<T>* j;
    string a,b;
    do{
        band=false;
        j=r;
        while(j!=i){
            aux = j->getNext();
            a=j->getData().first;
            b=aux->getData().first;
            /* cout<<strcmp(a.c_str(), b.c_str());cin.get();
             if(strcmp(a.c_str(),b.c_str())>1){*/
            if(a>b){
                band=true;
                T auxx;
                auxx = j->getData();
                j->getData()=j->getNext()->getData();
                j->getNext()->getData()=auxx;
            }
            j=j->getNext();
        }
        i=i->getPrev();
    }while(band);
}

template <class T>
void Huffman<T>::remove(NodeHuffman<T> * h1,NodeHuffman<T>* h2,NodeHuffman<T>*h3){
    if(!isValidPos(h1) || !isValidPos(h2) || !isValidPos(h3)){
        throw HuffmanException("Error al eliminar , posicion no valid");
    }
    header->setNext(h3->getNext());
    h3->getNext()->setPrev(header);
    
    
    
    h3->unique();
    h2->unique();
    
    
    h1->setLeft(h2);
    h1->setRight(h3);
    counter-=2;
}

template <class T>
bool Huffman<T>::isEmpty(){
    return header == header->getNext();
}

template <class T>
bool Huffman<T>::isValidPos(NodeHuffman<T> * pos){
    if(isEmpty()){
        return false;
    }
    if(pos==header)return true;
    NodeHuffman<T>* aux(header->getNext());
    do{
        if(aux == pos){
            return true;
        }
        aux = aux->getNext();
        
    }while(aux != header);
    
    return false;
}

template <class T>
NodeHuffman<T>* Huffman<T>::lowerData(int p){
    if(isEmpty()) {
        return nullptr;
    }
    
    NodeHuffman<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData().second.first == p) {
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}

template <class T>
NodeHuffman<T>* Huffman<T>::upperData(int p){
    if(isEmpty()) {
        return nullptr;
    }
    
    NodeHuffman<T>* aux = header->getNext();
    while(aux != header) {
        if(aux->getData().second.first == p) {
            if(aux->getNext()== header){
                return aux;
            }
            while(aux!=header && aux->getData().second.first==p){
                aux = aux->getNext();
            }
            return aux->getPrev();
        }
        
        aux = aux->getNext();
    }
    return nullptr;
}

template <class T>
bool Huffman<T>::find(char p){
    if(isEmpty()) {
        return false;
    }
    
    NodeHuffman<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData().first == p) {
            aux->getData().second.first;
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template <class T>
NodeHuffman<T>* Huffman<T>::getLastPos(){
    if (isEmpty()) {
        return nullptr;
    }
    return header->getPrev();
}

template <class T>
NodeHuffman<T>* Huffman<T>::getFirstPos(){
    return header->getNext();
}

template <class T>
NodeHuffman<T>* Huffman<T>::getNextPos(NodeHuffman<T>* h){
    if(!isValidPos(h) or h == getLastPos()) {
        return nullptr;
    }
    return h->getNext();
}

template <class T>
NodeHuffman<T>* Huffman<T>::getPrevPos(NodeHuffman<T> * h ){
    if(!isValidPos(h) or h == getFirstPos()) {
        return nullptr;
    }
    return h->getPrev();
}

template <class T>
NodeHuffman<T>* Huffman<T>::retrieve(const int pos){
    if(pos==-1)
        return nullptr;
    if(pos<-1&&pos>counter){
        throw invalid_argument("RETRIEVE DATA\n");
    }
    NodeHuffman<T>* aux(header->getNext());
    for(int i=0;i<pos;++i)
        aux=aux->getNext();
    return aux;
}

template <class T>
T& Huffman<T>::operator[](unsigned idx){
    if(isEmpty())
        throw HuffmanException("[] on empty list");
    if(idx>=counter){
        throw HuffmanException("[] on invalid position");
    }
    int i=0;
    NodeHuffman<T>* it;
    it=header->getNext();
    while(i<idx){
        it=it->getNext();
        i++;
    }
    return it->getData();
}

template <class T>
int Huffman<T>::operator[](NodeHuffman<T>* pos){
    NodeHuffman<T>* aux(header->getNext());
    int i=0;
    while(i<counter){
        if(aux==pos){
            return i;
        }
        i++;
        aux=aux->getNext();
    }
    return -1;
}

template <class T>
NodeHuffman<T>* Huffman<T>::getPos(T & data){
    if(isEmpty()){
        return nullptr;
    }
    NodeHuffman<T>* aux(header->getNext());
    while(aux!=header){
        if(aux->getData().second.first>=data.second.first){
            return aux->getPrev();
        }
        if(aux->getNext()==header){
            return aux;
        }
        aux = aux->getNext();
        
    }
    cout<<"valio madre";cin.get();
    return nullptr;
}
template <class T>
void Huffman<T>::getFrecuency(List<int>& list){
    
    int i=0;
    NodeHuffman<T>* aux(header->getNext());
    while(i<counter){
        if(!list.findh(aux->getData().second.first)){
            list.insertData(list.getLastPos(), aux->getData().second.first);
        }
        aux = aux->getNext();
        i++;
    }
    
}

template <class T>
NodeHuffman<T>* Huffman<T>::insertTree(NodeHuffman<T> * pos, T & data){
    if(!isValidPos(pos) and pos!=nullptr){
        throw HuffmanException("Posicion no valida para insertar");
    }
    
    NodeHuffman<T>* aux;
    
    try{
        aux = new NodeHuffman<T>(data);
    }catch(NodeHuffmanException& ex){
        throw HuffmanException("Error al insertar");
    }
    
    if(aux == nullptr){
        throw HuffmanException("Error al insertar");
    }
    
    if(pos == nullptr){
        pos = header;
    }
    
    aux->setPrev(pos);
    aux->setNext(pos->getNext());
    
    pos->getNext()->setPrev(aux);
    pos->setNext(aux);
    
    ++counter;
    return aux;
}

template <class T>
void Huffman<T>::preOder(){
    string a;
    List<T> aux;
    preOrder(header->getNext(),a,aux);
}

template <class T>
void Huffman<T>::preOrder(NodeHuffman<T> * h,string& myStr,List<T>& list){
    if(h==nullptr){
        return;
    }
    string aux=myStr;
    h->getData().second.second = myStr;
    if(h->getData().first!='*'){
        list.generateDiccionary(h->getData().first, myStr);
    }
    myStr+="0";
    preOrder(h->getLeft(),myStr,list);
    aux+="1";
    preOrder(h->getRight(),aux,list);
}

template <class T>
void Huffman<T>::generateDiccionary(List<T> & list){
    string myStr;
    preOrder(header->getNext(), myStr, list);
}

template <class T>
void Huffman<T>::printTree(NodeHuffman<T>* r, int c ,Console & graphics){
    /*
     graphics.moveTo(4, 27);
     cout<<"R"<<endl;*/
    if(r==nullptr||r==header){
        return;
        
    }
    printTree(r->getRight(), c+1, graphics);
    for(int i = 0;i<c;i++){
        cout<<"   ";
    }
    cout<<r->getData().first<<"/"<<r->getData().second.first<<endl;
    printTree(r->getLeft(), c+1, graphics);
}

template <class T>
void Huffman<T>::printTree(){
    int a(0);
    Console g;
    system("clear");
    printTree(header->getNext(),a ,g);
    //    printTree(header->getNext(), a, 0, g);
}

template <class T>
void Huffman<T>::printTree(NodeHuffman<T> * r, int &x, int y,Console& g){
    if(r==nullptr)return;
    x+=5;
    
    printTree(r->getLeft(), x, y+2,g);
    g.moveTo(15+y, 10+x-y);
    cout<<r->getData().first<<"/"<<r->getData().second.first<<endl;
    printTree(r->getRight(), x, y+2,g);
}
#endif /* huffman_h */
