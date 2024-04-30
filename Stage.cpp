#include "Stage.h"
#include"Engine\Model.h"
#include<fstream>
#include<sstream>
#include"Engine\CsvReader.h"
#include"Phase.h"
#include"Goal.h"
#include"Player.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hFloor_(-1), hLoad_(-1), stageWidth_(3), stageHeight_(15),ClearPhase(10),
	IsClear(false),speed(0.05)
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hLoad_ = Model::Load("Model\\load.fbx");
	assert(hFloor_ >= 0);
	//transform_.position_ = { 0.5,0,14 };
	//Player* sPlayer = (Player*)FindObject("Player");
	LoadTrans.position_ = { 0,0,-2 };
	LoadTrans2.position_ = { 0,0,-2+15*1.5 };
}

void Stage::Update()
{
	/*if (zpos >= 25*1.5) {
		zpos = 0;
	}*/
	//zpos += speed;
#if(true)
	pTrans.position_.z += 0.05;
#endif
	if (abs(LoadTrans.position_.z - pTrans.position_.z) >= 1.5*10*2) {
		LoadTrans.position_ = { 0.0f,0, LoadTrans2.position_.z + 1.5f*15.0f};
	}
	if (abs(LoadTrans2.position_.z - pTrans.position_.z) >= 1.5 * 10 * 2) {
		LoadTrans2.position_ = { 0.0f,0, LoadTrans.position_.z + 1.5f * 15.0f };
	}

	Phase* sPhase = (Phase*)FindObject("Phase");
	if (ClearPhase == sPhase->GetPhase() && !IsClear) {
		Goal* sGoal = Instantiate<Goal>(this);
		sGoal->SetPosition({0,0,pTrans.position_.z+15});
		IsClear = true;
	}
}

void Stage::Draw()
{
	/*Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };
	Transform wallTrans;
	wallTrans.position_ = { 0,0,0 };
	for (int x = 0; x < stageWidth_; x++) {
		for (int z = 0; z < stageHeight_; z++) {
			floorTrans.position_ = { float(x),0,float(z)};
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}*/
	//
	// Player‚ÌˆÊ’u‚Æ‚Ì·‚ª-15*1.5‚ð’´‚¦‚½‚çPlayer‚Ì‘O‚ÉˆÚ“®
	//
	Transform LT;
	LT.position_ = LoadTrans.position_;
	for (int i = 0; i < 15; i++) {
		LT.position_.z += 1.5;
		Model::SetTransform(hLoad_, LT);
		Model::Draw(hLoad_);
	}

	LT.position_ = LoadTrans2.position_;
	for (int i = 0; i < 15; i++) {
		LT.position_.z += 1.5;
		Model::SetTransform(hLoad_, LT);
		Model::Draw(hLoad_);
	}
}

void Stage::Release()
{
}