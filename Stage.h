#pragma once
#include "Engine\GameObject.h"
#include<vector>


class Stage :
    public GameObject
{
	int hFloor_;
	int hLoad_;

	std::vector<std::vector<int>> stageData;
	int stageWidth_, stageHeight_;
public:
	Stage(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
};

