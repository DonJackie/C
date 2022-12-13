
#include "pch.h"
#include "tipsware.h"

#define X_COUNT     6      // X축으로 그려질 사각형의 개수
#define Y_COUNT     3      // Y축으로 그려질 사각형의 개수
#define GRID_SIZE  50      // 사각형의 폭과 높이에 대한 크기

// 사각형의 선택 상태가 저장된 2차원 배열 형식의 메모리 주소를 ap_data 포인터로 받는다.
// 실제로 사용되는 메모리 구조는 char state[Y_COUNT][X_COUNT]이다.
void DrawRect(char(*ap_data)[X_COUNT])
{
    // 사각형의 채우기 색상이 0일때와 1일때 달라지기 때문에 색상을 테이블로 만든다.
    COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };
    // ap_data[y][x]의 값이 0이면 어두운 색상으로 사각형을 그리고
    // 1이면 밝은 색상으로 사각형을 그린다.
    for (unsigned int y = 0; y < Y_COUNT; y++) {
        for (unsigned int x = 0; x < X_COUNT; x++) {
            Rectangle(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1,
                RGB(0, 200, 255), fill_color[ap_data[y][x]]);
        }
    }
    ShowDisplay(); // 정보를 윈도우에 출력한다.
}

// 마우스 왼쪽 버튼이 눌러졌을 때 호출되는 함수를 정의한다!
void OnLButtonDown(int a_mixed_key, POINT a_pos)
{
    // 폭과 높이가 GRID_SIZE 크기인 격좌 좌표로 변환한다.
    unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE;

    // x는 0 ~ (X_COUNT-1) 사이의 값을 가져야 유효한 값이고
    // y는 0 ~ (Y_COUNT-1) 사이의 값을 가져야 유효한 값입니다.
    if (x < X_COUNT && y < Y_COUNT) {
        // 프로그램의 내부 데이터 주소를 가져온다. 2차원 배열의 주소를 받는다!
        char(*p)[X_COUNT] = (char(*)[X_COUNT])GetAppData();
        // 선택한 사각형의 상태를 0이면 1, 1이면 0으로 변경한다.
        p[y][x] = !p[y][x]; // (*(p + y))[x] = !(*(p + y))[x];
        // p가 가리키는 메모리를 사용해서 전체 사각형을 다시 그린다.
        DrawRect(p);
    }
}

// 마우스 왼쪽 버튼 누를 때 호출될 함수를 등록한다!
MOUSE_MESSAGE(OnLButtonDown, NULL, NULL)

int main()
{
    // 2차원 배열을 모두 0으로 초기화한다.
    char state[Y_COUNT][X_COUNT] = { {0, }, };
    SetAppData(state, sizeof(state));  // 지정한 변수를 내부 데이터로 저장한다.

    // state 배열에 저장된 정보를 가지고 전체 사각형을 다시 그린다.
    DrawRect(state);
    return 0;
}
