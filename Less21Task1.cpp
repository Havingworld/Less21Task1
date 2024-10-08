/*
Вы уже создавали программу чтения и записи ведомости. Теперь её надо будет обобщить и дополнить использованием структур.

Формат ведомости прежний. Сначала идёт имя и фамилия получателя денежных средств, далее — дата выдачи в формате ДД.ММ.ГГГГ.,
затем — сумма выплаты в рублях. Данные разделяются между собой пробелами. В конце каждой записи должен быть перевод строки.

Структура данных записи должна соответствовать указанному формату.

При старте программы пользователь указывает команду, которую следует осуществить: read или add.

Команда read осуществляет чтение из файла ведомости как и прежде, только уже в структуры данных и отображает их на экране.
Команда add добавляет новую запись в конец ведомости.

Советы и рекомендации

Чтобы определить конец файла, используйте функцию file.eof() как и прежде. Из-за завершающего переноса строки,
также стоит проверить и имя. Если оно было считано пустым, то можно считать, что файл закончился.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

struct MyStruct
{
    string cFirstname{ "unknown" };
    string cSecondname{ "unknown" };
    string cDate{ "01.01.1900" };
    int nCash{ 0 };
    string cCurrency{ "rub" };
};

void readfile(MyStruct& employee)
{

    fstream file("statement.txt", fstream::in);
    
    if (file.is_open())
    {
        string s{ "" };

        while (!file.eof())
        {
            getline(file, s);
            cout << s << endl;
        };     
     
        file.close();
    }
    else
    {
        cout << "error opening TXT";
    }
}

void writefile(MyStruct& employee)
{
    ofstream file("statement.txt", fstream::out | ios_base::app);
    
    if (file.is_open())
    {
        
        file << employee.cFirstname << " "
            << employee.cSecondname << " "
            << employee.cDate << " "
            << employee.nCash << " "
            << employee.cCurrency << endl;

        file.close();
    }
    else
    {
        cout << "error opening TXT";
    }
}


int main()
{
    MyStruct employee;
    string sInput{ "" };

    cout << """add"" - for add new write" << endl;
    cout << """read"" - for read all writes" << endl;
    cout << """-1"" - for exit" << endl;

    while (sInput != "-1")
    {
        cout << "input comand: ";
        cin >> sInput;
        if (sInput == "-1") break;

        if (sInput == "add")
        {
            string temp{ "" };
            cout << "Input: Firstname Secondname Date(DD.MM.YYYY) Cash Currency " << endl;

            cin >> employee.cFirstname >> employee.cSecondname >> temp;
            bool dateOk = false;
            while (!dateOk)
            {
                if (temp.size() != 10)
                {
                    cout << "invalid date, try again1" << endl;
                    cin >> temp;
                    continue;
                }
                int day = stoi(temp.substr(0, 2));
                int month = stoi(temp.substr(3, 2));
                int year = stoi(temp.substr(6, 4));
                if (day > 0 && day < 32
                    && month > 0 && month < 13
                    && year > 0 && year < 9999) dateOk = true;
                if (dateOk) break;
                cout << "invalid date, try again2" << endl;
                cin >> temp;
            }
            employee.cDate = temp;

            cin >> temp;
            employee.nCash = stoi(temp);

            cin >> employee.cCurrency;

            writefile(employee);
        }
        else if (sInput == "read")
        {
            readfile(employee);
        }
        else
        {
            cout << "error command, try again" << endl;
        }
    }
}
