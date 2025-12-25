#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Define types for simplicity
enum class Type { INT, FLOAT, STRING, INVALID };

// Function symbol table entry
struct Function {
    string name;
    vector<Type> paramTypes;
};

// Convert Type to readable string
string typeToString(Type t) {
    switch(t) {
        case Type::INT: return "int";
        case Type::FLOAT: return "float";
        case Type::STRING: return "string";
        default: return "invalid";
    }
}

// Symbol table
unordered_map<string, Function> symbolTable;

// Semantic check for function call
void checkFunctionCall(const string& funcName, const vector<Type>& argTypes) {
    if (symbolTable.find(funcName) == symbolTable.end()) {
        cout << "Error: Function '" << funcName << "' not declared.\n";
        return;
    }
    Function f = symbolTable[funcName];
    
    if (argTypes.size() != f.paramTypes.size()) {
        cout << "Error: Function '" << funcName << "' expects " 
             << f.paramTypes.size() << " arguments, got " << argTypes.size() << ".\n";
        return;
    }
    
    for (size_t i = 0; i < argTypes.size(); ++i) {
        if (argTypes[i] != f.paramTypes[i]) {
            cout << "Error: Argument " << i+1 << " of function '" << funcName 
                 << "' expects type " << typeToString(f.paramTypes[i]) 
                 << ", got " << typeToString(argTypes[i]) << ".\n";
        }
    }
}

// Test example
int main() {
    // Add functions to symbol table
    symbolTable["sum"] = {"sum", {Type::INT, Type::INT}};
    symbolTable["print"] = {"print", {Type::STRING}};

    // Valid call
    cout << "Testing sum(5, 10):\n";
    checkFunctionCall("sum", {Type::INT, Type::INT});

    // Missing argument
    cout << "\nTesting sum(5):\n";
    checkFunctionCall("sum", {Type::INT});

    // Extra argument
    cout << "\nTesting sum(5, 10, 15):\n";
    checkFunctionCall("sum", {Type::INT, Type::INT, Type::INT});

    // Type mismatch
    cout << "\nTesting sum(\"5\", 10):\n";
    checkFunctionCall("sum", {Type::STRING, Type::INT});

    // Undeclared function
    cout << "\nTesting multiply(2,3):\n";
    checkFunctionCall("multiply", {Type::INT, Type::INT});

    return 0;
}   