#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
using namespace std;

class IOUtils {
public:
	static vector<string>GetConentFile(string path);
};