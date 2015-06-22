/* FILENAME: ANIM.H
 * PROGRAMMER: LA1
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 11.06.2015
 */                                                               

#ifndef __ANIM_H_
#define __ANIM_H_

#include "render.h"

/* Максимальное количество элементов анимации */
#define LA1_MAX_UNITS 3000

/* Объявление типа объектов анимации "вперед" */
typedef struct tagla1UNIT la1UNIT;

/* Структура хранения контекста анимации */
typedef struct
{
  HWND hWnd;          /* Окно вывода */
  INT W, H;           /* Размер окна вывода */
  HDC hDC;            /* Контекст окна вывода */
  HGLRC hGLRC;        /* Контекст рендеринга */

  /* Массив элементов анимации и их количество */
  la1UNIT *Units[LA1_MAX_UNITS]; 
  INT NumOfUnits;

  /* Подсистема синхронизации */
  DBL
    Time,            /* время в секундах со старта анимации */
    GlobalTime,      /* время -"-, но без паузы */
    DeltaTime,       /* межкадровое время в секундах */
    GlobalDeltaTime, /* межкадровое время в секундах без паузы */
    FPS;             /* количество кадров в секунду */
  BOOL
    IsPause;         /* флаг паузы */

  /* Подсистема ввода */
  BYTE
    Keys[256],       /* Сотояние клавиш клавиатуры и мыши */
    KeysOld[256],    /* Сотояние клавиш на предыдущем кадре */
    KeysClick[256];  /* Флаги однократного нажатия */
  INT
    MsDeltaX, MsDeltaY, /* Относительные координаты курсора мыши */
    MsX, MsY,        /* Абсолютные координаты курсора мыши */
    MsWheel;         /* Состояние колеса мыши */
  BYTE
    JButs[32],       /* Сотояние кнопок джойстика */
    JButsOld[32],    /* Сотояние кнопок джойстика на предыдущем кадре */
    JButsClick[32],  /* Флаги однократного нажатия кнопок джойстика */
    JPOV;            /* Переключатель POV - 0..8 */
  DBL
    JX, JY, JZ, JR, JU, JV; /* Оси джойстика (-1.0 .. 1.0*/
  DBL
    AX, AY, AZ; 
  DBL
    TX, TY, TZ; 
} la1ANIM;

/* Системный контекст анимации */
extern la1ANIM LA1_Anim;

/* Базовые поля объекта анимации:
 * - размер структуры для наследования
 *     INT Size;
 * - идентификатор объеткта:
 *     INT Id;
 * - указатель на функцию инициализации
 *     VOID (*Init)( la1UNIT *Unit, la1ANIM *Ani );
 * - указатель на функцию деинициализации
 *     VOID (*Close)( la1UNIT *Unit, la1ANIM *Ani );
 * - указатель на функцию обновления межкадровых параметров
 *     VOID (*Response)( la1UNIT *Unit, la1ANIM *Ani );
 * - указатель на функцию построения
 *     VOID (*Render)( la1UNIT *Unit, la1ANIM *Ani );
 */
#define LA1_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( la1UNIT *Unit, la1ANIM *Ani );       \
  VOID (*Close)( la1UNIT *Unit, la1ANIM *Ani );      \
  VOID (*Response)( la1UNIT *Unit, la1ANIM *Ani );   \
  VOID (*Render)( la1UNIT *Unit, la1ANIM *Ani )

/* Базовый тип объекта анимации */
struct tagla1UNIT
{
  LA1_UNIT_BASE_FIELDS;
};

/* Глобальная переменная - счетчик прокрутки колеса мыши */
extern INT LA1_MouseWheel;

/* Функция инициализации анимации.
 * АРГУМЕНТЫ:
 *   - дескриптор окна:
 *       HWND hWnd;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL LA1_AnimInit( HWND hWnd );

/* Функция деинициализации анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimClose( VOID );

/* Функция обработки изменения размера области вывода.
 * АРГУМЕНТЫ:
 *   - новый размер области вывода:
 *       INT W, H;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimResize( INT W, INT H );

/* Функция построения кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimRender( VOID );

/* Функция вывода кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimCopyFrame( VOID );

/* Функция добавления в систему объекта анимации.
 * АРГУМЕНТЫ:
 *   - добавляемый объект анимации:
 *       la1UNIT *Unit;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimAddUnit( la1UNIT *Unit );

/* Функция переключения в/из полноэкранного режима
 * с учетом нескольких мониторов.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimFlipFullScreen( VOID );

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (la1UNIT *) указатель на созданный объект анимации.
 */
la1UNIT * LA1_AnimUnitCreate( INT Size );

/* Функция выхода из анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimDoExit( VOID );

/* Функция установки паузы анимации.
 * АРГУМЕНТЫ:
 *   - флаг паузы:
 *       BOOL NewPauseFlag;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_AnimSetPause( BOOL NewPauseFlag );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */