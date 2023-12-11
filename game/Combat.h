#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

class Game{
private:
	int gold;
	int level;
public:
	Game();
	void setLevel();
	void Combat(vector<Entity*> players);
	void ShopnCraft(Player *p);
};
