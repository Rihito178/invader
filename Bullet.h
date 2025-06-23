#pragma once
#include "GameObject.h"
#include "World.h"

class Bullet :
    public GameObject
{
private:
    int hImage_;//���̉摜
    float x_, y_;//���̍��W
    float speed_;//���̈ړ����x
    //bool isAlive_;//�������邩�ǂ���(�Q�[���I�u�W�F�N�g�Ɉړ�)
    int isize_x, isize_y;//���̕\��
    bool isShot_;//���˂��ꂽ��
    //���˂��ꂽ�Ȃ�false
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
    }// �e�̋�`���擾

};

