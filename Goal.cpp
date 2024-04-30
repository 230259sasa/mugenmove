#include "Goal.h"
#include "Engine\Model.h"

Goal::Goal(GameObject* parent)
	:GameObject(parent, "Goal"),hModel_(-1)
{
}

void Goal::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = { 0.5,0,15 };

	BoxCollider* collision = new BoxCollider({ 0,0.0,0 }, {3,1,1});
	AddCollider(collision);
}

void Goal::Update()
{
	//transform_.position_.z -= 0.1;
}

void Goal::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	CollisionDraw();
}

void Goal::Release()
{
}
