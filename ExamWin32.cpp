#include "pch.h"
#include "tipsware.h"

struct AppData // 프로그램에서 사용할 내부 데이터
{
    POINT start_pos;  // 시작 점을 기억할 변수
    char is_clicked;  // 마우스 클릭 여부를 저장할 변수 (1이면 클릭, 0이면 해제)
};
//함수들의 독립성을 가지기 위해서 전역변수를 사용하는 것보다
//아래와 같이 포인터를 사용해야한다.
//전역변수를 최대한 쓰지 않는게 좋다

// 마우스 왼쪽 버튼이 눌러졌을 때 호출되는 함수를 정의한다!
void OnLButtonDown(int a_mixed_key, POINT a_pos)
{
    AppData* p_data_1 = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.
    //AppData는 사용자가 정한 이름이라 모르기 때문에
    //보관했던 GetAppdata 주소를 호출하면 void pointer로 반환되기 때문에, 
    //사용자가 만들었던 구조체로 casting(형변환)해서 사용해야한다

    if (p_data_1->is_clicked == 0) { // 마우스가 클릭이 안된 상태인지 체크한다.
        p_data_1->is_clicked = 1;  // 마우스를 클릭 상태로 설정한다.
        p_data_1->start_pos = a_pos; // 선 그리기의 시작 점을 저장한다.
    }
}

// 마우스 왼쪽 버튼이 눌렀다가 해제 되었을 때 호출되는 함수를 정의한다!
void OnLButtonUp(int a_mixed_key, POINT a_pos)
{
    AppData* p_data_3 = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.

    if (p_data_3->is_clicked == 1) { // 마우스가 클릭된 상태인지 체크한다.
        p_data_3->is_clicked = 0; // 마우스를 클릭 해제 상태로 설정한다.
        Line(p_data_3->start_pos.x, p_data_3->start_pos.y, a_pos.x, a_pos.y);  // 시작 점과 끝점을 연결하여 선을 그린다.  
        ShowDisplay(); // 정보를 윈도우에 출력한다.
    }
}

// 마우스가 이동될 때마다 호출되는 함수를 정의한다!
void OnMouseMove(int a_mixed_key, POINT a_pos)
{
    AppData* p_data_2 = (AppData*)GetAppData(); // 프로그램의 내부 데이터 주소를 가져온다.

    if (p_data_2->is_clicked == 1) {  // 마우스가 클릭된 상태인지 체크한다.
        Line(p_data_2->start_pos.x, p_data_2->start_pos.y, a_pos.x, a_pos.y); // 시작 점과 끝점을 연결하여 선을 그린다.
        p_data_2->start_pos = a_pos; // 현재 점을 다음 선의 시작 점으로 사용하기 위해 시작 점을 변경한다.
        ShowDisplay(); // 정보를 윈도우에 출력한다.
    }
}

// 마우스 왼쪽 버튼 누르거나, 해제하거나 이동할 때 호출될 함수들을 등록한다!
MOUSE_MESSAGE(OnLButtonDown, OnLButtonUp, OnMouseMove)

int main()
{
    AppData data = { {0, 0}, 0 };  // 프로그램이 내부적으로 사용할 메모리를 선언한다.
    SetAppData(&data, sizeof(AppData)); // 지정한 변수를 내부 데이터로 저장한다.

    SelectPenObject(RGB(0, 0, 255), 3);  // 파랑색이고 굵기가 3인 선 속성을 사용한다.
    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
