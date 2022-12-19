#include <iostream>
#include <fstream>
#include <string>
#include <regex>

enum TTypes
{
    SPACE,
    TAB,
    LEFTFIGURE,
    RIGHTFIGURE,
    LEFTBRACKET,
    RIGHTBRACKET,
    STRINGCONST,
    ENDOFLINE,
    E,
    IDENTIFICATOR,
    NUMBER,
    REMARK,
    CMP,
    PRINT,
    ASSIGN,
    IFSTAT,
    THENSTAT,
    ELSESTAT,
    ENDSTAT,
    ERROR
};

const std::regex space(R"( )");
const std::regex tab(R"(\t)");
const std::regex leftFigure(R"([{])");
const std::regex rightFigure(R"([}])");
const std::regex leftBracket(R"([(])");
const std::regex rightBracket(R"([)])");
const std::regex stringConst(R"(\".*\")");
const std::regex endOfLine(R"(\n)");
const std::regex e(R"(;)");
const std::regex identificator(R"(([A-Z]|[a-z]|_)+([A-Z]|[a-z]|_|[0-9])*)");
const std::regex number(R"([0-9]+)");
const std::regex remark(R"((RAM.*)|('.*))");
const std::regex cmp(R"(!=|==|>=|<=|>|<)");
const std::regex print(R"(PRINT)");
const std::regex assign(R"(=)");
const std::regex ifStat(R"(if)");
const std::regex thenStat(R"(then)");
const std::regex elseStat(R"(else)");
const std::regex endStat(R"(END)");


#define countOfRegex 19
std::regex regexes[countOfRegex] = { space, tab, leftFigure, rightFigure, leftBracket, rightBracket, stringConst,
                                    endOfLine, e, identificator, number, remark, cmp, print, assign, ifStat, thenStat, elseStat, endStat };

struct Lexem
{
    enum TTypes type;
    std::string lexemStr;
};

std::ifstream in("in.txt");
std::ofstream out("out.txt");
std::vector<struct Lexem> terms;
int next = 0;
bool errorFlag = false;

bool getTerms(void)
{
    int strNum = 0;
    std::string str;
    char c;

    std::string line;
    getline(in, line);
    strNum++;

    std::string lex = "";

    enum TTypes lastTerm = SPACE;
    enum TTypes newTerm = ERROR;
    bool flag = false;
    int count, length;
    while (!line.empty())
    {
        length = line.length();
        std::string lineCopy = line;
        for (int i = 0; i < length; i++)
        {
            c = line.front();
            lex.push_back(c);
            newTerm = ERROR;
            for (int j = 0; j < countOfRegex; j++)
            {
                if (regex_match(lex, regexes[j]))
                    newTerm = (enum TTypes)j;
            }
            if (newTerm == ERROR && flag)
            {
                if (lastTerm != SPACE && lastTerm != TAB)
                {
                    if (newTerm != REMARK)
                        terms.push_back({ lastTerm, lex });
                }
                lex = "";
                flag = false;
                i--;
            }
            else
            {
                if (newTerm != ERROR)
                    flag = true;
                lastTerm = newTerm;
                line.erase(0, 1);
            }
        }
        if (newTerm != ERROR)
        {
            if (newTerm != SPACE && newTerm != TAB)
            {
                if (newTerm != REMARK)
                    terms.push_back({ lastTerm,  lex });

                lex = "";
                flag = false;
            }
            terms.push_back({ ENDOFLINE, "\n" });
        }
        else
        {
            if (!errorFlag)
            {
                printf("Лексическая ошибка в строке: %d\n", strNum);
                out << "Лексическая ошибка в строке: " << strNum << "\n";
                errorFlag = true;
            }
            return false;
        }
        getline(in, line);
        strNum++;
    }
    return true;
}

bool checkTerm(const enum TTypes expected)
{
    bool result;
    if (next < terms.size())
        result = (expected == terms[next].type);
    else
        result = false;
    next++;
    return result;
}

bool remarkBlock()
{
    if (!checkTerm(REMARK))
        return false;
    return true;
}

bool assignBlock()
{
    if (!checkTerm(IDENTIFICATOR))
        return false;
    if (!checkTerm(ASSIGN))
        return false;
    int save;
    save = next;
    if (!checkTerm(NUMBER))
    {
        next = save;
        if (!checkTerm(IDENTIFICATOR))
            return false;
    }
    return true;
}

bool printBlock()
{
    int save;

    if (!checkTerm(PRINT))
        return false;

    save = next;
    if (!checkTerm(STRINGCONST))
    {
        next = save;
        if (!checkTerm(IDENTIFICATOR))
            return false;
    }
        
    return true;
}

bool cmpBlock()
{
    int save;

    if (!checkTerm(IFSTAT))
        return false;

    save = next;
    if (!checkTerm(NUMBER))
    {
        next = save;
        if (!checkTerm(IDENTIFICATOR))
            return false;
    }

    if (!checkTerm(CMP))
        return false;

    save = next;
    if (!checkTerm(NUMBER))
    {
        next = save;
        if (!checkTerm(IDENTIFICATOR))
            return false;
    }

    if (!checkTerm(THENSTAT))
        return false;

    save = next;
    if (!checkTerm(ENDOFLINE))
    {
        next = save;
        if (!assignBlock())
        {
            next = save;
            if (!printBlock())
                return false;
        }
    }
    else
    {
        if (!assignBlock())
        {
            next = save + 1;
            if (!printBlock())
                return false;
        }
    }

    if (!checkTerm(ENDOFLINE))
        return false;

    if (!checkTerm(ELSESTAT))
        return true;
    else
    {

        save = next;
        if (!checkTerm(ENDOFLINE))
        {
            next = save;
            if (!assignBlock())
            {
                next = save;
                if (!printBlock())
                    return false;
            }
        }
        else
        {
            if (!assignBlock())
            {
                next = save + 1;
                if (!printBlock())
                    return false;
            }
        }
    }
    return true;
}

bool endBlock()
{
    if (!checkTerm(ENDSTAT))
        return false;
    return true;
}

void deleteEndsOfLine()
{
    while (next < terms.size() && ENDOFLINE == terms[next].type)
        next++;
}

bool mainBlock()
{
    while (next < terms.size())
    {
        int save = next;
        int counter = 0;
        if (!remarkBlock())
        {
            next = save;
            counter++;
        }
        else
            save = next;
        
        deleteEndsOfLine();

        if (!assignBlock())
        {
            next = save;
            counter++;
        }
        else
            save = next;

        deleteEndsOfLine();

        if (!printBlock())
        {
            next = save;
            counter++;
        }
        else
            save = next;

        deleteEndsOfLine();

        if (!cmpBlock())
        {
            next = save;
            counter++;
        }
        else
            save = next;

        deleteEndsOfLine();

        if (!endBlock())
        {
            next = save;
            counter++;
        }
        else
            save = next;

        deleteEndsOfLine();

        if (counter >= 5)
            return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    bool flag;
    if (in.is_open() && out.is_open())
    {

        next = 0;
        if (getTerms())
            if (!mainBlock())
            {
                printf("ERROR\n");
                out << "ERROR\n";
            }
            else
            {
                printf("SUCCESS\n");
                out << "SUCCESS\n";
            }
        in.close();
        out.close();
        return 0;
    }
}

