#include "Phase.h"
#include "Engine\Text.h"

namespace PS = PhaseSetting;

Phase::Phase(GameObject* parent)
	:GameObject(parent, "Phase"),PhaseCount(0),PhaseFrame(PS::PHASE_INTERVAL_FRAME)
{
}

void Phase::Initialize()
{
	PhaseGauge = Instantiate<Gauge>(this);
	PhaseGauge->SetPosition(0.45, 0.85, 0);
}

void Phase::Update()
{
	PhaseGauge->SetGaugeVal(PhaseFrame, PS::PHASE_INTERVAL_FRAME);
	if (PhaseFrame <= 0) {
		PhaseFrame = PS::PHASE_INTERVAL_FRAME;
		PhaseCount++;
	}

	PhaseFrame--;
}

void Phase::Draw()
{
	Text t;
	char c[] = "level";
	t.Initialize();
	t.Draw(800, 100, c);
	t.Draw(900, 100, PhaseCount);
}

void Phase::Release()
{
}
