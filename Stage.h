#pragma once  
#include "GameObject.h"  
#include <vector>  
#include "Bullet.h"  
#include "Player.h"  

class Player; // プレイヤーの前方宣言(ポインタ)  
class Enemy; // 敵の前方宣言(ポインタ)  

class Stage :  
   public GameObject  
{  
private:  
   Player* player_; // プレイヤーのポインタ  
   std::vector<Enemy*> enemy_; // 敵のポインタ  
   int hBackground; // 背景のハンドル  

public:  
   Stage();  
   ~Stage();  
   void Update() override;  
   void Draw() override;  
   Player* GetPlayer() { return player_; }  
};
