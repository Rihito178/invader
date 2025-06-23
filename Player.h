#pragma once
#include "GameObject.h"
#include "World.h"

class Bullet;//余計なincludeを減らせる

class Player :
    public GameObject
{
	//メンバー変数とわかるように_をつける
	int hImage_;//プレイヤーの画像
	float x_, y_;//プレイヤーの座標
	float speed_;//プレイヤーの移動速度
	std::vector<Bullet *>bullets_;
	Bullet* GetActiveBullet();//アクティブな弾を取得する
	Point imageSize_;
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Shoot();
	Rect GetRect() const { return { x_, y_, imageSize_.x,imageSize_.y }; } // プレイヤーの矩形を取得
	std::vector<Bullet*> GetAllBullets() const { return bullets_; } // 全ての弾を取得
};
