#include "Enemy.h"
#include "Engine\Model.h"
#include "Stage.h"
#include "Player.h"
#include "Engine\Input.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), speed_(0), pStage(nullptr)
{
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
}

void Enemy::Update()
{
	if (Frame <= 0) {
		Pursue();
		Frame = 100;
	}
	else
		Frame--;

	//上の関数でだしたプレイヤーの位置までの道のりを辿る
	//まずPursueArrのどの位置にいるかを調べる
	// そこから次に向かう座標を求める
	// 移動
	//
	
	int nowpos = 0;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	int myx = (int)(XMVectorGetX(pos) - 0.5);
	int myy = (int)(XMVectorGetZ(pos) * -1 + 0.4);
	for (int i = 0; i < PursueArr.size(); i++) {
		if (myx == PursueArr[i].x && myy == PursueArr[i].y) {
			nowpos = i;
			break;
		}
	}

	XMVECTOR move{ 0,0,0,0 };
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
		}

	pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);
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
	// 
	// 反省
	// int型に変換するせいで実際の位置と行きたい場所で誤差が生じている
	// 四隅の座標でおこなっていないので壁との当たり判定が機能していない
	//
	Player* pPlayer;
	pPlayer = (Player*)FindObject("Player");
	int px = pPlayer->GetVectorX();
	int py = pPlayer->GetVectorY();
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

	//自分の位置を０とする
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
		if (nowvec.y + 1 >= 0 && nowvec.y + 1 < STAGE_SIZE)
			if (table[nowvec.y + 1][nowvec.x] == nownum - 1)
				nowvec.y += 1;
		if (nowvec.y - 1 >= 0 && nowvec.y - 1 < STAGE_SIZE)
			if (table[nowvec.y - 1][nowvec.x] == nownum - 1)
				nowvec.y -= 1;
		if (nowvec.x + 1 >= 0 && nowvec.x + 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x + 1] == nownum - 1)
				nowvec.x += 1;
		if (nowvec.x - 1 >= 0 && nowvec.x - 1 < STAGE_SIZE)
			if (table[nowvec.y][nowvec.x - 1] == nownum - 1)
				nowvec.x -= 1;

		Arr.push_back(nowvec);

		nownum--;
	}

	for (int i = Arr.size(); i > 0; i--) {
		PursueArr.push_back(Arr[i - 1]);
	}
	nowPursue = 0;

	Arr.clear();
	
}
