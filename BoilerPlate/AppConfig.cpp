#include "AppConfig.h"
#include "DirectoryUtils.h"
#include "IOUtils.h"
#include "Ship.h"
#include "Vector2D.h"
#include "StringHelper.h"
using namespace Engine::FileSystem;
using namespace Engine::Math;
using namespace Engine::Helpers;
using namespace Asteroids::Entities;
namespace Asteroids 
{
	namespace Utilities 
	{
		std::vector<Entities::Ship*> AppConfig::Initialize()
		{
			string local_dir = DirectoryUtils::GetExeFileName();
			string folder = "Models";
			string path = DirectoryUtils::PathCombine(local_dir,folder);

			DirectoryUtils* directory = new DirectoryUtils(path);
			//Getting the files from the models directory
			auto dataModel = directory->GetDir();
			vector<Ship*> ships;
    
			for (auto model : dataModel)
			{
				string newpath = DirectoryUtils::PathCombine(path, model);
				vector<string>dataContent = IOUtils::GetConentFile(newpath);
				vector<Vector2D> points;
				for each (string item in dataContent)
				{
					vector<string> split = StringHelper::split(item, ",");
					Vector2D v = Vector2D(stof(split[0]), stof(split[1]));
					points.push_back(v);
				}
				ships.push_back(new Ship(points));
			}
		}
	}
}