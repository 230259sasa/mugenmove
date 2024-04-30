#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Enemy :
    public GameObject
{
	int hModel_;
	float speed_;
	bool ismove_;
public:
	Enemy(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetTransformPosition(float _x, float _y, float _z) {
		transform_.position_ = { _x,_y,_z };
	}

	void IsMoveStart() { ismove_ = true; }
	void IsMoveStop() { ismove_ = false; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool GetIsMove() { return ismove_; }
};

