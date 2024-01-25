#pragma once
#include "Engine\GameObject.h"
class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;
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

