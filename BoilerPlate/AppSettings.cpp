#include "AppSettings.h"

#include<string>
#include<fstream>

#include "SDL_opengl.h"

#include "DirectoryUtils.h"
#include "IOUtils.h"
#include "StringHelper.h"

using namespace Engine::FileSystem;
using namespace Engine::Helpers;

namespace Asteroids
{
	namespace Utilities
	{
		const int MIN_LIVE = 1;
		const int MAX_LIVE = 10;
		const Vector2D DEFAULT_SHIPS_POS(520, 250);
		const Vector2D SPACE_BETWEEN_ELEMENTS(-80, 0);


		AppSettings* AppSettings::m_instance = 0;


		AppSettings::AppSettings()
		{
			m_live = 1;
			m_scores = 0;
			m_isgameOver = false;
			m_totalSetLiveFunctionCalls = 0;
			m_modelLiveIconPos = Vector2D(DEFAULT_SHIPS_POS);
		}

		AppSettings * AppSettings::Instance()
		{
			if (AppSettings::m_instance == 0)
			{
				AppSettings::m_instance = new AppSettings();
				return AppSettings::m_instance;
			}
			return AppSettings::m_instance;
		}

		int AppSettings::GetLive()
		{
			return m_live;
		}


		void AppSettings::SetLive(int live)
		{
			if (m_totalSetLiveFunctionCalls > 0) return;
			if (live < MIN_LIVE || live > MAX_LIVE) return;

			m_live = live;
			m_totalSetLiveFunctionCalls++;

		}

		void AppSettings::SetModelLiveIcon(vector<Vector2D> model)
		{
			m_modelLiveIcon = model;
		}

		void AppSettings::ReduceLive()
		{
			m_live--;

			if (m_live == 0)
			{
				this->m_isgameOver = true;
				return;
			}

		}

		bool AppSettings::IsGameOver()
		{
			return m_isgameOver;
		}

		void AppSettings::DrawLife(int mode)
		{
			if (this->m_modelLiveIcon.size() <= 0) return;

			for (int i = 1; i <= m_live; i++)
			{
				// Reset transformation matrix to identity
				//
				glLoadIdentity();

				// Translate
				//
				glTranslatef(m_modelLiveIconPos.GetX(), m_modelLiveIconPos.GetY(), 0.0f);

				// Rotate
				//
				glRotatef(0.0f, 0.0f, 0.0f, 1.0f);

				// Change color
				//
				glColor3f(0, 1, 0);

				// Draw
				//
				glBegin(mode);
				for (auto point : m_modelLiveIcon)
				{
					glVertex2f(point.GetX(), point.GetY());
				}
				glEnd();

				m_modelLiveIconPos += SPACE_BETWEEN_ELEMENTS;
			}

			m_modelLiveIconPos = Vector2D(DEFAULT_SHIPS_POS);
		}

		void AppSettings::AddScore(int score)
		{
			m_scores += score;
		}

		int AppSettings::SaveScoreData()
		{
			string local_dir = DirectoryUtils::GetExeFileName();
			string file_name = "Scores.txt";
			string path = DirectoryUtils::PathCombine(local_dir, file_name);
			fstream file(path.c_str(), ios::out | ios::app);

			if (!file.fail())
			{
				file << m_scores << endl;
				return 0;
			}


			//reaching at this point of code means that something went wrong

			return -1;
		}

		vector<vector<Vector2D>> AppSettings::Initialize()
		{
			string local_dir = DirectoryUtils::SourcePath();
			string folder = "Models";
			string path = DirectoryUtils::PathCombine(local_dir, folder);

			DirectoryUtils* directory = new DirectoryUtils(path);
			//Getting the files from the models directory
			auto dataModel = directory->GetDir();
			vector<vector<Vector2D>> all_points;

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
				all_points.push_back(points);
			}

			return all_points;
		}




	}
}


