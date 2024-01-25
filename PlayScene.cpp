#include "PlayScene.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Stage.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Camera::SetPosition({ 0,20,-10 });
	Camera::SetTarget({ 0,10,-5 });
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
