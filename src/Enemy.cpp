#include <iostream>
#include <random>
#include "../include/rpg.h"

using namespace GameManager;

Enemy::Enemy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 4);
    this->locationX = dist(gen);
    this->locationY = dist(gen);

    //Player 초기 위치와 겹치는 경우 예외처리 
    if((this->locationX == 0)&&(this->locationY == 0)) {
        this->locationX = dist(gen);
        this->locationY = dist(gen);
    }

    //출구 위치와 겹치는 경우 예외처리
    if((this->locationX == EXIT_LOCATION_X)&&(this->locationY == EXIT_LOCATION_Y)) {
        this->locationX = dist(gen);
        this->locationY = dist(gen);
        
    }
}
void Enemy::setLocation(int x, int y) {
    this->locationX = x;
    this->locationY = y;
}
int Enemy::getEnemyAction() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 2);
    return dist(gen);
}

void Enemy::enemyAttack(Player& refPlayer, int playerDef) {
    std::cout << "적이 공격했다!\n";
    int dice = getDice();
    if (dice < 5) {
        std::cout << "실패!\n";
        refPlayer.setHp(0, playerDef);
    }
    else if (dice < 9) {
        std::cout << "성공!\n";
        refPlayer.setHp(this->atk, playerDef);
    }
    else {
        std::cout << "대성공!\n";
        refPlayer.setHp(this->atk * 2, playerDef);
    }
}

void Enemy::enemyDefend() {
    std::cout << "적이 방어했다!\n";
    int dice = getDice();
    if (dice < 5) {
        std::cout << "실패! (방어율 0%)\n";
        this->def = 0;
    }
    else if (dice < 9) {
        std::cout << "성공! (방어율 50%)\n";
        this->def = 50;
    }
    else {
        std::cout << "대성공! (방어율 100%)\n";
        this->def = 100;
    }
}