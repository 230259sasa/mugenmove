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
	:GameObject(parent,"Player"),hModel_(-1),speed_(0),pStage(nullptr)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	//transform_.position_ = { 0.7,0.5,-1 };
	transform_.position_ = { 1,0,1 };
	speed_ = PS::PLAYER_MOVE_SPEED;

	pStage = (Stage*)FindObject("Stage");
}

void Player::Update()
{
	XMVECTOR vFront = { 0,0,1,0 };
	XMVECTOR move{ 0,0,0,0 };
	
	if (Input::IsKey(DIK_UP)) {
		move = XMVECTOR{ 0,0,1,0 };
		//moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_DOWN)) {
		move = XMVECTOR{ 0,0,-1,0 };
		//moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		move = XMVECTOR{ 1,0,0,0 };
		//moveDir = Dir::RIGHT;
	}
	if (Input::IsKey(DIK_LEFT)) {
		move = XMVECTOR{ -1,0,0,0 };
		//moveDir = Dir::LEFT;
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero();
	posTmp = pos + speed_ * move;

	int tx, ty;
	tx = (int)(XMVectorGetX(pos));
	ty = (int)(XMVectorGetZ(pos) - 2) * -1;
	Debug::Log("x,z=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);

	if (!pStage->IsWall(tx,ty)) {
		pos = posTmp;
		if (!XMVector3Equal(move, XMVectorZero())) {
			XMStoreFloat3(&(transform_.position_), pos);
			//float rotAngle[5] = { 0,90,180,270,0 };
			//transform_.rotate_ = { 0,rotAngle[moveDir],0};

			XMVECTOR vdot = XMVector3Dot(vFront, move);
			assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
			float angle = acos(XMVectorGetX(vdot));
			XMVECTOR vCross = XMVector3Cross(vFront, move);
			if (XMVectorGetY(vCross) < 0) {
				angle *= -1;
			}
			transform_.rotate_.y = XMConvertToDegrees(angle);
		}
	}
	
	
}

void Player::Draw()
{
	Transform t = transform_;
	t.position_.x = (int)transform_.position_.x - 0.5;
	t.position_.y = transform_.position_.y;
	t.position_.z = (int)transform_.position_.z - 1.5;
	Model::SetTransform(hModel_, t);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
