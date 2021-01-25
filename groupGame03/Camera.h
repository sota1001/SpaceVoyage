#pragma once
class Camera{

public:
	static void Reset();
	static float GetX() { return x; }
	static float GetY() { return y; }
	static void Update(float target, float targetY);

private:
	
	static float x;
	static float y;
	
};

