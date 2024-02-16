#pragma once
#include "Engine\GameObject.h"

class Stage;

enum Dir {
	UP, RIGHT, DOWN, LEFT, NONE
};

class Player :
	public GameObject
{
	int hModel_;
	float speed_;
	Stage* pStage;
	int hpMax_;
	int hpCrr_;
	int vecx;
	int vecy;
public:
	Player(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	int GetVectorX() { return vecx; }
	int GetVectorY() { return vecy; }

	void OnCollision(GameObject* pTarget);
};