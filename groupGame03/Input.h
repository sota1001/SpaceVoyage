#pragma once

class Input{
private:
	static char keys[];
	static char oldkeys[];
	Input();

public:
	static void Update();
	static bool isKey(int key);
	static bool isKeyTrigger(int key);
};
