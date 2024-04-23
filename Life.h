#pragma once
#include "Engine/GameObject.h"
class Life :
    public GameObject
{
    int MaxLife;
    int NowLife;
	int hNonactiveLife;
	int hActiveLife;
public:
	Life(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetLife(int n) {
		MaxLife = n;
		NowLife = n;
	}

	void ReduseNowLife() {
		NowLife--;
	}

	int GetNowLife() {
		return NowLife;
	}
};

