#include "pch.h"
#include "tipsware.h"

#define MAX_COUNT   100   // 저장할 사각형의 최대 개수

struct AppData // 프로그램에서 사용할 내부 데이터
{
    POINT start_pos;  // 시작 점을 기억할 변수
    char is_clicked;  // 마우스 클릭 여부를 저장할 변수 (1이면 클릭, 0이면 해제)
    int r_count; // 현재 저장한 사각형의 개수
    RECT r_list[MAX_COUNT]; // 저장한 사각형 좌표 목록
};

// 마우스 왼쪽 버튼이 눌러졌을 때 호출되는 함수를 정의한다!
void OnLButtonDown(int a_mixed_key, POINT a_pos)
{
    AppData* p_data = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.

    if (p_data->is_clicked == 0) { // 마우스가 클릭이 안된 상태인지 체크한다.
        p_data->is_clicked = 1;  // 마우스를 클릭 상태로 설정한다.
        p_data->start_pos = a_pos; // 새로운 사각형의 시작 점을 저장한다.
    }
}

// 저장된 사각형들을 모두 다시 그리는 함수!
void DrawRectList(AppData* ap_data)
{
    Clear();  // 화면을 지운다.
    RECT* p = ap_data->r_list;  // 사각형 좌표 목록의 시작 주소를 얻는다.

    // 포인터를 사용해서 저장된 사각형 좌표로 사각형을 하나씩 그린다.
    for (int i = 0; i < ap_data->r_count; i++, p++) {
        Rectangle(p->left, p->top, p->right, p->bottom);
        //Rectangle(ap_data->r_list[i].left, ap_data->r_list[i].top,ap_data->r_list[i].right, ap_data->r_list[i].bottom);
        //위 구문은 구조체를 배열구문으로 쓰고 for문을 돌게 되면, 결국은 숨겨진 +i가 4번 돌아가는 것이라 비효율적이다.
        //따라서 RECT포인터를 하나 선언해서 
    }
}

// 마우스 왼쪽 버튼이 눌렀다가 해제 되었을 때 호출되는 함수를 정의한다!
void OnLButtonUp(int a_mixed_key, POINT a_pos)
{
    AppData* p_data = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.

    if (p_data->is_clicked == 1) { // 마우스가 클릭된 상태인지 체크한다.
        p_data->is_clicked = 0; // 마우스를 클릭 해제 상태로 설정한다.
        if (p_data->r_count < MAX_COUNT) { // 최대 저장 개수를 체크한다.
            // 현재 시작 점과, 끝점을 사각형 목록에 추가한다.
            p_data->r_list[p_data->r_count].left = p_data->start_pos.x;
            p_data->r_list[p_data->r_count].top = p_data->start_pos.y;
            p_data->r_list[p_data->r_count].right = a_pos.x;
            p_data->r_list[p_data->r_count].bottom = a_pos.y;
            p_data->r_count++;  // 저장된 사각형의 개수를 증가시킨다.
        }
        DrawRectList(p_data);  // 저장된 사각형을 다시 그린다.
        ShowDisplay(); // 정보를 윈도우에 출력한다. 메시지 처리 함수(Handler)에서도 구성된 그림을 화면에 출력하기 위해 꼭 써줘야한다
    }
}

// 마우스가 이동될 때마다 호출되는 함수를 정의한다!
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
    AppData* p_data = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.

    if (p_data->is_clicked == 1) {  // 마우스가 클릭된 상태인지 체크한다.
        DrawRectList(p_data); // 저장된 사각형을 다시 그린다.
        // 현재 편집중인 사각형을 그린다.
        Rectangle(p_data->start_pos.x, p_data->start_pos.y, a_pos.x, a_pos.y);
        ShowDisplay(); // 정보를 윈도우에 출력한다.
    }
}

// 마우스 왼쪽 버튼 누르거나, 해제하거나 이동할 때 호출될 함수들을 등록한다!
MOUSE_MESSAGE(OnLButtonDown, OnLButtonUp, OnMouseMove)//바로 위 라인 주석대로 3가지를 적을 수 있다. 

int main()
{
    AppData data = { {0, 0}, 0, 0 };  // 프로그램이 내부적으로 사용할 메모리를 선언한다.
    SetAppData(&data, sizeof(AppData)); // 지정한 변수를 내부 데이터로 저장한다.

    SelectPenObject(RGB(0, 0, 255), 3);  // 파랑색이고 굵기가 3인 선 속성을 사용한다.
    SelectStockObject(NULL_BRUSH);  // 사각형 내부를 채우지 않겠다고 설정한다.

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
