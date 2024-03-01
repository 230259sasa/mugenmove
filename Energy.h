#pragma once
#include "Engine/GameObject.h"
class Energy :
    public GameObject
{
	int hModel_;
public:
	Energy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPos(float _x, float _z);

	void OnCollision(GameObject* pTarget);
};

