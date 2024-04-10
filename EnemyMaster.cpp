#include "EnemyMaster.h"
#include"Engine\Debug.h"

EnemyMaster::EnemyMaster(GameObject* parent)
	:GameObject(parent, "EnemyMaster"), frame(0),enemyrow(0),Phase(0),NextPhase(0),
	spawnframe(120),PhaseFrame(600)
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

			enemy[enemyrow][posrand]->SetTransformPosition(posrand-0.5,0.2,15);
			enemyrand = posrand;
		}
		
		enemyrow = (enemyrow + 1) % 5;
	}

	if (PhaseFrame <= 0) {
		PhaseFrame = 600;
		NextPhase++;
	}

	if (Phase != NextPhase) {
		Phase = NextPhase;
		float nextspeed=0.05;
		switch (Phase) {
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
		default:
			nextspeed = 0.2;
		}
		spawnframe = 120 / (nextspeed / 0.05);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				enemy[i][j]->SetSpeed(nextspeed);
			}
		}
	}
	frame--;
	PhaseFrame--;
}

void EnemyMaster::Draw()
{
}

void EnemyMaster::Release()
{
}