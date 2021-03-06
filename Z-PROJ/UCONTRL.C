/* FILENAME: UCONTRL.C
 * PROGRAMMER: LA1
 * PURPOSE: Control unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <stdio.h>

#include "anim.h"

typedef struct tagla1UNIT_CTRL
{
  LA1_UNIT_BASE_FIELDS;
  HFONT hFnt; 
  /*VEC 
    CPos,
    Pos;

  la1GEOM H, A;
  FLT Head, om, V;  */

} la1UNIT_CTRL;

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitInit( la1UNIT_CTRL *Uni, la1ANIM *Ani )
{
  Uni->hFnt = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE,
    FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH, "Bookman Old Style");

  LA1_AnimFlipFullScreen();


} /* End of 'LA1_AnimUnitInit' function */

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitClose( la1UNIT_CTRL *Uni, la1ANIM *Ani )
{
  DeleteObject(Uni->hFnt);
} /* End of 'LA1_AnimUnitClose' function */

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitResponse( la1UNIT_CTRL *Uni, la1ANIM *Ani )
{


  if (Ani->Keys[VK_ESCAPE])
    LA1_AnimDoExit();
  if (Ani->KeysClick['F'])
    LA1_AnimFlipFullScreen();
  if (Ani->KeysClick['P'])
    LA1_AnimSetPause(!Ani->IsPause);
 /*
  Dir = MatrMulMatr3(VecSet(0, 0, 1), MatrRotatedY(Uni->Head);
  At = VecSubVec(Pos, VecMulNum(Dir, 3);
  At.Y += 1.5;

  Move = VecSubVec(At, Uni->CPos);
  Uni->CPos = VecAddVec(Uni->CPos, VecMulNum(Move, 0.1 * Ani->GlobalDeltaTime);

  LA1_RndMatrView = MatrView(Uni->CPos,
                             Uni->Pos,
                             VecSet(0, 1, 0));






     */



} /* End of 'LA1_AnimUnitResponse' function */

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitRender( la1UNIT_CTRL *Uni, la1ANIM *Ani )
{
  HFONT hFntOld = SelectObject(Ani->hDC, Uni->hFnt);
  static DBL count = 30;
  static CHAR Buf[1000];

  count += Ani->GlobalDeltaTime;
  if (count > 1)
  {
    count = 0;
    sprintf(Buf, "FPS: %.3f", Ani->FPS);
    SetWindowText(Ani->hWnd, Buf);
  }


 

  /*
  SetTextColor(Ani->hDC, RGB(255, 255, 255));
  SetBkMode(Ani->hDC, TRANSPARENT);
  rc.left = 0;
  rc.top = 0;
  rc.right = Ani->W;
  rc.bottom = Ani->H;
  DrawText(Ani->hDC, Buf,
    sprintf(Buf,
      "FPS: %.3f\n"
      "J: %i %i %i, POV:%i\n"
      "%.5f %.5f %.5f %.5f %.5f %.5f",
      Ani->FPS,
      Ani->JButs[0], Ani->JButs[1], Ani->JButs[2], Ani->JPOV,
      Ani->JX, Ani->JY, Ani->JZ, Ani->JR, Ani->JU, Ani->JV),
    &rc,
    DT_TOP | DT_LEFT);
  SelectObject(Ani->hDC, hFntOld);
  */
} /* End of 'LA1_AnimUnitRender' function */

/* 
 * 
 * 
 * 
 */
la1UNIT * LA1_UnitControlCreate( VOID )
{
  la1UNIT_CTRL *Uni;

  if ((Uni = (VOID *)LA1_AnimUnitCreate(sizeof(la1UNIT_CTRL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)LA1_AnimUnitInit;
  Uni->Close = (VOID *)LA1_AnimUnitClose;
  Uni->Response = (VOID *)LA1_AnimUnitResponse;
  Uni->Render = (VOID *)LA1_AnimUnitRender;
  return (la1UNIT *)Uni;
} /* End of 'LA1_UnitBallCreate' function */

/* END OF 'UCONTRL.C' FILE */