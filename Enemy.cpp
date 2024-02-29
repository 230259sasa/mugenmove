#include "Enemy.h"
#include "Engine\Model.h"
#include "Stage.h"
#include "Player.h"
#include "Engine\Input.h"
#include"Engine/Debug.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), speed_(0), pStage(nullptr)
{
	nowarrpos = 0;
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	pStage = (Stage*)FindObject("Stage");
	speed_ = 0.1f;
	transform_.position_ = { 13,0.3,-13 };
	SphereCollider* collision = new SphereCollider(XMFLOAT3(-0.5, 0, 0.4), 0.3f);
	AddCollider(collision);
	Pursue();
}

void Enemy::Update()
{
	if (Frame <= 0) {
		Pursue();
		Frame = 30;
	}
	else
		Frame--;

	//for (int i = 0; i < PursueArr.size(); i++) {
	//	Debug::Log("[");
	//	Debug::Log(PursueArr[i].x);
	//	Debug::Log(",");
	//	Debug::Log(PursueArr[i].y);
	//	Debug::Log("]");
	//	//PursueArr[i].x
	//	//PursueArr[i].y
	//}
	//Debug::Log("", true);
	//上の関数でだしたプレイヤーの位置までの道のりを辿る
	//まずPursueArrのどの位置にいるかを調べる
	// そこから次に向かう座標を求める
	// 移動
	//
	//XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	//XMVECTOR move{ 0,0,0,0 };
	/*int nowpos = 0;
	
	int myx = (int)(XMVectorGetX(pos) - 0.5);
	int myy = (int)(XMVectorGetZ(pos) * -1 + 0.4);
	for (int i = 0; i < PursueArr.size(); i++) {
		if (myx == PursueArr[i].x && myy == PursueArr[i].y) {
			nowpos = i;
			break;
		}
	}
	
	if (nowpos + 1 < PursueArr.size())
		if (nowpos < PursueArr.size()) {
			if (myx != PursueArr[nowpos + 1].x) {
				if (myx - PursueArr[nowpos + 1].x <= 0) {
					move = XMVECTOR{ 1,0,0,0 };
				}
				else {
					move = XMVECTOR{ -1,0,0,0 };
				}
			}
			else if (myy != PursueArr[nowpos + 1].y) {
				if (myy - PursueArr[nowpos + 1].y >= 0) {
					move = XMVECTOR{ 0,0,1,0 };
				}
				else {
					move = XMVECTOR{ 0,0,-1,0 };
				}
			}
		}*/
	/*pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);*/

	// Pursueを動かしたらnowarrを初期化
	// nowarrの数字を参照して配列から座標を取り出す
	// 座標に向かって移動
	// 目的地に着いたらnowarrを+1(PursueArrの大きさを超えたら移動をしない)
	// 
	// 改良点
	// Playerの位置をint変換しているので近すぎると追わなくなる
	// 配列の最後まで移動してかつPlayerの位置が近かったら(0.5くらい?)
	// 直接接近するようにする。 済み
	// プレイヤーが壁の中にいる扱いになるときがある　角とか
	// 
	//
	Player* pPlayer;
	pPlayer = (Player*)FindObject("Player");
	float px = pPlayer->GetFloatPosX();
	float pz = pPlayer->GetFloatPosZ();

	//PursueArrの大きさをnowarrが超えたら移動をしない
	if (PursueArr.size() > nowarrpos && PursueArr.size() != 0) {
		float x, z;//初期の位置から目的地までの距離
		x = PursueArr[nowarrpos].x - startX;
		z = -PursueArr[nowarrpos].y - startZ;
		//rateは1フレームに移動する割合
		// 割合は移動量/距離  
		// 割合が1を超える場合はrate=1.0にする
		//
		rateX += speed_ / abs(x);
		rateZ += speed_ / abs(z);
		
		/*Debug::Log(rateX);
		Debug::Log(",");
		Debug::Log(rateZ, true);*/
		
		if (rateX > 1.0f) {
			rateX = 1.0f;
		}
		if (rateZ > 1.0f) {
			rateZ = 1.0f;
		}
		//距離*レート+初期位置で移動
		transform_.position_.x = (x * rateX) + startX;
		transform_.position_.z = (z * rateZ) + startZ;
		//目標地点に着いたらnowarrを+１
		//startの更新,rateの初期化、
		if (rateX >= 1.0f && rateZ >= 1.0f) {
			nowarrpos++;
			startX = transform_.position_.x;
			startZ = transform_.position_.z;
			rateX = 0;
			rateZ = 0;
		}
	}
	else if(abs(px - transform_.position_.x) < 1.0f && abs(pz - transform_.position_.z) < 1.0f){
		float x, z;//初期の位置から目的地までの距離
		x = px - startX;
		z = pz - startZ;
		//rateは1フレームに移動する割合
		// 割合は移動量/距離  
		// 割合が1を超える場合はrate=1.0にする
		//
		rateX += speed_ / abs(x);
		rateZ += speed_ / abs(z);

		Debug::Log(rateX);
		Debug::Log(",");
		Debug::Log(rateZ, true);

		if (rateX > 1.0f) {
			rateX = 1.0f;
		}
		if (rateZ > 1.0f) {
			rateZ = 1.0f;
		}
		//距離*レート+初期位置で移動
		transform_.position_.x = (x * rateX) + startX;
		transform_.position_.z = (z * rateZ) + startZ;
		//目標地点に着いたらnowarrを+１
		//startの更新,rateの初期化、
		if (rateX >= 1.0f && rateZ >= 1.0f) {
			startX = transform_.position_.x;
			startZ = transform_.position_.z;
			rateX = 0;
			rateZ = 0;
		}
	}
}

void Enemy::Draw()
{
	Transform t = transform_;
	t.position_.x = transform_.position_.x - 0.5;
	t.position_.z = transform_.position_.z + 0.4;
	Model::SetTransform(hModel_, t);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::Pursue()
{
	//
	// 動き
	// エネミーの位置とプレイヤーの位置を取得
	// 一マス移動したマスを取得
	// 上のマスから1マス移動したマスを取得
	// プレイヤーのマスにくるまで繰り返す
	// 
	// 取得したプレイヤーまでのマスの座標を配列に入れる
	//
	nowarrpos = 0;
	startX = transform_.position_.x;
	startZ = transform_.position_.z;
	Player* pPlayer;
	pPlayer = (Player*)FindObject("Player");
	int px = pPlayer->GetVectorX();
	int py = -pPlayer->GetVectorZ();
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	int myx = (int)(XMVectorGetX(pos) + 0.5);
	int myy = (int)(XMVectorGetZ(pos) * -1 + 0.4);
	Transform m;
	int tx, ty, rx, ry;
	
	PursueArr.clear();

	for (int i = 0; i < STAGE_SIZE; i++) {
		for (int j = 0; j < STAGE_SIZE; j++) {
			table[i][j] = -1;
		}
	}

	//自分の位置を0とする
	table[myy][myx] = 0;

	int num = 0;
	//プレイヤーの座標に数字が割り当てられていなければ
	//壁に囲まれたら無限ループとかエラーしそう
	//num > 100は道筋が見つからなかったらという条件のつもり
	//数字を割り当てられなかったらのほうがスマート？
	while (table[py][px] < 0 && num < 100) {
		//tableからnumの値を探す
		for (int y = 0; y < STAGE_SIZE; y++) {
			for (int x = 0; x < STAGE_SIZE; x++) {
				if (table[y][x] == num) {
					//numの値から縦横の座標が未割当かつ壁じゃなかったらnum+1の値を入れる
					if (y + 1 >= 0 && y + 1 < STAGE_SIZE) {//配列の値内か
						if (table[y + 1][x] < 0 && !pStage->IsWall(x,y + 1))
							table[y + 1][x] = num + 1;
					}
					if (y - 1 >= 0 && y - 1 < STAGE_SIZE) {
						if (table[y - 1][x] < 0 && !pStage->IsWall(x, y - 1))
							table[y - 1][x] = num + 1;
					}
					if (x + 1 >= 0 && x + 1 < STAGE_SIZE) {
						if (table[y][x + 1] < 0 && !pStage->IsWall(x + 1, y))
							table[y][x + 1] = num + 1;
					}
					if (x - 1 >= 0 && x - 1 < STAGE_SIZE) {
						if (table[y][x - 1] < 0 && !pStage->IsWall(x - 1, y))
							table[y][x - 1] = num + 1;
					}
				}
			}
		}
		num++;
	}

	//手に入れた道筋を座標にして配列にいれる
	//プレイヤーの位置からさかのぼっていく
	int nownum = table[py][px];
	Vec nowvec;
	nowvec.x = px;
	nowvec.y = py;
	std::vector<Vec> Arr;
	while (nownum > 0 && num < 99) {
		//上下左右の配列内の数字を確認しそれが次の数字(nownum)なら
		if (nowvec.y + 1 >= 0 && nowvec.y + 1 < STAGE_SIZE)//配列内か確認
			if (table[nowvec.y + 1][nowvec.x] == nownum)
				nowvec.y += 1;
		if (nowvec.y - 1 >= 0 && nowvec.y - 1 < STAGE_SIZE)
			if (table[nowvec.y - 1][nowvec.x] == nownum)
				nowvec.y -= 1;
		if (nowvec.x + 1 >= 0 && nowvec.x + 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x + 1] == nownum)
				nowvec.x += 1;
		if (nowvec.x - 1 >= 0 && nowvec.x - 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x - 1] == nownum)
				nowvec.x -= 1;

		Arr.push_back(nowvec);

		nownum--;
	}

	for (int i = Arr.size(); i > 0; i--) {
		PursueArr.push_back(Arr[i - 1]);
	}
	//if (PursueArr.size() != 0) {
	//	//最後にプレイヤーの位置が入ってないのでいれる  改良済みなので不要
	//	Vec v;
	//	v.x = px;
	//	v.y = py;
	//	PursueArr.push_back(v);
	//}
	//nowPursue = 0;

	Arr.clear();

	float x, z;//初期の位置から目的地までの距離
	if (PursueArr.size() != 0) {
		x = PursueArr[0].x - startX;
		z = -PursueArr[0].y - startZ;
		rateX = speed_ / abs(x);
		rateZ = speed_ / abs(z);
	}
}
