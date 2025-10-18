#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
using namespace std;

const map<string, string> keyWords = {
    {
        "print",
        "OUTPUT"
    },
    {
        "(",
        "STARTPARAMS"
    },
    {
        ")",
        "ENDPARAMS"
    },
    {
        ";",
        "ENDLN"
    }
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
    cout << "PARSING (" << word << ")" << endl;
    if (keyWords.find(word) != keyWords.end())
    {
        tokenisedCode += keyWords.at(word);
        tokenisedCode += ' ';
    }
    else
    {
        tokenisedCode += word;
        tokenisedCode += ' ';
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
            parse(word);
            word = string();
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
            while (paramLoop == true) {
                if (RAW_CODE[i+c] == ')') {
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
        else
        {
            word += RAW_CODE[i];
        }
        cout << i << ' ' << RAW_CODE[i] << endl;
        //cout << tokenisedCode << endl;
    }

    ofstream refinedCode("RefinedCode.txt");
    refinedCode << tokenisedCode;
    refinedCode.close();

    cout << tokenisedCode;

    return 0;
}