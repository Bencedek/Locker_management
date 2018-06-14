#include <iostream>
#include <fstream>
#include "system.h"
#include "rng.h"
#include "memtrace.h"

#define TESTLEVEL 0

using std::string;
using std::cout;
using std::endl;

void System::printmenu(){
    cout << "\t(1) Arrive\n";
    cout << "\t(2) Close locker\n";
    cout << "\t(3) Open locker\n";
    cout << "\t(4) Leave\n";
    cout << "\t(5) Search for locker\n";
    cout << "\t(6) Add a new person\n";
    cout << "\t(7) Exit the program\n" << endl;
}

void System::menu(){
    printmenu();
    char m;
    std::cin >> m;
    string code;
    while(isdigit(m)){
        switch(m){
            case '1':
                code = codeInput();
                arrive(code);
                break;
            case '2':
                code = codeInput();
                closeLocker(code);
                break;
            case '3':
                code = codeInput();
                openLocker(code);
                break;
            case '4':
                code = codeInput();
                leave(code);
                break;
            case '5':
                searcher();
                break;
            case '6':
                RNG RNG;
                code = RNG.make_code();
                while(personin(code)) code = RNG.make_code();
                newPerson(code);
                break;
            case '7':
                return;
                break;
            default:
                cout << "Incorrect choice. Try again.\n" << endl;
                break;
        }
    printmenu();
    std::cin >> m;
    }
}

void System::searcher(){
    cout << "\nWhat would like to search for?\n\t(1) Person by ID code\n\t(2) Locker number" << endl;
    char c;
    std::cin >> c;
    if(isdigit(c)){
        string s;
        switch(c){
            case '1':
                s = codeInput();
                if(personin(s)){
                    if(findPerson(s).getLocker() != NULL){
                        cout << "Locker number: " << findPerson(s).getLocker()->getNum() << endl;
                    }
                    else cout << "Person has no locker assigned." << endl;
                }
                else cout << "Person not found in database." << endl;
                break;
            case '2':
                int n;
                n = numInput();
                cout << "Male or female locker? (M/F)" << endl;
                std::cin >> c;
                if(c == 'M' || c == 'm' || c == 'F' || c == 'f'){
                    Sex x = sexInput(c);
                    Locker* lck = findLocker(x, n);
                    if(lck->isTaken()){
                        cout << "Locker is taken, and it's ";
                        if(lck->isOpen()) cout << "open." << endl;
                        else cout << "closed." << endl;
                    }
                    else cout << "Locker is not taken yet." << endl;
                }
                else cout << "Incorrect answer.\n" << endl;
                break;
            default:
                cout << "Incorrect choice. Try again.\n" << endl;
                break;
        }
    }
    else cout << "Incorrect choice. Try again\n" << endl;
}

void System::load(){
    std::ifstream file;
    bool flag = true;
    string line;
    //szekrények betöltése
    file.open("system.txt");
    if(file.is_open()){
        while(getline(file, line)){
            int counter = 0;
            char c = line[counter]; Sex s;
            if(c == 'M') s = Male;
            else s = Female;
            int n = 0; c = line[++counter];
            while(isalnum(c)){
                n = 10 * n + (c-'0');
                c = line[++counter];
            }
            Locker* newl = new Locker(n, s);
            if(s == Male) ffi.addelement(newl);
            else noi.addelement(newl);
        }
        file.close();
        cout << "Lockers loaded successfully." << endl;
    }
    else{
        cout << "Unable to open system.txt." << endl;
        flag = false;
    }
    //emberek betöltése
    file.open("users.txt");
    if(file.is_open()){
        while(getline(file, line)){
            string name;
            int counter = 0;
            char c = line[counter];
            while(c != '\t'){
                name += c;
                c = line[++counter];
            }
            name[counter] = '\0';
            string code = "";
            for(int i = 0; i < 6; ++i)
                code += line[++counter];
            code[6] = '\0';
            Sex s;
            ++counter;
            if(line[++counter] == 'M') s = Male;
            else s = Female;
            Person* newp = new Person(name, code, s, NULL, true);
            ppl.addelement(newp);
        }
        file.close();
        cout << "Users loaded successfully." << endl;
    }
    else{
        cout << "Unable to open users.txt." << endl;
        flag = false;
    }
    if(flag) cout << "System successfully loaded." << endl;
}

void System::save(){
    std::ofstream file;
    bool flag = true;
    file.open("system.txt");
    if(file.is_open()){
        for(unsigned i = 0; i < ffi.getSiz(); ++i){
            file << 'M' << i+1 << '\n';
        }
        for(unsigned i = 0; i < noi.getSiz(); ++i){
            file << 'F' << i+1 << '\n';
        }
        file.close();
    }
    else{
        cout << "Unable to open system.txt." << endl;
        flag = false;
    }
    file.open("users.txt");
    if(file.is_open()){
        for(unsigned i = 0; i < ppl.getSiz(); ++i){
            Person* out = ppl[i];
            file << out->getName() << "\t" << out->getCode() << "\t" << out->getSexLetter() << '\n';
        }
        file.close();
    }
    else{
        cout << "Unable to open users.txt." << endl;
        flag = false;
    }
    if(flag) cout << "System saved succesfully." << endl;
}

void System::newPerson(string& code){
#if TESTLEVEL == 0
    cout << "\nFirst name:" << endl;
    string name;
    std::cin >> name;
    cout << "\nLast name:" << endl;
    string lname;
    std::cin >> lname;
    name += ' ';
    name += lname;
    char answer; Sex s;
    cout << "\nMale or female? (M/F)" << endl;
    std::cin >> answer;
    if(answer == 'M' || answer == 'm') s = Male;
    else s = Female;
    Person* newp = new Person(name, code, s, NULL, false);
    ppl.addelement(newp);
#endif // TESTLEVEL
#if TESTLEVEL == 1
    Person* testman = new Person("Teszt Elek", code, Male, NULL, false); //tesztalany létrehozása
    ppl.addelement(testman);
#endif // TESTLEVEL
    save();
}

void System::arrive(string& code){
    Person& current = findPerson(code);
    if(current.getLocker() != NULL){
        cout << "This person already has a locker." << endl;
        return;
    }
#if TESTLEVEL == 0
    Locker* wanted = findLocker(current.getSex(), numInput());
#endif // TESTLEVEL
#if TESTLEVEL == 1
    Locker* wanted = ffi[0];
#endif // TESTLEVEL
    if(wanted->isTaken()){
        cout << "This locker is already taken." << endl;
        return;
    }
    wanted->setTaken(true);
    current.setLocker(wanted);
    cout << current.getCode() << " successfully arrived." << endl;
}

void System::leave(string& code){
    Person& current = findPerson(code);
    if(!current.getLocker()->isOpen()){
        cout << "Locker still in closed state." << endl;
        return;
    }
    current.getLocker()->setTaken(false);
    current.setLocker(NULL);
    cout << current.getName() << " succesfully left." << endl;
}

void System::closeLocker(string& code){
    Person& current = findPerson(code);
    if(current.getLocker() != NULL){
        current.getLocker()->setOpen(false);
        cout << "Locker closed." << endl;
    }
    else cout << "This person doesn't have a locker." << endl;
}

void System::openLocker(string& code){
    Person& current = findPerson(code);
    if(current.getLocker() != NULL){
        current.getLocker()->setOpen(true);
        cout << "Locker opened." << endl;
    }
    else cout << "This person doesn't have a locker." << endl;
}

Person& System::findPerson(string& code){
    for(unsigned i = 0; i < ppl.getSiz(); ++i)
        if(code == ppl[i]->getCode()) return *ppl[i];
    throw "Person not found.";
}

bool System::personin(string& code){
    for(unsigned i = 0; i < ppl.getSiz(); ++i)
        if(code == ppl[i]->getCode()) return true;
    return false;
}

Locker* System::findLocker(Sex s, int n){
    if(s == Female){
        for(unsigned i = 0; i < noi.getSiz(); ++i){
            int p = noi[i]->getNum();
            if(n == p) return noi[i];
        }
    }
    else{
        for(unsigned i = 0; i < ffi.getSiz(); ++i)
            if(n == ffi[i]->getNum()) return ffi[i];
    }
    throw "Locker not found.";
}

string System::codeInput(){
    cout << "Type in your code.\n";
    string kod;
    std::cin >> kod;
    return kod;
}

int System::numInput(){
    cout << "Type in the chosen locker's number.\n";
    int num;
    std::cin >> num;
    return num;
}

Sex System::sexInput(const char c){
    if(c == 'M' || c == 'm') return Male;
    return Female;
}
