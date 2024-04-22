#include "Gauge.h"
#include"Engine/Image.h"
#include"Engine/Text.h"

Gauge::Gauge(GameObject* parent):
	GameObject(parent, "Gauge"), hGaugeBar_(-1), hGaugeFrame_(-1),
	gaugeCrrVal_(0), gaugeMaxVal_(0)
{
}

void Gauge::Initialize()
{
	hGaugeBar_ = Image::Load("bar.png");
	assert(hGaugeBar_ >= 0);
	hGaugeFrame_ = Image::Load("frame.png");
	assert(hGaugeFrame_ >= 0);

	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.9f;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	Transform tr = transform_;
	tr.scale_.x = (float)gaugeCrrVal_ / (float)gaugeMaxVal_;
	//¶‚É‚»‚ë‚¦‚é‚½‚ß‚É¶‚Ì‹ó”’‚ğ‚à‚Æ‚ß‚Ä‚»‚Ì•ª¶‚ÖˆÚ“®‚·‚é
	//’·‚³@0.4 
	//position.x(0) - ’·‚³‚Ì”¼•ª*(1 - HP‚ÌŠ„‡) 
	tr.position_.x -= 0.2 * (1 - ((float)gaugeCrrVal_ / (float)gaugeMaxVal_));
	Image::SetTransform(hGaugeBar_, tr);
	Image::Draw(hGaugeBar_);
	Image::SetTransform(hGaugeFrame_, transform_);
	Image::Draw(hGaugeFrame_);
}

void Gauge::Release()
{
}
