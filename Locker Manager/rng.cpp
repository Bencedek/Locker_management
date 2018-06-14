#include "rng.h"

string RNG::make_code(){
    string code = "";
    for(int i = 0; i < 6; ++i)
        code += random();
    return code;
}
