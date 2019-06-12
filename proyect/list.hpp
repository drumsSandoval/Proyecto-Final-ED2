//
//  list.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/14/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef list_h
#define list_h
#include "node.hpp"
#include "console.hpp"
#include "nodeHuffman.hpp"
#include <fstream>
using namespace std;
class ListException : public std::exception {
private:
    std::string msg;
public:
    explicit ListException(const char* message) : msg(message) {}
    explicit ListException(const std::string& message) :msg(message) {}
    virtual ~ListException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};
template <class T>
class List {
private:
    Node<T>* header;
    unsigned int counter;
    
    bool isValidPos(Node<T>*);
public:
    List();
    ~List();
    List(const List<T> &);
    
    bool isEmpty();
    int size();
    void insertData(Node <T>*, const T&);
    void deleteData(Node <T>*);
    void Sort();
    Node<T>* getFirstPos();
    Node<T>* getLastPos();
    Node<T>* getPrevPos(Node<T>*);
    Node<T>* getNextPos(Node<T>*);
    Node<T>* findData(const T&);
    bool find(const T&);
    int findPos(const T&);
    T& retrieve (Node<T>*);
    Node<T>* retrieve(const int);
    T& operator [](unsigned idx);
    int operator[](Node<T>*);
    void printData();
    void desendentPrint();
    void deleteAll();
    void printDestinos(Console&);
    void printIndices(Console&);
    void printListaInvertida(Console&);

    
    void printDiccionary();//
    void saveDiccionary(string&);//
    string getHuffmanCode(char);//
    string getHuffmanData(std::string);//
    bool findHuffman(string&);//
    void generateDiccionary(char,string&);//
    string getBinaryHuffman();//
    
    bool find(const char);
    bool findh(const int);
};

template <class T>
bool List<T>::isValidPos(Node<T>* p) {
    if(isEmpty()) {
        return false;
    }
    
    Node<T>* aux = header->getNext();
    do {
        if(aux == p) {
            return true;
        }
        aux = aux->getNext();
    } while(aux != header);
    
    return false;
}

template <class T>
List<T>::List() {
    header =  new Node<T>();
    
    if(header == nullptr) {
        throw ListException("Memoria no disponible al iniciar la lista");
    }
    header->setNext(header);
    header->setPrev(header);
    
    counter = 0;
}

template <class T>
List<T>::~List() {
    deleteAll();
    delete header;
}

template <class T>
List<T>::List(const List<T>& l) : List() {
    Node<T>* aux = l.header.getNext();
    
    while(aux != l.header) {
        insertData(getLastPos(), aux->getData());
        aux = aux->getNext();
    };
}

template <class T>
bool List<T>::isEmpty() {
    return header == header->getNext();
}

template <class T>
void List<T>::insertData(Node <T>* p, const T& e) {
    if(!isValidPos(p) and p != nullptr) {
        throw ListException("Posición no valida al tratar de insertar");
    }
    
    Node<T>* aux;
    
    try {
        aux = new Node<T>(e);
    } catch (NodeException ex) {
        throw ListException("Error al crear el nodo al INSERTAR DATOS");
    }
    
    if(aux == nullptr) {
        throw ListException("Error, no hay espacio de memoria al tratar de insertar");
    }
    
    if(p == nullptr) {
        p = header;
    }
    
    aux->setPrev(p);
    aux->setNext(p->getNext());
    
    p->getNext()->setPrev(aux);
    p->setNext(aux);
    
    counter++;
}

template <class T>
void List<T>::deleteData(Node <T>* p) {
    if(!isValidPos(p)) {
        throw ListException("Error al eliminar, posicion no valida");
    }
    
    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());
    
    delete p;
    counter--;
}
template <class T>
int List<T>::size(){
    return counter-1;
}
template <class T>
Node<T>* List<T>::getFirstPos() {
    if (isEmpty()) {
        return nullptr;
    }
    
    return header->getNext();
}

template <class T>
Node<T>* List<T>::getLastPos() {
    if (isEmpty()) {
        return nullptr;
    }
    
    return header->getPrev();
}

template <class T>
Node<T>* List<T>::getPrevPos(Node<T>* p) {
    if(!isValidPos(p) or p == getFirstPos()) {
        return nullptr;
    }
    
    return p->getPrev();
}

template <class T>
Node<T>* List<T>::getNextPos(Node<T>* p) {
    if(!isValidPos(p) or p == getLastPos()) {
        return nullptr;
    }
    
    return p->getNext();
}

template <class T>
Node<T>* List<T>::findData(const T& p) {
    if(isEmpty()) {
        return nullptr;
    }
    
    Node<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData() == p) {
            return aux;
        }
        aux = aux->getNext();
    }
    return nullptr;
}
template <class T>
bool List<T>::find(const T &p){
    if(isEmpty()) {
        return false;
    }
    
    Node<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData() == p) {
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}
template <class T>
int List<T>::findPos(const T &p){
    if(isEmpty()) {
        return -1;
    }
    
    Node<T>* aux = header->getNext();
    int i=0;
    while(aux != header) {
        if(aux->getData() == p) {
            return i;
        }
        i++;
        aux = aux->getNext();
    }
    return -1;
}
template <class T>
T& List<T>::retrieve(Node<T>* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion no valida en RETRIEVE");
    }
    return p->getData();
}

template <class T>
void List<T>::printData() {
    if(isEmpty()) {
        return;
    }
    
    Node<T>* aux = header->getNext();
    cout<<"┌───────────────────────────────────────────────────┐\n";
    cout<<"│                   TDA                             │\n";
    cout<<"└───────────────────────────────────────────────────┘\n";
    while(aux != header) {
        std::cout << aux->getData() << endl;
        aux = aux->getNext();
    }
}
template <class T>
void List<T>::desendentPrint(){
    if(isEmpty()){
        return;
    }
    Node<T>* aux = header->getPrev();
    cout<<"┌───────────────────────────────────────────────────┐\n";
    cout<<"│               Orden Descendente                   │\n";
    cout<<"└───────────────────────────────────────────────────┘\n";
    while(aux!=header){
        std::cout << aux->getData() << endl;
        aux = aux->getPrev();
    }
}
template <class T>
void List<T>::deleteAll() {
    if(isEmpty()) {
        return;
    }
    
    Node<T>* aux;
    
    while(header->getNext() != header) {
        aux = header->getNext();
        header->setNext(header->getNext()->getNext());
        delete aux;
    }
    
    counter = 0;
}
template <class T>
void List<T>::Sort(){
    if(isEmpty())
        return;
    Node<T>* j;
    Node<T>* i;
    Node<T>* s;
    bool band;
    i=getLastPos();
    do{
        band=false;
        j=getFirstPos();
        while(j!=header->getPrev()){
            s=j->getNext();
            if(j->getData()>s->getData()){
                T aux;
                aux=j->getData();
                j->getData()=j->getNext()->getData();
                j->getNext()->getData()=aux;
                band=true;
            }
            j=j->getNext();
        }
        i=i->getPrev();
    }while(band);
}
template <class T>
T& List<T>::operator[](unsigned idx){
    if(isEmpty())
        throw ListException("[] on empty list");
    if(idx>=counter){
        throw ListException("[] on invalid position");
    }
    int i=0;
    Node<T>* it;
    it=header->getNext();
    while(i<idx){
        it=it->getNext();
        i++;
    }
    return it->getData();
}
template <class T>
void List<T>::printDestinos(Console & graphics){
    if(isEmpty()){
        return;
    }
    Node<T>* aux = header->getPrev();
    int auxf,auxe,i;
    system("clear");
    graphics.moveTo(2,4);
    cout<<"┌─────────────────────────────────────────────────────────────────────────┐";
    for(int i=3;i<=24;i++){
        graphics.moveTo(i,4);
        cout<<"│";
        graphics.moveTo(i, 78);
        cout<<"│";
    }
    graphics.moveTo(24,4);
    cout<<"└─────────────────────────────────────────────────────────────────────────┘";
    graphics.setColor(graphics.FG_WHITE);
    graphics.moveTo(3, 15);
    cout<<"\t│               Orden Descendente                   │\n";

    auxf=7; auxe=8;
    i=0;
    while(aux!=header){
        graphics.moveTo(auxf,auxe);
        std::cout << aux->getData().name;
        graphics.moveTo(auxf+1,auxe);
        std::cout <<"Code : "<< aux->getData().code;
        graphics.moveTo(auxf+2, auxe);
        std::cout<<"Zona  : "<< aux->getData().zone;
        aux = aux->getPrev();
        i++;
        auxe+=18;
        if(i==3||i==6){
            auxf+=5;
            auxe=8;
        }
    }
    cin.get();
}
template <class T>
void List<T>::printIndices(Console &graphics){
    if(isEmpty()){
        return;
    }
    Node<T>* aux = header->getPrev();
    int auxf,auxe,i;
    system("clear");
    graphics.moveTo(2,4);
    cout<<"┌─────────────────────────────────────────────────────────────────────────┐";
    for(int i=3;i<=24;i++){
        graphics.moveTo(i,4);
        cout<<"│";
        graphics.moveTo(i, 78);
        cout<<"│";
    }
    graphics.moveTo(24,4);
    cout<<"└─────────────────────────────────────────────────────────────────────────┘";
    graphics.setColor(graphics.FG_WHITE);
    graphics.moveTo(4, 15);
    cout<<"\t│                  INDICES                          │\n";
  
    auxf=7; auxe=8;
    i=0;
    while(aux!=header){
        graphics.moveTo(auxf,auxe);
        std::cout<<"  Key : " << aux->getData().getKey();
        graphics.moveTo(auxf+1,auxe);
        std::cout << "  Direccion : "<< aux->getData().getAddress();
        aux = aux->getPrev();
        i++;
        auxe+=18;
        if(i==3||i==6){
            auxf+=4;
            auxe=8;
        }
    }
    cin.get();
}
template <class T>
int List<T>::operator[](Node<T>* pos){
    Node<T>* aux(header->getNext());
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
void List<T>::printListaInvertida(Console & graphics){
    if(isEmpty()){
        return;
    }
    Node<T>* aux = header->getNext();
    int auxf;
    graphics.setColor(graphics.FG_DARK_CYAN);
    graphics.moveTo(3, 15);
    cout<<"\t┌────────────────────────────────-───────┐\n";
    graphics.moveTo(4, 15);
    cout<<"\t│          LISTA INVERTIDA               │\n";
    graphics.moveTo(5, 15);
    cout<<"\t└────────────────────────────────────────┘\n";
    graphics.setColor(graphics.FG_LIGHT_GRAY);
    graphics.moveTo(7, 8);
    cout<<"KEY";
    graphics.moveTo(7, 22);
    cout<<"DIR NODO";
    graphics.moveTo(7, 37);
    cout<<"SIG SECUNDARIO";
    graphics.moveTo(7, 60);
    cout<<"SIG ENLAZADO";
    auxf=9;
    graphics.setColor(graphics.FG_WHITE);
    while(aux!=header){
        graphics.moveTo(auxf, 8);
        cout<<aux->getData().first;
        graphics.moveTo(auxf, 19);
        cout<<aux;
        graphics.moveTo(auxf, 37);
        if(aux->getData().second==nullptr)
            cout<<"    nullptr";
        else
            cout<<aux->getData().second;
        graphics.moveTo(auxf, 58);
        if(aux->getNext()==header)
            cout<<"nullptr";
        else
            cout<<aux->getNext();
        
        aux=aux->getNext();
        auxf+=2;
    }
    cin.get();
    
}
template <class T>
Node<T>* List<T>::retrieve(const int pos){
    if(pos==-1)
        return nullptr;
    if(pos<-1&&pos>counter){
        throw invalid_argument("RETRIEVE DATA\n");
    }
    Node<T>* aux(header->getNext());
    for(int i=0;i<pos;++i)
        aux=aux->getNext();
    return aux;
}
template <class T>
void List<T>::generateDiccionary(char  p, string &s){
    if(isEmpty()) {
        return;
    }
    
    Node<T>* aux = header->getNext();
    int i=0;
    while(aux != header) {
        if(aux->getData().first == p) {
            aux->getData().second.second = s;
        }
        i++;
        aux = aux->getNext();
    }
}
//
template <class T>
void List<T>::printDiccionary(){
    Node<T>* aux = header->getNext();
    cout<<"┌───────────────────────────────────────────────────┐\n";
    cout<<"│              Diccionario de datos                 │\n";
    cout<<"└───────────────────────────────────────────────────┘\n";
    while(aux != header) {
        std::cout << aux->getData().first <<" : "<<aux->getData().second.second <<endl;
        aux = aux->getNext();
    }
}
//
template <class T>
string List<T>::getHuffmanCode(char p){
    if(isEmpty()) {
        return"errror :( ";
    }
    
    Node<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData().first == p) {
            return aux->getData().second.second;
        }
        
        aux = aux->getNext();
    }
    return"errror :( ";
}
//
template <class T>
void List<T>::saveDiccionary(string& a){
    if(isEmpty()) {
        return;
    }
    Node<T>* aux = header->getNext();
    ofstream archive("/Users/oscarsandoval/Desktop/proyect/Diccionario de datos.txt",ios::out);
    while(aux != header) {
        archive<<aux->getData().first<<"@"<<aux->getData().second.second<<endl;
        aux = aux->getNext();
    }
    archive.close();
    archive.open("/Users/oscarsandoval/Desktop/proyect/proyect/a.txt",ios::out);
    archive<<a;
    archive.close();
}
//
template <class T>
string List<T>::getHuffmanData(std::string p){
    if(isEmpty()) {
        return" ";
    }
    Node<T>* aux = header->getNext();
    while(aux != header) {
        if(aux->getData().second == p) {
            return aux->getData().first;
        }
        
        aux = aux->getNext();
    }
    return " ";
}
//huffman
template <class T>
string List<T>::getBinaryHuffman(){
    string myStr;
    ifstream archive("/Users/oscarsandoval/Desktop/proyect/proyect/a.txt");
    getline(archive,myStr);
    return myStr;
}

template <class T>
bool List<T>::findHuffman(string& p){
    if(isEmpty()) {
        return false;
    }
    Node<T>* aux = header->getNext();
    while(aux != header) {
        if(aux->getData().second == p) {
            
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}


template <class T>
bool List<T>::findh(const int p){
    if(isEmpty()) {
        return false;
    }
    
    Node<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData() == p) {
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template <class T>
bool List<T>::find(const char p){
    if(isEmpty()) {
        return false;
    }
    
    Node<T>* aux = header->getNext();
    
    while(aux != header) {
        if(aux->getData().first == p) {
            aux->getData().second.first+=1;
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}
#endif /* list_h */
