

#include "pch.h"
#include "tipsware.h"

#define X_COUNT     19      // X축으로 그려질 줄의 개수
#define Y_COUNT     19      // Y축으로 그려질 줄의 개수
#define GRID_SIZE   20      // 사각형의 폭과 높이에 대한 크기

struct AppData  // 프로그램에서 사용할 내부 데이터
{
    char state[Y_COUNT][X_COUNT]; // 각 교차점의 상태(0:비어있음, 1:검은색 돌, 2:흰색 돌)
    char step;  // 검은색 돌(0) 또는 흰색 돌(1)을 놓을 것인지 저장하는 변수
};

// 마우스 왼쪽 버튼이 눌러졌을 때 호출되는 함수를 정의한다!
void OnLButtonDown(int a_mixed_key, POINT a_pos)
{
    // 폭과 높이가 GRID_SIZE 크기인 격좌 좌표로 변환한다.
    unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE;
    // 프로그램의 내부 데이터 주소를 가져온다. 2차원 배열의 주소를 받는다!
    AppData* p_data = (AppData*)GetAppData();

    // x는 0 ~ (X_COUNT-1) 사이의 값을 가져야 유효한 값이고
    // y는 0 ~ (Y_COUNT-1) 사이의 값을 가져야 유효한 값입니다.
    // 그리고 state[y][x] 값이 0인 경우에만 돌을 놓을수 있다
    if (x < X_COUNT && y < Y_COUNT && !p_data->state[y][x]) {
        // step 값이 0이면 state에 1을 대입하고 1이면 2를 대입한다.
        // 흰돌 또는 검은 돌이 놓여졌음을 설정한다.
        p_data->state[y][x] = p_data->step + 1;

        // state 값에 따라 흰색 또는 검은색 원을 그리기 위해 색상을 테이블로 만든다.
        COLORREF fill_color[2] = { RGB(0, 0, 0), RGB(255, 255, 255) };
        // state[y][x]의 값이 1이면 검은색 돌을 2이면 흰색 돌을 그린다.
        Ellipse(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1,
            RGB(0, 0, 0), fill_color[p_data->state[y][x] - 1]);

        // step 값을 토글(0이면1, 1이면 0)한다.
        p_data->step = !p_data->step;

        ShowDisplay(); // 정보를 윈도우에 출력한다.
    }
}

// 마우스 왼쪽 버튼 누를 때 호출될 함수를 등록한다!
MOUSE_MESSAGE(OnLButtonDown, NULL, NULL)

int main()
{
    AppData data;  // 프로그램이 내부적으로 사용할 메모리를 선언한다.
    memset(&data, 0, sizeof(AppData));  // data 변수의 값을 모두 0으로 초기화한다.
    SetAppData(&data, sizeof(data));  // 지정한 변수를 내부 데이터로 저장한다.

    // 바둑판을 그린다. 사각형을 18*18 = 324개를 그린다.
    for (unsigned int y = 0; y < Y_COUNT - 1; y++) {
        for (unsigned int x = 0; x < X_COUNT - 1; x++) {
            Rectangle(GRID_SIZE / 2 + x * GRID_SIZE, GRID_SIZE / 2 + y * GRID_SIZE,
                GRID_SIZE / 2 + (x + 1) * GRID_SIZE + 1, GRID_SIZE / 2 + (y + 1) * GRID_SIZE + 1,
                RGB(0, 0, 0), RGB(244, 176, 77));
        }
    }
    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
