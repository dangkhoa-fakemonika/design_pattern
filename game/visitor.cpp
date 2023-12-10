#pragma once
#include "Visitor.h"

AttackVisitor::AttackVisitor() : Attacker(NULL), ATK(0), BattlePoints(0) {}

void AttackVisitor::SetAttacker(Entity *e = NULL){
	Attacker = e;
	if (e != NULL)
		ATK = Attacker->getATK();
	else
		ATK = 0;
}
void AttackVisitor::InteractPlayer(Player *p){
	BattlePoints += p->Attacked(ATK);
}
void AttackVisitor::InteractNormalFoe(NormalFoe *nf){
	BattlePoints += nf->Attacked(ATK);
}
void AttackVisitor::InteractEpicFoe(EpicFoe *ef){
	BattlePoints += ef->Attacked(ATK);
}
void AttackVisitor::InteractBossFoe(BossFoe *bf){
	BattlePoints += bf->Attacked(ATK);
}

HealVisitor::HealVisitor() : Healer(NULL), HP(0){}

void HealVisitor::SetHealer(Entity *e = NULL){
	Healer = e;
	if (e != NULL)
		HP = e->getHP();
	else
		HP = 0;
}
void HealVisitor::InteractPlayer(Player *p){
	p->Healed(HP);
}
void HealVisitor::InteractNormalFoe(NormalFoe *nf){
	nf->Healed(0);
}
void HealVisitor::InteractEpicFoe(EpicFoe *ef){
	ef->Healed(0);
}
void HealVisitor::InteractBossFoe(BossFoe *bf){
	bf->Healed(0);
}

InfoVisitor::InfoVisitor(){}
void InfoVisitor::InteractPlayer(Player *p){
	p->ShowInfo();
}
void InfoVisitor::InteractNormalFoe(NormalFoe *nf){
	nf->ShowInfo();
}
void InfoVisitor::InteractEpicFoe(EpicFoe *ef){
	ef->ShowInfo();
}
void InfoVisitor::InteractBossFoe(BossFoe *bf){
	bf->ShowInfo();
}
