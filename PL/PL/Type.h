#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

enum Type { T_NULLTYPE = 0, T_ERROR, T_INT, T_NUMBER, T_BOOL, T_VECTOR2, T_NAME }; //need a null type for when the TypeMap map returns 0. 

string typeToString(Type type);

//defines a map from names to type and from names to variables
typedef std::unordered_map<string, Type> TypeMap;
