#include "DirectoryUtils.h"
#include <string>
#include <sstream>
namespace Engine 
{
	namespace FileSystem 
	{
		DirectoryUtils::DirectoryUtils(string path)
		{
			m_path = path;
		}

		string DirectoryUtils::GetExeFileName()
		{
			wchar_t buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			wstring current_dir(buffer);
			string::size_type pos = string(current_dir.begin(), current_dir.end()).find_last_of("\\/");
			return string(current_dir.begin(), current_dir.end()).substr(0, pos);
		}

		string DirectoryUtils::ExePath()
		{
			string full_dir = GetExeFileName();
			string::size_type pos = full_dir.find_last_of("\\/");
			return full_dir.substr(0, pos);
		}

		string DirectoryUtils::SourcePath()
		{
			string full_dir = Engine::FileSystem::DirectoryUtils::ExePath();
			string::size_type pos = full_dir.find_last_of("\\/");
			return full_dir.substr(0,pos);

		}

		string DirectoryUtils::PathCombine(string folder, string file)
		{
			std::stringstream path;

			path << folder;
			path << "\\";
			path << file;

			return path.str();
		}

		
		vector<string> DirectoryUtils::GetDir()
		{
			vector<string> result;

			WIN32_FIND_DATA ffd;
			LARGE_INTEGER filesize;
			TCHAR szDir[MAX_PATH];
			size_t length_of_arg;
			HANDLE hFind = INVALID_HANDLE_VALUE;
			DWORD dwError = 0;

			// Prepare string for use with FindFile functions.  First, copy the
			// string to a buffer, then append '\*' to the directory name.


			wstring current_directory = wstring(m_path.begin(), m_path.end());


			StringCchCopy(szDir, MAX_PATH, current_directory.c_str());
			StringCchCat(szDir, MAX_PATH, TEXT("\\*"));


			// Find the first file in the directory.

			hFind = FindFirstFile(szDir, &ffd);


			// List all the files in the directory with some info about them.


			do
			{
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					wstring a(ffd.cFileName);
					string  c(a.begin(), a.end());
					result.push_back(c);
				}
				else
				{
					wstring a(ffd.cFileName);
					string  c(a.begin(), a.end());
					result.push_back(c);
					filesize.LowPart = ffd.nFileSizeLow;
					filesize.HighPart = ffd.nFileSizeHigh;
				}
			} while (FindNextFile(hFind, &ffd) != 0);

			FindClose(hFind);

			vector<string>temp;
			for (int i = 2; i < result.size(); i++)
			{
				temp.push_back(result[i]);
			}


			return temp;
		}

	}
}

