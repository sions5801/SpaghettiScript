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
    {"=", "ASSIGN"},
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
    {"or?", "XOR"}
};

string ReadScript(ifstream& programFile)
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
        cout << "PARSING (" << word << ")" << endl;
        if (KEY_WORDS.find(word) != KEY_WORDS.end())
        {
            tokenisedCode += KEY_WORDS.at(word);
            tokenisedCode += ' ';
        }
        else
        {
            tokenisedCode += word;
            tokenisedCode += ' ';
        }
    }
}

int main()
{
    ifstream programFile("testscript.txt");
    const string RAW_CODE = ReadScript(programFile);
    programFile.close();

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
        else if (RAW_CODE[i] == '(')
        {
            parse(word);
            word = string();
            parse("(");
            int c = 1;
            bool paramLoop = true;
            while (paramLoop) {
                if (RAW_CODE[i+c] == ')') {

                    for (int w = 0; w < word.length(); w++) {
                        if (RAW_CODE[i+w] == ' ') {
                            
                        }
                    }

                    parse(word);
                    parse(")");
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
        else if (RAW_CODE[i] == '[')
        {
            parse(word);
            word = string();
            parse("[");
            int c = 1;
            bool paramLoop = true;
            while (paramLoop) {
                if (RAW_CODE[i+c] == ']') {
                    parse(word);
                    parse("]");
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
        else
        {
            word += RAW_CODE[i];
        }
        cout << i << " (" << RAW_CODE[i] << ") (" << (RAW_CODE[i] == ' ' && word == string()) << ")"<< endl;
    }

    ofstream refinedCode("RefinedCode.txt");
    refinedCode << tokenisedCode;
    refinedCode.close();

    cout << tokenisedCode;

    string endcode;
    cin >> endcode;
    return 0;
}