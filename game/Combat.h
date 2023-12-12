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
	static string item_list[13];
public:
	Game();
	void setLevel();
	void setGold(int g);
	void Combat(vector<Entity*> players);
	void ShopnCraft(Player *p);
};
