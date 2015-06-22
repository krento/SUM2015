/* FILENAME: RENDER.H
 * PROGRAMMER: LA1
 * PURPOSE: Rendering system declaration module.
 * LAST UPDATE: 13.06.2015
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "vec.h"


#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

/* Матрицы */
extern MATR
  LA1_RndMatrWorld,
  LA1_RndMatrView,
  LA1_RndMatrProj,
  LA1_RndMatrWorldViewProj;
MATR HF;

/* Матрица изменения примитива при создании */
extern MATR LA1_RndPrimMatrConvert;

/* Параметры проецирования */
extern DBL
  LA1_RndWp, LA1_RndHp,    /* размеры обрасти проецирования */
  LA1_RndProjDist;         /* расстояние до плоскости проекции */

/* Шейдер по умолчанию */
extern UINT LA1_RndProg;

/* Функция загрузки шейдеров для одной программы.
 * АРНУМЕНТЫ:
 *   - префикс имени файла:
 *       CHAR *FileNamePrefix;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (UINT) номер загруженной программы.
 */
UINT LA1_ShaderLoad( CHAR *FileNamePrefix );

/* Функция уничтодения шейдеров для программы.
 * АРНУМЕНТЫ:
 *   - номер программы:
 *       UINT PrgId;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_ShaderFree( UINT PrgId );

/***
 * Работа с материалами
 ***/

/* Тип задания материала поверхности */
typedef struct tagla1MATERIAL
{
  /* Имя материала */
  CHAR Name[300];

  /* Коэффициенты отражения */
  VEC Ka, Kd, Ks;
  FLT Kp; /* Степень "бликовости" */

  /* Коэффициент прозрачности */
  FLT Kt;

  /* Текстура поверхности */
  INT TexId;
} la1MATERIAL;

/* Глобальная таблица материалов */
#define LA1_MATERIAL_MAX 300
extern INT LA1_MtlLibSize;
extern la1MATERIAL LA1_MtlLib[LA1_MATERIAL_MAX];

/* Функция добавления материала в библиотеку.
 * АРГУМЕНТЫ:
 *   - структура с памаметрами материала:
 *       la1MATERIAL *Mtl;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) порядковый номер добавленного материала (0 при ошибке).
 */
INT LA1_MtlAdd( la1MATERIAL *Mtl );

/* Функция поиска материала по имени.
 * АРГУМЕНТЫ:
 *   - имя материала:
 *       CHAR *Name;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) порядковый номер найденного материала (0 при ошибке).
 */
INT LA1_MtlFind( CHAR *Name );

/* Функция загрузки материала из файла (*.MTL).
 * АРГУМЕНТЫ:
 *   - имя файла материала:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) количество загруженных материалов.
 */
INT LA1_MtlLoad( CHAR *FileName );

/***
 * Работа с примитивами
 ***/

/* Виды примитивов */
typedef enum tagla1PRIM_TYPE
{
  LA1_PRIM_TRIMESH,  /* примитив - набор треугольников */
  LA1_PRIM_GRID      /* регулярная сетка треугольников (через triangle strip) */
} la1PRIM_TYPE;

/* Тип хранения примитива */
typedef struct tagla1PRIM
{
  la1PRIM_TYPE Type; /* Тип примитива (LA1_PRIM_***) */
  INT
    VA,          /* массив вершин */
    VBuf, IBuf,  /* буфера вершин и индексов */
    NumOfI,      /* количество индексов для вывода примитива */
    MtlNo;       /* номер материала из библиотеки */
  MATR Mp;       /* матрица примитива */
  INT o;
} la1PRIM;

/* Тип хранения текстурных координат */
typedef struct tagla1UV
{
  FLT U, V; /* текстурные координаты */
} la1UV;

/* Функция задания текстурных координат.
 * АРГУМЕНТЫ:
 *   - новые значени координат:
 *       FLT U, V;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (la1UV) построенные координаты.
 */
__inline la1UV UVSet( FLT U, FLT V )
{
  la1UV UV = {U, V};

  return UV;
} /* End of 'UVSet' function */

/* Тип хранения одной вершины паримитива */
typedef struct tagla1VERTEX
{
  VEC P;    /* позиция вершины */
  la1UV T;  /* текстурные координаты вершины */
  VEC N;    /* нормаль в вершине */
  COLOR C;  /* цвет вершины */
} la1VERTEX;

/* Функция создания примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       la1PRIM *Prim;
 *   - тип примитива (LA1_PRIM_***):
 *       la1PRIM_TYPE Type;
 *   - количество вершин и индексов:
 *       INT NoofV, NoofI;
 *   - массив вершин:
 *       la1VERTEX *Vertices;
 *   - массив индексов:
 *       INT *Indices;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_PrimCreate( la1PRIM *Prim, la1PRIM_TYPE Type,
                     INT NoofV, INT NoofI, la1VERTEX *Vertices, INT *Indices);

/* Функция удаления примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       la1PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_PrimFree( la1PRIM *Prim );

/* Функция отрисовки примитива.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       la1PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_PrimDraw( la1PRIM *Prim );

/* Функция создания примитива плоскость.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       la1PRIM *Prim;
 *   - касательные вектора-стороны:
 *       VEC Du, Dv;
 *   - разбиение:
 *       INT N, M;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL LA1_PrimCreatePlane( la1PRIM *Prim, VEC Loc, VEC Du, VEC Dv, INT N, INT M );

/* Функция создания примитива сфера.
 * АРГУМЕНТЫ:
 *   - указатель на примитив:
 *       la1PRIM *Prim;
 *   - центр сферы:
 *       VEC С;
 *   - радиус сферы:
 *       FLT R;
 *   - разбиение:
 *       INT N, M;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе FALSE.
 */
BOOL LA1_PrimCreateSphere( la1PRIM *Prim, VEC C, FLT R, INT N, INT M );

/* Функция загрузки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - структура объекта для загрузки:
 *       la1PRIM *GObj;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, FALSE иначе.
 */
BOOL LA1_PrimLoad( la1PRIM *GObj, CHAR *FileName );

/***                      
 * Работа с геометрическими объектами
 ***/

/* Геометрический объект - набор примитивов */
typedef struct tagla1GEOM
{
  INT NumOfPrimitives; /* количество примитивов */
  la1PRIM *Prims;      /* массив примитивов */
} la1GEOM;

/* Функция добавления примитива к геометрическому объекту.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       la1GEOM *G;
 *   - указатель на добавляемый примитив:
 *       la1PRIM *Prim;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) номер добавленного примитива в массиве (-1 при ошибке).
 */
INT LA1_GeomAddPrim( la1GEOM *G, la1PRIM *Prim );

/* Функция освобождения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       la1GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_GeomFree( la1GEOM *G );

/* Функция отображения геометрического объекта.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       la1GEOM *G;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID LA1_GeomDraw( la1GEOM *G );

/* Функция загрузки геометрического объекта из G3D файла.
 * АРГУМЕНТЫ:
 *   - указатель на геометрический объект:
 *       la1GEOM *G;
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе, иначе - FALSE.
 */
BOOL LA1_GeomLoad( la1GEOM *G, CHAR *FileName );

/* Функция загрузки текстуры.
 * АРГУМЕНТЫ:
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT ) идентификатор OpenGL для текстуры.
 */
INT LA1_TextureLoad( CHAR *FileName );
BOOL LA1_PrimCreateHeightField( la1PRIM *Prim, VEC Loc, VEC Du, VEC Dv, DBL Scale, CHAR *FileName );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
