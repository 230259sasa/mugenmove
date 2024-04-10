#pragma once
#include "Engine\GameObject.h"
#include<vector>


class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;

	std::vector<std::vector<int>> stageData;
	int stageWidth_, stageHeight_;
public:
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
};

