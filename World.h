#pragma once

//XGA�T�C�Y
const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;

extern float gDeltaTime;//�t���[���Ԃ̎��ԍ��ق��̂ǂ����Ő錾���Ă���錾�ł���
inline float GetDeltaTime()//�錾�ƒ�`
{
	return gDeltaTime;
}

struct Point
{
	float x;
	float y;
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
	inline Point GetCounter()const//��`�̒��S���W���擾����
	{
		return { x + width / 2,y + height / 2 };

	}

};