#include "VibrationCamera.h"
#include "Engine/Camera.h"

VibrationCamera::VibrationCamera(GameObject* parent)
	:GameObject(parent, "VibrationCamera")
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
}

void VibrationCamera::Draw()
{
}

void VibrationCamera::Release()
{
}
