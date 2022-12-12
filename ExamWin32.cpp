#include "pch.h"
#include "tipsware.h"

NOT_USE_MESSAGE; //이 프로그램은 특별한 메시지를 사용하지 않는다.

int main()
{
    // 굵기가 3인 파랑색 선 속성을 사용한다.
    SelectPenObject(RGB(0, 0, 255), 3);

    // 선을 네 번 그려서 사각형을 그린다.
    Line(10, 10, 100, 10);
    Line(100, 10, 100, 100);
    Line(100, 100, 10, 100);
    Line(10, 100, 10, 10);

    // 굵기가 3이고 점선이면서 색상이 파랑색인 선 속성을 사용한다.
    // 선 굵기가 2이상이면 PS_GEOMETRIC 속성을 함께 사용해야 합니다.
    SelectPenObject(RGB(255, 0, 0), 3, PS_DOT | PS_GEOMETRIC);

    // 선 그리기의 기준점 설정
    MoveTo(210, 10);
    // 선을 네 번 그려서 사각형을 그린다.
    LineTo(300, 10);
    LineTo(300, 100);
    LineTo(210, 100);
    LineTo(210, 10);

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
