#include "Stage.h"
#include"Engine\Model.h"
#include<fstream>
#include<sstream>
#include"Engine\CsvReader.h"

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

	/*std::vector<std::string> rData;

	std::ifstream ifs;
	ifs.open("mapdata.csv");

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
	ifs.close();*/

	CsvReader csv;
	csv.Load("mapdata.csv");
	stageWidth_ = csv.GetWidth();
	stageHeight_ = csv.GetHeight();

	for (int i = 0; i < stageWidth_; i++) {
		std::vector<int>sdata(stageWidth_, 0);
		stageData.push_back(sdata);
	}

	for (int j = 0; j < stageHeight_; j++) {
		for (int i = 0; i < stageWidth_; i++) {
			stageData[j][i] = csv.GetValue(i,j);
		}
	}

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
			if (stageData[z][x] == 1) {
				wallTrans.position_ = { float(x),0,
					float(z) * -1 };
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			else if (stageData[z][x] == 0) {
				floorTrans.position_ = { float(x),0,
					float(z) * -1 };
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
	for (int i = 0; i < stageWidth_; i++) {
		std::vector<int>sdata(stageWidth_, 0);
		stageData.push_back(sdata);
	}
}

bool Stage::IsWall(int _x, int _y)
{
	//assert(_x > 0 && _x <= stageWidth_ && _y > 0 && _y <= stageHeight_);
	if (stageData[_y][_x] == STAGE_OBJ::WALL) {
		return true;
	}
	else
		return false;
}
