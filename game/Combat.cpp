#pragma once
#include "Visitor.h"
#include "Entity.h"
#include "Combat.h"

void Foe::SingularAttack(AttackVisitor *atv, Entity *target){
	atv->SetAttacker(this);
	target->Interact(atv);
}

void Foe::HealTarget(HealVisitor *hlv, Entity *target){
	hlv->SetHealer(NULL);
	target->Interact(hlv);
}

void EpicFoe::SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2 = NULL){
	atv->SetAttacker(this);
	buffATK -= 20;
	tar1->Interact(atv);
	if (!tar2)
		tar2->Interact(atv);
	buffATK += 20;
}

void BossFoe::SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2 = NULL){
	atv->SetAttacker(this);
	if (tar2 == NULL){
		tar1->Interact(atv);
		tar1->Interact(atv);
		Healed(0);
	}
	else{
		tar1->Interact(atv);
		tar2->Interact(atv);
		if (rand() % 2)
			tar1->Interact(atv);
		else
			tar2->Interact(atv);
	}
}

void Player::SingularAttack(AttackVisitor *atv, Entity *target){
	atv->SetAttacker(this);
	target->Interact(atv);
	if (target->getState() && (rand() % 20 == 0)){
		cout << "Bonus Attack!" << endl;
		target->Interact(atv);
	}
}

void Player::HealTarget(HealVisitor *hlv, Entity *target){
	hlv->SetHealer(this);
	target->Interact(hlv);
}

void NormalFoe::TakeAction(vector<Entity*> players, vector<Entity*> enemies, InteractiveVisitors *v){
	if (rand() % 10 == 1)
		cout << name << " does nothing!";
	else{
		v->Attack.SetAttacker(this);
		SingularAttack(&v->Attack, players[rand() % players.size()]);
	}
}

void EpicFoe::TakeAction(vector<Entity*> players, vector<Entity*> enemies, InteractiveVisitors *v){
	int action = rand() % 10;
	if (action > 7){
		v->Heal.SetHealer(this);
		for (int i = 0; i < enemies.size(); i++)
			HealTarget(&v->Heal, enemies[i]);
	}
	else if (action > 6){
		v->Attack.SetAttacker(this);
		SpecialAttack(&v->Attack, players[rand() % players.size()], players[rand() % players.size()]);
	}
	else{
		v->Attack.SetAttacker(this);
		SingularAttack(&v->Attack, players[rand() % players.size()]);
	}
}

void BossFoe::TakeAction(vector<Entity*> players, vector<Entity*> enemies, InteractiveVisitors *v){
	int action = rand() % 10;
	if (action > 9 && enemies.size() == 1){
		cout << name << " is spawning minions!!!!" ;
		enemies.push_back(new NormalFoe("Voidgrubs", 800, 150, 0));
		enemies.push_back(new NormalFoe("Voidgrubs", 800, 150, 0));
	}
	else if (action > 6){
		v->Attack.SetAttacker(this);
		SpecialAttack(&v->Attack, players[rand() % players.size()], players[rand() % players.size()]);
	}
	else{
		v->Attack.SetAttacker(this);
		SingularAttack(&v->Attack, players[rand() % players.size()]);
	}
}

void Player::TakeAction(vector<Entity*> players, vector<Entity*> enemies, InteractiveVisitors *v){
	int action, index;
	v->Attack.SetAttacker(this);
	v->Heal.SetHealer(this);
	cout << name << "'s turn!" << endl;
	cout << "Choose your action: " << endl;
	cout << "[1] Attack | [2] Heal | [3] Take Info | [4] Skip turn " << endl;
	cin >> action;
	switch (action){
		case 1:
			cout << "Choose your target: " << endl;
			for (int i = 0; i < enemies.size(); i++)
				if (enemies[i] != NULL)
					cout << "[" << i + 1 << "] " << enemies[i]->getName() << endl; 
			cin >> index;
			cout << name << " attack " << enemies[index - 1]->getName() << " !" << endl;
			SingularAttack(&v->Attack, enemies[index - 1]);
			break;
		case 2:
			cout << "Choose your target: " << endl;
			for (int i = 0; i < players.size(); i++)
				if (players[i] != NULL)
					cout << "[" << i + 1 << "] " << players[i]->getName() << endl; 
			cin >> index;
			cout << name << " heals " << players[index - 1]->getName() << " !" << endl;
			HealTarget(&v->Heal, players[index - 1]);
			break;
		case 3:
			cout << endl;
			cout << "Taking info of enemies..." << endl;
			cout << "###########################################" << endl;
			for (int i = 0; i < enemies.size(); i++){
					enemies[i]->ShowInfo();
					cout << endl;
			}
			cout << "###########################################" << endl;
			break;
		case 4:
			cout << "Skipping turn..." << endl;
			break;
		default:
			break;
	}
}

Game::Game() : gold(0), level(1){}

string Game::item_list[14] = {
		"Long Sword",
		"Cloak of Agility",
		"Kindle Gem",
		"Fiendish Codex",
		"Zeal",
		"Phage",
		"Hextech Alternator",
		"Needlessly Large Rod",
		"Galeforce",
		"Divine Sunderer",
		"Night Harvester",
		"Rabadon's Deathcap",
		"Long Long Sword",
		"Impossible Sword",
	};

void Game::setLevel(){
	cout << "Set level (1 | 2): ";
	cin >> level;
	while (level != 1 || level != 2){
		cout << "Invalid level!";
		cout << "Set level (1 | 2): ";
		cin >> level;
	}
}

void Game::setGold(int g){
	gold = abs(g);
}

void Game::Combat(vector<Entity*> players){
	cout << endl << "[=================================================]" << endl;
	cout << "Entering combat!" << endl << endl;
	for (int i = 0; i < players.size(); i++)
		players[i]->ResetState();
	
	vector<Entity*> enemies;
	vector<Entity*> dead_enemies;
	vector<Entity*> dead_players;
	
	InteractiveVisitors* v = new InteractiveVisitors;
	Entity* e1 = NULL;
	Entity* e2 = NULL;
	Entity* e3 = NULL;
	
	if (level == 1){
		e1 = new EpicFoe("Red Brambleback", 4000, 500, 100);
		e2 = new EpicFoe("Blue Sentinel", 5500, 400, 100);
		enemies.push_back(e1);
		enemies.push_back(e2);
	}
	else if (level == 2){
		e1 = new NormalFoe("Voidgrubs", 1000, 250, 20);
		e2 = new BossFoe("Baron Nashor", 7000, 650, 500);
		e3 = new NormalFoe("Voidgrubs", 1000, 250, 20);	
		enemies.push_back(e1);
		enemies.push_back(e2);
		enemies.push_back(e3);	
	}
	else{
		cout << "No level option available.";
		return;
	}
	
	bool ingame = true;
	while(ingame){
		for (int i = 0; i < players.size(); i++){
			players[i]->TakeAction(players, enemies, v);
			
			for (int i = 0; i < enemies.size(); i++)
				if (!enemies[i]->getState()){
					dead_enemies.push_back(enemies[i]);
					enemies.erase(enemies.begin() + i);
				}
			
			if (enemies.size() == 0){
				ingame = false;
				cout << "BATTLE WON!" << endl;
				break;
			}
			else
				ingame = true;
		}
			
		if (enemies.size() == 0){
			ingame = false;
//			cout << "BATTLE WON!" << endl;
			break;
		}
		else
			ingame = true;
			
		for (int i = 0; i < enemies.size(); i++){
			enemies[i]->TakeAction(players, enemies, v);
		
			for (int i = 0; i < players.size(); i++)
				if (!players[i]->getState()){
					dead_players.push_back(players[i]);
					players.erase(players.begin() + i);
				}
			
			if (players.size() == 0){
				ingame = false;
				cout << "y o u   d i e d" << endl;
				break;
			}
			else
				ingame = true;	
		}
		
		if (players.size() == 0){
			ingame = false;
//			cout << "y o u   d i e d" << endl;
			break;
		}
		else
			ingame = true;	
	}
	
	gold += v->Attack.GetBattlePoints() / 1000;
	cout << "You got " << v->Attack.GetBattlePoints() / 1000 << "!" << endl;
	cout << endl; 
	for (int i = 0; i < dead_players.size(); i++){
		dead_players[i]->ResetState();
		players.push_back(dead_players[i]);
	}
	for (int i = 0; i < dead_enemies.size(); i++)
		delete dead_enemies[i];
	level = level % 2 + 1;
}

void Game::ShopnCraft(Player *p){
	CraftingFacade *ShopAndCraft = new CraftingFacade;
	ShopAndCraft->setCrafter(p->getInventory());
	cout << endl << "[=================================================]" << endl;
	cout << "Welcome to Shop n' Craft!! " << endl;
	
	int action, option, amount;
	bool quit = true;
	while (quit){
		cout << "Current gold: " << gold << endl ;
		cout << "Current Inventory: " << endl;
			ShopAndCraft->displayInventory();
		cout << "Choose action: " << endl;
		cout << "[1] Buy | [2] Craft | [3] Sell" << endl;
		cin >> action;
		switch (action){
			case 1:
				cout << "Buy items (400G each): " << endl;
				for (int i = 0; i < 4; i++)
					cout << "[" << i + 1 << "] " << item_list[i] << endl;
				cin >> option;
				cout << "Quantity? : ";
				cin >> amount;
				if (option > 4 || option < 1 || amount < 1)
					cout << "Invalid option." << endl;
				else if (gold < 400 * amount)
					cout << "Not sufficient funds!" << endl;
				else{
					while(amount-- != 0)	
						ShopAndCraft->addItem(item_list[option - 1], 1);
					cout << "Items bought sucessfully." << endl;
				}
				break;
			case 2:
				cout << "Craft items (50G craft fees): " << endl;
				for (int i = 4; i < 13; i++)
					cout << "[" << i - 3 << "] " << item_list[i] << endl;
				cin >> option;
				if (option > 9 || option < 1)
					cout << "Invalid option." << endl;
				else if (gold < 50)
					cout << "Not sufficient funds!" << endl;
				else{
					ShopAndCraft->craftItem(item_list[option + 3]);
					cout << "Item crafted sucessfully." << endl;
				}
				break;
			case 3:
				cout << "Can't sell your items due to inflation." << endl;
//				int index = 1;
//				for (const auto& entry : *inventory){
//					if (entry.second != 0)
//			        	cout << "[" << index++ << "]" << entry.first->getName() << ": " << entry.second << "\n";
//			    }
				break;
			default:
				break;
		}
		
		cout << "Continue browsing? (1 = yes, 0 = no)" << endl;
		int i_quit;
		cin >> i_quit;
		if (i_quit > 0)
			quit = false;
	}
	
	ShopAndCraft->resetCrafter();
	delete ShopAndCraft;
}
