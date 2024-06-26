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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetTransformPosition(float _x, float _y, float _z) {
		transform_.position_ = { _x,_y,_z };
	}

	void IsMoveStart() { ismove_ = true; }
	void IsMoveStop() { ismove_ = false; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool GetIsMove() { return ismove_; }
};

