#include "pch.h"
#include "tipsware.h"

NOT_USE_MESSAGE; //이 프로그램은 특별한 메시지를 사용하지 않는다.

int main()
{
    // 2단 ~ 9단까지 출력!
    for (int dan = 2; dan <= 9; dan++) {
        // 각 단의 1 ~ 9까지 출력
        for (int i = 1; i <= 9; i++) {
            // 단이 증가하면 X축 방향으로 이동하기 위해 X 좌표에 dan을 사용했고
            // 각 단에서 곱하는 값이 증가하면 아래쪽으로 출력하기 위해
            // Y 좌표에 i를 사용했습니다.
            printf(10 + (dan - 2) * 90, 10 + 20 * i, "%d * %d = %d", dan, i, dan * i);
        }
    }
    
    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
