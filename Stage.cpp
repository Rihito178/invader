#include "Stage.h"//宣言の中身が必要なためインクルード
#include "Player.h"//宣言の中身が必要なためインクルード
#include "Enemy.h"//宣言の中身が必要なためインクルード
#include"Bullet.h"
#include <Dxlib.h>
#include"EnemyBeam.h"

namespace
{
	const int Enemy_Num = 10*7;//敵の数
	const int Enemy_Col_Size = 10;//敵の列数
	const int Enemy_Row_Size = 7;//敵の行数

	const float Enemy_Alingn_x = 55.0f; //敵を並べる幅
	const float Enemy_Alingn_y = 50.0f; //敵を並べる高さ
	const int ENEMY_LEFT_MARGIN = (WIN_WIDTH - (Enemy_Alingn_x * Enemy_Col_Size)) / 2;
	const int ENEMY_TOP_MARGIN = 75;


    bool IntersectRect(const Rect _a, const Rect _b)  
    {  
       bool xOverlap = (_a.x < _b.x + _b.width) && (_b.x < _a.x + _a.width);  
       bool yOverlap = (_a.y < _b.y + _b.height) && (_b.y < _a.y + _a.height);  
       return xOverlap && yOverlap;  
    }

}

//　敵の列を作るために
//　案1	敵の初期座標を設定しているSetPosをクラスにして列にする
// 　



Stage::Stage()
	:GameObject(), player_(nullptr), hBackground(-1)
{
	AddGameObject(this);
	player_ = new Player();//プレイヤーのインスタンスを生成

	enemy_ = std::vector<Enemy*>(Enemy_Num);
	for (int i = 0; i < Enemy_Num; i++)//横
	{
		//先生方式
		int col = i % Enemy_Col_Size;
		int row = i / Enemy_Col_Size;
		ETYPE enemyType[Enemy_Row_Size] = { BOSS,KNGHT,MID,ZAKO,ZAKO,ZAKO };

		enemy_[i] = new Enemy(i,enemyType[row]);//新たな敵の作成
		//enemy_[i]->SetPos(col * 55.0f, row * 50.0f);//敵の初期位置

		enemy_[i]->SetMaxMoveX(ENEMY_LEFT_MARGIN);
		enemy_[i]->SetPos(col * Enemy_Alingn_x + ENEMY_LEFT_MARGIN,
			row * Enemy_Alingn_y + ENEMY_TOP_MARGIN); // 敵の初期位置を設定
		enemy_[i]->SetXorigin(col * Enemy_Alingn_x + ENEMY_LEFT_MARGIN);
		//for (int j = 0; j < Enemy_Num; j++)//縦
		//{
		//	enemy_[i * Enemy_Col_Size * j] = new Enemy();
		//	enemy_[i * Enemy_Col_Size + j]->SetPos(100 + j * 50,100+i*50); // 列に基づくX座標設定
		//	// 敵のY座標を設定
		//	enemy_[i * Enemy_Col_Size + j]->SetID(i *Enemy_Col_Size*j); // 行に基づくY座標設定
		//}

	}
		//{
		//	enemy_[i * Enemy_Col_Size * j] = new Enemy(i,(ETYPE)(i % MAX_ETYPE));//敵のインスタンスを生成
		//	
		//	enemy_[i]->SetPos(i % Enemy_Col_Size * 55, i / Enemy_Col_Size * 50);
		//	
		//	
		//	//enemy_[i * Enemy_Col_Size * j]->SetPos(100 + i * 50, 100);
		//	//enemy_[i * Enemy_Col_Size * j]->SetPos(100 + j * 50, 100);

	hBackground = LoadGraph("Assets\\bg.png");//背景

	//	//enemy_[i]->SetPos(100 + i * 50, 100);//敵の初期座標を設定
		//	//enemy_[j]->SetPos(100 + j * 50, 100);//敵の初期座標を設定
		//}
		
		
}

	
	


Stage::~Stage()
{

}

void Stage::Update()
{	
	// EnemyBeamとの当たり判定処理
	std::vector<GameObject*> objects = gameObjects; // すべてのGameObjectを取得
	for (auto& obj : objects)
	{
		EnemyBeam* beam = dynamic_cast<EnemyBeam*>(obj);
		if (beam && beam->IsFired() && player_->IsAlive())
		{
			if (IntersectRect(player_->GetRect(), beam->GetRect()))
			{
				beam->SetFired(false);		// ビームを無効化
				beam->SetAlive(false);		// ビームを削除対象に
				player_->SetAlive(false);// プレイヤーを倒す（またはライフを減らす）
				// 必要に応じてエフェクトやサウンドを追加
			}
		}
	}

	std::vector<Bullet*>bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for (auto& b : bullets)
		{
			if (b->IsShot() && e->IsAlive())
			{
				if (IntersectRect(e->GetRect(), b->GetRect()))
				{
					if (b->IsShot())
						b->SetShot(false);
					if (e->IsAlive())
						e->SetAlive(false);

				}
			}
		}
	}

}

void Stage::Draw()//背景
{
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
