#include "Player.h"
#include "Engine\Model.h"
#include "Engine\Input.h"
#include "Engine\Debug.h"
#include "Stage.h"

namespace PlayerSetting {
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

namespace PS = PlayerSetting;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), speed_(0), pStage(nullptr),
	moveingpositionnum(1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	//transform_.scale_ = { 0.005,0.005,0.005 };
	//transform_.rotate_.x = -90;
	transform_.position_ = { 0.6,0.4,3 };
	speed_ = PS::PLAYER_MOVE_SPEED;
	SphereCollider* collision = new SphereCollider({ 0,-0.1,0 }, 0.3f);
	AddCollider(collision);

	moveingposition[0] = -0.5;
	moveingposition[1] = 0.5;
	moveingposition[2] = 1.5;
}

void Player::Update()
{
	
	if (Input::IsKey(DIK_RIGHT)) {
		/*if (transform_.position_.x < 1.6)
			transform_.position_.x = transform_.position_.x + 0.1;*/
		if (!IsRightDown) {
			if (moveingpositionnum < 2)
				moveingpositionnum++;
		}

		IsRightDown = true;
	}
	else
		IsRightDown = false;

	if (Input::IsKey(DIK_LEFT)) {
		/*if (transform_.position_.x > -0.5)
			transform_.position_.x = transform_.position_.x - 0.1;*/
		if (!IsLeftDown) {
			if (moveingpositionnum > 0)
				moveingpositionnum--;
		}
		IsLeftDown = true;
	}
	else
		IsLeftDown = false;
	//
	// 左右中心の座標を決める
	// ボタンを押したらその座標へ移動
	// 
	// 座標を配列へ入れる
	// ボタンを押したら配列を指定する数が変更される
	// その座標へ一定の速度で移動するプログラムが別に存在する
	// x座標の差分を確認して移動する
	// 目的地のX座標-現在のX座標
	// 移動はプレイヤーの速度だけ移動
	// 差分が移動より小さくなったら差分をプレイヤーの座標に加える
	//
	float difference;
	difference = moveingposition[moveingpositionnum] - transform_.position_.x;
	if(difference != 0)
	if (abs(difference) < speed_) {
		transform_.position_.x += difference;
	}
	else {
		if (difference < 0) {
			transform_.position_.x -= speed_;
		}
		else {
			transform_.position_.x += speed_;
		}
	}
}

void Player::Draw()
{
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
	CollisionDraw();
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		this->KillMe();
	}
}
