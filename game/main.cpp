#include "Visitor.cpp"
#include "Entity.cpp"
#include "Combat.cpp"
#include "Crafting.cpp"

int main(){
	srand(time(NULL));
	
	BossFoe *boss = new BossFoe("Baron Nashor", 1000000, 450, 0);
	NormalFoe *foe = new NormalFoe("Scuttle Crab", 10000, 10, 0);
	Player *p1 = new Player("Yasuo", 35000, 400);
	
	
	Entity *enemies[2] = {boss, foe};
	
	InfoVisitor *iv = new InfoVisitor();
	AttackVisitor *av = new AttackVisitor();
	HealVisitor *hv = new HealVisitor();
	
	CraftingFacade *CraftingTable = new CraftingFacade;
	CraftingTable->setCrafter(p1);
	
	int action;
	bool ingame = true, quit = false;
	
//	cout << p1->getName() << " strikes first! " << endl;
//	while (ingame){
//		ingame = false;
//		cout << "Choose your action: " << endl;
//		cout << "[1] Attack | [2] Heal | [3] Take Info | [4] Skip turn | [5] Quit" << endl;
//		cin >> action;
//		int index = 1;
//		switch (action){
//			case 1:
//				cout << "Choose your target: " << endl;
//				for (int i = 0; i < 2; i++)
//					if (enemies[i] != NULL)
//						cout << "[" << index++ << "] " << enemies[i]->getName() << endl; 
//				cin >> index;
//				cout << p1->getName() << " attack " << enemies[index - 1]->getName() << " !" << endl;
//				p1->SingularAttack(av, enemies[index - 1]);
//				break;
//			case 2:
//				cout << "Healing " << p1->getName() << "!" << endl;
//				p1->HealTarget(hv, p1);
//				break;
//			case 3:
//				p1->ShowInfo();
//				cout << endl;
//				cout << "Taking info of enemies..." << endl;
//				cout << "###########################################" << endl;
//				for (int i = 0; i < 2; i++)
//					if (enemies[i] != NULL){
//						enemies[i]->ShowInfo();
//						cout << endl;
//					}
//				cout << "###########################################" << endl;
//				break;
//			case 4:
//				cout << "Skipping turn..." << endl;
//				break;
//			case 5:
//				cout << "Quitting..." << endl;
//				quit = true;
//				break;
//			default:
//				break;
//		}
//		if (quit){
//			ingame = false;
//			break;
//		}
//		if (boss != NULL){
//			cout << boss->getName() << " is attacking! " << endl;
//			if (rand() % 11 == 7)
//				boss->SpecialAttack(av,p1);
//			else
//				boss->SingularAttack(av, p1);
//		}
//		if (foe != NULL){
//			cout << foe->getName() << " is attacking! " << endl;		
//			foe->SingularAttack(av, p1);
//		}
//		
//		for (int i = 0; i < 2; i++)
//			if (!enemies[i]->getState()){
//				delete enemies[i];
//				enemies[i] = NULL;
//			}
//			else
//				ingame = true;
//		
//		if (!p1->getState()){
//			delete p1;
//			p1 = NULL;
//			ingame = false;
//			cout << "GAME OVER!" << endl;
//		}
//	}
	
	delete iv;
	delete av;
	delete hv;
	
	for (int i = 0; i < 2; i++)
		if (enemies[i] != NULL)
			delete enemies[i];
	
	if (p1 != NULL)
		delete p1;
	
	return 0;
}
