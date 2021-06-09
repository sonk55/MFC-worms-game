// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

#define radius 20
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define MOVERANGE 15
#define BODYGAP 15

enum item{PLUS_BODY,MINUS_BODY,SIZE_UP,SIZE_DOWN,INVI};
enum GRADE {OPENING,PLAY,ENDING,RANKING};

#define MOVE 0
#define CREATECOIN 1
#define INVISIBLE 2
#define MAGNET 3
#define	REDUCE_HP 4

#define PER_PLUS 
#define PER_MINUS
#define PER_INVISIBLE

//#define N_WEAPON 9
//#define N_INVINCIBILITY 8
//#define N_PASS_OBSTRUCTION 7
//#define N_RESET_BODY 6
//#define N_INVISIBLE 5
//#define N_SPEED_UP 4
#define N_MAGNET 3
#define N_INVISIBLE 2
#define N_MINUS 1
#define N_PLUS 0

#define DURATION_TIME 30000

#define MAX_LEN 60

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#endif //PCH_H
