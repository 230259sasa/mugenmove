#include "VibrationCamera.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"

VibrationCamera::VibrationCamera(GameObject* parent)
	:GameObject(parent, "VibrationCamera"),frame(200),vibrationnum(0),
	VibrationStrenght(0.5)
{
}

void VibrationCamera::Initialize()
{
}

void VibrationCamera::Update()
{
	Transform tp,cp;
	cp.position_ = Camera::GetPosition();
	tp.position_ = Camera::GetTarget();

	if (frame <= 0) {
		frame = 5;

		float x = 0.0f;
		float y = VibrationStrenght;
		float rx, ry;
		int rotate = (vibrationnum * 90)%360;
		float radian = rotate * (3.141592 / 180);
		rx = x * cos(radian) - y * sin(radian);
		ry = x * sin(radian) + y * cos(radian);

		Transform p;
		p.position_ = { cp.position_.x + rx,cp.position_.y + ry,cp.position_.z };
		Camera::SetPosition(p.position_);
		p.position_ = { tp.position_.x + rx,tp.position_.y + ry,tp.position_.z };
		Camera::SetTarget(p.position_);

		Debug::Log("X = ");
		Debug::Log(rx, true);
		Debug::Log("Y = ");
		Debug::Log(ry, true);

		VibrationStrenght -= 0.08;
		if (VibrationStrenght <= 0.0f) {
			Camera::SetPosition(cp.position_);
			Camera::SetTarget(tp.position_);
			KillMe();
		}
		vibrationnum++;
	}

	frame--;
}

void VibrationCamera::Draw()
{
}

void VibrationCamera::Release()
{
}
