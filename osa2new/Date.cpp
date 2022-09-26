#include <iostream>
#include <sstream>

using namespace std;


class Date {
private:
    int day, month, year;
    char strDate[256];

    bool dateIsCorrect(char* date, int size) {
        if (size < 4 || size > 10)
            return false;
        for (int counter = 0; counter < size; counter++) {
            if (date[counter] - '0' > 9 || date[counter] - '0' < 0 && date[counter] != '.' && date[counter] != '/')
                return false;
        }
        return true;
    }

    bool dayAndMonthValueCheck(int day, int month) {

        return false;
    }

public:
    Date() { day = 0; month = 0; year = 0; }

    Date(string& bd) {
        stringstream sstr;
        int num;
        int ssize = bd.length();
        char* charbd = new char[ssize + 1];
        char correctDate[11];

        bd.copy(charbd, ssize + 1);
        charbd[bd.length()] = '\0';
        num = charbd[0] - '0';

        if (dateIsCorrect(charbd, ssize) == false) {
            throw string("Некорректая дата.\n");
        }

        switch (ssize)
        {
        case 4:
            sstr << 0 << charbd[0] << '.' << 0 << charbd[1] << ".20" << charbd[2] << charbd[3];
            break;
        case 6:
            if ((charbd[1] == '.' || charbd[1] == '/') && (charbd[3] == '.' || charbd[3] == '/'))
                sstr << 0 << charbd[0] << ".0" << charbd[2] << ".20" << charbd[4] << charbd[5];
            else
                sstr << charbd[0] << charbd[1] << '.' << charbd[2] << charbd[3] << ".20" << charbd[4] << charbd[5];
            break;
        case 8:
            if ((charbd[2] == '.' || charbd[2] == '/') && (charbd[5] == '.' || charbd[5] == '/'))
                sstr << charbd[0] << charbd[1] << '.' << charbd[3] << charbd[4] << ".20" << charbd[6] << charbd[7];
            else
                sstr << charbd[0] << charbd[1] << '.' << charbd[2] << charbd[3] << '.' <<
                charbd[4] << charbd[5] << charbd[6] << charbd[7];
            break;
        case 10:
            if (charbd[2] == '.' && charbd[5] == '.')
                sstr << charbd;
            else
                sstr << charbd[0] << charbd[1] << '.' << charbd[3] << charbd[4] << '.' << charbd[6] <<
                charbd[7] << charbd[8] << charbd[9];
            break;
        default:
            throw string("Некоректная дата.\n");
            break;
        }
        delete[] charbd;

        correctDate[10] = '\0';
        sstr.str().copy(correctDate, 10);
        day = int(correctDate[0] - '0') * 10 + int(correctDate[1] - '0');
        month = int(correctDate[3] - '0') * 10 + int(correctDate[4] - '0');
        year = int(correctDate[6] - '0') * 1000 + int(correctDate[7] - '0') * 100 +
            int(correctDate[8] - '0') * 10 + int(correctDate[9] - '0');
        int i;
        for (i = 0; i < sizeof(correctDate); i++) {
            strDate[i] = correctDate[i];
        }
        strDate[i + 1] = '\0';
    }

    string getStr() {
        return string(strDate);
    }

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }

};