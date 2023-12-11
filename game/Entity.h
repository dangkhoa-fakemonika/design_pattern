#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Visitor.h"

using namespace std;

class Player; class NormalFoe; class EpicFoe; class BossFoe; class Entity;

class Visitor{
public:
	virtual void InteractPlayer(Player *p) = 0;
	virtual void InteractNormalFoe(NormalFoe *nf) = 0;
	virtual void InteractEpicFoe(EpicFoe *ef) = 0;
	virtual void InteractBossFoe(BossFoe *bf) = 0;
};

class AttackVisitor : public Visitor{
private:
	Entity* Attacker;
	int ATK;
	int BattlePoints;
public:
	AttackVisitor();
	void SetAttacker(Entity *e);
	int GetBattlePoints();
	void InteractPlayer(Player *p);
	void InteractNormalFoe(NormalFoe *nf);
	void InteractEpicFoe(EpicFoe *ef);
	void InteractBossFoe(BossFoe *bf);
};

class HealVisitor : public Visitor{
private:
	Entity* Healer;
	int HP;
public:
	HealVisitor();
	void SetHealer(Entity *e);
	void InteractPlayer(Player *p);
	void InteractNormalFoe(NormalFoe *nf);
	void InteractEpicFoe(EpicFoe *ef);
	void InteractBossFoe(BossFoe *bf);
};

class InfoVisitor : public Visitor{
public:
	InfoVisitor();
	void InteractPlayer(Player *p);
	void InteractNormalFoe(NormalFoe *nf);
	void InteractEpicFoe(EpicFoe *ef);
	void InteractBossFoe(BossFoe *bf);
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
	Entity(string name, int baseHP, int baseATK);
	bool getState();
	string getName();
	virtual int getATK() = 0;
	virtual int getHP() = 0;
	virtual void Interact(Visitor *v) = 0;
	virtual int Attacked(int input_ATK) = 0;
	virtual void Healed(int HPsource) = 0;
	virtual void SingularAttack(AttackVisitor *atv, Entity *target) = 0;
	virtual void HealTarget(HealVisitor *hlv, Entity *target) = 0;
	virtual void ShowInfo() = 0;
};

class Foe : public Entity{
protected:
	int EXPdrop;
public:
	Foe(string name, int baseHP, int baseATK, int EXPdrop);
	int getATK();
	int getHP();
	void SingularAttack(AttackVisitor *atv, Entity *target);
	void HealTarget(HealVisitor *hlv, Entity *target);
	void ShowInfo();
};

class NormalFoe : public Foe{
public:
	NormalFoe(string name, int baseHP, int baseATK, int EXPdrop);
	void Interact(Visitor *v);
	int Attacked(int input_ATK);
	void Healed(int HPsource);
	void Flee();
};

class EpicFoe : public Foe{
private:
	int fury;
	int fury_rate;
public:
	EpicFoe(string name, int baseHP, int baseATK, int EXPdrop);
	void Interact(Visitor *v);
	int Attacked(int input_ATK);
	void Healed(int HPsource);
	void SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2);
};

class BossFoe : public Foe{
private:
	int progress;
public:
	BossFoe(string name, int baseHP, int baseATK, int EXPdrop);
	void Interact(Visitor *v);
	int Attacked(int input_ATK);
	void Healed(int HPsource);
	void SpecialAttack(AttackVisitor *atv, Entity *tar1, Entity *tar2);
};

class Player : public Entity{
private:
	unordered_map<Item*, int> inventory;
	int itemsATK;
	int itemsHP;
	int total_gold;
public:
	Player(string name, int baseHP, int baseATK);
	~Player();
	unordered_map<Item*, int>* getInventory(); 
	int getATK();
	int getHP();
	void Interact(Visitor *v);
	int Attacked(int input_ATK);
	void SingularAttack(AttackVisitor *atv, Entity *target);
	void HealTarget(HealVisitor *hlv, Entity *target);
	void Healed(int HPsource);
	void ShowInfo();
};

