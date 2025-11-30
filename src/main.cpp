#include <iostream>
#include <windows.h>
#include "../include/rpg.h"

using namespace GameManager;

int main() {
    //유니코드로 출력 설정(안하면 한글 깨짐)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Player player;
    Enemy enemy[3]; 
    enemyLocationInit(enemy[0], enemy[1], enemy[2]);
    
    printTutorial();
    while(1) {
        printMap(player, enemy[0], enemy[1], enemy[2]);
        while(1) {
            player.move();
            ifGameClear(player);
            //ifBattleStart(player, enemy[0], enemy[1], enemy[2]);
            printMap(player, enemy[0], enemy[1], enemy[2]);
        }
    }

    return 0;
}