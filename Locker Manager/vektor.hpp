#ifndef VEKTOR_HPP_INCLUDED
#define VEKTOR_HPP_INCLUDED

#include "memtrace.h"

template<class T>
class Vektor{
    T** data;
    unsigned siz;
public:
    Vektor(unsigned int n = 0) :siz(n) {
        data = new T*[siz];
    }
    T* operator[](unsigned x){
        if(x >= siz) throw "Overindexed.";
        return data[x];
    }

    void addelement(T* newdata){
        T** temp = new T*[siz+1];
        for(unsigned i = 0; i < siz; ++i){
                temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        data[siz++] = newdata;
    }

    unsigned getSiz(){return siz;}

    ~Vektor(){
        for(unsigned i = 0; i < siz; ++i){
            delete data[i];
        }
        delete[] data;
        siz = 0;
    }
};

#endif // VEKTOR_HPP_INCLUDED
