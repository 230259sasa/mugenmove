#include "Life.h"
#include "Engine/Image.h"

Life::Life(GameObject* parent)
	:GameObject(parent, "Stage"),MaxLife(0),NowLife(0),hNonactiveLife(-1),hActiveLife(-1)
{
}

void Life::Initialize()
{
	hActiveLife = Image::Load("Image\\life.png");
	assert(hActiveLife >= 0);
	hNonactiveLife = Image::Load("Image\\nlife.png");
	assert(hNonactiveLife >= 0);
}

void Life::Update()
{
}

void Life::Draw()
{
	Transform t;
	t.position_ = {-0.9,0.85,0};
	t.scale_ = { 0.2,0.2,0.2 };
	for (int i = 0; i < MaxLife; i++) {
		if (i < NowLife) {
			Image::SetTransform(hActiveLife,t);
			Image::Draw(hActiveLife);
		}
		else {
			Image::SetTransform(hNonactiveLife,t);
			Image::Draw(hNonactiveLife);
		}
		t.position_.x += 0.1;
	}
}

void Life::Release()
{
}
