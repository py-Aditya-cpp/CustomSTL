#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>
using namespace std;

template <typename T>
class monotonicStack {
private:
    T *st;
    size_t c; // Capacity
    size_t s; // Size

    int topIndex;
    bool isEmpty;
    bool descending;

    void new_allocation()
    {
        c += 20;
        T *temp = new T[c];

        for (size_t i = 0; i < s; i++)
        {
            temp[i] = st[i];
        }

        delete[] st; // Free the old memory
        st = temp;
    }

public:
    // Constructor

    monotonicStack() : st(new T[20]), s(0), c(20), isEmpty(true), topIndex(-1), descending(false){}

    monotonicStack(bool desc) : st(new T[20]), s(0), c(20), isEmpty(true), topIndex(-1), descending(desc){}

    // Destructor

    ~monotonicStack()
    {
        delete[] st;
    }

    // Methods

    void push(T& ele) {

        if (s == c)
        {
            new_allocation();
        }

        if(descending){
            while(topIndex>=0 && ele>st[topIndex]){
                st.pop();
                s--;
                topIndex--;
            }
        }
        else{
            while(topIndex>=0 && ele<st[topIndex]){
                st.pop();
                s--;
                topIndex--;
            }
        }

        topIndex++;
        s++;

        st[topIndex]=ele;
        if(isEmpty) isEmpty=false;
    }

    void pop() {
        if(isEmpty) {
            throw std::underflow_error("Stack underflow");
        }

        topIndex--;
        s--;
        if(topIndex==-1) isEmpty=true;
    }

    T top(){
        if(isEmpty) {
            throw std::underflow_error("Stack is empty");
        }
        return st[topIndex];
    }

    bool empty(){
        return isEmpty;
    }

    void clear()
    {
        for (auto i = 0; i < s; i++)
        { // Calling destructor on each element
            st[i].~T();
        }
        s = 0;
    }

};