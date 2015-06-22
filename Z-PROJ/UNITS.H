/* FILENAME: UNITS.H
 * PROGRAMMER: LA1
 * PURPOSE: Animation units samples declaration module.
 * LAST UPDATE: 10.06.2015
 */                           

#ifndef __UNITS_H_
#define __UNITS_H_

#include "def.h"

/* Функция создания объекта анимации "управление".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (la1UNIT *) указатель на созданный объект анимации.
 */
la1UNIT * LA1_UnitControlCreate( VOID );

/* Функция создания объекта анимации "модель".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (la1UNIT *) указатель на созданный объект анимации.
 */
la1UNIT * LA1_UnitModelCreate( VOID );
la1UNIT * LA1_UnitCCreate( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */