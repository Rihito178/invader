#pragma once
#include "GameObject.h"
#include "World.h"

class Bullet :
    public GameObject
{
private:
    int hImage_;//球の画像
    float x_, y_;//球の座標
    float speed_;//球の移動速度
    //bool isAlive_;//球があるかどうか(ゲームオブジェクトに移動)
    int isize_x, isize_y;//球の表示
    bool isShot_;//発射されたか
    //発射されたならfalse
    Point imageSize_;

public:
    Bullet();
    Bullet(float x, float y);
    ~Bullet();
    void Update()override;
    void Draw()override;
    void SetPos(float x, float y);
    void SetShot(bool Shot) { isShot_ = Shot; }
    bool IsShot() const { return isShot_; }
    Rect GetRect() const 
    {  
        return { x_, y_, imageSize_.x,imageSize_.y }; 
    }// 弾の矩形を取得

};

