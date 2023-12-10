#pragma once
#include "Visitor.h"
#include "Entity.h"

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

void Player::HealPlayer(HealVisitor *hlv, Entity *target){
	hlv->SetHealer(this);
	target->Interact(hlv);
}

