#include "Stage.h"
#include"Engine\Model.h"

#include<fstream>
#include<sstream>

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),hFloor_(-1),hWall_(-1)
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hFloor_ >= 0);

	std::vector<std::string> rData;

	std::ifstream ifs;
	ifs.open("mapdate.csv");

	if (ifs.fail())
	{
		exit(1);
	}
	std::string tmp;
	while (std::getline(ifs, tmp))
	{
		rData.push_back(tmp);
	}

	for (int i = 0; i < rData.size(); i++)
	{
		std::stringstream oss(rData[i]);
		std::string tmp;
		std::vector<int> vtmp;
		while (std::getline(oss, tmp, ',')) {
			std::stringstream iss(tmp);
			int ntmp;
			iss >> ntmp;
			vtmp.push_back(ntmp);
		}
		mapArray.push_back(vtmp);
	}
	ifs.close();
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

	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			if (mapArray[z][x] == 1) {
				wallTrans.position_ = { float(x) * 1 - mapArray[0].size() / 2,0,
					float(z) * -1 + mapArray.size() / 2 };
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			else if (mapArray[z][x] == 0) {
				floorTrans.position_ = { float(x) * 1 - mapArray[0].size() / 2,0,
					float(z) * -1 + mapArray.size() / 2 };
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
}
