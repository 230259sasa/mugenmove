#pragma once
#include "Engine\GameObject.h"
class ClearScene :
    public GameObject
{
	int hImage_;
public:
	ClearScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
