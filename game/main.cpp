#include "Crafting.cpp"
#include "Visitor.cpp"
#include "Entity.cpp"
#include "Combat.cpp"

int main(){
	srand(time(NULL));
	
	BossFoe *boss = new BossFoe("Baron Nashor", 10000, 450, 0);
	NormalFoe *foe = new NormalFoe("Scuttle Crab", 1000, 10, 0);
	Player *p1 = new Player("Healer", 70000, 9000);
//	Player *p2 = new Player("Attacker", 35000, 400);
	
	vector<Entity*> enemies;
	enemies.push_back(boss);
	enemies.push_back(foe);
	vector<Entity*> players;
	
	
	InfoVisitor *iv = new InfoVisitor();
	AttackVisitor *av = new AttackVisitor();
	HealVisitor *hv = new HealVisitor();
	
	CraftingFacade *CraftingTable = new CraftingFacade;
	CraftingTable->setCrafter(p1->getInventory());
	
	int action;
	bool ingame = true, quit = false;
	
	int options;
	cout << "Choose option: ";
	
	int index;
	cout << p1->getName() << " strikes first! " << endl;
	while (ingame){
		ingame = false;
		cout << "Choose your action: " << endl;
		cout << "[1] Attack | [2] Heal | [3] Take Info | [4] Skip turn | [5] Quit" << endl;
		cin >> action;
		switch (action){
			case 1:
				cout << "Choose your target: " << endl;
				for (int i = 0; i < enemies.size(); i++)
					if (enemies[i] != NULL)
						cout << "[" << i + 1 << "] " << enemies[i]->getName() << endl; 
				cin >> index;
				cout << p1->getName() << " attack " << enemies[index - 1]->getName() << " !" << endl;
				p1->SingularAttack(av, enemies[index - 1]);
				break;
			case 2:
				cout << "Healing " << p1->getName() << "!" << endl;
				p1->HealTarget(hv, p1);
				break;
			case 3:
				p1->ShowInfo();
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
			case 5:
				cout << "Quitting..." << endl;
				quit = true;
				break;
			default:
				break;
		}
		if (quit){
			ingame = false;
			break;
		}
		for (int i = 0; i < enemies.size(); i++)
			if (!enemies[i]->getState()){
				enemies.erase(enemies.begin() + i);
			}
		
		if (enemies.size() == 0){
			ingame = false;
			break;
		}
		else
			ingame = true;
		
		if (boss->getState()){
			cout << boss->getName() << " is attacking! " << endl;
			if (rand() % 11 == 7)
				boss->SpecialAttack(av,p1);
			else
				boss->SingularAttack(av, p1);
		}
		if (foe->getState()){
			cout << foe->getName() << " is attacking! " << endl;		
			foe->SingularAttack(av, p1);
		}
		
		if (!p1->getState()){
			ingame = false;
			cout << "GAME OVER!" << endl;
		}
	}
	cout << "Battle points: " << av->GetBattlePoints() / 1000 << endl;
	delete iv;
	delete av;
	delete hv;
	
	delete boss;
	delete foe;
	
	if (p1 != NULL)
		delete p1;
	
	return 0;
}
