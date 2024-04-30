#include "VibrationCamera.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include"Player.h"

VibrationCamera::VibrationCamera(GameObject* parent)
	:GameObject(parent, "VibrationCamera"), frame(0), vibrationnum(0),
	VibrationStrenght(0.3), IsVibration(false)
{
}

void VibrationCamera::Initialize()
{
#if(false)
	frame = 230;
#endif
	//cp.position_ = Camera::GetPosition();
	//tp.position_ = Camera::GetTarget();

	vPlayer = (Player*)FindObject("Player");
}

void VibrationCamera::Update()
{
	if (IsVibration) {

		float x = VibrationStrenght;
		float y = 0.0f;
		float rx, ry;
		int rotate = (vibrationnum * 180) % 360;
		float radian = rotate * (3.141592 / 180);
		rx = x * cos(radian) - y * sin(radian);
		ry = x * sin(radian) + y * cos(radian);

		Transform p;
		p.position_ = { 0.0f + rx,10.0f + ry,vPlayer->GetFloatPosZ() - 7.0f };
		Camera::SetPosition(p.position_);
		p.position_ = { 0.0f + rx,0.0f + ry,vPlayer->GetFloatPosZ() };
		Camera::SetTarget(p.position_);

		if (frame <= 0) {
			frame = 5;

#if(false)
			Debug::Log("X = ");
			Debug::Log(rx, true);
			Debug::Log("Y = ");
			Debug::Log(ry, true);
#endif

			VibrationStrenght -= 0.07;
			if (VibrationStrenght <= 0.0f) {
				//Camera::SetPosition(cp.position_);
				//Camera::SetTarget(tp.position_);
				VibrationStrenght = 0.3;
				IsVibration = false;
				vibrationnum = 0;
				frame = 0;
			}
			vibrationnum++;
		}
	}
	
	frame--;
}

void VibrationCamera::Draw()
{
}

void VibrationCamera::Release()
{
}
