#include "TitleScene.h"
#include"Engine\Image.h"
#include"Engine\Input.h"
#include"Engine\SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hImage_(-1)
{
}

void TitleScene::Initialize()
{
	hImage_ = Image::Load("Image\\Title.png");
	assert(hImage_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_F) || Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
}

void TitleScene::Release()
{
}
