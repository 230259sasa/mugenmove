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
	// ���E���S�̍��W�����߂�
	// �{�^�����������炻�̍��W�ֈړ�
	// 
	// ���W��z��֓����
	// �{�^������������z����w�肷�鐔���ύX�����
	// ���̍��W�ֈ��̑��x�ňړ�����v���O�������ʂɑ��݂���
	// x���W�̍������m�F���Ĉړ�����
	// �ړI�n��X���W-���݂�X���W
	// �ړ��̓v���C���[�̑��x�����ړ�
	// �������ړ���菬�����Ȃ����獷�����v���C���[�̍��W�ɉ�����
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
