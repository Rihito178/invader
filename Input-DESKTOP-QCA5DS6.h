#pragma once


namespace Input 
{
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();//�L�[�̏�Ԃ��X�V����֐�
	bool IsKeyUP(int keyCode);//�����ꂽ�u�Ԃ̏�Ԃ�Ԃ��֐�
	bool IsKeyDown(int keyCode);//�����ꂽ�u�Ԃ̏�Ԃ�Ԃ��֐�
	int IsKeepKeyDown(int keyCode);//�������ςȂ��̏�Ԃ�Ԃ��֐�

}