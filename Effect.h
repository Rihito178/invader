#pragma 
#include "GameObject.h"
#include "World.h"
#include <vector>

class Effect :
    public GameObject
{
public:
    Effect(Point _pos);
    ~Effect();
    void Update() override;
    void Draw() override;
protected:
private:
    //int hImage_;
    std::vector<int> hImage_;
    Point pos_;
   // float animeTimer_;
    float animeTimer_;//�G�t�F�N�g�̎���
    float frameTimer_;//�A�j���̃R�}�̃^�C�}�[
    int frame_;//�t���[���ԍ�
};
