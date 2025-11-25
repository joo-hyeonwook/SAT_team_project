#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h> // 키보드 입력을 즉시 받기 위한 함수 (_kbhit, _getch)가 있는 헤더
#include<windows.h> // 콘솔 화면을 조작하는 기능 (Sleep, SetConsoleCursorPosition)을 위한 헤더

using namespace std;

// --- 콘솔 화면 조작 함수 ---
void goToXY(int x, int y)
{
    // COORD는 Windows에서 좌표를 저장하는 구조체
    COORD coord;
    coord.X = x; // x 좌표
    coord.Y = y; // y 좌표

    // 이 함수가 실제로 커서를 움직이는 Windows API 함수
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// --- Player 클래스: 플레이어의 설계도 ---
// 변수와 그 변수를 다루는 함수인 메서드를 하나로 묶어놓은 틀
class Player
{
private:
    int x, y;      // 현재 x, y 좌표
    char avatar;

public:
    Player(int initialX, int initialY, char playerAvatar)
        : x(initialX), y(initialY), avatar(playerAvatar) {
        // 여기서 : x(initialX)는 멤버 변수 x에 초기값 initialX를 대입한다는 뜻
    }

    // 플레이어의 위치를 키 입력에 따라 바꾸고 화면에 다시 그리는 함수 (메서드)
    void updatePosition(char input)
    {
        // 1. 이전 위치 지우기
        goToXY(x, y); // 현재 위치로 커서를 옮기고
        cout << " ";  // 공백으로 덮어써서 캐릭터를 지움

        // 2. 키 입력에 따라 위치 변경
        switch (input)
        {
        case 'W': case 'w': // 위
            y--;
            break;
        case 'S': case 's': // 아래
            y++;
            break;
        case 'A': case 'a': // 왼쪽
            x--;
            break;
        case 'D': case 'd': // 오른쪽
            x++;
            break;
        }

        // 3. 새 위치에 플레이어 그리기
        goToXY(x, y);  // 바뀐 위치로 커서를 옮기고
        cout << avatar; // 캐릭터 모양을 출력
    }

    // 현재 위치를 외부에서 읽을 수 있도록 해주는 함수 Getter
    int getX() const { return x; }
    int getY() const { return y; }
};

// --- 메인 함수: 프로그램의 시작점 ---
int main()
{
    // 1. 콘솔 커서 숨기기 설정
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE; // 커서를 안 보이게 설정
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // 2. Player 객체 생성
    // 이 순간 Player(10, 5, 'P') 생성자가 호출됨
    Player player(10, 5, 'P');
    char key = 0;

    // 게임 시작 안내 메시지 출력
    cout << "WASD 키로 움직이세요. Z를 누르면 종료합니다." << endl;

    // 3. 메인 게임 루프 (무한 반복)
    while (key != 'z' && key != 'Z')
    { // Z를 누르기 전까지 계속 반복
        if (_kbhit())
        { // 키보드가 눌렸는지 확인하는 함수
            key = _getch(); // 눌린 키를 즉시 가져오는 함수

            // Player 객체의 updatePosition 메서드를 호출하여 위치를 업데이트
            player.updatePosition(key);
        }

        // CPU 과부하를 막기 위해 잠시 쉼
        Sleep(20);
    }

    // 4. 프로그램 종료 전 커서 다시 보이게 설정
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return 0;
}
