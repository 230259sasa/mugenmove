#include "Stage.h"
#include"Engine\Model.h"
Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),hFloor_(-1),hWall_(-1)
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Modell\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Modell\\Wall.fbx");
	assert(hFloor_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };
	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			floorTrans.position_ = { float(x)*1,0,float(z)*1 };
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}
	Transform wallTrans;
	wallTrans.position_ = { 0,0,0 };
	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			if (x == 0 || x == 14 || z == 0 || z == 14) {
				wallTrans.position_ = { float(x) * 1,0,float(z) * 1 };
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
		}
	}
}

void Stage::Release()
{
}
