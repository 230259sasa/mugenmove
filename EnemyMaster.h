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

class Enemy;
class Gauge;
class Phase;

class EnemyMaster :
    public GameObject
{
	Phase* ePhase;
	//Enemy* enemy[EMS::EnemyRow][EMS::EnemyLine];
	int frame;
	int enemyrow;
	int spawnframe;
	int PhaseFrame;
	int PhaseCount;
	int NextPhase;
	float speed_;
public:
	EnemyMaster(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

