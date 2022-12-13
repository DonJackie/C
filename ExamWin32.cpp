#include "pch.h"
#include "tipsware.h"

// 마우스 왼쪽 버튼이 눌러졌을 때 호출되는 함수를 정의한다!
void OnLButtonDown(int a_mixed_key, POINT a_pos)
{
    // 출력된 사각형은 일정한 크기를 가지기 때문에 사각형이 시작된 위치를 (0, 0)으로
    // 계산되도록 마우스의 x 좌표는 20을 빼고 y 좌표는 60을 뺍니다. 그리고 사각형의
    // 폭과 높이가 균일하게 60이기 때문에 마우스 좌표를 60으로 나누면 가로, 세로 60 크기의
    // 사각형 인덱스를 구할 수 있습니다. 즉, 6개의 사각형 중에 첫 번째 사각형은 x가 0이고
    // y도 0이며 두 번째 사각형은 x가 1이고 y가 0이 된다는 뜻입니다.
    unsigned int x = (unsigned int)(a_pos.x - 20) / 60, y = (unsigned int)(a_pos.y - 60) / 60;

    // 따라서 x는 0 ~ 5사이의 값을 가져야 유효한 값이고 y는 0만 유효한 값이 됩니다.
    if (x < 6 && y < 1) {
        char* p_data = (char*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.



        // 선택한 사각형의 상태를 0이면 1, 1이면 0으로 변경한다.
        p_data[x] = !p_data[x]; // *(p_data + x) = !*(p_data + x);
        // 사각형의 테두리 색상이 0일때와 1일때 달라지기 때문에 색상을 테이블로 만든다.
        COLORREF border_color[2] = { RGB(0, 100, 200), RGB(0, 200, 255) };
        // 사각형의 채우기 색상이 0일때와 1일때 달라지기 때문에 색상을 테이블로 만든다.
        COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };
        // p_data[i]의 값이 0이면 어두운 색상의 테두리와 채우기 색상으로 사각형을 그리고
        // 1이면 밝은 색상의 테두리와 채우기 색상으로 6개의 사각형을 그린다.
        for (int i = 0; i < 6; i++) {
            Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, border_color[p_data[i]], fill_color[p_data[i]]);
        }
        /*
        // 조건문을 사용해서 사각형의 색상을 다르게 표현하는 예시
        for (int i = 0; i < 6; i++) {
            if(p_data[i]) Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255));
            else Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
        }
        */
        ShowDisplay(); // 정보를 윈도우에 출력한다.
    }
}

// 마우스 왼쪽 버튼 누를 때 호출될 함수를 등록한다!
MOUSE_MESSAGE(OnLButtonDown, NULL, NULL)

int main()
{
    char state[6] = { 0, };
    SetAppData(state, sizeof(state));  // 지정한 변수를 내부 데이터로 저장한다.

    // (10, 10) 좌표에 파란색으로 안내 메시지를 출력한다!
    TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~!");

    // 수평 방향으로 6개의 파란색 사각형을 나열한다.
    for (int i = 0; i < 6; i++) {
        Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
    }

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
