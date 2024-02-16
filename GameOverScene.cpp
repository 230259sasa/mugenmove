#include "GameOverScene.h"
#include"Engine\Image.h"
#include"Engine\Input.h"

GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hImage_(-1)
{
}

void GameOverScene::Initialize()
{
	hImage_ = Image::Load("Image\\GameOver.png");
	assert(hImage_ >= 0);
}

void GameOverScene::Update()
{
}

void GameOverScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
}

void GameOverScene::Release()
{
}
