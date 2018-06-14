#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
#include <iostream>
#include <string>
#include "locker.h"

class Person{
    std::string name;
    std::string code;
    Sex sex;
    Locker* locker;
public:
    Person(){}
    Person(const std::string& n, const std::string& c, Sex s, Locker* l, bool load)
        :name(n), code(c), sex(s), locker(l)
        {if(!load) std::cout << "Your code is: " << code << "\nPlease don't forget it."<< std::endl;}
    std::string getName(){return name;}
    std::string getCode(){return code;}
    Sex getSex(){return sex;}
    char getSexLetter(){
        if(sex == Male) return 'M';
        else return 'F';
    }
    Locker* getLocker(){return locker;}
    void setLocker(Locker* lck){locker = lck;}
};

#endif // PERSON_H_INCLUDED
