//
//  queu.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/16/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef queu_h
#define queu_h
#include "node.hpp"
using namespace std;
//Excepcion queu
class queuException : public std::exception {
private:
    std::string msg;
public:
    explicit queuException(const char* message) : msg(message) {}
    explicit queuException(const std::string& message) :msg(message) {}
    virtual ~queuException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};
template <class T>
class Queu{
public:
    //Constructor
    Queu();
    //Constructor copia
    Queu(T& copy);
    //Destructor
    ~Queu();
    //Vacia
    bool isEmpty()const;
    //Encolar
    void enqueu(T elem);
    //Desencolar
    T dequeue();
    //Frente
    T getFront();
    //contador
    size_t size();
    //Operator =
    Queu<T>& operator = (const Queu<T>&);
private:
    Node<T>* queu;
    //Copiar Todo
    void copyAll(const Queu<T>& copy);
    //DeleteAll
    void deleteAll();
    size_t count;
};
//Constructor
template<class T>
Queu<T>::Queu():count(0){
    queu = new Node<T>();
    if(queu==nullptr)
        throw queuException("Memoria no deisponible al inicializar Queu");
    queu->setNext(queu);
    queu->setPrev(queu);
    
}
//Constructor copia
template<class T>
Queu<T>::Queu(T &copy){
    copyAll(copy);
}
//Destructor
template<class T>
Queu<T>::~Queu<T>(){
    deleteAll();
    delete queu;
}
//Copiar todo
template <class T>
void Queu<T>::copyAll(const Queu<T> &copy){
    Node<T>* aux = copy.queu.getNext();
    while(aux != copy.queu){
        push(aux->getData());
        aux = aux->getNext();
    }
}
//Borrar todo
template <class T>
void Queu<T>::deleteAll(){
    if(isEmpty())
        return;
    Node<T>* aux;
    while(queu->getNext() != queu) {
        aux = queu->getNext();
        queu->setNext(queu->getNext()->getNext());
        delete aux;
    }
    count=0;
}
//Vacia
template<class T>
bool Queu<T>::isEmpty()const{
    return queu==queu->getNext();
}
//Encolar
template<class T>
void Queu<T>::enqueu(T elem){
    Node<T>* aux;
    try{
        aux=new Node<T>(elem);
    }catch(NodeException ex){
        throw queuException("Error al crear el nodo al Insertar Datos\n");
    }
    if(aux==nullptr)
        throw queuException("Error, no hay espacio de memoria al tratar de insetar");
    aux->setPrev(queu->getPrev());
    aux->setNext(queu);
    queu->getPrev()->setNext(aux);
    queu->setPrev(aux);
    count++;
}
//Desencolar
template<class T>
T Queu<T>::dequeue(){
    if(isEmpty())
        throw queuException("Insuficiencia de Datos, Dequeue");
    
    Node<T>* aux(queu->getNext());
    T result(aux->getData());
    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());
    delete aux;
    count--;
    return result;
}
//Frente
template<class T>
T Queu<T>::getFront(){
    if(isEmpty())
        throw queuException("Insuficiencia de Datos, GetFront");
    Node<T>* aux(queu);
    aux=aux->getNext();
    return aux->getData();
}
//Size
template<class T>
size_t Queu<T>::size(){
    return count;
}
//Operador =
template <class T>
Queu<T>& Queu<T>::operator=(const Queu<T> &q){
    deleteAll();
    copyAll(q);
    return *this;
}
#endif /* queu_h */
