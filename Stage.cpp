#include "Stage.h"//�錾�̒��g���K�v�Ȃ��߃C���N���[�h
#include "Player.h"//�錾�̒��g���K�v�Ȃ��߃C���N���[�h
#include "Enemy.h"//�錾�̒��g���K�v�Ȃ��߃C���N���[�h
#include"Bullet.h"
#include <Dxlib.h>
#include"EnemyBeam.h"

namespace
{
	const int Enemy_Num = 10*7;//�G�̐�
	const int Enemy_Col_Size = 10;//�G�̗�
	const int Enemy_Row_Size = 7;//�G�̍s��

	const float Enemy_Alingn_x = 55.0f; //�G����ׂ镝
	const float Enemy_Alingn_y = 50.0f; //�G����ׂ鍂��
	const int ENEMY_LEFT_MARGIN = (WIN_WIDTH - (Enemy_Alingn_x * Enemy_Col_Size)) / 2;
	const int ENEMY_TOP_MARGIN = 75;


    bool IntersectRect(const Rect _a, const Rect _b)  
    {  
       bool xOverlap = (_a.x < _b.x + _b.width) && (_b.x < _a.x + _a.width);  
       bool yOverlap = (_a.y < _b.y + _b.height) && (_b.y < _a.y + _a.height);  
       return xOverlap && yOverlap;  
    }

}

//�@�G�̗����邽�߂�
//�@��1	�G�̏������W��ݒ肵�Ă���SetPos���N���X�ɂ��ė�ɂ���
// �@



Stage::Stage()
	:GameObject(), player_(nullptr), hBackground(-1)
{
	AddGameObject(this);
	player_ = new Player();//�v���C���[�̃C���X�^���X�𐶐�

	enemy_ = std::vector<Enemy*>(Enemy_Num);
	for (int i = 0; i < Enemy_Num; i++)//��
	{
		//�搶����
		int col = i % Enemy_Col_Size;
		int row = i / Enemy_Col_Size;
		ETYPE enemyType[Enemy_Row_Size] = { BOSS,KNGHT,MID,ZAKO,ZAKO,ZAKO };

		enemy_[i] = new Enemy(i,enemyType[row]);//�V���ȓG�̍쐬
		//enemy_[i]->SetPos(col * 55.0f, row * 50.0f);//�G�̏����ʒu

		enemy_[i]->SetMaxMoveX(ENEMY_LEFT_MARGIN);
		enemy_[i]->SetPos(col * Enemy_Alingn_x + ENEMY_LEFT_MARGIN,
			row * Enemy_Alingn_y + ENEMY_TOP_MARGIN); // �G�̏����ʒu��ݒ�
		enemy_[i]->SetXorigin(col * Enemy_Alingn_x + ENEMY_LEFT_MARGIN);
		//for (int j = 0; j < Enemy_Num; j++)//�c
		//{
		//	enemy_[i * Enemy_Col_Size * j] = new Enemy();
		//	enemy_[i * Enemy_Col_Size + j]->SetPos(100 + j * 50,100+i*50); // ��Ɋ�Â�X���W�ݒ�
		//	// �G��Y���W��ݒ�
		//	enemy_[i * Enemy_Col_Size + j]->SetID(i *Enemy_Col_Size*j); // �s�Ɋ�Â�Y���W�ݒ�
		//}

	}
		//{
		//	enemy_[i * Enemy_Col_Size * j] = new Enemy(i,(ETYPE)(i % MAX_ETYPE));//�G�̃C���X�^���X�𐶐�
		//	
		//	enemy_[i]->SetPos(i % Enemy_Col_Size * 55, i / Enemy_Col_Size * 50);
		//	
		//	
		//	//enemy_[i * Enemy_Col_Size * j]->SetPos(100 + i * 50, 100);
		//	//enemy_[i * Enemy_Col_Size * j]->SetPos(100 + j * 50, 100);

	hBackground = LoadGraph("Assets\\bg.png");//�w�i

	//	//enemy_[i]->SetPos(100 + i * 50, 100);//�G�̏������W��ݒ�
		//	//enemy_[j]->SetPos(100 + j * 50, 100);//�G�̏������W��ݒ�
		//}
		
		
}

	
	


Stage::~Stage()
{

}

void Stage::Update()
{	
	// EnemyBeam�Ƃ̓����蔻�菈��
	std::vector<GameObject*> objects = gameObjects; // ���ׂĂ�GameObject���擾
	for (auto& obj : objects)
	{
		EnemyBeam* beam = dynamic_cast<EnemyBeam*>(obj);
		if (beam && beam->IsFired() && player_->IsAlive())
		{
			if (IntersectRect(player_->GetRect(), beam->GetRect()))
			{
				beam->SetFired(false);		// �r�[���𖳌���
				beam->SetAlive(false);		// �r�[�����폜�Ώۂ�
				player_->SetAlive(false);// �v���C���[��|���i�܂��̓��C�t�����炷�j
				// �K�v�ɉ����ăG�t�F�N�g��T�E���h��ǉ�
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

void Stage::Draw()//�w�i
{
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
