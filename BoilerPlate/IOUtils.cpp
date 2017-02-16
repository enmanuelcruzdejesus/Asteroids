#include "IOUtils.h"
#include "vector"

namespace Engine
{
	namespace FileSystem 
	{

		vector<string> IOUtils::GetConentFile(string path)
		{
			vector<string>result;
			fstream txtfile(path);
			string value;
			if (!txtfile.fail())
			{
				while (!txtfile.eof())
				{
					txtfile >> value;
					result.push_back(value);
				}
			}
			return result;
		}

	}
}

