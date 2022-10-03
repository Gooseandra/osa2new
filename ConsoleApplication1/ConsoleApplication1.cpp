#include <iostream>
#include <fstream>

void save_string(std::ofstream& out, std::string str) {
    int length = str.length();
    out.write(reinterpret_cast<char*>(&length), sizeof(length));
    out << str.c_str();
}

int main(int argc, char** argv) {
    std::string
        country = "Russia",
        city = "Reutov",
        street = "Pobedy";
    std::ofstream file;
    file.open("bin.test", std::ios::binary);
    save_string(file, country);
    save_string(file, city);
    save_string(file, street);
}