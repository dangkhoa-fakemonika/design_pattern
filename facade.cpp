// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// class Player;

// class Item{
// private:
// 	int id;
// 	string name;

// 	int bonusATK;
// 	int bonusHP;

// 	vector <Item> Component;

// 	static vector <string> item_list;
// 	// {"Long Sword", "Cloak of Agility", "Kindle Gem", "Fiendish Codex"
// 	// "Zeal", "Phage", "Hextech Alternator", "Needlessly Large Rod",
// 	// "Galeforce", "Divine Sunderer", "Night Harvester", "Rabadon's Deathcap"};
// public:
	
// }

// class CraftingFacade{
// private:

// public:
	
// };
// // class Item{
// // protected:
// // 	int value;
// // 	string name;
// // 	int id;
// 	// static string item_list[12] = 
// 	// {"Long Sword", "Cloak of Agility", "Kindle Gem", "Fiendish Codex"
// 	// "Zeal", "Phage", "Hextech Alternator", "Needlessly Large Rod",
// 	// "Galeforce", "Divine Sunderer", "Night Harvester", "Rabadon's Deathcap"};
// // 	static int item_price[12] =
// // 	{300, 600, 800, 900,
// // 	 1000, 1200, 1800, 2000,
// // 	 2500, 2500, 2500, 2500};
// // 	int rarity;
// // public:
// // 	Item(int item_id): id(item_id), value(item_price[item_id]), name(item_list[item_id]), rarity(1) {}
// // 	void ItemInfo(){
// // 		cout << "\"" << name << "\"" << " - " << value << "G" << endl;
// // 	}
// // 	int getId(){return id;}
// // 	virtual void Active() const = 0;
	
// // };

// // class LegendaryItem : public Item{
// // private:
// // 	int BonusHP;
// // 	int BonusATK;
// // 	int BonusMP;
// // 	static int Bonus_Stats[4][3] =
// // 	{{100, 500, 0},
// // 	 {300, 300, 10},
// // 	 {300, 10, 300},
// // 	 {0, 0, 500}
// // 	};
// // public:
// // 	LegendaryItem(int item_id): BonusHP(Bonus_Stats[item_id%4][0]), BonusATK(Bonus_Stats[item_id%4][1]),
// // 								BonusMP(Bonus_Stats[item_id%4][2]), Item(item_id){}
// // 	int getHP() {return BonusHP;}
// // 	int getATK() {return BonusATK;}
// // 	int getMP() {return BonusMP;}
// // };

// // class CraftingFacade(){
// // public:
// // 	Item* Craft(int id_craft){
		
// // 	}
// // }

// // class Player{
// // private:
// // 	int gold;
// // 	vector<Item*> Inventory;
// // 	Legendary_Item* main_hand;
// // 	int baseATK;
// // 	int baseHP;
// // 	int baseMP;
// // 	int ATK;
// // 	int HP;
// // 	int MP;
// // public:
// // 	Player(int g): gold(g), baseATK(100), baseHP(100), baseMP(100), main_hand(NULL) {}
// // 	void showInventory(){
// // 		for (int i = 0; i < Inventory.size(); i++)
// // 			Inventory[i]->ItemInfo();
// // 	}
// // 	void Equip(int num){
// // 		if (dynamic_cast<Legendary_Item*>(Inventory[num]) == NULL){
// // 			cout << "Can't equip this!";
// // 			return;
// // 		}
// // 		main_hand = Inventory[num];
// // 		HP = baseHP + main_hand->getHP();
// // 		ATK = baseATK + main_hand->getATK();
// // 		MP = baseMP + main_hand->getMP();
// // 	}
// // 	void giveGold(int g){
// // 		if (g > gold)
// // 			cout << "Not enough gold!";
// // 		else{
// // 			gold -= g;
// // 			cout << g << "G given!";
// // 		}
// // 	}
	
// // 	void RemoveItem(int item_id){
// // 		for (int i = 0; i < Inventory.size(); i++)
// // 			if (item_id == Inventory[i]->getId())
// // 				Inventory.
// // 	}
// // };
 
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Item;
class CraftingRecipe;
class CraftingFacade;

class Item {
private:
    int id;
    string name;
    int bonusATK;
    int bonusHP;

public:
    Item(int itemId, const string& itemName, int atkBonus, int hpBonus)
        : id(itemId), name(itemName), bonusATK(atkBonus), bonusHP(hpBonus) {}

    int getID() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getBonusATK() const {
        return bonusATK;
    }

    int getBonusHP() const {
        return bonusHP;
    }
};

class CraftingRecipe {
private:
    Item* resultItem;
    unordered_map<Item*, int> requiredItems;

public:
    CraftingRecipe(Item* result, const unordered_map<Item*, int>& items)
        : resultItem(result), requiredItems(items) {}

    Item* getResultItem() const {
        return resultItem;
    }

    bool canCraft(unordered_map<Item*, int>& inventory){ // check if have enough material
        for (const auto& entry : requiredItems) {
            if (inventory.find(entry.first) != inventory.end() && inventory[entry.first] < entry.second) {
                return false;
            }
        }
        return true;
    }

	bool isCraftable(){
		if (requiredItems[NULL] == 1)
			return false;
		else
			return true;
	}

    void craft(unordered_map<Item*, int>& inventory) {
        if (canCraft(inventory)) {
            cout << "Crafting " << resultItem->getName() << "...\n";
            for (const auto& entry : requiredItems) {
                inventory[entry.first] -= entry.second;
            }
            inventory[resultItem] += 1;
            cout << resultItem->getName() << " crafted successfully!\n";
        } else {
            cout << "Not enough materials to craft " << resultItem->getName() << ".\n";
        }
    }
};

class CraftingFacade {
private:
    unordered_map<Item*, int> inventory;
    vector<CraftingRecipe*> craftingRecipes;

public:
    CraftingFacade() {
        initializeCraftingRecipes();
    }

    ~CraftingFacade() {
        for (CraftingRecipe* recipe : craftingRecipes) {
            delete recipe;
        }
    }

    void craftItem(const string& itemName) {
        Item* resultItem = getItemByName(itemName);
        if (resultItem) {
            CraftingRecipe* recipe = getCraftingRecipe(resultItem);
            if (recipe->isCraftable()) {
                recipe->craft(inventory);
            } else {
                cout << "Cant craft! " << itemName << " is a basic item.\n";
            }
        } else {
            cout << "Item not found: " << itemName << ".\n";
        }
    }

    void displayInventory() const {
        cout << "///////// Inventory ////////\n";
		//cout << "current Inventory size: " << inventory.size() << endl;
		if (inventory.size() == 0){
			cout << "there is none\n";
		}
        for (const auto& entry : inventory){
			if (entry.second != 0)
            	cout << setw(20) << left << entry.first->getName() << ": " << entry.second << "\n";
        }
		cout << "////////////////////////////\n"; 
    }

	void addItem(const string& itemName, const int& amount){
		Item* resultItem = getItemByName(itemName);
		if (resultItem)
			inventory[resultItem] += amount;
		else
			cout << "Unknown item: " << itemName << endl;
	}

	bool removeItem(const string& itemName, const int& amount){
		Item* resultItem = getItemByName(itemName);
		if (resultItem){
			if (inventory[resultItem] < amount){
				cout << "Not enough amount of " << itemName << " to remove(currently has " << inventory[resultItem] << ")" << endl;
			} else {
				inventory[resultItem] -= amount;
			}
		}
		else {
			cout << "Unknown item: " << itemName << endl;
			return false;
		}
	}

private:
    void initializeCraftingRecipes() {
        craftingRecipes.push_back(new CraftingRecipe(
            new Item(1, "Long Sword", 10, 0),
            {{nullptr, 1}})); // Recipe: None (base item)

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(2, "Cloak of Agility", 5, 5),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(3, "Kindle Gem", 0, 20),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(4, "Fiendish Codex", 20, 0),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(5, "Zeal", 15, 10),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(6, "Phage", 20, 10),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(7, "Hextech Alternator", 40, 0),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(8, "Needlessly Large Rod", 50, 0),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(9, "Galeforce", 30, 15),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(10, "Divine Sunderer", 40, 20),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(11, "Night Harvester", 45, 15),
            {{nullptr, 1}}));

        craftingRecipes.push_back(new CraftingRecipe(
            new Item(12, "Rabadon's Deathcap", 80, 0),
            {{nullptr, 1}}));
		craftingRecipes.push_back(new CraftingRecipe(
            new Item(13, "Long Long Sword", 100, 100),
            {{getItemByName("Long Sword"), 2}})); // craft by 2 Long Sword
		craftingRecipes.push_back(new CraftingRecipe(
            new Item(13, "Impossible Sword", 999, 999),
            {{getItemByName("Long Sword"), 999}})); 
    }

    Item* getItemByName(const string& itemName) const {
        for (const auto& recipe : craftingRecipes) {
            if (recipe->getResultItem()->getName() == itemName) {
                return recipe->getResultItem();
            }
        }
        return nullptr;
    }

    CraftingRecipe* getCraftingRecipe(Item* resultItem) const {
        for (const auto& recipe : craftingRecipes) {
            if (recipe->getResultItem() == resultItem) {
                return recipe;
            }
        }
        return nullptr;
    }
};

int main() {
    CraftingFacade myBag;
	
	
    // Display initial inventory
    myBag.displayInventory();

    // Add some items
	myBag.addItem("Long Sword", 1);
	myBag.addItem("Long Sword", 2);
	
	// Add unknown items
	myBag.addItem("MY BALL", 69);

	myBag.displayInventory();

	// Craft basic item(you cant)
	myBag.craftItem("Long Sword");
	// Craft item
	myBag.craftItem("Long Long Sword");
	// Attempt to craft an unknown item
    myBag.craftItem("Unknown Item");
    // Attempt to craft an item with insufficient materials
    myBag.craftItem("Impossible Sword");
	
	myBag.displayInventory();

	myBag.removeItem("Long Sword", 100);
	myBag.removeItem("Long Sword", 1);

	myBag.displayInventory();
    return 0;
}
