#include "EnemyMaster.h"
#include"Engine\Debug.h"
#include"Engine/Text.h"

EnemyMaster::EnemyMaster(GameObject* parent)
	:GameObject(parent, "EnemyMaster"), frame(0),enemyrow(0),Phase(0),NextPhase(0),
	spawnframe(120),PhaseFrame(600),speed_(0.05)
{
}

void EnemyMaster::Initialize()
{
	PhaseGauge = (Gauge*)FindObject("Gauge");
	PhaseGauge->SetPosition(0.45, 0.85, 0);
}

void EnemyMaster::Update()
{
	if (frame <= 0) {
		frame = spawnframe;

		int r = rand() % EMS::EnemyRow;
		float rspeed = 0.0f;

		if (rand() % 4 == 0)
			switch (rand() % 2) {
			case 0:
				rspeed = 0.02;
				break;
			case 1:
				rspeed = -0.02;
				break;
			default:
				break;
			}
		for (int i = 0; i < EMS::EnemyLine; i++) {

			//enemy[enemyrow][posrand]->SetTransformPosition(posrand-0.5,0.2,15);
			if (EMS::EnemyCombination[r][i] == 1) {
				Enemy* e = Instantiate<Enemy>(this);
				e->SetTransformPosition(i - 0.5, 0.2, 15);
				e->SetSpeed(speed_+rspeed);
				e->IsMoveStart();
			}
		}
	}

	PhaseGauge->SetGaugeVal(PhaseFrame, 600);
	if (PhaseFrame <= 0) {
		PhaseFrame = 600;
		NextPhase++;
	}

	if (Phase != NextPhase) {
		Phase = NextPhase;
		float nextspeed=0;
		switch (Phase) {
		case 0:
			nextspeed = 0.05;
		case 1:
			nextspeed = 0.06;
			break;
		case 2:
			nextspeed = 0.075;
			break;
		case 3:
			nextspeed = 0.1;
			break;
		case 4:
			nextspeed = 0.125;
			break;
		case 5:
			nextspeed = 0.15;
			break;
		case 6:
			nextspeed = 0.175;
			break;
		case 7:
			nextspeed = 0.2;
			break;
		default:
			nextspeed = 0.2;
			//nextspeed = 0.2 + (Phase-7) * 0.05;
		}
		spawnframe = 120 / (nextspeed / 0.05);
		speed_ = nextspeed;
	}

	frame--;
	PhaseFrame--;
}

void EnemyMaster::Draw()
{
	Text t;
	char c[] = "level";
	t.Initialize();
	t.Draw(800, 100, c);
	t.Draw(900, 100, Phase);
}

void EnemyMaster::Release()
{
}
