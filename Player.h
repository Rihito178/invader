#pragma once
#include "GameObject.h"
#include "World.h"

class Bullet;//�]�v��include�����点��

class Player :
    public GameObject
{
	//�����o�[�ϐ��Ƃ킩��悤��_������
	int hImage_;//�v���C���[�̉摜
	float x_, y_;//�v���C���[�̍��W
	float speed_;//�v���C���[�̈ړ����x
	std::vector<Bullet *>bullets_;
	Bullet* GetActiveBullet();//�A�N�e�B�u�Ȓe���擾����
	Point imageSize_;
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Shoot();
	Rect GetRect() const { return { x_, y_, imageSize_.x,imageSize_.y }; } // �v���C���[�̋�`���擾
	std::vector<Bullet*> GetAllBullets() const { return bullets_; } // �S�Ă̒e���擾
};
