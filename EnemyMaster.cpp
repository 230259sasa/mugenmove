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
	//敵を一定の間隔で呼び出す
	//敵を一列に出現させて一定の時間が過ぎたら新しく敵が出現
	// 
	// 敵を用意します。一組3人の５組くらい
	// 並べます。　この際に必ず１つから２つの空きをつくる。余った奴らは適当な場所で待機
	// 　乱数で1から２の数を出す
	// 　0なら配置なし
	// 　1なら0から2の乱数を出し、2なら再び乱数を出して被ったのならメモリから出ないように
	// 　+または-1する
	// 移動させます。待機している奴は動かさない。
	// 見えなくなったら待機
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
