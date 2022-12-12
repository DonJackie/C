#include "pch.h"
#include "tipsware.h"

NOT_USE_MESSAGE; //이 프로그램은 특별한 메시지를 사용하지 않는다.

int main()
{
    int data = 5;
    // 앞으로 출력될 문자열은 파랑색을 사용하게 설정한다.
    SetTextColor(RGB(0, 0, 255));

    // data 변수의 값을 10진 정숫값으로 화면에 출력한다.
    printf(100, 50, "data : %d", data);
    printf(100, 70, "결과를 출력했습니다!");

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
