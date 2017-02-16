#pragma once
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
using namespace std;

namespace Engine 
{
	namespace FileSystem 
	{
		class IOUtils {
		public:
			static vector<string>GetConentFile(string path);
		};
	}
}


