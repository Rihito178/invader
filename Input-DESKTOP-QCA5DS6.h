#pragma once


namespace Input 
{
	//キーボード取得関連
	void KeyStateUpdate();//キーの状態を更新する関数
	bool IsKeyUP(int keyCode);//押された瞬間の状態を返す関数
	bool IsKeyDown(int keyCode);//離された瞬間の状態を返す関数
	int IsKeepKeyDown(int keyCode);//押しっぱなしの状態を返す関数

}