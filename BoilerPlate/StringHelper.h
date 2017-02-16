#pragma once
#include <vector>
#include <string>
using namespace std;
namespace Engine 
{
	namespace Helpers 
	{
		class StringHelper
		{
		public:
			static vector<string> split(const string& str, const string& delim);
		};
	}
}