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
	Enemy* e;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			e = Instantiate<Enemy>(this);
			e->SetTransformPosition(20, 20, 20);
			e->IsMoveStart();
			enemy[i][j] = e;
		}
	}
	PhaseGauge = (Gauge*)FindObject("Gauge");
	PhaseGauge->SetPosition(0.45, 0.85, 0);
}

void EnemyMaster::Update()
{
	//�G�����̊Ԋu�ŌĂяo��
	//�G�����ɏo�������Ĉ��̎��Ԃ��߂�����V�����G���o��
	// 
	// �G��p�ӂ��܂��B��g3�l�̂T�g���炢
	// ���ׂ܂��B�@���̍ۂɕK���P����Q�̋󂫂�����B�]�����z��͓K���ȏꏊ�őҋ@
	// �@������1����Q�̐����o��
	// �@0�Ȃ�z�u�Ȃ�
	// �@1�Ȃ�0����2�̗������o���A2�Ȃ�Ăї������o���Ĕ�����̂Ȃ烁��������o�Ȃ��悤��
	// �@+�܂���-1����
	// �ړ������܂��B�ҋ@���Ă���z�͓������Ȃ��B
	// �����Ȃ��Ȃ�����ҋ@
	if (frame <= 0) {
		frame = spawnframe;

		int r = rand() % 2 + 1;
		int enemyrand = -1;
		for (int i = 0; i < r; i++) {
			int posrand = rand() % 3;

			if (enemyrand == posrand) {
				posrand++;
				if (posrand >= 3) {
					posrand -= 2;
				}
			}


			//enemy[enemyrow][posrand]->SetTransformPosition(posrand-0.5,0.2,15);
			Enemy* e = Instantiate<Enemy>(this);
			e->SetTransformPosition(posrand - 0.5, 0.2, 15);
			e->SetSpeed(speed_);
			e->IsMoveStart();
			enemyrand = posrand;
		}
		
		enemyrow = (enemyrow + 1) % 5;
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
		/*for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				enemy[i][j]->SetSpeed(nextspeed);
			}
		}*/
	}

	frame--;
	PhaseFrame--;
}

void EnemyMaster::Draw()
{
	Text t;
	char c[] = "level";
	t.Initialize();
	t.Draw(800, 55, c);
	t.Draw(900, 55, Phase);
}

void EnemyMaster::Release()
{
}
