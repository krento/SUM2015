/* FILENAME: ANIM.H
 * PROGRAMMER: LA1
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 11.06.2015
 */                                                               

#ifndef __ANIM_H_
#define __ANIM_H_

#include "render.h"

/* ������������ ���������� ��������� �������� */
#define LA1_MAX_UNITS 3000

/* ���������� ���� �������� �������� "������" */
typedef struct tagla1UNIT la1UNIT;

/* ��������� �������� ��������� �������� */
typedef struct
{
  HWND hWnd;          /* ���� ������ */
  INT W, H;           /* ������ ���� ������ */
  HDC hDC;            /* �������� ���� ������ */
  HGLRC hGLRC;        /* �������� ���������� */

  /* ������ ��������� �������� � �� ���������� */
  la1UNIT *Units[LA1_MAX_UNITS]; 
  INT NumOfUnits;

  /* ���������� ������������� */
  DBL
    Time,            /* ����� � �������� �� ������ �������� */
    GlobalTime,      /* ����� -"-, �� ��� ����� */
    DeltaTime,       /* ����������� ����� � �������� */
    GlobalDeltaTime, /* ����������� ����� � �������� ��� ����� */
    FPS;             /* ���������� ������ � ������� */
  BOOL
    IsPause;         /* ���� ����� */

  /* ���������� ����� */
  BYTE
    Keys[256],       /* �������� ������ ���������� � ���� */
    KeysOld[256],    /* �������� ������ �� ���������� ����� */
    KeysClick[256];  /* ����� ������������ ������� */
  INT
    MsDeltaX, MsDeltaY, /* ������������� ���������� ������� ���� */
    MsX, MsY,        /* ���������� ���������� ������� ���� */
    MsWheel;         /* ��������� ������ ���� */
  BYTE
    JButs[32],       /* �������� ������ ��������� */
    JButsOld[32],    /* �������� ������ ��������� �� ���������� ����� */
    JButsClick[32],  /* ����� ������������ ������� ������ ��������� */
    JPOV;            /* ������������� POV - 0..8 */
  DBL
    JX, JY, JZ, JR, JU, JV; /* ��� ��������� (-1.0 .. 1.0*/
  DBL
    AX, AY, AZ; 
  DBL
    TX, TY, TZ; 
} la1ANIM;

/* ��������� �������� �������� */
extern la1ANIM LA1_Anim;

/* ������� ���� ������� ��������:
 * - ������ ��������� ��� ������������
 *     INT Size;
 * - ������������� ��������:
 *     INT Id;
 * - ��������� �� ������� �������������
 *     VOID (*Init)( la1UNIT *Unit, la1ANIM *Ani );
 * - ��������� �� ������� ���������������
 *     VOID (*Close)( la1UNIT *Unit, la1ANIM *Ani );
 * - ��������� �� ������� ���������� ����������� ����������
 *     VOID (*Response)( la1UNIT *Unit, la1ANIM *Ani );
 * - ��������� �� ������� ����������
 *     VOID (*Render)( la1UNIT *Unit, la1ANIM *Ani );
 */
#define LA1_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( la1UNIT *Unit, la1ANIM *Ani );       \
  VOID (*Close)( la1UNIT *Unit, la1ANIM *Ani );      \
  VOID (*Response)( la1UNIT *Unit, la1ANIM *Ani );   \
  VOID (*Render)( la1UNIT *Unit, la1ANIM *Ani )

/* ������� ��� ������� �������� */
struct tagla1UNIT
{
  LA1_UNIT_BASE_FIELDS;
};

/* ���������� ���������� - ������� ��������� ������ ���� */
extern INT LA1_MouseWheel;

/* ������� ������������� ��������.
 * ���������:
 *   - ���������� ����:
 *       HWND hWnd;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
BOOL LA1_AnimInit( HWND hWnd );

/* ������� ��������������� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID LA1_AnimClose( VOID );

/* ������� ��������� ��������� ������� ������� ������.
 * ���������:
 *   - ����� ������ ������� ������:
 *       INT W, H;
 * ������������ ��������: ���.
 */
VOID LA1_AnimResize( INT W, INT H );

/* ������� ���������� ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID LA1_AnimRender( VOID );

/* ������� ������ ����� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID LA1_AnimCopyFrame( VOID );

/* ������� ���������� � ������� ������� ��������.
 * ���������:
 *   - ����������� ������ ��������:
 *       la1UNIT *Unit;
 * ������������ ��������: ���.
 */
VOID LA1_AnimAddUnit( la1UNIT *Unit );

/* ������� ������������ �/�� �������������� ������
 * � ������ ���������� ���������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID LA1_AnimFlipFullScreen( VOID );

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (la1UNIT *) ��������� �� ��������� ������ ��������.
 */
la1UNIT * LA1_AnimUnitCreate( INT Size );

/* ������� ������ �� ��������.
 * ���������: ���.
 * ������������ ��������: ���.
 */
VOID LA1_AnimDoExit( VOID );

/* ������� ��������� ����� ��������.
 * ���������:
 *   - ���� �����:
 *       BOOL NewPauseFlag;
 * ������������ ��������: ���.
 */
VOID LA1_AnimSetPause( BOOL NewPauseFlag );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */