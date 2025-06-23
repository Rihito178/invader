#include "Bullet.h"
#include"DxLib.h"
#include<string>
#include"World.h"

namespace
{
	const int Bullet_Image_Width = 13;//画像の幅
	const int Bullet_Image_Height = 33;//画像の高さ
	const float Bullet_Init_Speed = 200.0f;//弾の初速
	const std::string Bullet_Image_Path = "Assets\\laserBlue03.png";//弾の画像
	//const char* Bullet_Image_Path_CSTR ="Assets\\laserBlue03.png" ;
	//const char* Bullet_Image_Path_CSTR[] = "Assets\\laserBlue03.png";


}

Bullet::Bullet()
	:GameObject(),hImage_(-1),x_(0),y_(0),
	speed_(0), isShot_(false), 
	imageSize_({ Bullet_Image_Width ,Bullet_Image_Height })
	//isAlive_(true),
	//imageSize_.x(Bullet_Image_Width),imageSize_.y(Bullet_Image_Height)
{
	hImage_ = LoadGraph(Bullet_Image_Path.c_str());//読み込み
	speed_ = Bullet_Init_Speed;//移動速度
	//isAlive_ = true;
	AddGameObject(this);

}

Bullet::Bullet(float x, float y)
	:GameObject(), hImage_(-1), x_(x), y_(y), speed_(0),isShot_(false),
	imageSize_({ Bullet_Image_Width ,Bullet_Image_Height })
	//isize_x(Bullet_Image_Width), isize_y(Bullet_Image_Height)
{


	hImage_ = LoadGraph(Bullet_Image_Path.c_str());//読み込み
	speed_ = Bullet_Init_Speed;//移動速度
	//isAlive_=true;
	AddGameObject(this);

}

Bullet::~Bullet()
{
	if (hImage_!=-1)
	{
		DeleteGraph(hImage_);//画像の開放
	}
	hImage_ = -1;

}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	y_ = y_ - speed_ * dt;//弾をまっすぐ飛ばす
	if (y_ < 0) //0(画面端)より大きくなったら弾を消す
	{
		//isAlive_ = false;
		isShot_ = false;//画面外に出たら準備
	}

}

void Bullet::Draw()
{
	//if (isAlive_) //弾が残っていたら
	if(isShot_)//発射されたら描画
	{
		DrawExtendGraphF//Fはフロート
		(x_, y_,
		x_ + imageSize_.x,
		y_ + imageSize_.y,
		hImage_, TRUE);

	
	}

}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;

}
