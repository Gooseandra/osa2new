#include<iostream>
#include"Adress.h"
#include"Date.h"

using namespace std;

class Person {
private:
    string name;
    Date date;
    Adress adress;
public:
    Person(Adress adress, Date date, string name) {
        this->name = name;
        this->adress = adress;
        this->date = date;
    }

    string getName() {
        return name;
    }

    Date getDate() {
        return date;
    }

    Adress getAdress() {
        return adress;
    }

    void putName(string name) {
        this->name = name;
    }

    string getInfoStr() {
        stringstream sstr;
        sstr << "Имя: " << name << "\nДата рождения: " << date.getStr() << "\nАдрес: " << adress.getAdressStr();
        return sstr.str();
    }

};
