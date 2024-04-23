#pragma once
#include "Engine\GameObject.h"

class Stage;
class Life;

enum Dir {
	RIGHT,LEFT, NONE
};

class Player :
	public GameObject
{
	int hModel_;
	float speed_;
	float moveingposition[3];
	int moveingpositionnum;
	int InvincibleTime;
	int FlashingIntervalTime;
	bool IsFlash;
	Stage* pStage;
	Life* plife;
public:
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetVectorX() { return int(transform_.position_.x); }
	int GetVectorZ() { return int(transform_.position_.z); }
	float GetFloatPosX() { return transform_.position_.x; }
	float GetFloatPosZ() { return transform_.position_.z; }

	void OnCollision(GameObject* pTarget);
};