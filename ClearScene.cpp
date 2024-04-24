#include "ClearScene.h"
#include"Engine/Image.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hImage_(-1)
{
}

void ClearScene::Initialize()
{
	hImage_ = Image::Load("Image\\Clear.png");
	assert(hImage_ >= 0);
}

void ClearScene::Update()
{
}

void ClearScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
}

void ClearScene::Release()
{
}
