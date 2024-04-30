#include "EnemyMaster.h"
#include"Engine\Debug.h"
#include"Engine/Text.h"
#include "Stage.h"
#include "Engine/Debug.h"
#include "Player.h"

EnemyMaster::EnemyMaster(GameObject* parent)
	:GameObject(parent, "EnemyMaster"), frame(0),enemyrow(0),PhaseCount(0),NextPhase(0),
	spawnframe(120),PhaseFrame(600),speed_(0.0)
{
}

void EnemyMaster::Initialize()
{
	ePhase = (Phase*)FindObject("Phase");
	ePlayer = (Player*)FindObject("Player");

	for (int i = 0; i < EMS::EnemyRow; i++) {
		for (int j = 0; j < EMS::EnemyLine; j++) {
			enemy[i][j] = Instantiate<Enemy>(this);
		}
	}
}

void EnemyMaster::Update()
{
	if (frame <= 0) {
		frame = spawnframe;

		float rspeed = 0.0f;
		int r = rand() % EMS::EnemyRow;

		/*if (rand() % 4 == 0) {
			switch (rand() % 2) {
			case 0:
				rspeed = 0.01;
				break;
			case 1:
				rspeed = -0.01;
				break;
			default:
				break;
			}
		}*/

		for (int i = 0; i < EMS::EnemyLine; i++) {
			if (EMS::EnemyCombination[r][i] == 1) {
				/*Enemy* e = Instantiate<Enemy>(this);
				e->SetTransformPosition(i - 0.5, 0.2, 15);
				e->SetSpeed(speed_);
				if (speed_ > 1) {
					e->SetRotateY(0);
				}
				else {
					e->SetRotateY(180);
				}*/
				//e->IsMoveStart();
				
				enemy[enemyrow][i]->SetTransformPosition(i - 1.0f, 0.2,ePlayer->GetFloatPosZ() + 15);
				enemy[enemyrow][i]->IsMoveStart();
				
			}
		}
		enemyrow = (enemyrow + 1) % EMS::EnemyRow;
	}

	
	/*if (PhaseFrame <= 0) {
		PhaseFrame = 600;
		NextPhase++;
	}*/

	if (PhaseCount != ePhase->GetPhase()) {
		PhaseCount = ePhase->GetPhase();
		float nextspeed=0;
		switch (PhaseCount) {
		case 0:
			nextspeed = 0.01;
		case 1:
			nextspeed = 0.02;
			break;
		case 2:
			nextspeed = 0.04;
			break;
		case 3:
			nextspeed = 0.06;
			break;
		case 4:
			nextspeed = 0.08;
			break;
		case 5:
			nextspeed = 0.10;
			break;
		case 6:
			nextspeed = 0.12;
			break;
		case 7:
			nextspeed = 0.14;
			break;
		default:
			nextspeed = 0.14;
			//nextspeed = 0.2 + (Phase-7) * 0.05;
		}
		spawnframe = 120 / (nextspeed/0.035);
		if (spawnframe > 120) {
			spawnframe = 120;
		}
		speed_ = nextspeed;
		Stage* eStage = (Stage*)FindObject("Stage");
		eStage->SetSpeed(speed_);

		for (int i = 0; i < EMS::EnemyRow; i++) {
			for (int j = 0; j < EMS::EnemyLine; j++) {
				enemy[i][j]->SetSpeed(speed_);
			}
		}
	}

	frame--;
	//PhaseFrame--;
}

void EnemyMaster::Draw()
{
}

void EnemyMaster::Release()
{
}
