#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Item {
private:
    int id;
    string name;
    int bonusATK;
    int bonusHP;

public:
    Item(int itemId, const string& itemName, int atkBonus, int hpBonus);
    int getID() const;
    string getName() const;
    int getBonusATK() const;
    int getBonusHP() const;
};

class CraftingRecipe {
private:
    Item* resultItem;
    unordered_map<Item*, int> requiredItems;

public:
    CraftingRecipe(Item* result, const unordered_map<Item*, int>& items);
    Item* getResultItem() const;
    bool canCraft(unordered_map<Item*, int> *inventory);
	bool isCraftable();
    void craft(unordered_map<Item*, int> *inventory);
};

class CraftingFacade {
private:
    unordered_map<Item*, int> *inventory;
    static vector<CraftingRecipe*> craftingRecipes;

public:
    CraftingFacade();
    ~CraftingFacade();
    void setCrafter(unordered_map<Item*, int> *inv);
    void resetCrafter();
    void craftItem(const string& itemName);
    void displayInventory() const;
	void addItem(const string& itemName, const int& amount);
	bool removeItem(const string& itemName, const int& amount);
    static void initializeCraftingRecipes();
private:
    
    static Item* getItemByName(const string& itemName);
    CraftingRecipe* getCraftingRecipe(Item* resultItem) const;
};

vector<CraftingRecipe*> CraftingFacade::craftingRecipes;

