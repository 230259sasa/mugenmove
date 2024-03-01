#include "Player.h"
#include "Engine\Model.h"
#include "Engine\Input.h"
#include "Engine\Debug.h"
#include "Stage.h"
#include "Gauge.h"

namespace PlayerSetting {
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

namespace PS = PlayerSetting;


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), speed_(0), pStage(nullptr),
	hpCrr_(100), hpMax_(100)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	//transform_.position_ = { 0.7,0.5,-1 };
	transform_.position_ = { 1,0,-1 };
	speed_ = PS::PLAYER_MOVE_SPEED;

	pStage = (Stage*)FindObject("Stage");
	SphereCollider* collision = new SphereCollider(XMFLOAT3(-0.7, 0, 0.5), 0.3f);
	AddCollider(collision);
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

	int tx, ty,rx,ry;
	
	tx = (int)(XMVectorGetX(posTmp)  + 0);
	ty = (int)(XMVectorGetZ(posTmp) * -1 + 0);
	rx = (int)(XMVectorGetX(posTmp) + 0.7);
	ry = (int)(XMVectorGetZ(posTmp) * - 1 + 0.8);

	Debug::Log("x,z=");
	Debug::Log(int(transform_.position_.x));
	Debug::Log(",");
	Debug::Log(int(transform_.position_.z), true);

	if (!pStage->IsWall(tx, ty) && !pStage->IsWall(rx, ry) && !pStage->IsWall(tx, ry) && !pStage->IsWall(rx, ty)) {
		pos = posTmp;
		if (!XMVector3Equal(move, XMVectorZero())) {

			vecx = tx;
			vecy = ty;

			XMStoreFloat3(&(transform_.position_), pos);

			//XMMATRIX rot = XMMatrixRotationY(XM_PIDIV2);
			//XMVECTOR modifiedVec = XMPlaneTransform(move, rot);
			//Debug::Log(XMVectorGetX(modifiedVec));
			//Debug::Log(",");
			//Debug::Log(XMVectorGetZ(modifiedVec));

			//float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
			//Debug::Log("=>");
			//Debug::Log(XMConvertToDegrees(angle),true);
			//float rotAngle[5] = { 0,90,180,270,0 };
			//transform_.rotate_ = { 0,rotAngle[moveDir],0};

			/*XMVECTOR vdot = XMVector3Dot(vFront, move);
			assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
			float angle = acos(XMVectorGetX(vdot));*/
			float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
			/*XMVECTOR vCross = XMVector3Cross(vFront, move);
			if (XMVectorGetY(vCross) < 0) {
				angle *= -1;
			}*/
			transform_.rotate_.y = XMConvertToDegrees(angle);
		}
	}
	else {
		hpCrr_ -= 0.1;
		float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
		/*XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0) {
			angle *= -1;
		}*/
		transform_.rotate_.y = XMConvertToDegrees(angle);
	}
		
	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetGaugeVal(hpCrr_, hpMax_);
	
}

void Player::Draw()
{
	Transform t = transform_;
	t.position_.x = transform_.position_.x - 0.7;
	t.position_.y = transform_.position_.y;
	t.position_.z = transform_.position_.z + 0.5;
	Model::SetTransform(hModel_, t);
	Model::Draw(hModel_);
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
