#pragma once
class Enemy
{

public:

	Enemy();
	virtual void Update();
	virtual void Draw();
	
protected:

	float x;
	float y;
	int size;
	int graph;
	float sizeRate;
	float angle;
	
};

class ExplodingEnemy : public Enemy {

public:

	ExplodingEnemy(float x, float y);
	void Update() override;
	void Draw() override;
	
private:
	
	
};

