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
	{ x_ = x;y_ = y; }//敵の座標を設定
	
	//void SetID(int id) { ID_ = id; }//IDを設定

	Rect GetRect() const 
	{ 
		return { x_, y_, imageSize_.x, imageSize_.y }; 
	} // 敵の矩形を取得	
	void SetMaxMoveX(float xmax) { xMoveMax = xmax; }
	void SetXorigin(float x) { xorigin = x; }
	
protected:
private:
	int hImage_;  //敵の画像ハンドル
	float x_, y_; //敵の座標
	float speed_; //敵の移動速度
	Point imageSize_;

	int ID_; //敵のID
	ETYPE type_; //敵の種類

	float xMoveMax;//横方向の移動最大値Add commentMore actions
	float xorigin;//スタート地点
	float moveTime;
	
};

