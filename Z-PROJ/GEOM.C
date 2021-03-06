/* FILENAME: GEOM.C
 * PROGRAMMER: LA1
 * PURPOSE: Rendering system implementation module.
 * LAST UPDATE: 13.06.2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "anim.h"
/* 
 * 
 * 
 * 
 */
INT LA1_GeomAddPrim( la1GEOM *G, la1PRIM *Prim )
{
  la1PRIM *new_bulk;


  if ((new_bulk = malloc(sizeof(la1PRIM) * (G->NumOfPrimitives + 1))) == NULL)
    return -1;

  if (G->Prims != NULL)
  {
    memcpy(new_bulk, G->Prims, sizeof(la1PRIM) * G->NumOfPrimitives);
    free(G->Prims);
  }

  G->Prims = new_bulk;


  G->Prims[G->NumOfPrimitives] = *Prim;
  return G->NumOfPrimitives++;
} /* End of 'LA1_GeomAddPrim' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_GeomFree( la1GEOM *G )
{
  INT i;

  if (G->Prims != NULL)
  {
    for (i = 0; i < G->NumOfPrimitives; i++)
      LA1_PrimFree(&G->Prims[i]);
    free(G->Prims);
  }
  memset(G, 0, sizeof(la1GEOM));
} /* End of 'LA1_GeomFree' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_GeomDraw( la1GEOM *G )
{
  INT i, loc;

 
  glUseProgram(LA1_RndProg);
  loc = glGetUniformLocation(LA1_RndProg, "TotalParts");
  if (loc != -1)
    glUniform1f(loc, G->NumOfPrimitives);
  glUseProgram(0);


  for (i = 0; i < G->NumOfPrimitives; i++)
    if (LA1_MtlLib[G->Prims[i].MtlNo].Kt == 1)
    {

      glUseProgram(LA1_RndProg);
      loc = glGetUniformLocation(LA1_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);
      
      G->Prims[i].Mp = MatrIdentity();
      G->Prims[i].o = 0;
      LA1_PrimDraw(&G->Prims[i]);
    }


  for (i = 0; i < G->NumOfPrimitives; i++)
    if (LA1_MtlLib[G->Prims[i].MtlNo].Kt != 1)
    {

      glUseProgram(LA1_RndProg);
      loc = glGetUniformLocation(LA1_RndProg, "PartNo");
      if (loc != -1)
        glUniform1f(loc, i);
      glUseProgram(0);

      G->Prims[i].Mp = MatrIdentity();
    
      G->Prims[i].o = 0;
      LA1_PrimDraw(&G->Prims[i]);
    }
} /* End of 'LA1_GeomDraw' function */

/* 
 * 
 * 
 * 
 */
BOOL LA1_GeomLoad( la1GEOM *G, CHAR *FileName )
{
  FILE *F;
  INT i, j, n;
  CHAR Sign[4];
  MATR M;
  static CHAR MtlName[300];
  static CHAR
    path_buffer[_MAX_PATH],
    drive[_MAX_DRIVE],
    dir[_MAX_DIR],
    fname[_MAX_FNAME],
    ext[_MAX_EXT];


  _splitpath(FileName, drive, dir, fname, ext);

  memset(G, 0, sizeof(la1GEOM));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  M = MatrTranspose(MatrInverse(LA1_RndPrimMatrConvert));


  fread(Sign, 1, 4, F);
  if (*(DWORD *)Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }


  fread(&n, 4, 1, F);
  fread(MtlName, 1, 300, F);


  _makepath(path_buffer, drive, dir, MtlName, "");
  LA1_MtlLoad(path_buffer);


  for (i = 0; i < n; i++)
  {
    INT nv, ni, *Ind;
    la1VERTEX *Vert;
    la1PRIM P;


    fread(&nv, 4, 1, F);
    fread(&ni, 4, 1, F);

    fread(MtlName, 1, 300, F);


    if ((Vert = malloc(sizeof(la1VERTEX) * nv + sizeof(INT) * ni)) == NULL)
      break;
    Ind = (INT *)(Vert + nv);


    fread(Vert, sizeof(la1VERTEX), nv, F);

    for (j = 0; j < nv; j++)
    {
      Vert[j].P = VecMulMatr(Vert[j].P, LA1_RndPrimMatrConvert);
      Vert[j].N = VecMulMatr3(Vert[j].N, M);
    }
    fread(Ind, sizeof(INT), ni, F);


    LA1_PrimCreate(&P, LA1_PRIM_TRIMESH, nv, ni, Vert, Ind);
    P.MtlNo = LA1_MtlFind(MtlName);

    free(Vert);


    LA1_GeomAddPrim(G, &P);
  }
  fclose(F);
  LA1_RndPrimMatrConvert = MatrIdentity();
  return TRUE;
} /* End of 'LA1_GeomDraw' function */

/* END OF 'GEOM.C' FILE */
