#pragma once
#include "Engine/GameObject.h"
class Goal :
    public GameObject
{
	int hModel_;
public:
	Goal(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

