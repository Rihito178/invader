#pragma once
#include "GameObject.h"
#include "World.h"

enum ETYPE
{
	ZAKO,MID,KNGHT,BOSS,MAX_ETYPE
};

class Enemy :
    public GameObject
{


public:
	
	Enemy(int id,ETYPE type);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	
	void SetPos(float x, float y) 
	{ x_ = x;y_ = y; }//�G�̍��W��ݒ�
	
	//void SetID(int id) { ID_ = id; }//ID��ݒ�

	Rect GetRect() const 
	{ 
		return { x_, y_, imageSize_.x, imageSize_.y }; 
	} // �G�̋�`���擾	
	void SetMaxMoveX(float xmax) { xMoveMax = xmax; }
	void SetXorigin(float x) { xorigin = x; }
	
protected:
private:
	int hImage_;  //�G�̉摜�n���h��
	float x_, y_; //�G�̍��W
	float speed_; //�G�̈ړ����x
	Point imageSize_;

	int ID_; //�G��ID
	ETYPE type_; //�G�̎��

	float xMoveMax;//�������̈ړ��ő�lAdd commentMore actions
	float xorigin;//�X�^�[�g�n�_
	float moveTime;
	
};

