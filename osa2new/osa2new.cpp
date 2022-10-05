#include "Person.h"
#include"DataBase.h"

using namespace std;


template<typename T> T adressInput(string);

template<> string adressInput(string discription) {
    string str;
    std::cout << discription;
    cin >> str;
    return str;
}

template<> int adressInput(string discription) {
    int num;
    std::cout << discription;
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
        std::cout << "Введите дату: ";
        cin >> date;
        try {
            Date d(date);
            return d;
        }
        catch (string err) {
            std::cout << err;
        }
    }
}

string nameCreator() {
    string name;
    std::cout << "Введите имя: ";
    cin >> name;
    Adress::capitalLetter(name);
    return name;
}


//string s = "rfw";
//const char* c = new char[s.length()];
//c = s.c_str();

int main(int count, char** params)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    DataBase db;
    vector<Person> mainV;
    if (count == 2) {
        if (std::string(params[1]) == "add") {
            Person p(adressCreator(), dateCreator(), nameCreator());
            std::cout << endl << p.getInfoStr() << endl;
            db.add(p);
        }
        else if (std::string(params[1]) == "show") {
            mainV = db.getDB();
            for (int i = 0; i < mainV.size() - 1; i++) {
                cout << mainV[i].getName() << endl << mainV[i].getDate().getStr() << endl << mainV[i].getAdress().getAdressStr();
            }
            string n = mainV[0].getName();
            cout << endl << n;
        }
        else {
            std::cout << "none" << endl;
        }
    if (count == 4)
        if (std::string(params[1]) == "search") {
            vector<int> indexV = db.search(params[2], params[3]);
            for (int i = 0; i < indexV.size() - 1; i++) {
                cout << indexV[i] << ", ";
            }
        }
    }
    else {
        std::cout << "не" << endl;
    }
}
