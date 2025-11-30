#include <iostream>
#include "../include/rpg.h"

using namespace GameManager;

Character::Character() {
    this->hp = 50;
    this->atk = 10;
    this->def = 100;
}

void Character::setAtk(int newAtk) {
    this->atk = newAtk;
}

void Character::setDef(int newDef) {
    this->def = newDef;
}

void Character::setHp(int atk, int def) {
    if (def < 0) def = 0;
    if (def > 100) def = 100;

    double reduction = def / 100.0;          // 방어율 계산
    double damage = atk * (1.0 - reduction); // 실제 입는 피해
    this->hp -= static_cast<int>(damage);

    //체력이 0 이하일 때의 오류처리
    if (this->hp < 0) {
        this->hp = 0;
    }

    //변화된 스텟 출력
    std::cout << "[DEBUG] 공격력: " << atk
        << " | 방어율: " << def
        << "% | 실제 피해: " << static_cast<int>(damage)
        << " | 남은 HP: " << this->hp << std::endl;
}


