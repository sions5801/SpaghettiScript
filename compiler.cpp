#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
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
    {"char", "TYPE_CHAR"},
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
    {"++", "INCREMENT"},
    {"-", "SUBTRACT"},
    {"--", "DECREMENT"},
    {"*", "MULTIPLY"},
    {"**", "EXPONENTIATE"},
    {"/", "DIVIDE"},
    {"//", "DIV"},
    {"&", "MOD"},
    {".", "PROPERTY"}
};

string readScript(ifstream& programFile)
{
    string line;
    string fileContent;
    while (getline(programFile, line)) { fileContent += line; }
    return fileContent;
}

vector<string> translatedWords;

void translator(const string TOKENISED_CODE)
{
    string translatedCode;
    string token;

    for (int i = 0; i < TOKENISED_CODE.length(); i++)
    {
        if (TOKENISED_CODE[i] == ' ')
        {
            if (token != string()) {
                translatedWords.push_back(token);
                token = string();
            }
        } else if (TOKENISED_CODE[i] == '"')
        {
            string fullString;
            translatedWords.push_back(token);
            token = string();
            fullString += '"';
            int c = 1;
            bool paramLoop = true;
            while (paramLoop) {
                if (TOKENISED_CODE[i+c] == '"') {

                    /*for (int w = 0; w < word.length(); w++) {
                        if (RAW_CODE[i+w] == ' ') {
                            
                        }
                    }*/

                    fullString += (token+"\"");
                    token = string();
                    paramLoop = false;
                    i += c;
                    c = 0;
                }
                else
                {
                    token += TOKENISED_CODE[i+c];
                }
                //cout << c << " " << i+c << TOKENISED_CODE[i+c] << endl;
                c++;
            }
        }
        else
        {
            token += TOKENISED_CODE[i];
        }

    for (string token : translatedWords)
    {
        translatedCode += (token + ' ');
    }

    }
    const string WRITE_STRING = ("int main() {" + translatedCode + "return 0;}");
    
    ofstream translatedFile("TranslatedCode.cpp");
    translatedFile << WRITE_STRING;
    translatedFile.close();
}

string tokenisedCode;

void parseWord(const string WORD)
{
    if (WORD != string()) {
        //cout << "PARSING (" << word << ")" << endl;
        if (KEY_WORDS.find(WORD) != KEY_WORDS.end())
        {
            tokenisedCode += KEY_WORDS.at(WORD);
            tokenisedCode += ' ';
        }
        else
        {
            tokenisedCode += WORD;
            if (WORD != "\"") {
                tokenisedCode += ' ';
            }
        }
    }
}

string tokeniser(string RAW_CODE)
{
    string word;

    for (int i = 0; i < RAW_CODE.length(); i++)
    {
        if (RAW_CODE[i] == ' ')
        {
            if (word != string())
            {
                parseWord(word);
                cout << "parseWord space!" << endl;
                word = string();
            }
        }
        else if (RAW_CODE[i] == '"')
        {
            parseWord(word);
            word = string();
            parseWord("\"");
            int c = 1;
            bool paramLoop = true;
            while (paramLoop) {
                if (RAW_CODE[i+c] == '"') {

                    /*for (int w = 0; w < word.length(); w++) {
                        if (RAW_CODE[i+w] == ' ') {
                            
                        }
                    }*/

                    parseWord(word+'\"');
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
        else if (RAW_CODE[i] == '[' || RAW_CODE[i] == ']' || RAW_CODE[i] == '{' || RAW_CODE[i] == '}' || RAW_CODE[i] == '(' || RAW_CODE[i] == ')' || RAW_CODE[i] == ';' || RAW_CODE[i] == '.')
        {
            if (word != string()) { parseWord(word); }
            word = string();
            parseWord(RAW_CODE[i]+string());
        }
        else if (RAW_CODE[i] == '+' || RAW_CODE[i] == '-' || RAW_CODE[i] == '*' || RAW_CODE[i] == '/')
        {
            //parseWord(word);
            //if (RAW_CODE[i-1] != ' ') {parseWord(" "); cout << "space";}
            if (RAW_CODE[i+1] == RAW_CODE[i] || RAW_CODE[i+1] == '=')
            {
                cout << "equal or = found!";
                parseWord(word);
                word = RAW_CODE[i];
                i++;
                word += RAW_CODE[i];
            }
            else
            {
                parseWord(word);
                word = RAW_CODE[i];
                parseWord(word);
                word = string();
            }
        }
        else
        {
            word += RAW_CODE[i];
        }
        cout << i << " (" << RAW_CODE[i] << ") (" << (RAW_CODE[i] == ' ' && word == string()) << ")" << endl;
    }
    parseWord(word);

    ofstream refinedCode("RefinedCode.txt");
    refinedCode << tokenisedCode;
    refinedCode.close();

    cout << tokenisedCode;
    /*
    string endStr;
    cin >> endStr;
    */
   return tokenisedCode;
}

int main()
{
    ifstream programFile("testscript.txt");
    const string RAW_CODE = readScript(programFile);
    programFile.close();

    translator(tokeniser(RAW_CODE));
    return 0;
}