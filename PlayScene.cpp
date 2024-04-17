#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Stage.h"
#include"Enemy.h"
#include"EnemyMaster.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	p = Instantiate<Player>(this);
	Instantiate<EnemyMaster>(this);
	//Camera::SetPosition({ 0.5,10,-2});
	Camera::SetPosition({ 20,0,5 });
	Camera::SetTarget({ 0.5,0,5 });
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
