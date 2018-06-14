#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <string>
#include "person.h"
#include "locker.h"
#include "vektor.hpp"

class System{
    Vektor<Person> ppl;
    Vektor<Locker> noi;
    Vektor<Locker> ffi;
public:
    void printmenu();                       //kiírja a menürendszert
    void menu();                            //menürendszer
    void searcher();                        //kereső funkció
    void load();                            //system.txt fileból létrehozza az összes szekrényt, users.txt fileból pedig az embereket
    void save();                            //system.txt fileba kimenti a szekrényeket, users.txt fileba pedig az embereket
    void newPerson(std::string& code);      //bekéri az adatokat és abból létrehoz egy személyt, akit behelyez a személyek tömbjébe
    void arrive(std::string& code);         //személy érkezése
    void leave(std::string& code);          //személy távozása
    void closeLocker(std::string& code);    //szekrény zárása
    void openLocker(std::string& code);     //szekrény nyitása
    Person& findPerson(std::string& code);  //megadott kódú személy keresése a személyek tömbjében
    bool personin(std::string& code);       //igaz, ha a megadott kódú személy nincs a személyek tömbjében
    Locker* findLocker(Sex s, int n);       //megadott sorszámú szekrény keresése az adott nemû szekrények tömbjében
    std::string codeInput();                //azonosító kód bekérése felhasználótól
    int numInput();                         //szekrényszám bekérése fekhasználótól
    Sex sexInput(const char c);             //nem bekérése felhasználótól
};



#endif // SYSTEM_H_INCLUDED
