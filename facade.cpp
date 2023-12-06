#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player;

class Item{
protected:
	int value;
	string name;
	int id;
	static string item_list[12] = 
	{"Long Sword", "Cloak of Agility", "Kindle Gem", "Fiendish Codex"
	"Zeal", "Phage", "Hextech Alternator", "Needlessly Large Rod",
	"Galeforce", "Divine Sunderer", "Night Harvester", "Rabadon's Deathcap"};
	static int item_price[12] =
	{300, 600, 800, 900,
	 1000, 1200, 1800, 2000,
	 2500, 2500, 2500, 2500};
	int rarity;
public:
	Item(int item_id): id(item_id), value(item_price[item_id]), name(item_list[item_id]), rarity(1) {}
	void ItemInfo(){
		cout << "\"" << name << "\"" << " - " << value << "G" << endl;
	}
	int getId(){return id;}
	virtual void Active() const = 0;
	
};

class LegendaryItem : public Item{
private:
	int BonusHP;
	int BonusATK;
	int BonusMP;
	static int Bonus_Stats[4][3] =
	{{100, 500, 0},
	 {300, 300, 10},
	 {300, 10, 300},
	 {0, 0, 500}
	};
public:
	LegendaryItem(int item_id): BonusHP(Bonus_Stats[item_id%4][0]), BonusATK(Bonus_Stats[item_id%4][1]),
								BonusMP(Bonus_Stats[item_id%4][2]), Item(item_id){}
	int getHP() {return BonusHP;}
	int getATK() {return BonusATK;}
	int getMP() {return BonusMP;}
};

class CraftingFacade(){
public:
	Item* Craft(int id_craft){
		
	}
}

class Player{
private:
	int gold;
	vector<Item*> Inventory;
	Legendary_Item* main_hand;
	int baseATK;
	int baseHP;
	int baseMP;
	int ATK;
	int HP;
	int MP;
public:
	Player(int g): gold(g), baseATK(100), baseHP(100), baseMP(100), main_hand(NULL) {}
	void showInventory(){
		for (int i = 0; i < Inventory.size(); i++)
			Inventory[i]->ItemInfo();
	}
	void Equip(int num){
		if (dynamic_cast<Legendary_Item*>(Inventory[num]) == NULL){
			cout << "Can't equip this!";
			return;
		}
		main_hand = Inventory[num];
		HP = baseHP + main_hand->getHP();
		ATK = baseATK + main_hand->getATK();
		MP = baseMP + main_hand->getMP();
	}
	void giveGold(int g){
		if (g > gold)
			cout << "Not enough gold!";
		else{
			gold -= g;
			cout << g << "G given!";
		}
	}
	
	void RemoveItem(int item_id){
		for (int i = 0; i < Inventory.size(); i++)
			if (item_id == Inventory[i]->getId())
				Inventory.
	}
};
