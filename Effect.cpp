#include "Effect.h"
#include <DxLib.h>
#include <string>

namespace 
{
	
	//float Anime_Time = { 3.0f };

	const float Anime_Time = { 1.0f }; //�A�j���̑����Ԃ̏����l
	const int Effect_Image_Size = 48;//�摜�T�C�Y
	const std::string EIMG_PATH = "Assets\\explosion.png";
	const int MAX_frame = 9; //�摜�̕�����
	const int DIV_NUM = 3; //�摜�̕������i����Z�p�j
	const float FRAME_TIME = Anime_Time / MAX_frame; //1�R�}�̎��Ԃ̏����l
}

//
//FileName�@�@�@:�@�����ǂݍ��݂���摜�t�@�C��������̃|�C���^
//AllNum�@�@�@�@ : �摜�̕�������
//XNum, YNum�@�@ : �摜�̉������ɑ΂��镪�����Əc�ɑ΂��镪����
//SizeX, SizeY�@ : �������ꂽ�摜��̑傫��
//HandleBuf�@�@ : �����ǂݍ��݂��ē����O���t�B�b�N�n���h����
//�ۑ�����int�^�̔z��ւ̃|�C���^

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
		frame_++;//�t���[�����P���₷
		frameTimer_ = FRAME_TIME - frameTimer_;//���Z�b�g
	}
}

void Effect::Draw()
{
	DrawExtendGraphF(pos_.x, pos_.y, 
		pos_.x + Effect_Image_Size, 
		pos_.y + Effect_Image_Size,
		hImage_[frame_], TRUE);
}
