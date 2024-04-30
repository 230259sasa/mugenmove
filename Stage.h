#pragma once
#include "Engine\GameObject.h"
#include<vector>

class Player;

class Stage :
    public GameObject
{
	int hFloor_;
	int hLoad_;
	int ClearPhase;
	float zpos;
	float speed;
	bool IsClear;

	Player* sPlayer;

	Transform LoadTrans;
	Transform LoadTrans2;
	Transform pTrans;
	std::vector<std::vector<int>> stageData;
	int stageWidth_, stageHeight_;
public:
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
	void SetSpeed(float s) { speed = s; }
	bool GetIsClear() { return IsClear; }
	void SetPlayerPos(Transform _t) { pTrans.position_ = _t.position_; }//erroe
};

