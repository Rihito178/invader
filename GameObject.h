#pragma once
#include<vector>

class GameObject
{
protected:
	bool isAlive_;//弾が生きているか

public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;//純粋仮想関数
	virtual void Draw() = 0;
	
	bool IsAlive() { return isAlive_; }
	//弾が生きている
	
	void SetAlive(bool alive) { isAlive_ = alive; }
	//ゲームオブジェクトが生きているかどうか

};

extern std::vector<GameObject*>gameObjects;
extern std::vector<GameObject*>newObjects;
inline void AddGameObject(GameObject* obj)
{
	//gameObjects.push_back(obj);
	newObjects.push_back(obj);
}
//gameObjects.push_back(obj);
