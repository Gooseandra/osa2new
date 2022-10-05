#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include <cstring>

class DataBase {
private:
    vector<Person> v;

    void saveArg(ofstream& out, string arg) {
        int length = arg.length();
        out.write(reinterpret_cast<char*>(&length), sizeof(length));
        out << arg.c_str();
    }

    void save() {
        ofstream file;
        cout << "—охран€ю...\n";
        file.open("bin.test", ios::binary | ios::app);
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
        file.close();
    }

    void load() {
        ifstream file;
        cout << "«агрузка данных...\n";
        file.open("bin.test", ios::binary);
        char S[255] = {};
        while (!file.eof()) {
            file.read((char*)&S, 1);
            break;
        }
        cout << endl << S << endl;
    }

    bool compareDay(Person a, Person b) {
        return a.getDate().getDay() < b.getDate().getDay();
    }

    bool compareMonth(Person a, Person b) {
        return a.getDate().getDay() < b.getDate().getDay();
    }

    bool compareYear(Person a, Person b) {
        return a.getDate().getDay() < b.getDate().getDay();
    }

public:
    void add(Person p) {
        v.push_back(p);
        save();
    }

    void remove(int index) {
        v.erase(v.begin() + index);
    }

    vector<int> search(string searchField, string word) {
        int i;
        vector<int> toReturn;
        if (searchField == "name") {// им€ 
            for (i = 0; i < v.size(); i++) {
                if (v[i].getName() == word) {
                    toReturn.push_back(i);
                }
            }
        }
        else if (searchField == "day")// день
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getDay() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "month")// мес€ц
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getMonth() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "year")// год
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getYear() == stoi(word)) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "date")// полна€ дата
            for (i = 0; i < v.size(); i++) {
                if (v[i].getDate().getStr() == word) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "country")// страна
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getCountry() == word) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "city")// город
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getCity() == word) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "street")// улица
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getStreet() == word) {
                    toReturn.push_back(i);
                }
            }
        else if (searchField == "adress")// полный адрес
            for (i = 0; i < v.size(); i++) {
                if (v[i].getAdress().getAdressStr() == word) {
                    toReturn.push_back(i);
                }
            }
        return toReturn;
    }

    Person getByIndex(int index) {
        return v[index];
    }

    void show() {
        for (int i = 0; i < v.size() - 1; i++) {
            cout << v[i].getName() << endl << v[i].getDate().getStr() << endl << v[i].getAdress().getAdressStr();
        }
    }

    vector<Person> sortDB(string sortField) {
        if (sortField == "day") {
            sort(v.begin(), v.end(), compareDay);
        }
        else if (sortField == "month") {
            sort(v.begin(), v.end(), compareMonth);
        }
        else if (sortField == "year") {
            sort(v.begin(), v.end(), compareYear);
        }
    }

    vector<Person> getDB() {
        return v;
    }
};
#pragma once
