#pragma once
#include "Engine\GameObject.h"
#include"Enemy.h"
#include"Gauge.h"
#include"Phase.h"

namespace EnemyMasterSetting {
	const int EnemyRow(6);
	const int EnemyLine(3);
	const int EnemyCombination[EnemyRow][EnemyLine] = { {1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1} };
}

namespace EMS = EnemyMasterSetting;

class Enemy;
class Gauge;
class Phase;
class Player;

class EnemyMaster :
    public GameObject
{
	Player* ePlayer;
	Phase* ePhase;
	Enemy* enemy[EMS::EnemyRow][EMS::EnemyLine];
	int frame;
	int enemyrow;
	int spawnframe;
	int PhaseFrame;
	int PhaseCount;
	int NextPhase;
	float speed_;
public:
	EnemyMaster(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

