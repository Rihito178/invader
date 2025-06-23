#include "Effect.h"
#include <DxLib.h>
#include <string>

namespace 
{
	
	//float Anime_Time = { 3.0f };

	const float Anime_Time = { 1.0f }; //アニメの総時間の初期値
	const int Effect_Image_Size = 48;//画像サイズ
	const std::string EIMG_PATH = "Assets\\explosion.png";
	const int MAX_frame = 9; //画像の分割数
	const int DIV_NUM = 3; //画像の分割数（割り算用）
	const float FRAME_TIME = Anime_Time / MAX_frame; //1コマの時間の初期値
}

//
//FileName　　　:　分割読み込みする画像ファイル文字列のポインタ
//AllNum　　　　 : 画像の分割総数
//XNum, YNum　　 : 画像の横向きに対する分割数と縦に対する分割数
//SizeX, SizeY　 : 分割された画像一つの大きさ
//HandleBuf　　 : 分割読み込みして得たグラフィックハンドルを
//保存するint型の配列へのポインタ

Effect::Effect(Point _pos)
	: GameObject(), pos_({ _pos.x, _pos.y }),
	animeTimer_(Anime_Time), 
	hImage_(std::vector<int>(MAX_frame, -1)),
	frameTimer_(FRAME_TIME), frame_(0)
{
	//hImage_ = LoadGraph(Enemy_Shot.c_str());
	LoadDivGraph
	(EIMG_PATH.c_str(), MAX_frame,
	DIV_NUM, DIV_NUM,
	Effect_Image_Size, Effect_Image_Size, 
	hImage_.data());
	AddGameObject(this);
}

Effect::~Effect()
{
	//DeleteGraph(hImage_);
	for (auto& itr : hImage_)
		DeleteGraph(itr);
	hImage_.clear();
}

void Effect::Update()
{
	float dt = GetDeltaTime();
	animeTimer_ = animeTimer_ - dt;

	if (animeTimer_ < 0)
	{
		this->isAlive_ = false;
	}

	frameTimer_ = frameTimer_ - dt;

	if (frameTimer_ < 0)
	{
		frame_++;//フレームを１増やす
		frameTimer_ = FRAME_TIME - frameTimer_;//リセット
	}
}

void Effect::Draw()
{
	DrawExtendGraphF(pos_.x, pos_.y, 
		pos_.x + Effect_Image_Size, 
		pos_.y + Effect_Image_Size,
		hImage_[frame_], TRUE);
}
