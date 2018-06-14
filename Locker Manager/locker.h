#ifndef LOCKER_H_INCLUDED
#define LOCKER_H_INCLUDED

enum Sex{Male, Female};

class Locker{
    int num;
    Sex sex;
    bool open;
    bool taken;
public:
    Locker(){}
    Locker(int n, Sex s):num(n), sex(s), open(true), taken(false){}
    int getNum(){return num;}
    Sex getSex(){return sex;}
    void setOpen(bool o){open = o;}
    void setTaken(bool t){taken = t;}
    bool isOpen(){return open;}
    bool isTaken(){return taken;}
};

#endif // LOCKER_H_INCLUDED
