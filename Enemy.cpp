#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include<assert.h>
#include "EnemyBeam.h"
#include"Effect.h"

namespace
{
	
	const int Enemy_IMAGE_W = 48;//敵の初期画像ID
	const int Enemy_IMAGE_H = 48;//敵の初期画像ID

	
	const float Enemy_Init_X = 100;//初期位置X座標
	const float Enemy_Init_Y = 100;//初期位置Y座標
	const float Enemy_Init_Speed = 100.0f;//敵の初期移動速度

}






Enemy::Enemy()
	:GameObject(), 
	hImage_(-1),
	x_(0),y_(0),
	speed_(0),
	imageSize_({ Enemy_IMAGE_W ,Enemy_IMAGE_H})
	//isAlive_(true)//座標・スピードを初期化
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png");//敵の画像を読み込む
	if (hImage_ == -1)
	{
		assert(false);//画像の読み込みに失敗した場合の処理
		//エラーメッセージを表示する
	}

	x_ = Enemy_Init_X;   // 初期位置X座標
	y_ = Enemy_Init_Y;   // 初期位置Y座標
	speed_ = Enemy_Init_Speed; // 移動速度
	AddGameObject(this);

}

Enemy::Enemy(int id, ETYPE type)
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	speed_(0),
	//isAlive_(true),//座標・スピードを初期化
	ID_(id),type_(type),
	imageSize_({ Enemy_IMAGE_W ,Enemy_IMAGE_H })
{
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets\\tiny_ship10.png",
		"Assets\\tiny_ship18.png",
		"Assets\\tiny_ship16.png",
		"Assets\\tiny_ship9.png",
	};
		moveTime = 0.0f;
		hImage_ = LoadGraph(imagePath[type_].c_str());//敵の画像を読み込む
		if (hImage_ == -1)
		{
			//画像の読み込みに失敗した場合の処理
			//エラーメッセージを表示する
		}

		x_ = Enemy_Init_X;   // 初期位置X座標
		y_ = Enemy_Init_Y;   // 初期位置Y座標
		speed_ = Enemy_Init_Speed; // 移動速度
		AddGameObject(this);

}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
		if (hImage_ != -1)
		{
			DeleteGraph(hImage_); // 画像のハンドルを解放
		}
}

void Enemy::Update()
{

	static float beamTimer = 3.0f; // 弾の発射タイマー
	float period = 10.0f; // 1往復にかける時間（秒）
	float omega = 2.0f * 3.14159265f / period; // 角速度 ω = 2π / T
	moveTime = moveTime + GetDeltaTime();
	x_ = xorigin + xMoveMax / 2.0 
	* sinf(omega * moveTime);
	y_ = y_;

	if (beamTimer < 0)
	{
		// 弾を発射
		new EnemyBeam(x_ + Enemy_IMAGE_W / 2, y_ + Enemy_IMAGE_H); // 敵の弾を生成
		beamTimer = 3.0f; // タイマーをリセット
	}

	beamTimer -= GetDeltaTime(); // タイマーを減少
}

void Enemy::Draw()
{
	//if (isAlive_)
	//{
		//画面左上に描画
		//DrawGraph(x_, y_, hImage_, TRUE);//敵の画像を描画
		DrawExtendGraphF(x_, y_, 
			x_ + Enemy_IMAGE_W,
			y_ + Enemy_IMAGE_H,
			hImage_, TRUE);
	//}
}
