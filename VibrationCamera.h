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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

