#pragma once

//XGAサイズ
const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;

extern float gDeltaTime;//フレーム間の時間差ほかのどこかで宣言している宣言である
inline float GetDeltaTime()//宣言と定義
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
	inline Point GetCounter()const//矩形の中心座標を取得する
	{
		return { x + width / 2,y + height / 2 };

	}

};