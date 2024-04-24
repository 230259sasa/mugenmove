#pragma once
#include "Engine/GameObject.h"
class Goal :
    public GameObject
{
	int hModel_;
public:
	Goal(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

