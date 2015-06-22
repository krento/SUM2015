/* FILENAME: UNIT.C
 * PROGRAMMER: LA1
 * PURPOSE: Animation unit handle module.
 * LAST UPDATE: 10.06.2015
 */

#include <string.h>

#include "anim.h"

/* Функция по-умолчанию инициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       la1UNIT *Uni;
 *   - указатель на контекст анимации:
 *       la1ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID LA1_AnimUnitInit( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitInit' function */

/* Функция по-умолчанию деинициализации объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       la1UNIT *Uni;
 *   - указатель на контекст анимации:
 *       la1ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID LA1_AnimUnitClose( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitClose' function */

/* Функция по-умолчанию обновления межкадровых параметров объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       la1UNIT *Uni;
 *   - указатель на контекст анимации:
 *       la1ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID LA1_AnimUnitResponse( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitResponse' function */

/* Функция по-умолчанию построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       la1UNIT *Uni;
 *   - указатель на контекст анимации:
 *       la1ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID LA1_AnimUnitRender( la1UNIT *Uni, la1ANIM *Ani )
{
} /* End of 'LA1_AnimUnitRender' function */

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (la1UNIT *) указатель на созданный объект анимации.
 */
la1UNIT * LA1_AnimUnitCreate( INT Size )
{
  la1UNIT *Uni;

  if (Size < sizeof(la1UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* заполняем поля по-умолчанию */
  Uni->Size = Size;
  Uni->Init = LA1_AnimUnitInit;
  Uni->Close = LA1_AnimUnitClose;
  Uni->Response = LA1_AnimUnitResponse;
  Uni->Render = LA1_AnimUnitRender;
  return Uni;
} /* End of 'LA1_AnimUnitCreate' function */
                              
/* END OF 'UNIT.C' FILE */