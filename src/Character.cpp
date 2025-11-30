#include <iostream>
#include "../include/rpg.h"

using namespace GameManager;

Character::Character() {
    this->hp = 50;
    this->atk = 10;
    this->def = 0;
}

void Character::setAtk(int newAtk) {
    this->atk = newAtk;
}

void Character::setDef(int newDef) {
    this->def = newDef;
}

void Character::setHp(int atk, int def) {
    //방어력이 0 이하 혹은 100 이상일 때의 오류처리
    if (def < 0) {
        def = 0;
    }
    if (def > 100) {
        def = 100;
    }

    //방어율과 실제 입는 피해 계산 후 체력 차감
    double reduction = def / 100.0;       
    double damage = atk * (1.0 - reduction);
    this->hp -= static_cast<int>(damage);

    //체력이 0 이하일 때의 오류처리
    if (this->hp < 0) {
        this->hp = 0;
    }

    
}


