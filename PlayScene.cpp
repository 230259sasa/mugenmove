#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Stage.h"
#include"Enemy.h"
#include"EnemyMaster.h"
#include "Phase.h"
#include"Gauge.h"
#include"Goal.h"
#include"VibrationCamera.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Camera::SetPosition({ 0.0,10,-2 });
	//Camera::SetPosition({ 0,10,8 });
	//Camera::SetPosition({ 2,6,-2 });
	//Camera::SetPosition({ 20,0,5 });
	//Camera::SetPosition({ 0,0,-2 });
	Camera::SetTarget({ 0.0,0,5 });

	Instantiate<Phase>(this);
	Instantiate<Stage>(this);
	p = Instantiate<Player>(this);
	//Instantiate<Gauge>(this);
	Instantiate<EnemyMaster>(this);
	//Instantiate<Goal>(this);
}

void PlayScene::Update()
{
	if (p->IsDead()) {
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
