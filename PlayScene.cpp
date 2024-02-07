#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Stage.h"
#include "Gauge.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Gauge>(this);
	Camera::SetPosition({ 7,15,-16 });
	Camera::SetTarget({ 7,0,-8 });
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
