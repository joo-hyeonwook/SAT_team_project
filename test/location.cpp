#include <iostream> 
#include <vector>
#include <cstdlib> // enemy의 위치를 계속 바꿔야 하므로 rnad()와 srand()를 사용해야함 따라서 rand()와 srand()의 정보가 들어있는 헤더파일을 이용함.
#include <ctime> // 현재 시간을 초 단위로 가져오는 함수가 있는 헤더파일을 사용 --> 이걸 통해서 srand()를 사용해서 매번 무작위로 위치 선언 가능

using namespace std;

// 5x5 맵 크기
const int MAP_SIZE = 5; // const는 절대 바꿀 수 없는 상수를 의미하므로 값이 절대 변하지 않는 Map size에 5를 대입한다.

// Player 클래스
class Player {
public:
    int x, y; // 2차원 배열에서는 [x][y]를 의미하는 x,y 변수 선언

    Player() {
        // 플레이어는 항상 (0,0)에서 시작
        x = 0;
        y = 0;
    }
};

// Enemy 클래스
class Enemy {
public:
    int x, y;

    Enemy() {
        // 랜덤 위치 생성
        // 단, (0,0)과 (4,4)는 피해야 한다.
        do {
            // rand()는 0부터 일반적으로 32767 사이의 정수 중 하나를 무작위로 반환해주므로 우리가 결국 5x5인 맵 안에서 
            // 놀아야하므로 %(나머지 정리)를 MAP_SIZE 만큼 해주면 결과적으로 나올 수 있는 값은 0~4까지임을 알 수 있다.
            x = rand() % MAP_SIZE;
            y = rand() % MAP_SIZE;
        } while ((x == 0 && y == 0) || (x == 4 && y == 4)); 
        // 그리고 만약 [0][0]이나 [4][4]에서 생성되면 다시 랜덤 위치 생성
        // do-while 쓴 이유는 적어도 처음 한번은 실행되야하므로 사용해줬다.
    }
};

// 맵 출력 함수
void printMap(Player& p, Enemy& e) { //player 객체와 enemy 객체의 참조로 받는다.
    // 5x5 행렬 생성함수
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (p.x == i && p.y == j) // 우리가 설정해놓은 player의 위치와 같으면 P를 맵에 출력
                cout << "P ";
            else if (e.x == i && e.y == j)
                cout << "E ";  // 우리가 설정해놓은 enemy의 위치와 같으면 E를 맵에 출력
            else
                cout << ". "; // 둘 다 아닌경우 그 위치를 점으로 맵에 출력
        }
        cout << endl;
    }
}

// 예시용 메인 함수 실제로 필요한건 위의 코드임 여기는 그냥 어떤식으로 작동하는지 보여주고 싶어서 쓴 코드
int main() {
    srand(time(NULL));

    Player player;
    Enemy enemy;

    cout << "초기 맵 상태:\n";
    printMap(player, enemy);

    // 플레이어 움직임 예시
    cout << "player가 움직일 위치를 설정해주세요" << endl;
    cin >> player.x >> player.y;
    cout << endl <<"플레이어가 (" << player.x << "," << player.y << ")" << "로 이동" << endl;
    player.x; player.y;
    printMap(player, enemy);

    return 0;
}
