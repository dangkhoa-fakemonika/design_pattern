#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class BossFoe;
class NormalFoe;
class EpicFoe;
class Player;
//
class AttackVisitor;
class HealVisitor;
class InfoVisitor;
//class SpecialAttackVisitor;

class Visitor{
public:
	virtual void InteractPlayer(Player *p) = 0;
	virtual void InteractNormalFoe(NormalFoe *nf) = 0;
	virtual void InteractEpicFoe(EpicFoe *ef) = 0;
	virtual void InteractBossFoe(BossFoe *bf) = 0;
};

class Entity{
protected:
	string name;
	int baseHP;
	int baseATK;
	bool state; // Alive = true
	int buffATK;
	int currentHP;
public:
	Entity() : state(true) {}
	bool getState(){return state;}
	virtual int getATK() = 0;
	virtual int getHP() = 0;
	virtual ~Entity(){}
	virtual void Interact(Visitor *v) = 0;
	virtual int Attacked(int input_ATK) = 0;
	virtual void Healed(int HPsource) = 0;
	virtual void SingularAttack(AttackVisitor *atv, Entity *target) = 0;
	virtual void HealTarget(HealVisitor *hlv, Entity *target) = 0;
	virtual void ShowInfo() = 0;
};

class AttackVisitor : public Visitor{
private:
	Entity* Attacker;
	int ATK;
	int BattlePoints;
public:
	void SetAttacker(Entity *e = NULL){
		Attacker = e;
		if (e != NULL)
			ATK = Attacker->getATK();
		else
			ATK = 0;
	}
	void InteractPlayer(Player *p){
		BattlePoints += p->Attacked(ATK);
	}
	void InteractNormalFoe(NormalFoe *nf){
		BattlePoints += nf->Attacked(ATK);
	}
	void InteractEpicFoe(EpicFoe *ef){
		BattlePoints += ef->Attacked(ATK);
	}
	void InteractBossFoe(BossFoe *bf){
		BattlePoints += bf->Attacked(ATK);
	}
};

class HealVisitor : public Visitor{
private:
	Entity *Healer;
	int HP;
public:
	void SetHealer(Entity *e = NULL){
		Healer = e;
		if (e != NULL)
			HP = e->getHP();
		else
			HP = 0;
	}
	void InteractPlayer(Player *p){
		p->Healed(HP);
	}
	void InteractNormalFoe(NormalFoe *nf){
		nf->Healed(0);
	}
	void InteractEpicFoe(EpicFoe *ef){
		ef->Healed(0);
	}
	void InteractBossFoe(BossFoe *bf){
		bf->Healed(0);
	}
};

class InfoVisitor{
public:
	void InteractPlayer(Player *p){
		p->ShowInfo();
	}
	void InteractNormalFoe(NormalFoe *nf){
		nf->ShowInfo();
	}
	void InteractEpicFoe(EpicFoe *ef){
		ef->ShowInfo();
	}
	void InteractBossFoe(BossFoe *bf){
		bf->ShowInfo();
	}
};

class Foe : public Entity{
protected:
	int EXPdrop;
public:
	Foe()
	int getATK();
	int getHP();
	void SingularAttack(AttackVisitor *atv, Entity *target);
	void HealTarget(HealVisitor *hlv, Entity *target);
	void ShowInfo();
};

class NormalFoe : public Foe{
public:
	void Interact(Visitor *v){
		v->InteractNormalFoe(this);
	}
	
	int Attacked(int input_ATK){
		if (!state)
			return 0;
		currentHP -= input_ATK;
		if (currentHP <= 0){
			currentHP = 0;
			state = false;
			cout << name << "has been defeated!" << endl;
			return max(EXPdrop - input_ATK / 100, 100);
		}
		else if (currentHP == int(baseHP * 0.15)){
			if (rand() % 10 % 3 == 0){
				Flee();
				return EXPdrop;
			}
		}	
	}
	
	void Healed(int HPsource){
		cout << name << " is healing up!" << endl;
		currentHP += 100;
	}
	
	void Flee(){
		cout << name << "has surrendered itself! " << endl;
		state = false;	
	}
};

class EpicFoe : public Foe{
private:
	int fury;
	int fury_rate;
public:
	void Interact(Visitor *v){
		v->InteractEpicFoe(this);
	}
	
	int Attacked(int input_ATK){
		if (!state)
			return 0;
		currentHP -= int(input_ATK * 0.8);
		fury += fury_rate;
		if (currentHP <= 0){
			if (fury > 100){
				currentHP = int(baseHP * 0.3) + 50;
				fury_rate /= 10;
				fury = 0;
			}
			else{
				currentHP = 0;
				state = false;
				cout << name << "has been defeated!" << endl;
				return max(EXPdrop - input_ATK / 100, 300);
			}
		}
	}
	
	void Healed(){
		cout << name << " is healing up!" << endl;
		currentHP += 100;
	}
	
	void SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2 = NULL){
		atv->SetAttacker(this);
		buffATK -= 20;
		tar1->Interact(atv);
		if (!tar2)
			tar2->Interact(atv);
		buffATK += 20;
	}
};

class BossFoe : public Foe{
private:
	int progress;
public:
	void Interact(Visitor *v){
		v->InteractBossFoe(this);
	}
	
	int Attacked(int input_ATK){
		if (!state)
			return 0;
		currentHP -= int(input_ATK * 0.6);
		if (currentHP <= 0){
			if (progress < 3){
				baseHP += baseHP / 10;
				currentHP = baseHP / 3;
				buffATK += 100;
				cout << name << "has became stronger!" << endl;
				progress++;
			}
			else{
				currentHP = 0;
				state = false;
				cout << name << "has fallen!";
				return max(EXPdrop - input_ATK / 100, 300);
			}
		}
	}
	
	void Healed(int HPsource){
		cout << name << "is regenerating it's health back!" << endl;
		currentHP += baseHP * 0.2 + 20;
	}
	
	void SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2 = NULL){
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
};

class Player : public Entity{
private:
//	unordered_map<Item*, int> inventory;
	int item_slots;
	int itemsATK;
	int itemsHP;
public:
	int getATK(){return baseATK + buffATK + itemsATK;}
	int getHP(){return baseHP + itemsHP;}
	void Interact(Visitor *v){
		v->InteractPlayer(this);
	}
	
	int Attacked(int input_ATK){
		if (!state)
			return 0;
		if (rand() % 10 == 7){
			cout << name << "dodged the attack!" << endl;
			return input_ATK / 2;
		}
		currentHP -= input_ATK/2;
		if (currentHP <= 0){
			currentHP = 0;
			state = false;
			cout << name << "has fallen down!" << endl;
			return -100;
		}
		return input_ATK / 10;
	}
	
	void SingularAttack(AttackVisitor *atv, Entity *target){
		atv->SetAttacker(this);
		target->Interact(atv);
		if (target->getState() && (rand() % 20 == 0)){
			cout << "Bonus Attack!" << endl;
			target->Interact(atv);
		}
	}
	
	void HealPlayer(HealVisitor *hlv, Entity *target){
		hlv->SetHealer(this);
		target->Interact(hlv);
	}
	
	void Healed(int HPsource){
		cout << name << "is healing...";
		buffATK += 10;
		currentHP += int((HPsource - currentHP) * 0.3) ;
	}
	
	void ShowInfo(){
		cout << "<" << name << "> - [HP : " << getHP() << "] [ATK : " << getATK() << "]";
	}
};

int main(){
	
	return 0;
}
