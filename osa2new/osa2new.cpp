#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "Date.cpp"

using namespace std;

class Adress {
private:
    char country[256];
public:
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str = "2222";
    Date mydate(str);
    char x[256];
    string xs;
    xs = mydate.getStr();
    cout << xs;
}
