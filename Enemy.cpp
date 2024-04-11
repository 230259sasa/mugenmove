#include "Enemy.h"
#include "Engine\Model.h"
#include "Stage.h"
#include "Player.h"
#include "Engine\Input.h"
#include"Engine/Debug.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), speed_(0),ismove_(false)
{
}

void Enemy::Initialize()
{
	//hModel_ = Model::Load("Model\\Bullet.fbx");
	hModel_ = Model::Load("Model\\car1.fbx");
	assert(hModel_ >= 0);
	speed_ = 0.05f;
	//transform_.scale_ = { 0.3,0.3,0.3 };
	transform_.rotate_.y = 90;
	transform_.position_ = { 3,0,8 };
	SphereCollider* collision = new SphereCollider({ 0,0,0 }, 0.3f);
	AddCollider(collision);
}

void Enemy::Update()
{
	if (ismove_) {
		transform_.position_.z -= speed_;
	}

	if (transform_.position_.z < -5) {
		KillMe();
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	CollisionDraw();
}

void Enemy::Release()
{
}