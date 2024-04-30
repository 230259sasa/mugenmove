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

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void StartVibration() { IsVibration = true; }
	bool GetIsVibration() { return IsVibration; }
};

