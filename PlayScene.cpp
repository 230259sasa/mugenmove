#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Stage.h"
#include "Gauge.h"
#include"Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	p = Instantiate<Player>(this);
	Instantiate<Gauge>(this);
	Instantiate<Enemy>(this);
	Camera::SetPosition({ 7,15,-16 });
	Camera::SetTarget({ 7,0,-8 });
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
