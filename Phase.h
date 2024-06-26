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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetPhase() { return PhaseCount; }
};

