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
    string cFirstname = "unknown";
    string cSecondname = "unknown";
    string cDate = "01.01.1900";
    int nCash = 0;
    string cCurrency = "rub\n";
};

void readfile(MyStruct& employee)
{

    fstream file("statement.txt", fstream::in | fstream::binary);
    //fstream cash("cash.txt");
    if (file.is_open())
    {
        //file.read((char*)money.data(), money.size() * sizeof(int));
        while (!file.eof())
        {
            int len;

            file.read((char*)&len, sizeof(len));
            employee.cFirstname.resize(len);
            file.read((char*)employee.cFirstname.c_str(), len);
            cout << employee.cFirstname;

            file.read((char*)&len, sizeof(len));
            employee.cSecondname.resize(len);
            file.read((char*)employee.cSecondname.c_str(), len);
            cout << employee.cSecondname;

            file.read((char*)&len, sizeof(len));
            employee.cDate.resize(len);
            file.read((char*)employee.cDate.c_str(), len);
            cout << employee.cDate;

            file.read((char*)employee.nCash, sizeof(employee.nCash));
            cout << employee.nCash;

            file.read((char*)&len, sizeof(len));
            employee.cCurrency.resize(len);
            file.read((char*)employee.cCurrency.c_str(), len);
            cout << employee.cCurrency;   
        };     
     
        file.close();
    }
    else
    {
        // show error message
        cout << "error opening TXT";
    }
}

void writefile(MyStruct& employee)
{
    fstream file("statement.txt", fstream::out | fstream::binary | ios::app);
    //fstream cash("cash.txt");
    if (file.is_open())
    {
        //file.write((char*)money.data(), money.size() * sizeof(int));
        int len = employee.cFirstname.length();
        file.write((char*)&len, sizeof(len));
        file.write(employee.cFirstname.c_str(), len);
        
        len = employee.cSecondname.length();
        file.write((char*)&len, sizeof(len));
        file.write(employee.cSecondname.c_str(), len);

        len = employee.cDate.length();
        file.write((char*)&len, sizeof(len));
        file.write(employee.cDate.c_str(), len);

        file.write((char*)&employee.nCash, sizeof(employee.nCash));

        len = employee.cCurrency.length();
        file.write((char*)&len, sizeof(len));
        file.write(employee.cCurrency.c_str(), len);

        file.close();
    }
    else
    {
        // show error message
        cout << "error opening TXT";
    }
}


int main()
{
   // MyStruct employee = { "Name", "Secondname", "24.12.2022"};
   // employee.nCash = 3000;
    MyStruct employee;
    string sInput;

    cout << """add"" for add new write" << endl;
    cout << """read"" for read all writes" << endl;
    cout << """-1"" for exit" << endl;

    while (sInput != "-1")
    {
        cout << "input comand: ";
        cin >> sInput;

        if (sInput == "add")
        {
            //MyStruct employee;
            string temp;
            //string firstname, secondname, date;
            //int cash;
            cout << "Input: Firstname Secondname Date(DD.MM.YYYY) Cash Currency " << endl;
            //cin >> firstname >> secondname >> date >> cash;
            
            cin >> temp;
            employee.cFirstname = temp;

            cin >> temp;
            employee.cSecondname = temp;

            cin >> temp;
            bool dateOk = false;
            while (!dateOk)
            {
                //string to int
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
                    && year > 1970 && year < 2222) dateOk = true;
                if (dateOk) break;
                cout << "invalid date, try again2" << endl;
                cin >> temp;
            }
            employee.cDate = temp;

            cin >> temp;
            employee.nCash = stoi(temp);

            cin >> temp;
            temp += "\n";
            employee.cCurrency;

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

    //cout << "input comand: ";
    //cin >> sInput;



    //ofstream statement("statement.txt", ios::app);
    //if (statement.is_open())
    //{

    //    string firstname, secondname, date;
    //    int cash;
    //    cout << "Input: Firstname Secondname Date(DD.MM.YYYY) Cash " << endl;
    //    cin >> firstname >> secondname >> date >> cash;

    //    bool dateOk = false;
    //    while (!dateOk)
    //    {

    //        //string to int
    //        if (date.size() != 10)
    //        {
    //            cout << "invalid date, try again1" << endl;
    //            cin >> date;
    //            continue;
    //        }
    //        int day = stoi(date.substr(0, 2));
    //        int month = stoi(date.substr(3, 2));
    //        int year = stoi(date.substr(6, 4));
    //        if (day > 0 && day < 32
    //            && month > 0 && month < 13
    //            && year > 1970 && year < 2222) dateOk = true;
    //        if (dateOk) break;
    //        cout << "invalid date, try again2" << endl;
    //        cin >> date;
    //    }

    //    statement << firstname << " " << secondname << " " << date << " " << cash << "rub" << endl;
    //}
    //else
    //{
    //    // show message:
    //    cout << "Error opening file";
    //}
    //statement.close();
}