#pragma once  //include 시 #include "../include/rpg.h" 사용할 것(상대경로)

//출구 위치
#define EXIT_LOCATION_X 4
#define EXIT_LOCATION_Y 0

class Character {
    protected:
    int locationX, locationY;
    int hp;//05 고정
    int atk;//10 고정
    int def;//100 고정
    public:
    Character();
    int getLocationX() {return this->locationX;}
    int getLocationY() {return this->locationY;}
    int getHp() {return this->hp;}
    int getAtk() {return this->atk;}
    int getDef() {return this->def;}
    void setAtk(int newAtk);// atk를 newAtk로 수정
    void setDef(int newDef);// def를 newAef로 수정
    void setHp(int atk = 10, int def = 100);//hp를newHp로 수정 

};

//전방 선언
class Enemy;

class Player : public Character {
    public:
    Player();
    void move();
    int getPlayerAction(); //플레이어 행동 선택 후 리턴
    void playerAttack(Enemy& refEnemy); 
    //주사위 값에 따른 피해량만큼 적 체력 차감

    void playerDefend();//주사위 값에 따른 방어력만큼 플레이어가 받는 피해 경감
    bool run();//주사위 값에 따른 성공여부에 따라 전투 종료 혹은 행동 무효화
};

class Enemy : public Character {
    public:
    Enemy();
    void setLocation(int x = 0, int y = 0); //매개변수로 위치 변경
    int getEnemyAction(); //적 행동 무작위 결정 후 리턴
    void enemyAttack(Player& refPlayer);
    //주사위 값에 따른 피해량만큼 플레이어 체력 차감
    
    void enemyDefend();//주사위 값에 따른 방어력만큼 플레이어가 받는 피해 경감
};

namespace GameManager {
    void enemyLocationInit(Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC);
    //각 Enemy 객체의 위치를 비교해 겹치는 경우 하나의 위치를 수정

    void printTutorial();//튜토리얼 출력
    void printMap(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC);
    //맵과 플레이어, 출구 위치(P, E) 출력 

    int getDice();//주사위 함수, 2~12 사이의 무작위 정수 반환
    void ifBattleStart(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC);
    // 플레이어와 적 객체의 위치 비교 후 플레이어와 적의 위치가 겹칠 시 전투 함수 호출
    //전투 함수는 플레이어와 위치가 겹치는 적을 참조 매개 변수로 함

    void battle(Player &refPlayer, Enemy &refEnemy);
    //둘 중 하나의 체력이 0이 될 때까지 플레이어와 적의 행동을 번갈아 선택 후 실행 

    void gameOver();//게임오버 메시지 출력 후 파일 종료
    void ifGameClear(Player &refPlayer);//플레이어의 위치에 따라 게임 클리어 여부를 판단
    void gameClear();//게임 클리어 메시지 출력 후 파일 종료
}