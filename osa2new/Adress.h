#include <iostream>
#include <sstream>

using namespace std;

class Adress {
private:
    string country;
    string city;
    string street;
    int house, bilding, flat;



public:
    Adress(string country, string city, string street, int house, int bilding, int flat) {
        this->country = country;
        capitalLetter(this->country);
        this->city = city;
        capitalLetter(this->city);
        this->street = street;
        capitalLetter(this->street);
        this->house = house;
        this->flat = flat;
        this->bilding = bilding;
    }

    Adress() { country = ""; city = ""; street = ""; house = NULL; bilding = NULL; flat = NULL; }

    static void capitalLetter(string& s) {
        char* correct = new char[s.length() + 1];
        s.copy(correct, s.length());
        correct[s.length()] = '\0';
        int ascii = int(correct[0]);
        if (ascii >= 97 && ascii <= 122 || ascii >= -32 && ascii <= -1)
            correct[0] = int(correct[0] - 32);
        s = correct;
    }

    string getCountry() {
        return country;
    }
    
    string getCity() {
        return city;
    }

    string getStreet() {
        return street;
    }

    int getHouse() {
        return house;
    }

    int getBilding() {
        return bilding;
    }

    int getFlat() {
        return flat;
    }

    void putCountry(string country) {
        this->country = country;
    }

    void putCity(string city) {
        this->city = city;
    }

    void putStreet(string street) {
        this->street = street;
    }

    void putHouse(int house) {
        this->house = house;
    }

    void putBilding(int bilding) {
        this->bilding = bilding;
    }

    void putFlat(int flat) {
        this->flat = flat;
    }

    string getAdressStr() {
        stringstream sstr;
        sstr << country << ", г." << city << ", ул." << street << ", д." << house;
        if (bilding != 0)
            sstr << ", стр." << bilding;
        sstr << ", кв." << flat;
        return sstr.str();
    }
};




