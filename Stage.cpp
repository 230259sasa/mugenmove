#include "Stage.h"
#include"Engine\Model.h"
#include<fstream>
#include<sstream>
#include"Engine\CsvReader.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hFloor_(-1), hWall_(-1), stageWidth_(3), stageHeight_(20)
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hFloor_ >= 0);

}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };
	Transform wallTrans;
	wallTrans.position_ = { 0,0,0 };
	for (int x = 0; x < stageWidth_; x++) {
		for (int z = 0; z < stageHeight_; z++) {
			floorTrans.position_ = { float(x),0,float(z)};
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}
	floorTrans.position_ = { 0,1,0 };
	Model::SetTransform(hFloor_, floorTrans);
	Model::Draw(hFloor_);
}

void Stage::Release()
{
	for (int i = 0; i < stageWidth_; i++) {
		std::vector<int>sdata(stageWidth_, 0);
		stageData.push_back(sdata);
	}
}