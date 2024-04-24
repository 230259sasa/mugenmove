#include "Stage.h"
#include"Engine\Model.h"
#include<fstream>
#include<sstream>
#include"Engine\CsvReader.h"
#include"Phase.h"
#include"Goal.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hFloor_(-1), hLoad_(-1), stageWidth_(3), stageHeight_(15),ClearPhase(10),
	IsClear(false)
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hLoad_ = Model::Load("Model\\load.fbx");
	assert(hFloor_ >= 0);
	//transform_.position_ = { 0.5,0,14 };
}

void Stage::Update()
{
	if (zpos >= 1.5) {
		zpos = 0;
	}
	zpos += 0.1;

	Phase* sPhase = (Phase*)FindObject("Phase");
	if (ClearPhase == sPhase->GetPhase() && !IsClear) {
		Instantiate<Goal>(this);
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

	Transform LoadTrans;
	LoadTrans.position_ = { 0.5,0,-2-zpos };
	for (int i = 0; i < 12; i++) {
		LoadTrans.position_.z += 1.5;
		Model::SetTransform(hLoad_, LoadTrans);
		Model::Draw(hLoad_);
	}
}

void Stage::Release()
{
	for (int i = 0; i < stageWidth_; i++) {
		std::vector<int>sdata(stageWidth_, 0);
		stageData.push_back(sdata);
	}
}