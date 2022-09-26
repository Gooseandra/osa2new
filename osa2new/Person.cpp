#include<iostream>
#include"Adress.cpp"
#include"Date.cpp"

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

    string getInfoStr() {
        stringstream sstr;
        sstr << "���: " << name << "\n���� ��������: " << date.getStr() << "\n�����: " << adress.getAdressStr();
        return sstr.str();
    }

};
