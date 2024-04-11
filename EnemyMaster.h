#pragma once
#include "Engine\GameObject.h"
#include"Enemy.h"

namespace EnemyMasterSetting {
	const int EnemyRow(5);
	const int EnemyLine(3);
}

namespace EMS = EnemyMasterSetting;

class Enemy;

class EnemyMaster :
    public GameObject
{
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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

