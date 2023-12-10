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
				cout << "Not enough amount of " << itemName << " to remove (currently has " << inventory[resultItem] << ")" << endl;
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
	
	// Facade instruction:
	//	addItem()
	//  removeItem()
	//  displayInventory()
	// 	craftItem()


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
