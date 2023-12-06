#include <iostream>
#include <string>

using namespace std;

class Player;
class Foe;
class Terrain;

class Visitor{
public:
	virtual void InteractPlayer(Player *p) = 0;
	virtual void InteractFoe(Foe *f) = 0;
	virtual void InteractTerrain(Terrain *t) = 0;
};

class Element{
protected:
	bool state;
public:
	Element(): state(true) {}
	virtual ~Element(){}
	virtual void Interact(Visitor *v) = 0;
};
class Entity: public Element{
protected:
	int HP;
	int ATK;
public:
	Entity(int HP = 1, int ATK = 1) : HP(HP), ATK(ATK), Element(){}
	int getATK() {return ATK;}
};

class Player: public Entity{
private:
	string name;
	int EXPLVL;
public:
	Player(string n = "Bob", int HP = 1000, int ATK = 100, int exp = 0): Entity(HP, ATK), name(n), EXPLVL(exp) {}
	void ShowStatusPlayer() const{
		cout << "Player's name: " << name << endl;
		cout << "Current level: " << EXPLVL << endl;
		cout << "HP: " << HP << ", ATK: " << ATK << endl;
	}
	
	void Interact(Visitor *v) {
		v->InteractPlayer(this);
	}
	
	int DamagePlayer(int input_ATK) {
		if (!state)
			return 0;
		HP -= input_ATK;
		if (HP <= 0){
			HP = 0;
			state = false;
			return EXPLVL / 3;
		}
		
		return 0;
	}
};

class Foe: public Entity{
private:
	string type;
public:
	Foe(string t = "Basic Slime", int HP = 100, int ATK = 10) : Entity(HP, ATK), type(t){}
	void ShowStatusFoe() const{
		cout << "Foe: " << type << endl;
		cout << "HP: " << HP << ", ATK: " << ATK << endl;
	}
	
	void Interact(Visitor *v) {
		v->InteractFoe(this);
	}
	
	int DamageFoe(int input_ATK) {
		if (!state)
			return 0;
		HP -= input_ATK;
		if (HP <= 0){
			HP = 0;
			state = false;
			return 10;
		}
		return 0;
	}
};

class Terrain : public Element{
private:
	string type;
	string drops[3];
	int drops_num[3];
public:
	Terrain(string t = "House"): type(t), Element() {}
	void BuildTerrain(string mat1, int count1, string mat2 = "Nothing", int count2 = 0, string mat3 = "Nothing", int count3 = 0){
		drops[0] = mat1;
		drops_num[0] = count1;
		drops[1] = mat2;
		drops_num[1] = count2;
		drops[2] = mat3;
		drops_num[2] = count3;
	}
	
	void ShowInfoTerrain() {
		cout << type << ": " << endl;
		for (int i = 0; i < 3; i++)
			cout << drops[i] << ": " << drops_num[i] << endl;
	}
	void Interact(Visitor *v) {
		v->InteractTerrain(this);
	}
	
	int DamageTerrain(int input_ATK) {
		if (!state)
			return 0;
		if (input_ATK < 300){
			cout << "Can't destroy!";
			return 0;
		}
		else{
			state = false;
			return (drops_num[0] + drops_num[1] + drops_num[2]) * 5;
		}
	}
};


class ScanVisitor: public Visitor{
public:
	void InteractPlayer(Player *p) {
		cout << "Player info: " << endl;
		p->ShowStatusPlayer();
	}
	void InteractFoe(Foe *f) {
		cout << "Enemy info: " << endl;
		f->ShowStatusFoe();
	}
	void InteractTerrain(Terrain *t) {
		cout << "Current building: " << endl;
		t->ShowInfoTerrain();
	}
};

class AttackVisitor: public Visitor{
private:
	Entity *pe;
public:
	AttackVisitor(Entity *pe_ = NULL) : pe(pe_) {}
	void InteractPlayer(Player *p) {
		cout << "Fighiting Player:... " << endl;
		p->DamagePlayer(pe->getATK());
	}
	void InteractFoe(Foe *f) {
		cout << "Fighting Enemy:... " << endl;
		f->DamageFoe(pe->getATK());
	}
	void InteractTerrain(Terrain *t) {
		cout << "Destroying building:... " << endl;
		t->DamageTerrain(pe->getATK());
	}
};

void Demo(Element **list, int n, Visitor *v){
	for (int i = 0; i < n; i++){
		list[i]->Interact(v);
		cout << endl;
	}
}

int main(){
	Player *P1 = new Player("Steve", 500, 200, 100);
	Player *P2 = new Player("Alex", 200, 100, 50);
	
	Foe *F1 = new Foe("Small Slime", 5, 5);
	Foe *F2 = new Foe("Mega Slime", 10000, 1000);
	
	Terrain *T = new Terrain("Average Wall");
	T->BuildTerrain("Brick", 2, "Steel", 2);
	
	Element *list[5] = {P1, P2, F1, F2, T}; 
	
	ScanVisitor *scv = new ScanVisitor;
	AttackVisitor *atv = new AttackVisitor(P1);
	
	cout  << endl << "=============================================================" << endl;
	
	Demo(list, 5, scv);
	
	cout  << endl << "=============================================================" << endl;
	
	Demo(list, 5, atv);
	
	cout  << endl << "=============================================================" << endl;
	
	Demo(list, 5, scv);
	
	cout  << endl << "=============================================================" << endl;
	
	
	for (int i = 0; i < 5; i++)
		delete list[i];
	
	delete scv;
	delete atv;
	
	return 0;
}
