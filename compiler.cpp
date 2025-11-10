#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

const map<string, string> KEY_WORDS = {
    {"(", "START_PARAMS"},
    {")", "END_PARAMS"},
    {"{", "START_FUNC"},
    {"}", "END_FUNC"},
    {"[", "START_ARRAY"},
    {"]", "END_ARRAY"},
    {";", "ENDLN"},
    {"print", "OUTPUT"},
    {"if", "IF"},
    {"while", "WHILE"},
    {"for", "FOR"},
    {"int", "TYPE_INT"},
    {"float", "TYPE_FLOAT"},
    {"double", "TYPE_DOUBLE"},
    {"string", "TYPE_STRING"},
    {"bool", "TYPE_BOOL"},
    {"true", "TRUE"},
    {"false", "FALSE"},
    {"=", "ASSIGN"},
    {"+=", "ASSIGN_ADD"},
    {"-=", "ASSIGN_SUBTRACT"},
    {"*=", "ASSIGN_MULTIPLY"},
    {"/=", "ASSIGN_DIVIDE"},
    {"==", "EQUAL_TO"},
    {"!=", "NOT_EQUAL_TO"},
    {">", "GREATER_THAN"},
    {"<", "LESSER_THAN"},
    {">=", "GREATER_EQUAL_TO"},
    {"<=", "LESSER_EQUAL_TO"},
    {"and", "AND"},
    {"or", "OR"},
    {"not", "NOT"},
    {"and!", "NAND"},
    {"or!", "NOR"},
    {"and?", "XAND"},
    {"or?", "XOR"},
    {"+", "ADD"},
    {"-", "SUBTRACT"},
    {"*", "MULTIPLY"},
    {"/", "DIVIDE"},
    {"//", "DIV"},
    {"&", "MOD"},
    {"++", "INCREMENT"},
    {"--", "DECREMENT"}
};

string readScript(ifstream& programFile)
{
    string line;
    string fileContent;
    while (getline(programFile, line)) { fileContent += line; }
    return fileContent;
}

string tokenisedCode;

void parse(string word)
{
    if (word != string()) {
        //cout << "PARSING (" << word << ")" << endl;
        if (KEY_WORDS.find(word) != KEY_WORDS.end())
        {
            tokenisedCode += KEY_WORDS.at(word);
            tokenisedCode += ' ';
        }
        else
        {
            tokenisedCode += word;
            if (word != "\"") {
                tokenisedCode += ' ';
            }
        }
    }
}

void tokeniser(string RAW_CODE)
{
    string word;

    for (int i = 0; i < RAW_CODE.length(); i++)
    {
        if (RAW_CODE[i] == ' ')
        {
            if (word != string())
            {
                parse(word);
                cout << "parse space!" << endl;
                word = string();
            }
        }
        else if (RAW_CODE[i] == ';')
        {
            if (word != string()) { parse(word); }
            word = string();
            parse(";");
        }
        else if (RAW_CODE[i] == '"')
        {
            parse(word);
            word = string();
            parse("\"");
            int c = 1;
            bool paramLoop = true;
            while (paramLoop) {
                if (RAW_CODE[i+c] == '"') {

                    for (int w = 0; w < word.length(); w++) {
                        if (RAW_CODE[i+w] == ' ') {
                            
                        }
                    }

                    parse(word+'\"');
                    word = string();
                    paramLoop = false;
                    i += c;
                    c = 0;
                }
                else
                {
                    word += RAW_CODE[i+c];
                }
                cout << c << " " << i+c << RAW_CODE[i+c] << endl;
                c++;
            }
        }
        else if (RAW_CODE[i] == '[' || RAW_CODE[i] == ']' || RAW_CODE[i] == '{' || RAW_CODE[i] == '}' || RAW_CODE[i] == '(' || RAW_CODE[i] == ')')
        {
            parse(word);
            word = string();
            parse(RAW_CODE[i]+string());
        }
        else if (RAW_CODE[i] == '+' || RAW_CODE[i] == '-' || RAW_CODE[i] == '*' || RAW_CODE[i] == '/')
        {
            //parse(word);
            //if (RAW_CODE[i-1] != ' ') {parse(" "); cout << "space";}
            if (RAW_CODE[i+1] == RAW_CODE[i] || RAW_CODE[i+1] == '=')
            {
                cout << "equal or = found!";
                parse(word);
                word = RAW_CODE[i];
                i++;
                word += RAW_CODE[i];
            }
        }
        else
        {
            word += RAW_CODE[i];
        }
        cout << i << " (" << RAW_CODE[i] << ") (" << (RAW_CODE[i] == ' ' && word == string()) << ")" << endl;
    }
    parse(word);

    ofstream refinedCode("RefinedCode.txt");
    refinedCode << tokenisedCode;
    refinedCode.close();

    cout << tokenisedCode;
    /*
    string endStr;
    cin >> endStr;
    */
}

int main()
{
    ifstream programFile("testscript.txt");
    const string RAW_CODE = readScript(programFile);
    programFile.close();

    tokeniser(RAW_CODE);
    return 0;
}