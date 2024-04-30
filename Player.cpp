#include "Player.h"
#include "Engine\Model.h"
#include "Engine\Input.h"
#include "Engine\Debug.h"
#include "Stage.h"
#include "Life.h"
#include"Engine/SceneManager.h"
#include"VibrationCamera.h"
#include"Engine/Camera.h"

namespace PS = PlayerSetting;

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), speed_(0), pStage(nullptr), InvincibleTime(0),
	moveingpositionnum(1)
{
}

void Player::Initialize()
{
	//hModel_ = Model::Load("Model\\human.fbx");
	hModel_ = Model::Load("Model\\Player.fbx");
	//hModel_ = Model::Load("Model\\play2.fbx");
	assert(hModel_ >= 0);

	//Model::SetAnimFrame(hModel_, 3, 90, 60);
	//transform_.scale_ = {0.01,0.01,0.01 };
	//transform_.rotate_.y = 180;
	transform_.position_ = { 0,0,3 };
	speed_ = PS::PLAYER_MOVE_SPEED;
	SphereCollider* collision = new SphereCollider({ 0,0.3,0 }, 0.3f);
	AddCollider(collision);

	plife = Instantiate<Life>(this);
	plife->SetLife(3);

	pVib = Instantiate<VibrationCamera>(this);

	moveingposition[0] = -1.0;
	moveingposition[1] = 0.0;
	moveingposition[2] = 1.0;
}

void Player::Update()
{
	if (Input::IsKeyDown(DIK_RIGHT)) {
		/*if (transform_.position_.x < 1.6)
			transform_.position_.x = transform_.position_.x + 0.1;*/
		if (moveingpositionnum < 2)
			moveingpositionnum++;
	}

	if (Input::IsKeyDown(DIK_LEFT)) {
		/*if (transform_.position_.x > -0.5)
			transform_.position_.x = transform_.position_.x - 0.1;*/
		if (moveingpositionnum > 0)
			moveingpositionnum--;
	}

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
	if (difference != 0)
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

	//�ʏ�@1
	//Invincibletime 1��0�����݂�

	if (InvincibleTime < 0) {
		FlashingIntervalTime = PS::FLASHING_INTERVAL;
		IsDraw = true;
	}
	else {
		if (FlashingIntervalTime < 0) {
			if (IsDraw) {
				IsDraw = false;
			}
			else {
				IsDraw = true;
			}
			FlashingIntervalTime = PS::FLASHING_INTERVAL;
		}
		FlashingIntervalTime--;
	}

	transform_.position_.z += 0.05;

	if (!pVib->GetIsVibration()) {
		Camera::SetPosition({ 0.0f,10.0f,transform_.position_.z - 7.0f });
		Camera::SetTarget({ 0.0f,0.0f,transform_.position_.z });
	}

	//pStage->SetPlayerPos(transform_);
	InvincibleTime--;
}

void Player::Draw()
{
	if (IsDraw) {
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}

	CollisionDraw();
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy" && InvincibleTime <= 0)
	{
		plife->ReduseNowLife();
		InvincibleTime = PS::INVINCIBLE_INTERVAL;
		IsDraw = false;
		if (plife->GetNowLife() <= 0) {
			this->KillMe();
		}
		else {
			pVib->StartVibration();
		}
	}

	if (pTarget->GetObjectName() == "Goal") {
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID_CLEAR);
	}
}
