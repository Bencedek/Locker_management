#ifndef RNG_H_INCLUDED
#define RNG_H_INCLUDED
#include <stdlib.h>
#include <string>

using std::string;

struct RNG{
    int random(){return rand()%26 + 65;} //random karakter ASCII k�dja A-Z k�z�tt
    string make_code();
};

#endif // RNG_H_INCLUDED
