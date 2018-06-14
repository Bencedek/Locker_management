#include <iostream>
#include <time.h>
#include "system.h"
#include "locker.h"
#include "person.h"
#include "rng.h"
#include "gtest_lite.h"
#include "memtrace.h"

#define TESTLEVEL 0

using namespace std;



int main()
{
    srand(time(NULL)); // randomgenerátor indítása
#if TESTLEVEL == 0
    System SYS;
    SYS.load();
    cout << "What would you like to do?\n" << endl;
    SYS.menu();
#endif // TEST
#if TESTLEVEL == 1
    try{
    RNG RNG; //rng létrehozása
    System SYS; //rendszervezérlõ létrehozása
    SYS.load(); //szekrények és tulajdonosaik rendszerbe töltése
    //szekrény létrehozása, tagfüggvényeinek ellenőrzése
    Locker* tesztszekreny;
    tesztszekreny = new Locker(999, Male);
    TEST(szekreny tagfuggvenyei, Locker())
        EXPECT_EQ(999, tesztszekreny->getNum());
        EXPECT_EQ(Male, tesztszekreny->getSex());
    END
    //random kóddal létrehozott személy tagfüggvényeinek tesztelése
    string code = RNG.make_code();
    SYS.newPerson(code);
    TEST(testman tagfuggvenyei, SYS.findPerson(code))
        EXPECT_EQ("Teszt Elek", SYS.findPerson(code).getName());
        EXPECT_EQ(code, SYS.findPerson(code).getCode());
        EXPECT_EQ(Male, SYS.findPerson(code).getSex());
    END
    //SYS.load() során betöltött személy tagfüggvényeinek tesztelése
    string code2 = "AAAAAA";
    TEST(bentlevo tagfuggvenyei, SYS.findPerson("AAAAAA"))
        EXPECT_EQ("Bentlevo Tag", SYS.findPerson(code2).getName());
        EXPECT_EQ("AAAAAA", SYS.findPerson(code2).getCode());
        EXPECT_EQ(Female, SYS.findPerson(code2).getSex());
    END
    //SYS.arrive() elemeinek tesztelése
    TEST(arrive reszei, SYS.findperson(code2))
        EXPECT_FALSE(tesztszekreny->isTaken());
        SYS.findPerson(code).setLocker(tesztszekreny);
        tesztszekreny->setTaken(true);
        EXPECT_TRUE(tesztszekreny->isTaken());
    END
    //SYS.closeLocker() helyett szekrény bezárás teszt
    TEST(closeLocker reszei, SYS.closeLocker())
        SYS.findPerson(code).getLocker()->setOpen(false);
        EXPECT_FALSE(tesztszekreny->isOpen());
    END
    //SYS.openLocker() helyett szekrény nyitás teszt
    TEST(openLocker reszei, SYS.openLocker())
        SYS.findPerson(code).getLocker()->setOpen(true);
        EXPECT_TRUE(tesztszekreny->isOpen());
    END
    //SYS.leave() elemeinek tesztelése
    SYS.findPerson(code).setLocker(NULL);

    delete tesztszekreny;
    tesztszekreny = NULL;
    }
    catch(const char* p){cout << p << endl;}
#endif // TEST
    return 0;
}
