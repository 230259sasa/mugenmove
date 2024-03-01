#pragma once
#include "Engine/GameObject.h"
class Energy :
    public GameObject
{
	int hModel_;
public:
	Energy(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetPos(float _x, float _z);

	void OnCollision(GameObject* pTarget);
};

