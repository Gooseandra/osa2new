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

    bool is_empty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
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
        //save_string(file, "0");
    }

    void save() {
        ofstream file;
        //ifstream isFileEmpty;
        cout << "—охран€ю...\n";
       // isFileEmpty.open("bin.test");
        file.open("bin.test", ios::binary | ios::app);
       // if (is_empty(isFileEmpty) == true) {
            saving(file);
        //}
        //else {
     /*       file.seekp(file.end);
            long pos = file.tellp();
            file.seekp(pos - 1);
            save_string(file, "");
            saving(file);
        }*/
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
        file.open("bin.test", ios::binary | ios::in);
        while (counter != 3) {
            std::string name = load_string(file);
            Date date;
            date.putDay(load_int(file));
            date.putMonth(load_int(file));
            date.putYear(load_int(file));
            Adress adress;
            adress.putCountry(load_string(file));
            adress.putCity(load_string(file));
            adress.putStreet(load_string(file));
            adress.putHouse(load_int(file));
            adress.putBilding(load_int(file));
            adress.putFlat(load_int(file));
            v.push_back(Person(adress, date, name));
            counter++;
        }
    }

public:
    void saveNew() {
        ofstream file;
        cout << "—охран€ю...\n";
        file.open("bin.test", ios::binary);
        saving(file);
        file.close();
    }

    void add(Person p) {
        v.push_back(p);
        save();
    }

    void remove(int index) {
        load();
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

    bool searchLike(string wordToFind, string word) {
        int i = 0, u = 0, q = 0;
        int ssize = word.length();
        char* parseWord = new char[ssize + 1];
        bool add = false;
        word.copy(parseWord, ssize);
        parseWord[ssize] = '\0';

        char* info = new char[wordToFind.length()];
        wordToFind.copy(info, wordToFind.length() + 1);
        info[wordToFind.length()] = '\0';

        for (u; u < wordToFind.length(); u++) {
            for (q; q < ssize; q++) {
                if (u + q > wordToFind.length()) {
                    break;
                    break;
                }
                if (parseWord[q] != info[u + q]) {
                    add = false;
                    break;
                }
                if (q == ssize - 1)
                    add = true;
            }
            if (add == true) {
                delete[] parseWord;
                return true;
                break;
            }

        }
        return false;
    }

    vector<int> searchLikeManager(string searchField, string word) {
        vector<int> indexes;
        load();
        if (searchField == "name") {
            for (int i = 0; i < v.size(); i++) {
                if (searchLike(v[i].getName(), word) == true)
                    indexes.push_back(i);
            }
        }
        else if (searchField == "date") {
            for (int i = 0; i < v.size(); i++) {
                if (searchLike(v[i].getDate().getStr(), word) == true)
                    indexes.push_back(i);
            }
        }
        else if (searchField == "country") {
            for (int i = 0; i < v.size(); i++) {
                if (searchLike(v[i].getAdress().getCountry(), word) == true)
                    indexes.push_back(i);
            }
        }
        else if (searchField == "city") {
            for (int i = 0; i < v.size(); i++) {
                if (searchLike(v[i].getAdress().getCity(), word) == true)
                    indexes.push_back(i);
            }
        }
        else if (searchField == "street") {
            for (int i = 0; i < v.size(); i++) {
                if (searchLike(v[i].getAdress().getStreet(), word) == true)
                    indexes.push_back(i);
            }
        }
        return indexes;
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

    void sortDB(string sortField) {
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

    void reverseV() {
        reverse(v.begin(), v.end());
    }

    Person getMin(string minField) {
        sortDB(minField);
        return v[0];
    }

    Person getMax(string maxField) {
        sortDB(maxField);
        return v[v.size() - 1];
    }
    
    vector<Person> getDB() {
        load();
        return v;
    }
};
