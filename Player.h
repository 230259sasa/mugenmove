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

	int GetVectorX() { return int(transform_.position_.x); }
	int GetVectorZ() { return int(transform_.position_.z); }
	float GetFloatPosX() { return transform_.position_.x; }
	float GetFloatPosZ() { return transform_.position_.z; }

	void OnCollision(GameObject* pTarget);
};