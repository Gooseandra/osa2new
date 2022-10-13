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
    system("cls");
    if (count == 2) {
        if (std::string(params[1]) == "add") {
            Person p(adressCreator(), dateCreator(), nameCreator());
            std::cout << endl << p.getInfoStr() << endl;
            db.add(p);
            system("pause");
        }
        else if (std::string(params[1]) == "show") {
            mainV = db.getDB();
            for (int i = 0; i <= mainV.size() - 1; i++) {
                cout << mainV[i].getName() << endl << mainV[i].getDate().getStr() << endl
                    << mainV[i].getAdress().getAdressStr() << endl << endl;
            }
            system("pause");
        }
        else if (std::string(params[1]) == "help") {
            cout << "add - добавить элемент\nshow - вывести на экране все элементы\n" <<
                "search <наименование поля> <значение поля> - поиск элемента\n" <<
                "remove <индекс элемента> - удалить элемент\n" <<
                "sortmax <поле> - сортировка данных по возрастанию поля\n" <<
                "sortmin <поле> - сортировка данных по убыванию поля\n" <<
                "min/max <наименование поля> - вывести на экран меньшее/большее значение поля" <<
                "search like <наименование поля> <строка для поиска> - поиск похожих элементов на строку для поиска\n";
            system("pause");
        }
        else {
            std::cout << "none" << endl;
            system("pause");
        }
    }
    else if (count == 3) {
        if (std::string(params[1]) == "remove") {
            db.remove(int(params[2]));
        }
        else if (std::string(params[1]) == "sortmax") {
            db.sortDB(params[2]);
            db.saveNew();
        }
        else if (std::string(params[1]) == "sortmin") {
            db.sortDB(params[2]);
            db.reverseV();
            db.saveNew();
        }
        else if (std::string(params[1]) == "min") {
            Person p = db.getMin(params[2]);
            cout << p.getInfoStr();
            system("pause");
        }
        else if (std::string(params[1]) == "max") {
            Person p = db.getMax(params[2]);
            cout << p.getInfoStr();
            system("pause");
        }
    }
    else if (count == 4){
        if (std::string(params[1]) == "search") {
            vector<int> indexV = db.search(params[2], params[3]);
            for (int i = 0; i < indexV.size(); i++) {
                cout << indexV[i] << " ";
            }
            system("pause");
        }
    }
    else if (count == 5) {
        if (std::string(params[1]) == "search" && std::string(params[2]) == "like") {
            vector<int> indexV = db.searchLikeManager(params[3], params[4]);
            if (indexV.size() == 0) {
                cout << "Ничего не найдено\n";
                return 0;
            }
            for (int i = 0; i < indexV.size(); i++) {
                cout << indexV[i] << " ";
            }
            system("pause");
        }
    }
    else {
        std::cout << "не" << endl;
        system("pause");
        return 0;
    }
}
