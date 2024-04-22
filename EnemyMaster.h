#pragma once
#include "Engine\GameObject.h"
#include"Enemy.h"
#include"Gauge.h"

namespace EnemyMasterSetting {
	const int EnemyRow(5);
	const int EnemyLine(3);
}

namespace EMS = EnemyMasterSetting;

class Enemy;
class Gauge;

class EnemyMaster :
    public GameObject
{
	Gauge* PhaseGauge;
	Enemy* enemy[EMS::EnemyRow][EMS::EnemyLine];
	int frame;
	int enemyrow;
	int spawnframe;
	int PhaseFrame;
	int Phase;
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

