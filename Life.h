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

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
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

