#include "DxLib.h"
//#include "Player.h"//Stageに移行済み
//#include"Enemy.h"//Stageに移行済み
#include "World.h"
#include "Input.h"
#include <vector>
#include "Stage.h"



namespace 
{
	const int BGCOLOR[3] = { 0, 0, 0 };//背景色
	int crrTime;//前の時間
	int prevTime;//経過時間
}

enum Screen 
{
	SCREEN_TITLE,
	SCREEN_GAME,
	SCREEN_GAMEOVER
};



Screen currentScreen = SCREEN_TITLE;

std::vector<GameObject*> gameObjects;//ゲームオブジェクトのVector
std::vector<GameObject*>newObjects;//ゲームオブジェクト

float gDeltaTime = 0.0f;//時間の初期化・このファイル内でのみ使えるグローバル変数

//部分部分で作ったものをまとめるだけで一つのゲームができる
//シンプルなものを考える

void DxInit()
{
	ChangeWindowMode(true);//// ウィンドウモードにする
	SetWindowSizeChangeEnableFlag(false, false);//// ウィンドウサイズ変更を無効にする
	SetMainWindowText("TITLE");// ウィンドウのタイトルを設定する
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);// ウィンドウのサイズを設定する
	SetWindowSizeExtendRate(1.0);// ウィンドウの背景色を設定する
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);//定義した背景色を表示

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();//前の時間を取得
	prevTime = GetNowCount();//経過時間を取得

	/*
	const int Enemy_Num = 10;//敵の数

	Player* player = new Player();
	
	Enemy* enemy = new Enemy();
	
	Enemy* enemy = new Enemy[Enemy_Num];//敵を10体作成
	for (int i = 0;i < Enemy_Num;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//敵の座標を設定
	}

	std::vector<Enemy> enemy(Enemy_Num);//敵を10体作成
	for (int i = 0;i < Enemy_Num;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//敵の座標を設定
	}

	int i = 0;
	for (auto& e : enemy)//敵を10体作成
	{
		e.SetPos(100 + i * 50, 100);//敵の座標を設定
		i++;
	}


	Enemy* enemy = new Enemy[10];
	for (int i = 0;i < 10;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//敵の座標を設定
	}

	GameApp game = new GameApp();//ゲームのシステム
	*/
	
	
	//Stage* stage = new Stage();//ステージのインスタンスを生成
	Stage* stage = nullptr;


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();//キーの状態を更新する


		crrTime = GetNowCount();//前回の時間との差を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f;//秒単位に変換する
		gDeltaTime = deltaTime;//グローバル変数に保存する
		
		//ここに処理を描く

		switch (currentScreen)
		{
		case SCREEN_TITLE:
			DrawFormatString
			(100, 100, GetColor(255, 255, 255), "タイトル画面 - Zキーで開始");
			
			if (Input::IsKeyDown(KEY_INPUT_Z)) 
			{
				currentScreen = SCREEN_GAME;
				stage = new Stage();
			}
			break;

		case SCREEN_GAME:

			if (newObjects.size() > 0)
			{
				for (auto& obj : newObjects)
				{
					gameObjects.push_back(obj);
				}
				newObjects.clear();//新しいゲームオブジェクトをクリア

			}

			//ゲームオブジェクトの更新
			for (auto& obj : gameObjects)
			{
				obj->Update();
			}

			//ゲームオブジェクトの描画
			for (auto& obj : gameObjects)
			{
				obj->Draw();
			}

			for (auto it = gameObjects.begin();it != gameObjects.end();)
			{
				if (!(*it)->IsAlive())
				{
					delete* it;
					it = gameObjects.erase(it);//

				}
				else
				{
					++it;//次へ
				}

			}

			// プレイヤー死亡時の画面遷移（stage から player を取得する前提）
			if (stage && !stage->GetPlayer()->IsAlive())
			{
				currentScreen = SCREEN_GAMEOVER;
			}
			break;

		case SCREEN_GAMEOVER:

			DrawFormatString
			(100, 100, GetColor(255, 0, 0), "ゲームオーバー - Rキーでタイトルへ");
			
			if (Input::IsKeyDown(KEY_INPUT_R)) 
			{
				currentScreen = SCREEN_TITLE;
				for (auto& obj : gameObjects) delete obj;
				gameObjects.clear();
				if (stage) 
				{
					delete stage;
					stage = nullptr;
				}
			}
			break;
		}


	
		


		/*
		//if (newObjects.size() > 0)
		//{
		//	for (auto& obj : newObjects)
		//	{
		//		gameObjects.push_back(obj);
		//	}
		//	newObjects.clear();//新しいゲームオブジェクトをクリア

		//}

		//for (auto& obj : gameObjects)
		//{
		//	obj->Update();
		//}
		//for (auto& obj : gameObjects)
		//{
		//	obj->Draw();
		//}



		//stage->Update();//ステージの更新
		//stage->Draw();//ステージの描画


		
		
		player->Update();
		player->Draw();
		for (auto& elm : enemy)//敵を10体作成
		{
			elm.Update();
			elm.Draw();
		}



		enemy->Update();
		enemy->Draw();

		場所をずらして描画する

		for (int i = 0;i < 10;i++)//enemyを10体作成
		{
			(enemy + i)->Update();
			(enemy + i)->Draw();
		}

		*/
		
		//裏画面の描画
		ScreenFlip();
		WaitTimer(16);
		prevTime = crrTime;//現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}