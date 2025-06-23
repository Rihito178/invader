#include "Player.h"
#include "DxLib.h"
#include"World.h"
#include "Input.h"
#include"Bullet.h"
#include"Effect.h"


namespace 
{
	const int Player_Init_Speed = 200.0f;//�v���C���[�̏����ړ����x
	const int Player_IMAGE_W = 48;//�v���C���[�̏����摜ID
	const int Player_IMAGE_H = 48;//�v���C���[�̏����摜ID
	const int Player_Base_Margin = 32;//�v���C���[�̏����ʒuX���W

	const int Player_Init_X = WIN_WIDTH / 2 - Player_IMAGE_W / 2;//�v���C���[�̏����ʒuX���W���v�Z�����ꏊ
	const int Player_Init_Y = WIN_HEIGHT - Player_IMAGE_H - Player_Base_Margin;//�v���C���[�̏����ʒuY���W���v�Z�����ꏊ

	const int BULLET_IMAGE_MARGIN = 17;//�e�̉摜
	const float  Bullet_Interval=0.5f;//�ˌ��Ԋu
	const int Player_Bullet_Num = 5;//�����ɔ��˂ł���e
}	




Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), 
	speed_(0), imageSize_({ Player_IMAGE_W ,Player_IMAGE_H })//���W�E�X�s�[�h��������
{
	//�v���C���[�̉摜��ǂݍ���
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");//�v���C���[�摜�̓ǂݍ���
	if (hImage_ == -1)
	{
		//�摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̏���
		//�G���[���b�Z�[�W��\������
	}

	//�����l��0�łȂ��\��������̂ŁA���������s��
	x_ = Player_Init_X;   // �����ʒuX���W
	y_ = Player_Init_Y;   // �����ʒuY���W
	speed_ = Player_Init_Speed; // �ړ����x

	for (int i = 0;i < Player_Bullet_Num;i++)
	{
		bullets_.push_back(new Bullet());//�e��������(Vector)
	}
	AddGameObject(this);//�Q�[���I�u�W�F�N�g�ɒǉ�����

}

Player::~Player()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // �摜�̃n���h�������
	}
}


void Player::Update()
{
	Point nextP = { x_, y_ };
	float dt = GetDeltaTime();//�t���[���Ԃ̎��ԍ����擾
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		//x_ -=   speed_ * GetDeltaTime();//���Ɉړ�
		//x_ = x_ - speed_ * dt;//���Ɉړ�
		nextP.x = x_ - speed_ * dt; // ���Ɉړ�
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) 
	{
		//x_ += speed_ * GetDeltaTime();//�E�Ɉړ�
		//x_ = x_ + speed_ * dt;//�E�Ɉړ�
		nextP.x = x_ + speed_ * dt; // �E�Ɉړ�
	}
	//static float bulletTimer = 0.0f;//�e�ۂ̎ˌ��Ԋu
	if (nextP.x >= 0 && (nextP.x + Player_IMAGE_W) <= WIN_WIDTH)
	{
		x_ = nextP.x;
		y_ = nextP.y;
	}


	static float bulletTimer = 0.0f; // �e�̔��˃^�C�}�[
	if (bulletTimer > 0.0f)
	{
		bulletTimer -= dt;//�ł�����^�C�}�[�����炷(�����ɑłĂȂ��悤�ɂ���)
	}

	//�X�y�[�X���������玩�@�̈ʒu����e���o��
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		if (bulletTimer <= 0.0f) 
		{
			Shoot();
			//new Bullet(x_ + BULLET_IMAGE_MARGIN, y_);//���@��������e���o��
			bulletTimer = Bullet_Interval;//�e�̎ˌ��Ԋu
		}
	}

}

void Player::Draw()
{
	DrawExtendGraphF(x_, y_, x_ + Player_IMAGE_W,
					y_ + Player_IMAGE_H,hImage_, TRUE);
	//64�̓v���C���[�̉摜�̃T�C�Y
}

void Player::Shoot()
{
	Bullet* blt = GetActiveBullet();
	if (blt != nullptr) {
		blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // �e�̈ʒu��ݒ�
		blt->SetShot(true); // ���ˏ�Ԃɂ���
	}


	//for (auto& itr : bullets_)
	//{
	//	if (itr->IsShot() == false)//�e�����˂���Ă��Ȃ��Ȃ�
	//	{
	//		itr->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);//���@��������e���o��
	//		itr->SetShot(true);//�e�𔭎ˏ�Ԃɂ���
	//		break;//1�������˂���
	//	}
	//}
	//Bullet* blt = GetActiveBullet();
	//if(blt != nullptr)
	//{
	//	blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);//���@��������e���o��
	//	blt->SetShot(true);//�e�𔭎ˏ�Ԃɂ���
	//}

}


Bullet* Player::GetActiveBullet()
{

	for (auto& itr : bullets_)
	{
		if (!itr->IsShot())//�e�����˂���Ă��Ȃ��Ȃ�
		{
			return itr;//�e��Ԃ�
		}
	}
	return nullptr; // ���˂���Ă��Ȃ��e���Ȃ��ꍇ��nullptr��Ԃ�
}