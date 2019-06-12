//
//  stack.hpp
//  proyect
//
//  Created by Oscar Sandoval on 2/21/19.
//  Copyright © 2019 Oscar Sandoval. All rights reserved.
//

#ifndef stack_h
#define stack_h
#include <string>
#include <exception>
//Definicion
template <class T, int ARRAYSIZE = 36>
class Stack
{
public:
    class Exception: public std::exception
    {
    public:
        explicit Exception(const char* message): msg(message) {}
        explicit Exception(const std::string& message): msg(message) {}
        virtual ~Exception() noexcept {}
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    protected:
        std::string msg;
    };
    
private:
    T data[ARRAYSIZE];
    int top;
    
    void copyAll(const Stack<T, ARRAYSIZE> &s);
    
public:
    Stack();
    Stack(const Stack<T, ARRAYSIZE> &s);
    
    bool isEmpty()const;
    bool isFull();
    
    void push(const T &e);
    T pop();
    T getTop() const;
    
    Stack<T, ARRAYSIZE> &operator = (const Stack<T, ARRAYSIZE> &s);
    
};

//Implementacion

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack<T, ARRAYSIZE> &s)
{
    for (int i(0); i <= s.top; i++) {
        data[i] = s.data[i];
    }
    
    top = s.top;
}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack() : top(-1) {}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack<T, ARRAYSIZE> &s)
{
    copyAll(s);
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty()const
{
    return top == -1;
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull()
{
    return top == ARRAYSIZE -1;
}

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T &e)
{
    if (isFull()) {
        throw Exception("Desbordamiento de datos, push");
    }
    
    data[++top] = e;
}

template<class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::pop()
{
    if (isEmpty()) {
        throw Exception("Insuficiencia de datos, pop");
    }
    
    return data[top--];
}

template<class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::getTop() const
{
    if (isEmpty()) {
        throw Exception("Insuficiencia de datos, getTop");
    }
    
    return data[top];
}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>&Stack<T, ARRAYSIZE>::operator = (const Stack<T, ARRAYSIZE> &s)
{
    copyAll(s);
    
    return *this;
}

#endif /* stack_h */
