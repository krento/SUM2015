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

/* ������� */
extern MATR
  LA1_RndMatrWorld,
  LA1_RndMatrView,
  LA1_RndMatrProj,
  LA1_RndMatrWorldViewProj;
MATR HF;

/* ������� ��������� ��������� ��� �������� */
extern MATR LA1_RndPrimMatrConvert;

/* ��������� ������������� */
extern DBL
  LA1_RndWp, LA1_RndHp,    /* ������� ������� ������������� */
  LA1_RndProjDist;         /* ���������� �� ��������� �������� */

/* ������ �� ��������� */
extern UINT LA1_RndProg;

/* ������� �������� �������� ��� ����� ���������.
 * ���������:
 *   - ������� ����� �����:
 *       CHAR *FileNamePrefix;
 * ������������ ��������:
 *   (UINT) ����� ����������� ���������.
 */
UINT LA1_ShaderLoad( CHAR *FileNamePrefix );

/* ������� ����������� �������� ��� ���������.
 * ���������:
 *   - ����� ���������:
 *       UINT PrgId;
 * ������������ ��������: ���.
 */
VOID LA1_ShaderFree( UINT PrgId );

/***
 * ������ � �����������
 ***/

/* ��� ������� ��������� ����������� */
typedef struct tagla1MATERIAL
{
  /* ��� ��������� */
  CHAR Name[300];

  /* ������������ ��������� */
  VEC Ka, Kd, Ks;
  FLT Kp; /* ������� "����������" */

  /* ����������� ������������ */
  FLT Kt;

  /* �������� ����������� */
  INT TexId;
} la1MATERIAL;

/* ���������� ������� ���������� */
#define LA1_MATERIAL_MAX 300
extern INT LA1_MtlLibSize;
extern la1MATERIAL LA1_MtlLib[LA1_MATERIAL_MAX];

/* ������� ���������� ��������� � ����������.
 * ���������:
 *   - ��������� � ����������� ���������:
 *       la1MATERIAL *Mtl;
 * ������������ ��������:
 *   (INT) ���������� ����� ������������ ��������� (0 ��� ������).
 */
INT LA1_MtlAdd( la1MATERIAL *Mtl );

/* ������� ������ ��������� �� �����.
 * ���������:
 *   - ��� ���������:
 *       CHAR *Name;
 * ������������ ��������:
 *   (INT) ���������� ����� ���������� ��������� (0 ��� ������).
 */
INT LA1_MtlFind( CHAR *Name );

/* ������� �������� ��������� �� ����� (*.MTL).
 * ���������:
 *   - ��� ����� ���������:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (INT) ���������� ����������� ����������.
 */
INT LA1_MtlLoad( CHAR *FileName );

/***
 * ������ � �����������
 ***/

/* ���� ���������� */
typedef enum tagla1PRIM_TYPE
{
  LA1_PRIM_TRIMESH,  /* �������� - ����� ������������� */
  LA1_PRIM_GRID      /* ���������� ����� ������������� (����� triangle strip) */
} la1PRIM_TYPE;

/* ��� �������� ��������� */
typedef struct tagla1PRIM
{
  la1PRIM_TYPE Type; /* ��� ��������� (LA1_PRIM_***) */
  INT
    VA,          /* ������ ������ */
    VBuf, IBuf,  /* ������ ������ � �������� */
    NumOfI,      /* ���������� �������� ��� ������ ��������� */
    MtlNo;       /* ����� ��������� �� ���������� */
  MATR Mp;       /* ������� ��������� */
  INT o;
} la1PRIM;

/* ��� �������� ���������� ��������� */
typedef struct tagla1UV
{
  FLT U, V; /* ���������� ���������� */
} la1UV;

/* ������� ������� ���������� ���������.
 * ���������:
 *   - ����� ������� ���������:
 *       FLT U, V;
 * ������������ ��������:
 *   (la1UV) ����������� ����������.
 */
__inline la1UV UVSet( FLT U, FLT V )
{
  la1UV UV = {U, V};

  return UV;
} /* End of 'UVSet' function */

/* ��� �������� ����� ������� ���������� */
typedef struct tagla1VERTEX
{
  VEC P;    /* ������� ������� */
  la1UV T;  /* ���������� ���������� ������� */
  VEC N;    /* ������� � ������� */
  COLOR C;  /* ���� ������� */
} la1VERTEX;

/* ������� �������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       la1PRIM *Prim;
 *   - ��� ��������� (LA1_PRIM_***):
 *       la1PRIM_TYPE Type;
 *   - ���������� ������ � ��������:
 *       INT NoofV, NoofI;
 *   - ������ ������:
 *       la1VERTEX *Vertices;
 *   - ������ ��������:
 *       INT *Indices;
 * ������������ ��������: ���.
 */
VOID LA1_PrimCreate( la1PRIM *Prim, la1PRIM_TYPE Type,
                     INT NoofV, INT NoofI, la1VERTEX *Vertices, INT *Indices);

/* ������� �������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       la1PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID LA1_PrimFree( la1PRIM *Prim );

/* ������� ��������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       la1PRIM *Prim;
 * ������������ ��������: ���.
 */
VOID LA1_PrimDraw( la1PRIM *Prim );

/* ������� �������� ��������� ���������.
 * ���������:
 *   - ��������� �� ��������:
 *       la1PRIM *Prim;
 *   - ����������� �������-�������:
 *       VEC Du, Dv;
 *   - ���������:
 *       INT N, M;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
BOOL LA1_PrimCreatePlane( la1PRIM *Prim, VEC Loc, VEC Du, VEC Dv, INT N, INT M );

/* ������� �������� ��������� �����.
 * ���������:
 *   - ��������� �� ��������:
 *       la1PRIM *Prim;
 *   - ����� �����:
 *       VEC �;
 *   - ������ �����:
 *       FLT R;
 *   - ���������:
 *       INT N, M;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� FALSE.
 */
BOOL LA1_PrimCreateSphere( la1PRIM *Prim, VEC C, FLT R, INT N, INT M );

/* ������� �������� ��������������� �������.
 * ���������:
 *   - ��������� ������� ��� ��������:
 *       la1PRIM *GObj;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, FALSE �����.
 */
BOOL LA1_PrimLoad( la1PRIM *GObj, CHAR *FileName );

/***                      
 * ������ � ��������������� ���������
 ***/

/* �������������� ������ - ����� ���������� */
typedef struct tagla1GEOM
{
  INT NumOfPrimitives; /* ���������� ���������� */
  la1PRIM *Prims;      /* ������ ���������� */
} la1GEOM;

/* ������� ���������� ��������� � ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       la1GEOM *G;
 *   - ��������� �� ����������� ��������:
 *       la1PRIM *Prim;
 * ������������ ��������:
 *   (INT) ����� ������������ ��������� � ������� (-1 ��� ������).
 */
INT LA1_GeomAddPrim( la1GEOM *G, la1PRIM *Prim );

/* ������� ������������ ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       la1GEOM *G;
 * ������������ ��������: ���.
 */
VOID LA1_GeomFree( la1GEOM *G );

/* ������� ����������� ��������������� �������.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       la1GEOM *G;
 * ������������ ��������: ���.
 */
VOID LA1_GeomDraw( la1GEOM *G );

/* ������� �������� ��������������� ������� �� G3D �����.
 * ���������:
 *   - ��������� �� �������������� ������:
 *       la1GEOM *G;
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (BOOL) TRUE ��� ������, ����� - FALSE.
 */
BOOL LA1_GeomLoad( la1GEOM *G, CHAR *FileName );

/* ������� �������� ��������.
 * ���������:
 *   - ��� �����:
 *       CHAR *FileName;
 * ������������ ��������:
 *   (INT ) ������������� OpenGL ��� ��������.
 */
INT LA1_TextureLoad( CHAR *FileName );
BOOL LA1_PrimCreateHeightField( la1PRIM *Prim, VEC Loc, VEC Du, VEC Dv, DBL Scale, CHAR *FileName );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
