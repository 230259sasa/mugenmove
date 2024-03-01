#include "Energy.h"
#include "Engine/Model.h"

Energy::Energy(GameObject* parent)
	:GameObject(parent, "Energy"), hModel_(-1)
{
}

void Energy::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 0.4,0.4,0.4 };
	SphereCollider* collision = new SphereCollider(XMFLOAT3(-0.5, 0, 0.5), 0.2f);
	AddCollider(collision);
}

void Energy::Update()
{
}

void Energy::Draw()
{
	Transform t = transform_;
	t.position_.x = transform_.position_.x - 0.5;
	t.position_.z = transform_.position_.z + 0.5;
	Model::SetTransform(hModel_, t);
	Model::Draw(hModel_);
}

void Energy::Release()
{
}

void Energy::SetPos(float _x, float _z)
{
	transform_.position_.x = _x;
	transform_.position_.z = _z;
}

void Energy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		this->KillMe();
	}
}
