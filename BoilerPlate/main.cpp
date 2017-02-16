#if _MSC_VER && _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

// C++ STL
#include <cassert>
#include <iostream>

// 
#include "App.hpp"
#include "DirectoryUtils.h"
#include "IOUtils.h"
#include "fstream"


const int WIDTH = 1136;
const int HEIGHT = 640;



int main(int argc, char* argv[])
{
#if _MSC_VER && _DEBUG
	// https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	// This will help you detect leaks when using Visual C++
	// Uncomment this line to start getting reports!
	assert(_CrtCheckMemory());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	string local_dir = Engine::FileSystem::DirectoryUtils::GetExeFileName();
	string file = "Models";
	string file_path = local_dir + "\\" + file;
	
	Engine::FileSystem::DirectoryUtils* dirObject = new Engine::FileSystem::DirectoryUtils(file_path);
	vector<string> directoryList = dirObject->GetDir();
	
	string newPath = "";
	for each (string dirItem in directoryList)
	{
		std::cout <<"***"<<dirItem <<"***"<< endl;
		newPath = file_path + "\\" + dirItem;
		vector<string> contentFile = Engine::FileSystem::IOUtils::GetConentFile(newPath);
		for each (string item in contentFile)
		{
			std::cout << item << endl;
		}
	}
	


	// Create Game Object
	//
	Engine::App* app = new Engine::App("Boiler Plate!", WIDTH, HEIGHT);

	// Initialize game
	//
	if(!app->Init())
	{
		std::cout << "App Init error!\n";
		return -1;
	}

	// Execute game
	//
	app->Execute();

	// Delete game object
	//
	delete app;

	return 0;
}