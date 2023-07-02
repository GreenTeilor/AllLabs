#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>

enum TTypes
{
    SPACE,
    TAB,
    LEFTFIGURE,
    RIGHTFIGURE,
    LEFTBRACKET,
    RIGHTBRACKET,
    LEFTSQUAREBRACKET,
    RIGHTSQUAREBRACKET,
    STRINGCONST,
    ENDOFLINE,
    E,
    IDENTIFICATOR,
    NUMBER,
    REMARK,
    CMP,
    PRINT,
    INPUT,
    ASSIGN,
    IFSTAT,
    THENSTAT,
    ELSESTAT,
    COLON,
    PLUS,
    MINUS,
    STAR,
    DIVIDE,
    MOD,
    COMMA,
    BITNOT,
    LOGICALNOT,
    INC,
    DEC,
    AMPERSAND,
    LOGICALAND,
    BITOR,
    LOGICALOR,
    EXCEPTOR,
    SHIFT,
    COMPLEX,
    CHOOSE,
    POINT,
    QUESTION,
    SIZEOF,
    CAST,
    SWITCHSTAT,
    CASESTAT,
    DEFAULTSTAT,
    WHILESTAT,
    DOSTAT,
    FORSTAT,
    GOTOSTAT,
    CONTINUESTAT,
    BREAKSTAT,
    DATATYPE,
    INCLUDESTAT,
    DEFINESTAT,
    RETURNSTAT,
    CHARCONST,
    CONSTSTAT,
    ERROR
};

const std::regex space(R"( )");
const std::regex tab(R"(\t)");
const std::regex leftFigure(R"([{])");
const std::regex rightFigure(R"([}])");
const std::regex leftBracket(R"([(])");
const std::regex rightBracket(R"([)])");
const std::regex leftSquareBracket(R"(\[)");
const std::regex rightSquareBracket(R"(\])");
const std::regex stringConst(R"(".*")");
const std::regex endOfLine(R"(\n)");
const std::regex e(R"(;)");
const std::regex identificator(R"(([A-Z]|[a-z]|_)+([A-Z]|[a-z]|_|[0-9])*)");
const std::regex number(R"([0-9]+)");
const std::regex remark(R"((//.*))");
const std::regex cmp(R"(!=|==|>=|<=|>|<)");
const std::regex print(R"(cout|std::cout)");
const std::regex input(R"(cin|std::cin)");//лексер видит только cout, соответственно на данном этапе рассматривает std - идентификатор, : - двоеточие, : - двоеточие, cout - print
const std::regex assign(R"(=)");
const std::regex ifStat(R"(if)");
const std::regex thenStat(R"(then)");
const std::regex elseStat(R"(else)");
const std::regex colon(R"(:)");
const std::regex plus(R"(\+)");
const std::regex minus(R"(-)");
const std::regex star(R"(\*)");
const std::regex divide(R"(/)");
const std::regex mod(R"(%)");
const std::regex comma(R"(,)");
const std::regex bitNot(R"(~)");
const std::regex logicalNot(R"(!)");
const std::regex inc(R"(\+\+)");
const std::regex dec(R"(\-\-)");
const std::regex ampersand(R"(&)");
const std::regex logicalAnd(R"(&&)");
const std::regex bitOr(R"(\|)");
const std::regex logicalOr(R"(\|\|)");
const std::regex exceptOr(R"(\^)");
const std::regex shift(R"(<<|>>)");
const std::regex complex(R"(\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=)");
const std::regex choose(R"(->)");
const std::regex point(R"(\.)");
const std::regex question(R"(\?)");
const std::regex sizeOf(R"(sizeof)");
const std::regex cast(R"(\(int\))");
const std::regex switchStat(R"(switch)");
const std::regex caseStat(R"(case)");
const std::regex defaultStat(R"(default)");
const std::regex whileStat(R"(while)");
const std::regex doStat(R"(do)");
const std::regex forStat(R"(for)");
const std::regex goToStat(R"(goto)");
const std::regex continueStat(R"(continue)");
const std::regex breakStat(R"(break)");
const std::regex dataType(R"(int\**|bool\**|char\**|void\**)");
const std::regex includeStat(R"(#include +<.+>)");
const std::regex defineStat(R"(#define +([A-Z]|[a-z])+ +-*[0-9]+)");
const std::regex returnStat(R"(return)");
const std::regex charConst(R"('.'|'\\.')");
const std::regex constStat(R"(const)");





#define countOfRegex 59
std::regex regexes[countOfRegex] = { space, tab, leftFigure, rightFigure, leftBracket, rightBracket, leftSquareBracket, rightSquareBracket, stringConst,
                                    endOfLine, e, identificator, number, remark, cmp, print, input, assign, ifStat, thenStat, elseStat, colon, plus, minus,
                                    star, divide, mod, comma, bitNot, logicalNot, inc, dec, ampersand, logicalAnd, bitOr, logicalOr, exceptOr, shift,
                                    complex, choose, point, question, sizeOf, cast, switchStat, caseStat, defaultStat,  whileStat, doStat, forStat, goToStat,
                                    continueStat, breakStat, dataType, includeStat, defineStat, returnStat, charConst, constStat };

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
int operatorsCount = 0;
int absoluteDifficulty = 0;
double relativeDifficulty;
int maximalDepth = 0;
int currentDepth = -1;
int switchCount = 0;

//Лексер должен уметь распознавать приведение типов, иначе добавить это в парсер
bool getTerms(void)
{
    int strNum = 0;
    std::string str;
    char c;

    std::string line;
    strNum++;

    std::string lex = "";

    enum TTypes lastTerm = SPACE;
    enum TTypes newTerm = ERROR;
    bool flag = false;
    int count, length;
    while (!in.eof())
    {
        getline(in, line);
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
                if (lastTerm != SPACE && lastTerm != TAB && lex != "")
                {
                    if (newTerm != REMARK)
                        terms.push_back({ lastTerm, lex.substr(0, lex.length() - 1) });
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
            if (newTerm != SPACE && newTerm != TAB && lex != "")
            {
                if (newTerm != REMARK)
                    terms.push_back({ lastTerm,  lex });

                lex = "";
                flag = false;
            }
            //terms.push_back({ ENDOFLINE, "\n" });
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

//=====PARSER BEGIN=====

/*
//===INITIAL VARIANT===
void cmpBlockDepthCounter() 
{
    //Here shell be logic to count inner if's(maximal depth)
    int save = next;
    ++currentDepth;
    int bracketsCounter = 0;
    if (!checkTerm(IFSTAT))
    {
        --currentDepth;
        return;
    }
    if (!checkTerm(LEFTBRACKET))
    {
        --currentDepth;
        return;
    }
    while (!checkTerm(RIGHTBRACKET))
        ;
    if (terms[next].type == LEFTFIGURE)
    {
        ++bracketsCounter;
        while (bracketsCounter != 0)
        {
            if (terms[next].type == LEFTFIGURE)
                ++bracketsCounter;
            else if (terms[next].type == RIGHTFIGURE)
                --bracketsCounter;
            save = next;
            cmpBlockDepthCounter();
            next = save;
            if (currentDepth > maximalDepth)
                maximalDepth = currentDepth;
            ++next;
        }
    }
    else
    {
        while (terms[next].type != E)
        {
            save = next;
            cmpBlockDepthCounter();
            next = save;
            if (currentDepth > maximalDepth)
                maximalDepth = currentDepth;
            ++next;
        }
        ++next;
    }
    if (checkTerm(ELSESTAT))
    {
        if (terms[next].type == LEFTFIGURE)
        {
            ++bracketsCounter;
            while (bracketsCounter != 0)
            {
                if (terms[next].type == LEFTFIGURE)
                    ++bracketsCounter;
                else if (terms[next].type == RIGHTFIGURE)
                    --bracketsCounter;
                save = next;
                cmpBlockDepthCounter();
                next = save;
                if (currentDepth > maximalDepth)
                    maximalDepth = currentDepth;
                ++next;
            }
        }
        else
        {
            while (terms[next].type != E)
            {
                save = next;
                cmpBlockDepthCounter();
                next = save;
                if (currentDepth > maximalDepth)
                    maximalDepth = currentDepth;
                ++next;
            }
            ++next;
        }
    }
    --currentDepth;
}
//===INITIAL VARIANT END===
*/

void switchBlockDepthCounter();

void cmpBlockDepthCounter()
{
    //Here shell be logic to count inner if's(maximal depth)
    int save = next;
    ++currentDepth;
    int bracketsCounter = 0;
    if (!checkTerm(IFSTAT))
    {
        --next;
        if (!checkTerm(FORSTAT))
        {
            --next;
            if (!checkTerm(WHILESTAT))
            {
                --next;
                if (!checkTerm(WHILESTAT))
                {
                    --next;
                    if (!checkTerm(DOSTAT))
                    {
                        --currentDepth;
                        return;
                    }
                }
            }

        }
    }
    if (!checkTerm(LEFTBRACKET))
    {
        --currentDepth;
        return;
    }
    while (!checkTerm(RIGHTBRACKET))
        ;
    if (terms[next].type == LEFTFIGURE)
    {
        ++bracketsCounter;
        ++next;
        while (bracketsCounter != 0)
        {
            if (terms[next].type == LEFTFIGURE)
                ++bracketsCounter;
            else if (terms[next].type == RIGHTFIGURE)
                --bracketsCounter;
            save = next;
            switchBlockDepthCounter();
            next = save;
            cmpBlockDepthCounter();
            next = save;
            if (currentDepth > maximalDepth)
                maximalDepth = currentDepth;
            ++next;
        }
    }
    else
    {
        while (terms[next].type != E)
        {
            save = next;
            switchBlockDepthCounter();
            next = save;
            cmpBlockDepthCounter();
            next = save;
            if (currentDepth > maximalDepth)
                maximalDepth = currentDepth;
            ++next;
        }
        ++next;
    }
    if (checkTerm(ELSESTAT))
    {
        if (terms[next].type == LEFTFIGURE)
        {
            ++bracketsCounter;
            ++next;
            while (bracketsCounter != 0)
            {
                if (terms[next].type == LEFTFIGURE)
                    ++bracketsCounter;
                else if (terms[next].type == RIGHTFIGURE)
                    --bracketsCounter;
                save = next;
                switchBlockDepthCounter();
                next = save;
                cmpBlockDepthCounter();
                next = save;
                if (currentDepth > maximalDepth)
                    maximalDepth = currentDepth;
                ++next;
            }
        }
        else
        {
            while (terms[next].type != E && terms[next - 1].type != IFSTAT) // Here probably I should delete: && terms[next - 1].type != IFSTAT
            {
                save = next;
                switchBlockDepthCounter();
                next = save;
                cmpBlockDepthCounter();
                next = save;
                if (currentDepth > maximalDepth)
                    maximalDepth = currentDepth;
                ++next;
            }
            ++next;
        }
    }
    --currentDepth;
}


//===VARIANT 1(inside switch depth is always +1)===
void switchBlockDepthCounter()
{
    //Here shell be logic to count inner cases(maximal depth)
    int bracketsCounter = 0;
    int branchesCounter = 0;
    if (!checkTerm(SWITCHSTAT))
        return;
    //++currentDepth;
    if (!checkTerm(LEFTBRACKET))
        return;
    while (!checkTerm(RIGHTBRACKET))
        ;
    if (!checkTerm(LEFTFIGURE))
        return;
    ++bracketsCounter;
    while (bracketsCounter != 0)
    {
        int save = next;
        cmpBlockDepthCounter();
        next = save;
        if (terms[next].type == SWITCHSTAT)
            switchBlockDepthCounter();

        if (terms[next].type == LEFTFIGURE)
            ++bracketsCounter;
        else if (terms[next].type == RIGHTFIGURE)
            --bracketsCounter;
        else if (terms[next].type == DEFAULTSTAT)
            ++branchesCounter;
        else if (terms[next].type == CASESTAT)
        {
            ++branchesCounter;
            ++currentDepth;
            if (maximalDepth < currentDepth)
                maximalDepth = currentDepth;
        }
        ++next;
    }
    currentDepth -= (branchesCounter - 1);
}
//===VARIANT 1 END===

/*
//===VARIANT 2(inside switch depth depends on branch we go)===
void switchBlockDepthCounter()
{
    //Here shell be logic to count inner cases(maximal depth)
    int bracketsCounter = 0;
    if (!checkTerm(SWITCHSTAT))
        return;
    if (!checkTerm(LEFTBRACKET))
        return;
    while (!checkTerm(RIGHTBRACKET))
        ;
    if (!checkTerm(LEFTFIGURE))
        return;
    ++bracketsCounter;
    while (bracketsCounter != 0)
    {
        if (terms[next].type == LEFTFIGURE)
            ++bracketsCounter;
        else if (terms[next].type == RIGHTFIGURE)
            --bracketsCounter;
        else if (terms[next].type == CASESTAT || terms[next].type == DEFAULTSTAT)
            ++currentDepth;
        ++next;
    }
    if (maximalDepth < currentDepth)
        maximalDepth = currentDepth;
    currentDepth = -1;
}
//===VARIANT 2 END===


//===INITIAL VARIANT===
void switchBlockDepthCounter()
{
    //Here shell be logic to count inner cases(maximal depth)
    int bracketsCounter = 0;
    if (!checkTerm(SWITCHSTAT))
        return;
    if (!checkTerm(LEFTBRACKET))
        return;
    while (!checkTerm(RIGHTBRACKET))
        ;
    if (!checkTerm(LEFTFIGURE))
        return;
    ++bracketsCounter;
    while (bracketsCounter != 0)
    {
        if (terms[next].type == LEFTFIGURE)
            ++bracketsCounter;
        else if (terms[next].type == RIGHTFIGURE)
            --bracketsCounter;
        else if (terms[next].type == CASESTAT || terms[next].type == DEFAULTSTAT)
            ++currentDepth;
        ++next;
    }
    if (maximalDepth < currentDepth)
        maximalDepth = currentDepth;
    currentDepth = -1;
}
//===INITIAL VARIANT END===
*/

bool functionCall() 
{
    if (!checkTerm(IDENTIFICATOR))
        return false;
    if (!checkTerm(LEFTBRACKET))
        return false;
    while (!checkTerm(RIGHTBRACKET))
        ;
    ++operatorsCount;
    return true;
}

bool functionDeclaration()
{
    if (!checkTerm(DATATYPE))
        return false;
    if (!checkTerm(IDENTIFICATOR))
        return false;
    if (!checkTerm(LEFTBRACKET))
        return false;
    while (!checkTerm(RIGHTBRACKET))
        ;
    return true;
}

//Parser main part, above represented some functions to implement it, but currently it's not fully working parser, but just Holsted metrics counter
bool mainBlock() {
    while (next < terms.size())
    {
        int save = next;

        if (next < terms.size())
        {
            if (!functionDeclaration())
                next = save;
            else
                save = next;

            if (!functionCall())
                next = save;
            else
                save = next;

            switchBlockDepthCounter();
            next = save;

            cmpBlockDepthCounter();
            next = save;


            //HERE LOGIC OF PROGRAM WITH IF ELSE
            //EXAMPLE: if (terms[next].type == QUESTION) ... else if ...
            if (terms[next].type == CASESTAT || terms[next].type == DEFAULTSTAT || terms[next].type == IFSTAT || terms[next].type == FORSTAT || terms[next].type == WHILESTAT) {
                ++absoluteDifficulty;
                ++operatorsCount;
            }
            if (terms[next].type == SWITCHSTAT)
                ++switchCount;
            if (terms[next].type == ASSIGN || terms[next].type == INPUT || terms[next].type == PRINT || terms[next].type == COMPLEX
                || terms[next].type == SIZEOF || terms[next].type == INC || terms[next].type == DEC)
                ++operatorsCount;
            ++next;
        }

    }
    absoluteDifficulty -= switchCount;
    operatorsCount -= switchCount;
    return true;
}
//=====PARSER END=====

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
                relativeDifficulty = (double)absoluteDifficulty / operatorsCount;
                printf("Absolute difficulty: %d;\nRelative difficulty: %lf;\nAmount of operators: %d;\nMaximal depth: %d;\n", absoluteDifficulty, relativeDifficulty, operatorsCount, maximalDepth);
            }
        in.close();
        out.close();
        return 0;
    }
}
