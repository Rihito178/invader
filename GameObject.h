#pragma once
#include<vector>

class GameObject
{
protected:
	bool isAlive_;//�e�������Ă��邩

public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;//�������z�֐�
	virtual void Draw() = 0;
	
	bool IsAlive() { return isAlive_; }
	//�e�������Ă���
	
	void SetAlive(bool alive) { isAlive_ = alive; }
	//�Q�[���I�u�W�F�N�g�������Ă��邩�ǂ���

};

extern std::vector<GameObject*>gameObjects;
extern std::vector<GameObject*>newObjects;
inline void AddGameObject(GameObject* obj)
{
	//gameObjects.push_back(obj);
	newObjects.push_back(obj);
}
//gameObjects.push_back(obj);
