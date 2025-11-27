#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "References.hpp"
using namespace std;

/*
class Statement
{
    public:
        string Output(vector<string> tokenList, int &index) {
            return "printf";
        }
        string EndLine() {
            return ";";
        }
        string TypeExpression(vector<string> tokenList, int &index)
        {
            string statement;

            if (tokenList[index] == "TYPE_INT")
            {
                statement = "int";
            }
            else if (tokenList[index] == "TYPE_FLOAT")
            {
                statement = "float";
            }
            else if (tokenList[index] == "TYPE_DOUBLE")
            {
                statement = "double";
            }
            else if (tokenList[index] == "TYPE_STRING")
            {
                statement = "std::string";
            }
            else if (tokenList[index] == "TYPE_CHAR")
            {
                statement = "char";
            }
            else if (tokenList[index] == "TYPE_BOOL")
            {
                statement = "bool";
            }
            index++;
            string varName = tokenList[index];
            return statement + ' ' + varName + ' ';
        }
        string Assign()
        {
            return "= ";
        }
        string Params(string token)
        {
            if (token == "START_PARAMS")
            {
                return "(";
            }
            return ")";
        }
        string Func(string token)
        {
            if (token == "START_FUNC")
            {
                return "{";
            }
            return "}";
        }
        string Array(string token)
        {
            if (token == "START_ARRAY")
            {
                return "[";
            }
            return "]";
        }
};

Statement statementHandler;
*/
string readScript(ifstream& programFile)
{
    string line;
    string fileContent;
    while (getline(programFile, line)) { fileContent += line; }
    return fileContent;
}
/*

vector<string> addedLibraries;
vector<string> translatedWords;

//Maybe for easier translation, convert tokens into a class and make an object for every word?
//Would let you display the type and value of a token, for example token 'OUTPUT' would have Value:
//"OUTPUT" alongside Type: Function
string createStatement(string token, int &currentIndex)
{
    string returnToken;
    if (token == "OUTPUT")
    {
        //if (find(addedLibraries.begin(), addedLibraries.end(), "stdio.h") != addedLibraries.end())
        if (count(addedLibraries.begin(), addedLibraries.end(), "stdio.h") == 0)
        {
            addedLibraries.push_back("stdio.h");
        }
        return statementHandler.Output(translatedWords, currentIndex);
    }
    if (token == "ENDLN")
    {
        return statementHandler.EndLine();
    }
    if (token == "TYPE_INT" || token == "TYPE_FLOAT" || token == "TYPE_DOUBLE" || token == "TYPE_STRING" || token == "TYPE_CHAR" || token == "TYPE_BOOL")
    {
        if (token == "TYPE_STRING" && (count(addedLibraries.begin(), addedLibraries.end(), "string") == 0))
        {
            addedLibraries.push_back("string");
        }
        return statementHandler.TypeExpression(translatedWords, currentIndex);
    }
    if (token == "ASSIGN") {
        return statementHandler.Assign();
    }
    if (token == "START_PARAMS" || token == "END_PARAMS")
    {
        return statementHandler.Params(token);
    }
    if (token == "START_FUNC" || token == "END_FUNC")
    {
        return statementHandler.Func(token);
    }
    if (token == "START_ARRAY" || token == "END_ARRAY")
    {
        return statementHandler.Array(token);
    }
    else
    {
        return token;
    }
}

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
            if (token != string()) {translatedWords.push_back(token);}
            token = string();
            fullString += '"';
            int c = 1;
            bool paramLoop = true;
            while (paramLoop)
            {
                if (TOKENISED_CODE[i+c] == '"')
                {

                    

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
            if (fullString != string()) {translatedWords.push_back(fullString);}
        }
        else
        {
            token += TOKENISED_CODE[i];
        }
    }

    for (int i; i < translatedWords.size(); i++)
    {
        translatedCode += createStatement(translatedWords[i], i);
    }

    string libraries;
    for (int i = 0; i < addedLibraries.size(); i++)
    {
        libraries += ("#include<" + addedLibraries[i] + ">" + "\n");
    }
    const string WRITE_STRING = (libraries + "int main() {" + translatedCode + "return 0;}");
    
    ofstream translatedFile("TranslatedCode.cpp");
    translatedFile << WRITE_STRING;
    translatedFile.close();
}
*/
class Token {
    public:
        string Value;
        TokenType Type;
        void Init(const string WORD, const TokenType PREVIOUS_TYPE)
        {
            this->Value = toToken(WORD);
            this->Type = initToken(Value, PREVIOUS_TYPE); //pass value of previous token as string
        }
};

vector<Token> tokenisedCode;

void parseWord(string word)
{
    //Trim word
    while(isspace(word[0]))
    {
        word.erase(0);
        if (word.length() == 0) {break;}
    }
    while(isspace(word[word.length()-1]))
    {
        word.erase(word.length()-1);
        if (word.length() == 0) {break;}
    }

    if (word == string()) {return;}
    
    Token newToken;
    //if (tokenisedCode.size()>1) {cout << "PREVIOUS TYPE IS: " << tokenisedCode[tokenisedCode.size()-1].Type << ", CURRENT WORD IS: " << word << " PREVIOUS VALUE IS: " << tokenisedCode[tokenisedCode.size()-1].Value;}
    if (tokenisedCode.size()>1) {cout << tokenisedCode.size() << ">1" << endl; newToken.Init(word, tokenisedCode[tokenisedCode.size()-1].Type);}
    else {cout << tokenisedCode.size() << "<1" << endl; newToken.Init(word, UNKNOWN);}

    tokenisedCode.push_back(newToken);
}

vector<Token> tokeniser(string RAW_CODE)
{
    string word;

    for (int i = 0; i < RAW_CODE.length(); i++)
    {
        //cout << RAW_CODE[i] << " " << endl;
        if (isspace(RAW_CODE[i]))
        {
            if (word != string())
            {
                parseWord(word);
                word = string();
            }
        }
        else if (RAW_CODE[i] == '"' || RAW_CODE[i] == '\'')
        {
            parseWord(word);
            word = string();
            char typeChar = RAW_CODE[i];
            word = typeChar+string();
            int c = 1;
            while (true)
            {
                if (RAW_CODE[i+c] == typeChar)
                {
                    word += typeChar;
                    parseWord(word);
                    word = string();
                    i += c;
                    break;
                }
                word += RAW_CODE[i+c];
                //cout << word;
                c++;
            }
        }
        else if (RAW_CODE[i] == '+' || RAW_CODE[i] == '-' || RAW_CODE[i] == '*' || RAW_CODE[i] == '/')
        {
            parseWord(word);
            word = string();
            if (RAW_CODE[i+1] == '=' || RAW_CODE[i+1] == RAW_CODE[i])
            {
                i++;
                parseWord(string() + RAW_CODE[i-1] + RAW_CODE[i]);
            }
            else
            {
                parseWord(string() + RAW_CODE[i]);
            }
        }
        else if (RAW_CODE[i] == '=')
        {
            parseWord(word);
            word = string();
            if (RAW_CODE[i+1] == '=')
            {
                i++;
                parseWord(string() + RAW_CODE[i-1] + RAW_CODE[i]);
            }
            else
            {
                parseWord(string() + RAW_CODE[i]);
            }
        }
        else if (RAW_CODE[i] == '[' || RAW_CODE[i] == ']' || RAW_CODE[i] == '{' || RAW_CODE[i] == '}' || RAW_CODE[i] == '(' || RAW_CODE[i] == ')' || RAW_CODE[i] == ';' || RAW_CODE[i] == '.' || RAW_CODE[i] == ',')
        {
            cout << "found punctuator " << RAW_CODE[i] << endl;
            if (word != string())
            {
                parseWord(word);
            }
            parseWord(RAW_CODE[i] + string());
            word = string();
        }
        else
        {
            word += RAW_CODE[i];
        }
        //cout << "word is " << word << endl;
    }


    return tokenisedCode;
}

int main()
{
    ifstream programFile("testscript.txt");
    const string RAW_CODE = readScript(programFile);
    programFile.close();

    //translator(tokeniser(RAW_CODE));#
    map <int, string> debugTypes = {
        {0, "IDENTIFIER"},
        {1, "OPERATOR"},
        {2, "PUNCTUATOR"},
        {3, "TYPE"},
        {4, "STRING"},
        {5, "INTEGER"},
        {6, "DOUBLE"},
        {7, "FLOAT"},
        {8, "CHARACTER"},
        {9, "BOOLEAN"},
        {10, "KEYWORD"},
        {11, "UNKNOWN"}
    };

    tokeniser(RAW_CODE);
    for(int i = 0; i < tokenisedCode.size(); i++)
    {
        cout << tokenisedCode[i].Value << " " << debugTypes.at(tokenisedCode[i].Type) << " ";
        //cout << tokenisedCode[i].Value << " " << tokenisedCode[i].Type;
    }

    string test;
    cin >> test;
    return 0;
}