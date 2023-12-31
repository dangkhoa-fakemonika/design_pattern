#include "Crafting.cpp"
#include "Visitor.cpp"
#include "Entity.cpp"
#include "Combat.cpp"

int main(){
	srand(time(NULL));
	string nametemp;
	cout << "Enter your name: ";
	getline(cin, nametemp);
	
	Player *p1 = new Player(nametemp, 20000, 9000);
	Player *p2 = new Player(nametemp + "'s healer", 70000, 400);
	
	vector<Entity*> players;
	players.push_back(p1);
	players.push_back(p2);

	Game maingame;
	maingame.setGold(200000);
	int options;
	while (true){
		cout << endl << "[=================================================]" << endl;
		cout << "[1] FIGHT!!! | [2] Shop n' craft | [3] Quit" << endl;
		cout << "Select option: ";
		cin >> options;
		cout << "[=================================================]" << endl;
		if (options == 1)
			maingame.Combat(players);
		else if (options == 2)
			maingame.ShopnCraft(p1);
		else if (options == 3)
			break;
		else
			cout << "Invalid option.";
	}
	
	delete p1;
	delete p2;
	
	return 0;
}
