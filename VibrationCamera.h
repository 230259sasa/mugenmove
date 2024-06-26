#pragma once
#include "Engine/GameObject.h"

class Player;

class VibrationCamera :
    public GameObject
{
	int frame;
	int vibrationnum;
	float VibrationStrenght;
	Transform tp, cp;
	bool IsVibration;
	Player* vPlayer;
public:
	VibrationCamera(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void StartVibration() { IsVibration = true; }
	bool GetIsVibration() { return IsVibration; }
};

