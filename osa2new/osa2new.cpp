#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "Date.cpp"
#include "Adress.cpp"
#include "Person.cpp"

using namespace std;



template<typename T> T adressInput(string);

template<> string adressInput(string discription) {
    string str;
    cout << discription;
    cin >> str;
    return str;
}

template<> int adressInput(string discription) {
    int num;
    cout << discription;
    cin >> num;
    return num;
}

Adress adressCreator() {
    string country = adressInput<string>("Введите страну: ");
    string city = adressInput<string>("Введите город: ");
    string street = adressInput<string>("Введите название улицы: ");
    int house = adressInput<int>("Введите номер дома: ");
    int bilding = adressInput<int>("Введите номер корпуса (0 при отсутствии): ");
    int flat = adressInput<int>("Введите номер квартиры: ");
    Adress ads(country, city, street, house, bilding, flat);
    return ads;
}

Date dateCreator() {
    string date;
    while (1) {
        cout << "Введите дату: ";
        cin >> date;
        try {
            Date d(date);
            return d;
        }
        catch (string err) {
            cout << err;
        }
    }
}

string nameCreator() {
    string name;
    cout << "Введите имя: ";
    cin >> name;
    Adress::capitalLetter(name);
    return name;
}


//string s = "rfw";
//const char* c = new char[s.length()];
//c = s.c_str();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Person p(adressCreator(), dateCreator(), nameCreator());
    cout << endl << p.getInfoStr();
}
