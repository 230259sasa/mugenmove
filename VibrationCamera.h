#pragma once
#include "Engine/GameObject.h"
class VibrationCamera :
    public GameObject
{
	int frame;
	int vibrationnum;
	float VibrationStrenght;
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
};

