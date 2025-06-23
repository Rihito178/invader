#include "DxLib.h"
//#include "Player.h"//Stage�Ɉڍs�ς�
//#include"Enemy.h"//Stage�Ɉڍs�ς�
#include "World.h"
#include "Input.h"
#include <vector>
#include "Stage.h"



namespace 
{
	const int BGCOLOR[3] = { 0, 0, 0 };//�w�i�F
	int crrTime;//�O�̎���
	int prevTime;//�o�ߎ���
}

enum Screen 
{
	SCREEN_TITLE,
	SCREEN_GAME,
	SCREEN_GAMEOVER
};



Screen currentScreen = SCREEN_TITLE;

std::vector<GameObject*> gameObjects;//�Q�[���I�u�W�F�N�g��Vector
std::vector<GameObject*>newObjects;//�Q�[���I�u�W�F�N�g

float gDeltaTime = 0.0f;//���Ԃ̏������E���̃t�@�C�����ł̂ݎg����O���[�o���ϐ�

//���������ō�������̂��܂Ƃ߂邾���ň�̃Q�[�����ł���
//�V���v���Ȃ��̂��l����

void DxInit()
{
	ChangeWindowMode(true);//// �E�B���h�E���[�h�ɂ���
	SetWindowSizeChangeEnableFlag(false, false);//// �E�B���h�E�T�C�Y�ύX�𖳌��ɂ���
	SetMainWindowText("TITLE");// �E�B���h�E�̃^�C�g����ݒ肷��
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);// �E�B���h�E�̃T�C�Y��ݒ肷��
	SetWindowSizeExtendRate(1.0);// �E�B���h�E�̔w�i�F��ݒ肷��
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);//��`�����w�i�F��\��

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "�E�B���h�E�̃e�X�g");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();//�O�̎��Ԃ��擾
	prevTime = GetNowCount();//�o�ߎ��Ԃ��擾

	/*
	const int Enemy_Num = 10;//�G�̐�

	Player* player = new Player();
	
	Enemy* enemy = new Enemy();
	
	Enemy* enemy = new Enemy[Enemy_Num];//�G��10�̍쐬
	for (int i = 0;i < Enemy_Num;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//�G�̍��W��ݒ�
	}

	std::vector<Enemy> enemy(Enemy_Num);//�G��10�̍쐬
	for (int i = 0;i < Enemy_Num;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//�G�̍��W��ݒ�
	}

	int i = 0;
	for (auto& e : enemy)//�G��10�̍쐬
	{
		e.SetPos(100 + i * 50, 100);//�G�̍��W��ݒ�
		i++;
	}


	Enemy* enemy = new Enemy[10];
	for (int i = 0;i < 10;i++)
	{
		enemy[i].SetPos(100 + i * 50, 100);//�G�̍��W��ݒ�
	}

	GameApp game = new GameApp();//�Q�[���̃V�X�e��
	*/
	
	
	//Stage* stage = new Stage();//�X�e�[�W�̃C���X�^���X�𐶐�
	Stage* stage = nullptr;


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();//�L�[�̏�Ԃ��X�V����


		crrTime = GetNowCount();//�O��̎��ԂƂ̍����v�Z
		float deltaTime = (crrTime - prevTime) / 1000.0f;//�b�P�ʂɕϊ�����
		gDeltaTime = deltaTime;//�O���[�o���ϐ��ɕۑ�����
		
		//�����ɏ�����`��

		switch (currentScreen)
		{
		case SCREEN_TITLE:
			DrawFormatString
			(100, 100, GetColor(255, 255, 255), "�^�C�g����� - Z�L�[�ŊJ�n");
			
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
				newObjects.clear();//�V�����Q�[���I�u�W�F�N�g���N���A

			}

			//�Q�[���I�u�W�F�N�g�̍X�V
			for (auto& obj : gameObjects)
			{
				obj->Update();
			}

			//�Q�[���I�u�W�F�N�g�̕`��
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
					++it;//����
				}

			}

			// �v���C���[���S���̉�ʑJ�ځistage ���� player ���擾����O��j
			if (stage && !stage->GetPlayer()->IsAlive())
			{
				currentScreen = SCREEN_GAMEOVER;
			}
			break;

		case SCREEN_GAMEOVER:

			DrawFormatString
			(100, 100, GetColor(255, 0, 0), "�Q�[���I�[�o�[ - R�L�[�Ń^�C�g����");
			
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
		//	newObjects.clear();//�V�����Q�[���I�u�W�F�N�g���N���A

		//}

		//for (auto& obj : gameObjects)
		//{
		//	obj->Update();
		//}
		//for (auto& obj : gameObjects)
		//{
		//	obj->Draw();
		//}



		//stage->Update();//�X�e�[�W�̍X�V
		//stage->Draw();//�X�e�[�W�̕`��


		
		
		player->Update();
		player->Draw();
		for (auto& elm : enemy)//�G��10�̍쐬
		{
			elm.Update();
			elm.Draw();
		}



		enemy->Update();
		enemy->Draw();

		�ꏊ�����炵�ĕ`�悷��

		for (int i = 0;i < 10;i++)//enemy��10�̍쐬
		{
			(enemy + i)->Update();
			(enemy + i)->Draw();
		}

		*/
		
		//����ʂ̕`��
		ScreenFlip();
		WaitTimer(16);
		prevTime = crrTime;//���݂̎��Ԃ�O��̎��ԂƂ��ĕۑ�

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}