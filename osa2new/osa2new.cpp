#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <string>
#include <cstring>
#include <fstream>
#include <string>

#include "Person.h"

using namespace std;

class DataBase {
private:
    vector<Person> v;

    void saveArg(ofstream& out, string arg) {
        int length = arg.length();
        out.write(reinterpret_cast<char*>(&length), sizeof(length));
        out << arg.c_str();
    }

public:
    void add(Person p) {
        v.push_back(p);
        save();
    }

    void remove(int index) {
        v.erase(v.begin() + index);
    }

    vector<int> search(int searchField, string word) {
        int i;
        vector<int> toReturn;
        switch (searchField)
        {
        case 0: // имя
            for (i = 0; i < v.size(); i++) {
                if (v[i].getName() == word){
                    toReturn.push_back(i);
                }
            }
            break;
        case 1: // день
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getDay() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 2: // месяц
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getMonth() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 3: // год
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getYear() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 4: // полная дата
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getStr() == word) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 5: // страна
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getCountry() == word) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 6: // город
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getCity() == word) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 7: // улица
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getStreet() == word) {
                    toReturn.push_back(i);
                }
            }
            break;
        case 8: // полный адрес
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getAdressStr() == word) {
                    toReturn.push_back(i);
                }
            }
            break;
        default:
            break;
        }
        return toReturn;
    }

    Person getByIndex(int index) {
        return v[index];
    }

     void save() {
        ofstream file;
        char* intStr;
        cout << "Сохраняю...\n";
        file.open("bin.test", ios::binary);
        for (int i = 0; i < v.size(); i++) {
            saveArg(file, v[i].getName());
            saveArg(file, to_string(v[i].getDate().getDay()));
            saveArg(file, to_string(v[i].getDate().getMonth()));
            saveArg(file, to_string(v[i].getDate().getYear()));
            saveArg(file, v[i].getAdress().getCountry());
            saveArg(file, v[i].getAdress().getCity());
            saveArg(file, v[i].getAdress().getStreet());
            saveArg(file, to_string(v[i].getAdress().getHouse()));
            saveArg(file, to_string(v[i].getAdress().getBilding()));
            saveArg(file, to_string(v[i].getAdress().getFlat()));
        }
        //file.close();
    }

     void show() {
         for (int i = 0; i < v.size(); i++) {
             cout << v[i].getName() << endl << v[i].getDate().getStr() << endl << v[i].getAdress().getAdressStr();
         }
     }

     vector<Person> getDB() {
         return v;
     }
};


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
        else if (std::string(params[1]) == "save") {
            db.save();
            cout << "Данные сохранены" << endl;
        }
        else if (std::string(params[1]) == "show") {
            mainV = db.getDB();
            for (int i = 0; i < mainV.size(); i++) {
                cout << mainV[i].getName() << endl << mainV[i].getDate().getStr() << endl << mainV[i].getAdress().getAdressStr();
            }
            string n = mainV[0].getName();
            cout << endl << n;
        }
        else {
            std::cout << "none" << endl;
        }
    }
    else {
        std::cout << "не" << endl;
    }
}
