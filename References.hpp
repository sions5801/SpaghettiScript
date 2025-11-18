#ifndef REFERENCES_HPP
#define REFERENCES_HPP

#include <string>
#include <map>
#include <vector>
using namespace std;

const map<string, string> KEY_WORDS = {
    {"(", "("},
    {")", ")"},
    {"{", "{"},
    {"}", "}"},
    {"[", "["},
    {"]", "]"},
    {";", ";"},
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


enum TokenType {
    IDENTIFIER,
    OPERATOR,
    PUNCTUATOR,
    TYPE,
    STRING,
    INTEGER,
    DOUBLE,
    FLOAT,
    CHARACTER,
    BOOLEAN,
    KEYWORD,
    UNKNOWN
};

const map<string, TokenType> TYPE_MAP = {
    {")", PUNCTUATOR},
    {"(", PUNCTUATOR},
    {"{", PUNCTUATOR},
    {"}", PUNCTUATOR},
    {"[", PUNCTUATOR},
    {"]", PUNCTUATOR},
    {";", PUNCTUATOR},
    {".", PUNCTUATOR},
    {",", PUNCTUATOR},
    {"OUTPUT", KEYWORD},
    {"IF", KEYWORD},
    {"WHILE", KEYWORD},
    {"FOR", KEYWORD},
    {"TYPE_INT", TYPE},
    {"TYPE_FLOAT", TYPE},
    {"TYPE_DOUBLE", TYPE},
    {"TYPE_STRING", TYPE},
    {"TYPE_CHAR", TYPE},
    {"TYPE_BOOL", TYPE},
    {"TRUE", BOOLEAN},
    {"FALSE", BOOLEAN},
    {"ASSIGN", OPERATOR},
    {"ASSIGN_ADD", OPERATOR},
    {"ASSIGN_SUBTRACT", OPERATOR},
    {"ASSIGN_MULTIPLY", OPERATOR},
    {"ASSIGN_DIVIDE", OPERATOR},
    {"EQUAL_TO", OPERATOR},
    {"NOT_EQUAL_TO", OPERATOR},
    {"GREATER_THAN", OPERATOR},
    {"LESSER_THAN", OPERATOR},
    {"GREATER_EQUAL_TO", OPERATOR},
    {"LESSER_EQUAL_TO", OPERATOR},
    {"AND", OPERATOR},
    {"OR", OPERATOR},
    {"NOT", OPERATOR},
    {"NAND", OPERATOR},
    {"NOR", OPERATOR},
    {"XAND", OPERATOR},
    {"XOR", OPERATOR},
    {"ADD", OPERATOR},
    {"INCREMENT", OPERATOR},
    {"SUBTRACT", OPERATOR},
    {"DECREMENT", OPERATOR},
    {"MULTIPLY", OPERATOR},
    {"EXPONENTIATE", OPERATOR},
    {"DIVIDE", OPERATOR},
    {"DIV", OPERATOR},
    {"MOD", OPERATOR}
};

string toToken(const string WORD)
{
    if (KEY_WORDS.find(WORD) != KEY_WORDS.end())
    {
        return KEY_WORDS.at(WORD);
    }
    return WORD;
}

vector<string> identifiers;

TokenType initToken(const string VALUE)
{
    if (TYPE_MAP.find(VALUE) != TYPE_MAP.end())
    {
        return TYPE_MAP.at(VALUE);
    }
    
    try {if (stoi(VALUE)) {return INTEGER;}}
    catch (const exception& e) {}

    try {if (stof(VALUE)) {return FLOAT;}}
    catch (const exception& e) {}

    try {if (stod(VALUE)) {return DOUBLE;}}
    catch (const exception& e) {}

    try {if (VALUE == "TRUE" || VALUE == "FALSE") {return BOOLEAN;}}
    catch (const exception& e) {}

    try {if (VALUE.length() == 3 && VALUE[0] == '\'' && VALUE[VALUE.length()-1] == '\'') {return CHARACTER;}}
    catch (const exception& e) {}

    try {if (VALUE[0] == '"' && VALUE[VALUE.length()-1] == '"') {return STRING;}}
    catch (const exception& e) {}
    
    return UNKNOWN;
}

#endif