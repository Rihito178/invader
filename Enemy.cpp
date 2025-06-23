#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include<assert.h>
#include "EnemyBeam.h"
#include"Effect.h"

namespace
{
	
	const int Enemy_IMAGE_W = 48;//�G�̏����摜ID
	const int Enemy_IMAGE_H = 48;//�G�̏����摜ID

	
	const float Enemy_Init_X = 100;//�����ʒuX���W
	const float Enemy_Init_Y = 100;//�����ʒuY���W
	const float Enemy_Init_Speed = 100.0f;//�G�̏����ړ����x

}






Enemy::Enemy()
	:GameObject(), 
	hImage_(-1),
	x_(0),y_(0),
	speed_(0),
	imageSize_({ Enemy_IMAGE_W ,Enemy_IMAGE_H})
	//isAlive_(true)//���W�E�X�s�[�h��������
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png");//�G�̉摜��ǂݍ���
	if (hImage_ == -1)
	{
		assert(false);//�摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̏���
		//�G���[���b�Z�[�W��\������
	}

	x_ = Enemy_Init_X;   // �����ʒuX���W
	y_ = Enemy_Init_Y;   // �����ʒuY���W
	speed_ = Enemy_Init_Speed; // �ړ����x
	AddGameObject(this);

}

Enemy::Enemy(int id, ETYPE type)
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	speed_(0),
	//isAlive_(true),//���W�E�X�s�[�h��������
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
		hImage_ = LoadGraph(imagePath[type_].c_str());//�G�̉摜��ǂݍ���
		if (hImage_ == -1)
		{
			//�摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̏���
			//�G���[���b�Z�[�W��\������
		}

		x_ = Enemy_Init_X;   // �����ʒuX���W
		y_ = Enemy_Init_Y;   // �����ʒuY���W
		speed_ = Enemy_Init_Speed; // �ړ����x
		AddGameObject(this);

}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
		if (hImage_ != -1)
		{
			DeleteGraph(hImage_); // �摜�̃n���h�������
		}
}

void Enemy::Update()
{

	static float beamTimer = 3.0f; // �e�̔��˃^�C�}�[
	float period = 10.0f; // 1�����ɂ����鎞�ԁi�b�j
	float omega = 2.0f * 3.14159265f / period; // �p���x �� = 2�� / T
	moveTime = moveTime + GetDeltaTime();
	x_ = xorigin + xMoveMax / 2.0 
	* sinf(omega * moveTime);
	y_ = y_;

	if (beamTimer < 0)
	{
		// �e�𔭎�
		new EnemyBeam(x_ + Enemy_IMAGE_W / 2, y_ + Enemy_IMAGE_H); // �G�̒e�𐶐�
		beamTimer = 3.0f; // �^�C�}�[�����Z�b�g
	}

	beamTimer -= GetDeltaTime(); // �^�C�}�[������
}

void Enemy::Draw()
{
	//if (isAlive_)
	//{
		//��ʍ���ɕ`��
		//DrawGraph(x_, y_, hImage_, TRUE);//�G�̉摜��`��
		DrawExtendGraphF(x_, y_, 
			x_ + Enemy_IMAGE_W,
			y_ + Enemy_IMAGE_H,
			hImage_, TRUE);
	//}
}
