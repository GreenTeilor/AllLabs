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
const std::regex defineStat(R"(#define +([A-Z]|[a-z]|_)+ +-*[0-9]*)");
const std::regex returnStat(R"(return)");
const std::regex charConst(R"('.'|'\\.')");





#define countOfRegex 58
std::regex regexes[countOfRegex] = { space, tab, leftFigure, rightFigure, leftBracket, rightBracket, leftSquareBracket, rightSquareBracket, stringConst,
                                    endOfLine, e, identificator, number, remark, cmp, print, input, assign, ifStat, thenStat, elseStat, colon, plus, minus,
                                    star, divide, mod, comma, bitNot, logicalNot, inc, dec, ampersand, logicalAnd, bitOr, logicalOr, exceptOr, shift,
                                    complex, choose, point, question, sizeOf, cast, switchStat, caseStat, defaultStat,  whileStat, doStat, forStat, goToStat,
                                    continueStat, breakStat, dataType, includeStat, defineStat, returnStat, charConst };

struct Lexem
{
    enum TTypes type;
    std::string lexemStr;
};

typedef std::unordered_map<std::string, int> mapType;

std::ifstream in("in.txt");
std::ofstream out("out.txt");
std::vector<struct Lexem> terms;
int next = 0;
bool errorFlag = false;

mapType spans;

mapType P;
mapType M;
mapType C;
mapType T;

mapType IOPMCT;

mapType IOP;
mapType IOM;
mapType IOC;
mapType IOT;




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

void incInMap(mapType& map, const std::string& key, bool isNegativeBase = false, int count = 1)
{
    if (map.find(key) == map.end() && isNegativeBase)
    {
        map.emplace(key, 0);
    }
    else
    {
        if (map.find(key) == map.end())
            map.emplace(key, count);
        else
            map.find(key)->second += count;
    }
}

void decInMap(mapType& map, const std::string& key, int count = -1)
{
    if (map.find(key) == map.end())
        map.emplace(key, count);
    else
        map.find(key)->second += count;
}

void deleteIfPresent(mapType& map, const std::string& key)
{
    if (map.find(key) != map.end())
        map.erase(key);
}

bool isPresentInMap(const mapType& map, const std::string& key)
{
    return map.find(key) != map.end();
}

bool functionDeclaration()
{
    if (!checkTerm(DATATYPE))
        return false;
    if (!checkTerm(IDENTIFICATOR))
        return false;
    if (!checkTerm(LEFTBRACKET))
        return false;
    while (terms[next].type != RIGHTBRACKET)
    {
        if (terms[next].type == IDENTIFICATOR)
        {
            incInMap(spans, terms[next].lexemStr, true);
        }
        ++next;
    }
    ++next;
    return true;
}

bool functionCall()
{
    if (!checkTerm(IDENTIFICATOR))
        return false;
    if (!checkTerm(LEFTBRACKET))
        return false;
    while (terms[next].type != RIGHTBRACKET)
    {
        if (terms[next].type == IDENTIFICATOR)
            incInMap(spans, terms[next].lexemStr, true);
        ++next;
    }
    ++next;
    return true;
}

void countOperatingVariables()
{
    int save = next;
    if (terms[next].type != WHILESTAT && terms[next].type != FORSTAT && terms[next].type != IFSTAT && terms[next].type != SWITCHSTAT)
        return;
    ++next;
    if (!checkTerm(LEFTBRACKET))
    {
        next = save;
        return;
    }
    while (terms[next].type != RIGHTBRACKET)
    {
        if (terms[next].type == IDENTIFICATOR)
        {
            incInMap(C, terms[next].lexemStr);
            deleteIfPresent(P, terms[next].lexemStr);
            deleteIfPresent(M, terms[next].lexemStr);
            deleteIfPresent(T, terms[next].lexemStr);
        }
        ++next;
    }
    next = save;
}

void countModifiedVariables()
{
    int save = next;
    if (terms[next].type == INC || terms[next].type == DEC)
    {
        ++next;
        if (terms[next].type == IDENTIFICATOR)
        {
            if (!isPresentInMap(C, terms[next].lexemStr))
            {
                incInMap(M, terms[next].lexemStr);
                deleteIfPresent(P, terms[next].lexemStr);
                deleteIfPresent(T, terms[next].lexemStr);
            }
        }
    }
    else
    {
        std::string lexemStr;
        if (!checkTerm(IDENTIFICATOR))
        {
            next = save;
            return;
        }
        lexemStr = terms[next - 1].lexemStr;
        if (terms[next].type == LEFTSQUAREBRACKET)
        {
            while (terms[next].type != RIGHTSQUAREBRACKET)
            {
                ++next;
            }
            ++next;
        }
        if (terms[next].type == ASSIGN || terms[next].type == COMPLEX || terms[next].type == INC || terms[next].type == DEC)
        {
            if (!isPresentInMap(C, lexemStr))
            {
                incInMap(M, lexemStr);
                deleteIfPresent(P, lexemStr);
                deleteIfPresent(T, lexemStr);
            }
        }
    }
    next = save;
}

void countPlainVariables()
{
    int save = next;
    if (!checkTerm(INPUT))
    {
        next = save;
        return;
    }
    if (!checkTerm(SHIFT))
    {
        next = save;
        return;
    }
    if (terms[next].type == IDENTIFICATOR)
    {
        if (!isPresentInMap(C, terms[next].lexemStr) && !isPresentInMap(M, terms[next].lexemStr))
        {
            incInMap(P, terms[next].lexemStr);
            deleteIfPresent(T, terms[next].lexemStr);
        }
    }
    next = save;
}

void countIOPMCT()
{
    int save = next;
    if (terms[next].type != INPUT && terms[next].type != PRINT)
        return;
    ++next;
    while (terms[next].type != E)
    {
        if (!checkTerm(SHIFT))
        {
            next = save;
            return;
        }
        if (terms[next].type == IDENTIFICATOR)
            incInMap(IOPMCT, terms[next].lexemStr);
        ++next;
    }
    next = save;
}

void countTrashVariables()
{
    if (terms[next].type == IDENTIFICATOR)
    {
        if (!isPresentInMap(C, terms[next].lexemStr) && !isPresentInMap(M, terms[next].lexemStr) && !isPresentInMap(P, terms[next].lexemStr))
        {
            incInMap(T, terms[next].lexemStr);
        }
    }
}
/*
void moveFromTrash(std::unordered_map<std::string, int>& M, std::unordered_map<std::string, int>& T)
{
    std::vector<std::string> toMove;
    for (const auto& elem : T)
    {
        if (elem.second > 1)
        {
            M.emplace(elem.first, elem.second);
            toMove.push_back(elem.first);
        }
    }
    for (const std::string& str : toMove)
    {
        deleteIfPresent(T, str);
    }
}
*/

void moveActualValues(const mapType& source, mapType& P, mapType& M, mapType& C, mapType& T)
{
    for (const auto& elem : source)
    {
        if (isPresentInMap(P, elem.first))
            P.find(elem.first)->second = elem.second + 1;
        else  if (isPresentInMap(M, elem.first))
            M.find(elem.first)->second = elem.second + 1;
        else  if (isPresentInMap(C, elem.first))
            C.find(elem.first)->second = elem.second + 1;
        else  if (isPresentInMap(T, elem.first))
            T.find(elem.first)->second = elem.second + 1;
    }
}

void moveToTrash(mapType& T, mapType& P, mapType& M, mapType& C)
{
    
    for (auto it = begin(P); it != end(P);)
    {
        if (it->second < 2)
        {
            T.emplace(it->first, it->second);
            it = P.erase(it);
        }
        else
            ++it;
    }

    for (auto it = begin(M); it != end(M);)
    {
        if (it->second < 2)
        {
            T.emplace(it->first, it->second);
            it = M.erase(it);
        }
        else
            ++it;
    }

    for (auto it = begin(C); it != end(C);)
    {
        if (it->second < 2)
        {
            T.emplace(it->first, it->second);
            it = C.erase(it);
        }
        else
            ++it;
    }
    
}

void moveOnlyIOPMCT(const mapType& IOPMCT, mapType& IOP, mapType& IOM, mapType& IOC, mapType& IOT, const mapType& P, const mapType& M, const mapType& C, const mapType& T)
{
    for (const auto& elem : IOPMCT)
    {
        if (isPresentInMap(P, elem.first))
            IOP.emplace(P.find(elem.first)->first, P.find(elem.first)->second);
        else if (isPresentInMap(M, elem.first))
            IOM.emplace(M.find(elem.first)->first, M.find(elem.first)->second);
        else if (isPresentInMap(C, elem.first))
            IOC.emplace(C.find(elem.first)->first, C.find(elem.first)->second);
        else if (isPresentInMap(T, elem.first))
            IOT.emplace(T.find(elem.first)->first, T.find(elem.first)->second);
    }
}

double getPMCT_Q(const mapType& P, const mapType& M, const mapType& C, const mapType& T) {
    return 1 * P.size() + 2 * M.size() + 3 * C.size() + 0.5 * T.size();
}


//Parser main part, above represented some functions to implement it, but currently it's not fully working parser, but just Holsted metrics counter
bool mainBlock() {
    while (next < terms.size())
    {
        int save = next;

        if (functionDeclaration())
            save = next;
        else
            next = save;

        if (functionCall())
            save = next;
        else
            next = save;

        countIOPMCT();
        countOperatingVariables();
        countModifiedVariables();
        countPlainVariables();
        countTrashVariables();

        if (next < terms.size())
        {
            if (terms[next].type == IDENTIFICATOR)
            {
                incInMap(spans, terms[next].lexemStr, true);
            }
            ++next;
        }
    }
    moveActualValues(spans, P, M, C, T);
    moveToTrash(T, P, M, C);
    moveOnlyIOPMCT(IOPMCT, IOP, IOM, IOC, IOT, P, M, C, T);
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
                printf("SPANS:\n");
                int resultSpan = 0;
                for (const auto& elem : spans)
                {
                    std::cout << elem.first << "\t" << elem.second << "\n";
                    resultSpan += elem.second;
                }
                printf("|S = %d|", resultSpan);
                printf("\n================================================================================\n\n");

                printf("P:\n");
                for (const auto& elem : P)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<p = %d>", P.size());

                printf("\n\n\n");

                printf("M:\n");
                for (const auto& elem : M)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<m = %d>", M.size());

                printf("\n\n\n");

                printf("C:\n");
                for (const auto& elem : C)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<c = %d>", C.size());

                printf("\n\n\n");

                printf("T:\n");
                for (const auto& elem : T)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<t = %d>\n", T.size());
                printf("|Q = %lf|", getPMCT_Q(P, M, C, T));

                printf("\n================================================================================\n\n");

                printf("IOP:\n");
                for (const auto& elem : IOP)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<p = %d>", IOP.size());

                printf("\n\n\n");

                printf("IOM:\n");
                for (const auto& elem : IOM)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<m = %d>", IOM.size());

                printf("\n\n\n");

                printf("IOC:\n");
                for (const auto& elem : IOC)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<c = %d>", IOC.size());

                printf("\n\n\n");

                printf("IOT:\n");
                for (const auto& elem : IOT)
                    std::cout << elem.first << "\t" << elem.second << "\n";
                printf("<t = %d>\n", IOT.size());
                printf("|Q = %lf|", getPMCT_Q(IOP, IOM, IOC, IOT));
            }
        in.close();
        out.close();
        return 0;
    }
}