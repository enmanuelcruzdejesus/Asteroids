#pragma once
#include "iostream"
#include <vector>

#include "Vector2D.h"
#include "OpenglGameObject.h"
using namespace std;
using namespace Engine::Math;

namespace Asteroids
{
	namespace Utilities
	{
		class AppSettings
		{
		public:
			static AppSettings* Instance();
			int GetLive();
			int GetScores();
			void SetLive(int live);
			void SetModelLiveIcon(vector<Vector2D> model);
			void ReduceLive();
			bool IsGameOver();
			void DrawLife(int mode);
			void AddScore(int score);
			int  SaveScoreData();
			vector<vector<Vector2D>> Initialize();
		private:
			AppSettings();
			static AppSettings* m_instance;
			vector<Vector2D> m_modelLiveIcon;
			Vector2D m_modelLiveIconPos;
			int m_live;
			int m_scores;
			bool m_isgameOver;
			int  m_totalSetLiveFunctionCalls;
		};
	}
}

