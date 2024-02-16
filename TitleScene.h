#pragma once
#include "Engine\GameObject.h"
class TitleScene :
    public GameObject
{
	int hImage_;
public:
	TitleScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

