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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void StartVibration() { IsVibration = true; }
	bool GetIsVibration() { return IsVibration; }
};

