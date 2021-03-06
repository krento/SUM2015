/* FILENAME: UNIT.C
 * PROGRAMMER: LA1
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <string.h>

#include "anim.h"

/* ������� ��-��������� ������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       la1UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       la1ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID LA1_AnimUnitInit( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitInit' function */

/* ������� ��-��������� ��������������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       la1UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       la1ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID LA1_AnimUnitClose( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitClose' function */

/* ������� ��-��������� ���������� ����������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       la1UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       la1ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID LA1_AnimUnitResponse( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitResponse' function */

/* ������� ��-��������� ���������� ������� ��������.
 * ���������:
 *   - ��������� �� "����" - ��� ������ ��������:
 *       la1UNIT *Uni;
 *   - ��������� �� �������� ��������:
 *       la1ANIM *Ani;
 * ������������ ��������: ���.
 */
static VOID LA1_AnimUnitRender( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitRender' function */

/* ������� �������� ������� ��������.
 * ���������:
 *   - ������ ��������� ������� ��������:
 *       INT Size;
 * ������������ ��������:
 *   (la1UNIT *) ��������� �� ��������� ������ ��������.
 */
la1UNIT * LA1_AnimUnitCreate( INT Size )
{
  la1UNIT *Uni;

  if (Size < sizeof(la1UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* ��������� ���� ��-��������� */
  Uni->Size = Size;
  Uni->Init = LA1_AnimUnitInit;
  Uni->Close = LA1_AnimUnitClose;
  Uni->Response = LA1_AnimUnitResponse;
  Uni->Render = LA1_AnimUnitRender;
  return Uni;
} /* End of 'LA1_AnimUnitCreate' function */
                              
/* END OF 'UNIT.C' FILE */