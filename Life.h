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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
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

