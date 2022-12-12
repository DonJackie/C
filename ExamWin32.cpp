//https://www.mathsisfun.com/algebra/trig-sin-cos-tan-graphs.html
#include "pch.h"
#include "tipsware.h"
#include <math.h>   // sin, cos 함수 사용!

NOT_USE_MESSAGE; //이 프로그램은 특별한 메시지를 사용하지 않는다.

int main()
{
    // 회색 점선을 사용해서 X축과 Y축을 의미하는 선을 그린다!!
    Line(0, 100, 720, 100, RGB(200, 200, 200), 1, PS_DOT);  // 수평선 (X축)
    Line(360, 0, 360, 200);   // 수직선 (Y축)

    SelectPenObject(RGB(0, 0, 255), 3);  // 3 굵기의 파랑색 선을 사용!
    MoveTo(0, 100);  // sin 그래프의 시작 위치를 정한다.
    int y;
    for (int degree = 0; degree < 720; degree++) {   // 0도에서 720도까지 반복한다.
        // degree에 해당하는 sin 값을 구하고 sin 값을 100배 증가시켜서 사용한다.
        y = 100 - (int)(sin(degree * 3.141592 / 180) * 100);
        // 기준점에서 (degree, y) 좌표까지 선을 그린다.
        // 지금 그린 이 끝점이 다음 그리기의 기준점이 된다.
        LineTo(degree, y);
    }

    SelectPenObject(RGB(255, 0, 0), 3);  // 3 굵기의 빨강색 선을 사용!
    MoveTo(0, 0);  // cos 그래프의 시작 위치를 정한다.
    for (int degree = 0; degree < 720; degree++) {  // 0도에서 720도까지 반복한다.
        // degree에 해당하는 cos 값을 구하고 cos 값을 100배 증가시켜서 사용한다.
        y = 100 - (int)(cos(degree * 3.141592 / 180) * 100);
        // 기준점에서 (degree, y) 좌표까지 선을 그린다.
        LineTo(degree, y);
    }

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
