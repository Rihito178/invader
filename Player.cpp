#include "Player.h"
#include "DxLib.h"
#include"World.h"
#include "Input.h"
#include"Bullet.h"
#include"Effect.h"


namespace 
{
	const int Player_Init_Speed = 200.0f;//プレイヤーの初期移動速度
	const int Player_IMAGE_W = 48;//プレイヤーの初期画像ID
	const int Player_IMAGE_H = 48;//プレイヤーの初期画像ID
	const int Player_Base_Margin = 32;//プレイヤーの初期位置X座標

	const int Player_Init_X = WIN_WIDTH / 2 - Player_IMAGE_W / 2;//プレイヤーの初期位置X座標を計算した場所
	const int Player_Init_Y = WIN_HEIGHT - Player_IMAGE_H - Player_Base_Margin;//プレイヤーの初期位置Y座標を計算した場所

	const int BULLET_IMAGE_MARGIN = 17;//弾の画像
	const float  Bullet_Interval=0.5f;//射撃間隔
	const int Player_Bullet_Num = 5;//同時に発射できる弾
}	




Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), 
	speed_(0), imageSize_({ Player_IMAGE_W ,Player_IMAGE_H })//座標・スピードを初期化
{
	//プレイヤーの画像を読み込む
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");//プレイヤー画像の読み込み
	if (hImage_ == -1)
	{
		//画像の読み込みに失敗した場合の処理
		//エラーメッセージを表示する
	}

	//初期値が0でない可能性があるので、初期化を行う
	x_ = Player_Init_X;   // 初期位置X座標
	y_ = Player_Init_Y;   // 初期位置Y座標
	speed_ = Player_Init_Speed; // 移動速度

	for (int i = 0;i < Player_Bullet_Num;i++)
	{
		bullets_.push_back(new Bullet());//弾を初期化(Vector)
	}
	AddGameObject(this);//ゲームオブジェクトに追加する

}

Player::~Player()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // 画像のハンドルを解放
	}
}


void Player::Update()
{
	Point nextP = { x_, y_ };
	float dt = GetDeltaTime();//フレーム間の時間差を取得
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		//x_ -=   speed_ * GetDeltaTime();//左に移動
		//x_ = x_ - speed_ * dt;//左に移動
		nextP.x = x_ - speed_ * dt; // 左に移動
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) 
	{
		//x_ += speed_ * GetDeltaTime();//右に移動
		//x_ = x_ + speed_ * dt;//右に移動
		nextP.x = x_ + speed_ * dt; // 右に移動
	}
	//static float bulletTimer = 0.0f;//弾丸の射撃間隔
	if (nextP.x >= 0 && (nextP.x + Player_IMAGE_W) <= WIN_WIDTH)
	{
		x_ = nextP.x;
		y_ = nextP.y;
	}


	static float bulletTimer = 0.0f; // 弾の発射タイマー
	if (bulletTimer > 0.0f)
	{
		bulletTimer -= dt;//打ったらタイマーを減らす(すぐに打てないようにする)
	}

	//スペースを押したら自機の位置から弾が出る
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		if (bulletTimer <= 0.0f) 
		{
			Shoot();
			//new Bullet(x_ + BULLET_IMAGE_MARGIN, y_);//自機中央から弾が出る
			bulletTimer = Bullet_Interval;//弾の射撃間隔
		}
	}

}

void Player::Draw()
{
	DrawExtendGraphF(x_, y_, x_ + Player_IMAGE_W,
					y_ + Player_IMAGE_H,hImage_, TRUE);
	//64はプレイヤーの画像のサイズ
}

void Player::Shoot()
{
	Bullet* blt = GetActiveBullet();
	if (blt != nullptr) {
		blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // 弾の位置を設定
		blt->SetShot(true); // 発射状態にする
	}


	//for (auto& itr : bullets_)
	//{
	//	if (itr->IsShot() == false)//弾が発射されていないなら
	//	{
	//		itr->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);//自機中央から弾が出る
	//		itr->SetShot(true);//弾を発射状態にする
	//		break;//1つだけ発射する
	//	}
	//}
	//Bullet* blt = GetActiveBullet();
	//if(blt != nullptr)
	//{
	//	blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);//自機中央から弾が出る
	//	blt->SetShot(true);//弾を発射状態にする
	//}

}


Bullet* Player::GetActiveBullet()
{

	for (auto& itr : bullets_)
	{
		if (!itr->IsShot())//弾が発射されていないなら
		{
			return itr;//弾を返す
		}
	}
	return nullptr; // 発射されていない弾がない場合はnullptrを返す
}