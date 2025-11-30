#include <iostream>
#include <limits> // std::numeric_limits 사용하기 위해서 추가
#include "../include/rpg.h"

using namespace GameManager;

Player::Player() {
    this->locationX = 0;
    this->locationY = 4;
}

void Player::move() {
    char playerInput;
    std::cout << "움직일 방향 입력 (w/a/s/d): ";
    std::cin >> playerInput;
    switch(playerInput) {
        case 'w':
        case 'W':
            //위로 한칸 움직임 (y 좌표 감소)
            if (this->locationY <= 0) {
                std::cout << "이 방향으로 움직일 수 없습니다" << std::endl;
                break;
            }
            --this->locationY;
            break;
        case 'a':
        case 'A':
            //왼쪽으로 한칸 움직임 (x 좌표 감소)
            if (this->locationX <= 0) {
                std::cout << "이 방향으로 움직일 수 없습니다" << std::endl;
                break;
            }
            --this->locationX;
            break;
        case 's':
        case 'S':
            //아래로 한칸 움직임 (y 좌표 증가)
            if (this->locationY >= 4) {
                std::cout << "이 방향으로 움직일 수 없습니다" << std::endl;
                break;
            }
            ++this->locationY;
            break;
        case 'd':
        case 'D':
            //오른쪽으로 한칸 움직임 (x 좌표 증가)
            if (this->locationX >= 4) {
                std::cout << "이 방향으로 움직일 수 없습니다" << std::endl;
                break;
            }
            ++this->locationX;
            break;
        default:
           // 잘못된 입력 받은 경우 오류메시지 출력 후 오류처리, 입력 다시받기
            std::cout << "잘못된 입력입니다. (w/a/s/d 중 하나를 입력하세요.)" << std::endl;
            // 입력 스트림 오류 상태 초기화 및 버퍼 비우기
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // 루프가 계속되어 입력을 다시 받음
            break;
    }
//Player 이동한 좌표 출력
    std::cout << "플레이어가 (" << this->locationX << ", " 
    << this->locationY << ")로 이동했습니다." << std::endl;
}
int Player::getPlayerAction() {
    int action;
    while (true) {
        std::cout << "\n행동 입력 (1:공격, 2:방어, 3:도망): ";
        std::cin >> action;
        if ((action == 1)||(action == 2)||(action == 3)) {
            return action;
        }
        else {
            return 0;
        }
    }
} //플레이어 행동 선택
void Player::playerAttack(Enemy& refEnemy, int enemyDef) {
    std::cout << "플레이어가 공격했다!\n";
    int dice = getDice();
    if (dice < 5) {
        std::cout << "실패!\n";
        refEnemy.setHp(0, enemyDef);
    }
    else if (dice < 9) {
        std::cout << "성공!\n";
        refEnemy.setHp(atk, enemyDef);
    }
    else {
        std::cout << "대성공!\n";
        refEnemy.setHp(atk * 2, enemyDef);
    }
}
void Player::playerDefend() {
    std::cout << "플레이어가 방어했다!\n";
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
bool Player::run() {
    int dice = getDice();
    if (dice <= 7) {
        return false;
    }
    else {
        return true;
    }
}