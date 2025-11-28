#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include "../include/rpg.h"

using namespace GameManager; 

void GameManager::enemyLocationInit(Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 4);
    if ((refEnemyA.getLocationX() == refEnemyB.getLocationX())&&(refEnemyA.getLocationY() == refEnemyB.getLocationY())) {
        refEnemyB.setLocation(dist(gen), dist(gen));
        while((refEnemyB.getLocationX() == 0)&&(refEnemyB.getLocationY() == 0)) {
            refEnemyB.setLocation(dist(gen), dist(gen));
        }
    }

    if ((refEnemyA.getLocationX() == refEnemyC.getLocationX())&&(refEnemyA.getLocationY() == refEnemyC.getLocationY())) {
         refEnemyC.setLocation(dist(gen), dist(gen));
         while((refEnemyC.getLocationX() == 0)&&(refEnemyC.getLocationY() == 0)) {
            refEnemyC.setLocation(dist(gen), dist(gen));
        }
    }

    if ((refEnemyC.getLocationX() == refEnemyB.getLocationX())&&(refEnemyC.getLocationY() == refEnemyB.getLocationY())) {
         refEnemyC.setLocation(dist(gen), dist(gen));
         while((refEnemyC.getLocationX() == 0)&&(refEnemyC.getLocationY() == 0)) {
            refEnemyC.setLocation(dist(gen), dist(gen));
        }
    }
}

void GameManager::printTutorial() {
    std::cout << "당신은 5X5타일로 이뤄진 맵에서 적들을 물리치며 출구를 찾아야 합니다." << std::endl
    << "맵 상에서 플레이어가 위치한 타일은 'P', 출구가 위치한 타일은 'E'로 표시됩니다." << std::endl
    << "당신은 위, 아래, 왼쪽, 오른쪽 중 한 방향을 골라 한 번에 한 칸씩 움직일 수 있습니다." << std::endl
    << "맵 곳곳에는 보이지 않는 적들이 숨어있습니다. 만약 적이 위치한 타일을 밟게 되면 전투가 시작됩니다." << std::endl
    << "전투 시, 당신은 적과 번갈아 행동을 수행하게 됩니다." << std::endl
    << "당신은 1, 2, 3 중 하나의 숫자를 입력해 각각 공격, 방어, 도망치기 중 하나의 행동을 수행할 수 있습니다." << std::endl
    << "적은 공격 혹은 방어를 무작위로 수행할 수 있습니다." << std::endl
    << "행동의 성공 여부는 6면체 주사위를 두 번 굴려 나온 눈금의 합에 의해 결정됩니다." << std::endl
    << "공격과 방어는 실패, 성공, 대성공의 결과가, 도망치기는 실패 혹은 성공의 결과를 가질 수 있습니다." << std::endl
    << "모든 행동은 실패 시 무효화되어 아무런 효과를 가지지 않습니다." << std::endl
    << "공격은 성공 시 10, 대성공 시 20의 피해를 적에게 줄 수 있습니다." << std::endl
    << "방어는 성공 시 50%, 대성공 시 100%의 받는 피해량 감소 효과가 부여됩니다." << std::endl
    << "도망치기는 성공 시 전투가 즉시 종료됩니다. 하지만 해당 타일에 적이 남아있으므로 동일한 타일을 또 밟게 되면 다시 전투가 시작됩니다. " << std::endl
    << "이제 게임이 시작됩니다. 행운을 빕니다!" << std::endl;
}

void GameManager::printMap(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC) {
    int playerLocationX = refPlayer.getLocationX();
    int playerLocationY = refPlayer.getLocationY();

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std:: cout << "[";

            //player 위치를 P로 표시
            if ((i == playerLocationX)&&(j == playerLocationY)) {
                std:: cout << "P";
            }

            //출구 위치를 E로 표시
            if ((i == EXIT_LOCATION_X)&&(j == EXIT_LOCATION_Y)) {
                std:: cout << "E";
            }

            std:: cout << " ";
            std:: cout << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int GameManager::getDice() {
    //1~6 사이의 정수를 두 번 생성해 더한 값을 리턴
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 6);
    return dist(gen) + dist(gen);
}

void GameManager::gameOver() {
    std::cout << "Game Over";
    for (int i = 5; i > 0; --i) {
        std::cout << i << "초 후 게임 종료" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    exit(1);
}
    
void GameManager::gameClear() {
    std::cout << "Game Clear!";
    for (int i = 5; i > 0; --i) {
        std::cout << i << "초 후 게임 종료" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    exit(1);
}

void GameManager::ifGameClear(Player &refPlayer) {
    int playerLocationX = refPlayer.getLocationX();
    int playerLocationY = refPlayer.getLocationY();

    if ((playerLocationX == EXIT_LOCATION_X)&&(playerLocationY == EXIT_LOCATION_Y)) {
        gameClear();
    }
}

void GameManager::battle(Player& refPlayer, Enemy& refEnemy) {
    if(refEnemy.getHp() <= 0) {
        std::cout << "이미 물리친 적입니다!" << std::endl;
        return;
    }
    std::cout << "전투 시작!"<< std::endl;

    int turn = 1;
    while (true) {
        std::cout << std::endl << "===== 턴 " << turn++ << " =====" << std::endl;
        std::cout << "플레이어 HP: " << refPlayer.getHp() << " | 적 HP: " << refEnemy.getHp() << std::endl;

        //  플레이어 턴
        std::cout << std::endl << ">> 플레이어의 차례!" << std::endl;
        int playerAction = refPlayer.getPlayerAction();

        //잘못된 입력 시 오류처리 및 버퍼 초기화 후 재입력
        if (playerAction == 0) {
            std::cout << "잘못된 입력입니다" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            bool wrongInput = true;
            while (wrongInput == true) {
                playerAction = refPlayer.getPlayerAction();
                if ((playerAction == 1)||(playerAction == 2)||(playerAction == 3)) {
                    break;
                }
            }
        }

        //Player, Enemy 능력치 저장
        int playerAtk = refPlayer.getAtk();
        int enemyAtk = refEnemy.getAtk();
        int playerDef = refPlayer.getDef();
        int enemyDef = refEnemy.getDef();

        //Player 행동
        if (playerAction == 1) {
            refPlayer.playerAttack(refEnemy, enemyDef);
        }
        else if (playerAction == 2) {
            refPlayer.playerDefend();
        }
        else if (playerAction == 3) {
            bool ifRun = refPlayer.run();
            if (ifRun == true) {
                std::cout << "도망치기에 성공했다!";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                return;
            }
        }

        // 전투 종료 체크
        if (refEnemy.getHp() <= 0) {
            std::cout << std::endl << "적을 물리쳤다!" << std::endl;
            break;
        }

        // 적 턴
        std::cout << std::endl << ">> 적의 차례!" << std::endl;
        int enemyAction = refEnemy.getEnemyAction();

        //Enemy 행동
        if (enemyAction == 1) { 
            refEnemy.enemyAttack(refPlayer, playerDef);
        }
        else if (enemyAction == 2) {
            refEnemy.enemyDefend();
        }

        // 전투 종료 체크
        if (refPlayer.getHp() <= 0) {
            std::cout << std::endl << "플레이어가 쓰러졌다..." << std::endl;
            gameOver();
            break;
        }

        // 턴 종료 시 상태 표시
        std::cout << std::endl << "[턴 종료] 플레이어 HP: " << refPlayer.getHp()
            << " | 적 HP: " << refEnemy.getHp() << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //공격력 초기화(오류 방지)
        refPlayer.setAtk(10);
        refEnemy.setAtk(10);
        
    }
}

void GameManager::ifBattleStart(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC) {
    //Player, Enemy 객체 위치 저장
    int playerLocationX = refPlayer.getLocationX();
    int playerLocationY = refPlayer.getLocationY();
    int enemyALocationX = refEnemyA.getLocationX();
    int enemyALocationY = refEnemyA.getLocationY();
    int enemyBLocationX = refEnemyB.getLocationX();
    int enemyBLocationY = refEnemyB.getLocationY();
    int enemyCLocationX = refEnemyC.getLocationX();
    int enemyCLocationY = refEnemyC.getLocationY();
    char enemyToBattle = '\0';

    if((playerLocationX == enemyALocationX)&&(playerLocationY == enemyALocationY)) {
       enemyToBattle = 'A';
    }
    else if((playerLocationX == enemyBLocationX)&&(playerLocationY == enemyBLocationY)) {
        enemyToBattle = 'B';
    }
    else if((playerLocationX == enemyCLocationX)&&(playerLocationY == enemyCLocationY)) {
        enemyToBattle = 'C';
    }

    switch(enemyToBattle) {
        case 'A': 
          battle(refPlayer, refEnemyA);
          break;

        case 'B': 
          battle(refPlayer, refEnemyB);
          break;

        case 'C':
          battle(refPlayer, refEnemyC);
          break;
        
        default:
          break;
    }
}


    