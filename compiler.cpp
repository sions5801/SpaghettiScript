#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

class keyWord {
    public:
        string content;
};

class line {
    public:
        queue<keyWord> content;
};

class code {
    public:
        queue<line> content;
};

string ReadScript(ifstream& programFile)
{
    string line;
    string fileContent;
    while (getline(programFile, line)) { fileContent += line; }
    return fileContent;
}

int main()
{
    ifstream programFile("testscript.txt");

    string fileContent;
    string word;

    code script;
    
    const string rawCode = ReadScript(programFile);
    line currentLine;
    for (int i = 0; i < fileContent.length(); i++)
    {
        if (fileContent[i] == ' ') {
            keyWord newWord;
            newWord.content = word;
            word = string();

            currentLine.content.push(newWord);
        }
        else if (fileContent[i] == ';')
        {
            script.content.push(currentLine);
            currentLine.content = queue<keyWord>();
        }
        else
        {
            word += fileContent[i];
        }
    }

    return 0;
}