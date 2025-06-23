#pragma once  
#include "GameObject.h"  
#include <vector>  
#include "Bullet.h"  
#include "Player.h"  

class Player; // �v���C���[�̑O���錾(�|�C���^)  
class Enemy; // �G�̑O���錾(�|�C���^)  

class Stage :  
   public GameObject  
{  
private:  
   Player* player_; // �v���C���[�̃|�C���^  
   std::vector<Enemy*> enemy_; // �G�̃|�C���^  
   int hBackground; // �w�i�̃n���h��  

public:  
   Stage();  
   ~Stage();  
   void Update() override;  
   void Draw() override;  
   Player* GetPlayer() { return player_; }  
};
