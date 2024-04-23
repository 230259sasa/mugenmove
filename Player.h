#pragma once
#include "Engine\GameObject.h"

namespace PlayerSetting {
	const int FLASHING_INTERVAL(15);
	const int INVINCIBLE_INTERVAL(60);
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

namespace PS = PlayerSetting;

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
	bool IsDraw;
	Stage* pStage;
	Life* plife;
public:
	Player(GameObject* parent);

	//èâä˙âª
	void Initialize() override;

	//çXêV
	void Update() override;

	//ï`âÊ
	void Draw() override;

	//äJï˙
	void Release() override;

	int GetVectorX() { return int(transform_.position_.x); }
	int GetVectorZ() { return int(transform_.position_.z); }
	float GetFloatPosX() { return transform_.position_.x; }
	float GetFloatPosZ() { return transform_.position_.z; }

	void OnCollision(GameObject* pTarget);
};