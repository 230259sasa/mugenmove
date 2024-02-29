#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Stage;

const int STAGE_SIZE(15);

class Enemy :
    public GameObject
{
	struct Vec {
		int x;
		int y;
	};
	int hModel_;
	float speed_;
	Stage* pStage;
	int table[STAGE_SIZE][STAGE_SIZE];
	int nowPursue;
	std::vector<Vec> PursueArr;
	int Frame;
	int nowarrpos; //現在の位置が配列のどこか
	float startX, startZ;
	float rateX, rateZ;
public:
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Pursue();
};

