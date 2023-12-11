#pragma once
#include "Crafting.h"
#include "Entity.h"

Item::Item(int itemId, const string& itemName, int atkBonus, int hpBonus): id(itemId), name(itemName), bonusATK(atkBonus), bonusHP(hpBonus) {}

int Item::getID() const {
    return id;
}

string Item::getName() const {
    return name;
}

int Item::getBonusATK() const {
    return bonusATK;
}

int Item::getBonusHP() const {
    return bonusHP;
}

CraftingRecipe::CraftingRecipe(Item* result, const unordered_map<Item*, int>& items): resultItem(result), requiredItems(items) {}

Item* CraftingRecipe::getResultItem() const {
    return resultItem;
}

bool CraftingRecipe::canCraft(unordered_map<Item*, int> *inventory){ // check if have enough material
    for (const auto& entry : requiredItems) {
        if (inventory->find(entry.first) != inventory->end() && (*inventory)[entry.first] < entry.second) {
            return false;
        }
    }
    return true;
}

bool CraftingRecipe::isCraftable(){
	if (requiredItems[NULL] == 1)
		return false;
	else
		return true;
}

void CraftingRecipe::craft(unordered_map<Item*, int> *inventory) {
    if (canCraft(inventory)) {
        cout << "Crafting " << resultItem->getName() << "...\n";
        for (const auto& entry : requiredItems) {
            (*inventory)[entry.first] -= entry.second;
        }
        (*inventory)[resultItem] += 1;
        cout << resultItem->getName() << " crafted successfully!\n";
    } else {
        cout << "Not enough materials to craft " << resultItem->getName() << ".\n";
    }
}



CraftingFacade::CraftingFacade() {
    initializeCraftingRecipes();
}

CraftingFacade::~CraftingFacade() {
    for (CraftingRecipe* recipe : craftingRecipes) {
        delete recipe;
    }
}
void CraftingFacade::setCrafter(unordered_map<Item*, int> *inv){
	inventory = inv;
}

void CraftingFacade::resetCrafter(){
	inventory = NULL;
}

void CraftingFacade::craftItem(const string& itemName) {
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

void CraftingFacade::displayInventory() const {
    cout << "///////// Inventory ////////\n";
	//cout << "current Inventory size: " << inventory.size() << endl;
	if (inventory->size() == 0){
		cout << "there is none\n";
	}
    for (const auto& entry : *inventory){
		if (entry.second != 0)
        	cout << setw(20) << left << entry.first->getName() << ": " << entry.second << "\n";
    }
	cout << "////////////////////////////\n"; 
}

void CraftingFacade::addItem(const string& itemName, const int& amount){
	Item* resultItem = getItemByName(itemName);
	if (resultItem)
		(*inventory)[resultItem] += amount;
	else
		cout << "Unknown item: " << itemName << endl;
}

bool CraftingFacade::removeItem(const string& itemName, const int& amount){
	Item* resultItem = getItemByName(itemName);
	if (resultItem){
		if ((*inventory)[resultItem] < amount){
			cout << "Not enough amount of " << itemName << " to remove (currently has " << (*inventory)[resultItem] << ")" << endl;
		} else {
			(*inventory)[resultItem] -= amount;
		}
	}
	else {
		cout << "Unknown item: " << itemName << endl;
		return false;
	}
}


void CraftingFacade::initializeCraftingRecipes() {
    craftingRecipes.push_back(new CraftingRecipe(new Item(1, "Long Sword", 10, 0), {{nullptr, 1}})); // Recipe: None (base item)

    craftingRecipes.push_back(new CraftingRecipe(new Item(2, "Cloak of Agility", 5, 5), {{nullptr, 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(3, "Kindle Gem", 0, 20), {{nullptr, 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(4, "Fiendish Codex", 20, 0), {{nullptr, 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(5, "Zeal", 15, 10), {{getItemByName("Long Sword"), 1},{getItemByName("Cloak of Agility"), 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(6, "Phage", 20, 10), {{getItemByName("Long Sword"), 1},{getItemByName("Kindle Gem"), 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(7, "Hextech Alternator", 40, 0), {{getItemByName("Kindle Gem"), 1}, {getItemByName("Fiendish Codex"), 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(8, "Needlessly Large Rod", 50, 0), {{getItemByName("Fiendish Codex"), 1}, {getItemByName("Cloak of Agility"), 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(9, "Galeforce", 30, 15), {{getItemByName("Zeal"), 1},{getItemByName("Long Sword"), 2}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(10, "Divine Sunderer", 40, 20), {{nullptr, 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(11, "Night Harvester", 45, 15), {{nullptr, 1}}));

    craftingRecipes.push_back(new CraftingRecipe(new Item(12, "Rabadon's Deathcap", 80, 0), {{nullptr, 1}}));
    
	craftingRecipes.push_back(new CraftingRecipe(new Item(13, "Long Long Sword", 100, 100), {{getItemByName("Long Sword"), 2}})); // craft by 2 Long Sword
	
	craftingRecipes.push_back(new CraftingRecipe(new Item(14, "Impossible Sword", 999, 999), {{getItemByName("Long Sword"), 999}})); 
}

Item* CraftingFacade::getItemByName(const string& itemName) const {
    for (const auto& recipe : craftingRecipes) {
        if (recipe->getResultItem()->getName() == itemName) {
            return recipe->getResultItem();
        }
    }
    return nullptr;
}

CraftingRecipe* CraftingFacade::getCraftingRecipe(Item* resultItem) const {
    for (const auto& recipe : craftingRecipes) {
        if (recipe->getResultItem() == resultItem) {
            return recipe;
        }
    }
    return nullptr;
}


