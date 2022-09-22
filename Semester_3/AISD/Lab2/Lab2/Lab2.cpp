#include <iostream>
#include "Termin.h"

using namespace std;

void printReference()
{
    cout << "Справочник команд\n";
    cout << "\t1 - Добавить термин/подтермин\n" <<
        "\t2 - Добавить страницу к термину/подтермину\n" <<
        "\t3 - Удалить страницу термина/подтермина\n" <<
        "\t4 - Удалить термин/подтермин\n" <<
        "\t5 - Изменить термин\n" <<
        "\t6 - Изменить страницу\n" <<
        "\t7 - Поиск термина/подтермина\n" <<
        "\t8 - Вывести указатель отсортированный по алфавиту\n" <<
        "\t9 - Вывести указатель отсортированный по страницам\n" <<
        "\t10 - Выход\n";
    cout << "Введите команду: ";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Termin objectPointer;
    //objectPointer.addSubTermin(Termin("a", { 12, 2 }));
    //objectPointer.addSubTermin(Termin("b", { 14, 3 }));
    //objectPointer.printTerminsWithName("a");
    //objectPointer.printTerminsWithName("b");
    bool isExit{ false };
    int option, subOption;
    while (!isExit)
    {
        cout << "==========================================================\n";
        objectPointer.printSubjectPointer();
        cout << "==========================================================\n\n";
        printReference();
        cin >> option;
        cout << endl;
        int page, newPage;
        string input;
        string newName;
        vector<Termin*> termins;
        vector<int> pagesNums;
        string pagesNumsStr;
        switch (option)
        {
        case 1:
            cout << "Введите имя родительского термина/подтермина для добавления к нему в подтермина( / - основная ветвь ): ";
            cin >> input;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой родительский термин/подтермин не найден!\n";
            else
            {
                cout << "\nВведите имя добавляемого термина/подтермина: ";
                cin >> newName;
                cout << "\nВведите через пробел номера страниц термина/подтермина: ";
                cin.ignore(32767, '\n');
                getline(cin, pagesNumsStr);
                for (int i = 0; i < pagesNumsStr.size(); ++i)
                {
                    string pageNum = "";
                    while (pagesNumsStr[i] != ' ' && i < pagesNumsStr.size())
                    {
                        pageNum += pagesNumsStr[i];
                        ++i;
                    }
                    pagesNums.push_back(stoi(pageNum));
                }
                cout << '\n';
                if (termins.size() > 1)
                {
                    cout << "================================================\n";
                    for (int i = 0; i < termins.size(); ++i)
                    {
                        cout << i + 1 << ")";
                        objectPointer.printTerminAndSubTermins(termins[i]);
                        cout << '\n';
                    }
                    cout << "================================================\n";
                    cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                    cin >> subOption;
                    if (termins[subOption - 1]->addSubTermin(Termin(newName, pagesNums)))
                        cout << "Термин/подтермин успешно добавлен!\n";
                    else
                        cout << "Термин не был добавлен так как родительский термин носит то же имя, или среди подтерминов уже присутсутвует данное имя!\n";
                }
                else
                {
                    if (termins[0]->addSubTermin(Termin(newName, pagesNums)))
                        cout << "Термин/подтермин успешно добавлен!\n";
                    else
                        cout << "Термин не был добавлен, так как родительский термин носит то же имя \n или среди подтерминов уже присутсутвует данное имя!\n";
                }
            }
            break;
        case 2:
            cout << "Введите имя термина/подтермина, к которому хотите добавить страницу: ";
            cin >> input;
            cout << "Введите страницу, которую хотите добавить: ";
            cin >> page;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
            if (termins.size() > 1)
            {
                cout << "================================================\n";
                for (int i = 0; i < termins.size(); ++i)
                {
                    cout << i + 1 << ")";
                    objectPointer.printTerminAndSubTermins(termins[i]);
                    cout << '\n';
                }
                cout << "================================================\n";
                cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                cin >> subOption;
                if (termins[subOption - 1]->addPage(page))
                    cout << "Страница успешна добавлена к термину/подтермину!\n";
                else
                    cout << "Страница не была добавлена, так как уже содержится в термине/подтермине!\n";
            }
            else
            {
                if (termins[0]->addPage(page))
                    cout << "Страница успешна добавлена к термину/подтермину!\n";
                else
                    cout << "Страница не была добавлена, так как уже содержится в термине/подтермине!\n";
            }
            break;
        case 3:
            cout << "Введите имя термина/подтермина, страницу которого хотите удалить: ";
            cin >> input;
            cout << "Введите страницу, которую хотите удалить: ";
            cin >> page;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
            if (termins.size() > 1)
            {
                cout << "================================================\n";
                for (int i = 0; i < termins.size(); ++i)
                {
                    cout << i + 1 << ")";
                    objectPointer.printTerminAndSubTermins(termins[i]);
                    cout << '\n';
                }
                cout << "================================================\n";
                cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                cin >> subOption;
                if (termins[subOption - 1]->deletePage(page))
                    cout << "Страница успешна удалена!\n";
                else
                    cout << "Страница не была удалена, т.к. ее не существовало или она была единственной!\n";
            }
            else
            {
                if (termins[0]->deletePage(page))
                    cout << "Страница успешна удалена!\n";
                else
                    cout << "Страница не была удалена, т.к. ее не существовало или она была удинственной!\n";
            }
            break;
        case 4:
            cout << "Введите имя термина/подтермина, который вы желаете удалить: ";
            cin >> input;
            objectPointer.findParentsWithSubTerminName(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
            if (termins.size() > 1)
            {
                cout << "================================================\n";
                for (int i = 0; i < termins.size(); ++i)
                {
                    cout << i + 1 << ")";
                    objectPointer.printTerminAndSubTermins(termins[i]);
                    cout << '\n';
                }
                cout << "================================================\n";
                cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                cin >> subOption;
                if (termins[subOption - 1]->deleteSubTermin(input))
                    cout << "Термин/подтермин успешно удален!\n";
                else
                    cout << "В данном термине/подтермине нет подтермина с таким названием!\n";
            }
            else
            {
                if (termins[0]->deleteSubTermin(input))
                    cout << "Термин/подтермин успешно удален!\n";
                else
                    cout << "В данном термине/подтермине нет подтермина с таким названием!\n";
            }
            break;
        case 5:
            cout << "Введите имя термина/подтермина, который вы желаете редактировать: ";
            cin >> input;
            cout << "Введите новое имя для термина/подтермина: ";
            cin >> newName;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
            if (termins.size() > 1)
            {
                cout << "================================================\n";
                for (int i = 0; i < termins.size(); ++i)
                {
                    cout << i + 1 << ")";
                    objectPointer.printTerminAndSubTermins(termins[i]);
                    cout << '\n';
                }
                cout << "================================================\n";
                cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                cin >> subOption;
                termins[subOption - 1]->setName(newName);
                cout << "Имя термина/подтермина успешно изменено!\n";
            }
            else
            {
                termins[0]->setName(newName);
                cout << "Имя термина/подтермина успешно изменено!\n";
            }
            break;
        case 6:
            cout << "Введите имя термина/подтермина, который вы желаете редактировать: ";
            cin >> input;
            cout << "Введите номер страницы, который желаете редактировать: ";
            cin >> page;
            cout << "Введите новый номер для страницы: ";
            cin >> newPage;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
                if (termins.size() > 1)
                {
                    cout << "================================================\n";
                    for (int i = 0; i < termins.size(); ++i)
                    {
                        cout << i + 1 << ")";
                        objectPointer.printTerminAndSubTermins(termins[i]);
                        cout << '\n';
                    }
                    cout << "================================================\n";
                    cout << "Имеются следующие варианты терминов/подтерминов, выберите номер: ";
                    cin >> subOption;
                    if (termins[subOption - 1]->replacePageNum(page, newPage))
                        cout << "Номер страницы успешно изменен!\n";
                    else
                        cout << "Номер страницы не изменен, т.к. старая страница отсутствует или новая уже присутсутвует!э\n";
                }
                else
                {
                    if (termins[0]->replacePageNum(page, newPage))
                        cout << "Номер страницы успешно изменен!\n";
                    else
                        cout << "Номер страницы не изменен, т.к. старая страница отсутствует или новая уже присутсутвует!э\n";
                }
            break;
        case 7:
            cout << "Введите имя термина/подтермина, который вы желаете найти: ";
            cin >> input;
            objectPointer.findTermins(input, termins);
            if (termins.size() == 0)
                cout << "Такой термин/подтермин не найден!\n";
            else
            {
                cout << "================================================\n";
                cout << "По вашему запросу найдены следующие результаты:\n";
                for (int i = 0; i < termins.size(); ++i)
                {
                    cout << i + 1 << ")";
                    objectPointer.printTerminAndSubTermins(termins[i]);
                    cout << '\n';
                }
                cout << "================================================\n";
            }
            break;
        case 8:
            objectPointer.sortByAlphabet();
            objectPointer.printSubjectPointer();
            break;
        case 9:
            objectPointer.sortByPages();
            objectPointer.printSubjectPointer();;
            break;
        default:
            isExit = true;
            break;
        }
        
    }
}

