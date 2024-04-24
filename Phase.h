#pragma once
#include "Engine/GameObject.h"
#include"Gauge.h"

namespace PhaseSetting {
	const int PHASE_INTERVAL_FRAME(600);
}

class Phase :
    public GameObject
{
	Gauge* PhaseGauge;
	int PhaseCount;
	int PhaseFrame;
public:
	Phase(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	int GetPhase() { return PhaseCount; }
};

