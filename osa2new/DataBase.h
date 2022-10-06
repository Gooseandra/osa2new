#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include <cstring>


bool compareDay(Person a, Person b) {
    return a.getDate().getDay() < b.getDate().getDay();
}

bool compareMonth(Person a, Person b) {
    return a.getDate().getDay() < b.getDate().getDay();
}

bool compareYear(Person a, Person b) {
    return a.getDate().getDay() < b.getDate().getDay();
}

class DataBase {
private:
    vector<Person> v;

    void save_string(std::ofstream& out, std::string str) {
        int length = str.length();
        out.write(reinterpret_cast<char*>(&length), sizeof(length));
        out << str.c_str();
    }

    void save_int(std::ofstream& out, int val) {
        out.write(reinterpret_cast<char*>(&val), sizeof(val));
    }

    void saving(std::ofstream& file) {
        for (int i = 0; i < v.size(); i++) {
            save_string(file, v[i].getName());
            save_int(file, v[i].getDate().getDay());
            save_int(file, v[i].getDate().getMonth());
            save_int(file, v[i].getDate().getYear());
            save_string(file, v[i].getAdress().getCountry());
            save_string(file, v[i].getAdress().getCity());
            save_string(file, v[i].getAdress().getStreet());
            save_int(file, v[i].getAdress().getHouse());
            save_int(file, v[i].getAdress().getBilding());
            save_int(file, v[i].getAdress().getFlat());
        }
    }

    void save() {
        ofstream file;
        cout << "—охран€ю...\n";
        file.open("bin.test", ios::binary | ios::app);
        saving(file);
        file.close();
    }

    void saveNew() {
        ofstream file;
        cout << "—охран€ю...\n";
        file.open("bin.test", ios::binary);
        saving(file);
        file.close();
    }

    std::string load_string(std::ifstream& in) {
        int length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        std::string buffer(length, '\x0');
        in.read(&buffer[0], length);
        return buffer;
    }

    int load_int(std::ifstream& in) {
        int val;
        in.read(reinterpret_cast<char*>(&val), sizeof(val));
        return val;
    }

    void load() {
        ifstream file;
        int counter = 0;
        cout << "«агрузка данных...\n";
        file.open("bin.test", ios::binary);
        while (counter <= 2) {
            Person p;
            v.push_back(p);
            v[counter].putName(load_string(file));
            v[counter].getDate().putDay(load_int(file));
            v[counter].getDate().putMonth(load_int(file));
            v[counter].getDate().putYear(load_int(file));
            v[counter].getAdress().putCountry(load_string(file));
            v[counter].getAdress().putCity(load_string(file));
            v[counter].getAdress().putStreet(load_string(file));
            v[counter].getAdress().putHouse(load_int(file));
            v[counter].getAdress().putBilding(load_int(file));
            v[counter].getAdress().putFlat(load_int(file));
            counter++;
        }
    }

public:
    void add(Person p) {
        v.push_back(p);
        save();
    }

    void remove(int index) {
        v.erase(v.begin() + index);
        saveNew();
    }

    vector<int> search(string searchField, string word) {
        int i;
        vector<int> toReturn;
        load();
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
        load();
        return v[index];
    }

    void show() {
        load();
        for (int i = 0; i < v.size() - 1; i++) {
            cout << v[i].getName() << endl << v[i].getDate().getStr() << endl << v[i].getAdress().getAdressStr();
        }
    }

    vector<Person> sortDB(string sortField) {
        load();
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
        load();
        return v;
    }
};
