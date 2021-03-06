#pragma once
#ifndef _DIRECTORYUTILS_
#include "windows.h"
#include "iostream"
#include "string"
#include "tchar.h"
#include "strsafe.h"
#include "vector"
#pragma comment(lib,"User32.lib")
using namespace std;

namespace Engine 
{
	namespace FileSystem 
	{
		class DirectoryUtils
		{

		public:
			DirectoryUtils(string path);
			static string GetExeFileName();
			static string ExePath();
			static string SourcePath();
			static string PathCombine(string folder,string file);
			vector<string> GetDir();
						

		private:
			string m_path;
		};

	}
}
#endif _DIRECTORYUTILS_// !_DIRECTORYUTILS_

