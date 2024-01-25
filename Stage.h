#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;

	std::vector<std::vector<int>> mapArray;
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
};

