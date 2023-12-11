#pragma once
#include "Entity.h"

Entity::Entity(string name = "",int baseHP = 1000,int baseATK = 100)
: state(true), name(name), baseHP(baseHP), baseATK(baseATK), buffATK(0), currentHP(baseHP) {}

bool Entity::getState() { return state; }
string Entity::getName() { return name; }

void Entity::ResetState(){
	state = true;
	buffATK = 0;
	currentHP = baseHP;
}

Foe::Foe(string name = "", int baseHP = 1000, int baseATK = 100, int EXPdrop = 500): Entity(name, baseHP, baseATK), EXPdrop(EXPdrop) {}
int Foe::getATK() { return baseATK + buffATK; }
int Foe::getHP() { return baseHP; }

void Foe::ShowInfo(){
	cout << "<" << name << "> - [HP : " << currentHP << "/" << getHP() << "] [ATK : " << getATK() << "] [EXP : " << EXPdrop << "]";
}

NormalFoe::NormalFoe(string name = "", int baseHP = 1000, int baseATK = 100, int EXPdrop = 500) : Foe(name, baseHP, baseATK, EXPdrop){
	cout << "A wild " << name << " appeared!" << endl;
}

void NormalFoe::Interact(Visitor *v){
	v->InteractNormalFoe(this);
}

int NormalFoe::Attacked(int input_ATK){
	if (!state)
		return 0;
	currentHP -= input_ATK;
	cout << name << " lost " << input_ATK << " HP!" << endl;
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

void NormalFoe::Healed(int HPsource){
	cout << name << " is healing up!" << endl;
	currentHP += 100;
}

void NormalFoe::Flee(){
	cout << name << " has surrendered itself! " << endl;
	state = false;	
}

EpicFoe::EpicFoe(string name = "", int baseHP = 1000, int baseATK = 100, int EXPdrop = 0): Foe(name, baseHP, baseATK, EXPdrop), fury(0), fury_rate(20) {
	cout << name << " seeks it's prey!" << endl;
}

void EpicFoe::Interact(Visitor *v){
	v->InteractEpicFoe(this);
}

int EpicFoe::Attacked(int input_ATK){
	if (!state)
		return 0;
	currentHP -= int(input_ATK * 0.8);
	cout << name << " lost " << int(input_ATK * 0.8) << " HP!" << endl;
	fury += fury_rate;
	if (currentHP <= 0){
		if (fury > 100){
			currentHP = int(baseHP * 0.3) + 50;
			fury_rate /= 4;
			fury = 0;
		}
		else{
			currentHP = 0;
			state = false;
			cout << name << " has been defeated!" << endl;
			return max(EXPdrop - input_ATK / 100, 300);
		}
	}
}

void EpicFoe::Healed(int HPsource){
	cout << name << " is healing up!" << endl;
	currentHP += 100;
}

BossFoe::BossFoe(string name = "", int baseHP = 1000, int baseATK = 100, int EXPdrop = 0): Foe(name, baseHP, baseATK, EXPdrop), progress(0) {
	cout << "Crumble before " << name << " !!!!!!" << endl; 
}

void BossFoe::Interact(Visitor *v){
	v->InteractBossFoe(this);
}

int BossFoe::Attacked(int input_ATK){
	if (!state)
		return 0;
	currentHP -= int(input_ATK * 0.6);
	cout << name << " lost " << int(input_ATK * 0.6) << " HP!" << endl;
	if (currentHP <= 0){
		if (progress < 3){
			baseHP += baseHP / 10;
			currentHP = baseHP / 3;
			buffATK += 100;
			cout << name << " has became stronger!" << endl;
			progress++;
		}
		else{
			currentHP = 0;
			state = false;
			cout << name << " has fallen!" << endl;
			return max(EXPdrop - input_ATK / 100, 300);
		}
	}
}

void BossFoe::Healed(int HPsource){
	cout << name << " is regenerating it's health back!" << endl;
	currentHP += baseHP * 0.2 + 20;
}

Player::Player(string name = "", int baseHP = 15000, int baseATK = 250): Entity(name, baseHP, baseATK), itemsATK(0), itemsHP(0), total_gold(0) {
	cout << name << " joins combat!" << endl;
}

Player::~Player(){
	
}

unordered_map<Item*, int>* Player::getInventory(){return &inventory;}
int Player::getATK(){
	return baseATK + buffATK + itemsATK;
}
int Player::getHP(){return baseHP + itemsHP;}
void Player::Interact(Visitor *v){
	v->InteractPlayer(this);
}

void Player::ResetState(){
	itemsATK = 0;
	itemsHP = 0;
	state = true;
	for (const auto& it : inventory){
		itemsATK += it.first->getBonusATK() * it.second;
		itemsHP += it.first->getBonusHP() * it.second;
	}
	buffATK = 0;
	currentHP = baseHP + itemsHP;
}

int Player::Attacked(int input_ATK){
	if (!state)
		return 0;
	if (rand() % 10 == 7){
		cout << name << " dodged the attack!" << endl;
		return input_ATK / 2;
	}
	currentHP -= input_ATK/2;
	cout << name << " lost " << int(input_ATK/2) << " HP!" << endl;
	if (currentHP <= 0){
		currentHP = 0;
		state = false;
		cout << name << " has been knocked out!" << endl;
		return -100;
	}
	return input_ATK / 10;
}

void Player::Healed(int HPsource){
	cout << name << " is healing..." << endl;
	buffATK += 10;
	currentHP += int((HPsource - currentHP) * 0.3) + 100;
	cout << name << " healed " << int((HPsource - currentHP) * 0.3) + 100 << " HP and buffed itself!" << endl;
}

void Player::ShowInfo(){
	getATK();
	cout << "<" << name << "> - [HP : " << currentHP << "/" << getHP() << "] [ATK : " << baseATK << "(+ " << buffATK + itemsATK << ")]";
}
