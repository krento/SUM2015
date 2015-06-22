 /* FILENAME: UMODEL.C
 * PROGRAMMER: LA1
 * PURPOSE: Model view unit handle module.
 * LAST UPDATE: 10.06.2015
 */

                   
#include "anim.h"
#include "stdio.h"

typedef struct tagla1UNIT_C
{
  LA1_UNIT_BASE_FIELDS;
  la1PRIM Pr;
  INT TextId;  

} la1UNIT_C;    

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitInit( la1UNIT_C *Uni, la1ANIM *Ani )
{
  la1MATERIAL Mtl = LA1_MtlLib[1];
  

  LA1_PrimCreateSphere(&Uni->Pr, VecSet(0, 0, 0), 1200, 100, 100);
  Mtl.TexId = LA1_TextureLoad("HeightFields\\33.BMP");
  Uni->Pr.MtlNo = Uni->TextId = LA1_MtlAdd(&Mtl);
} /* End of 'LA1_AnimUnitInit' function */



/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitClose( la1UNIT_C *Uni, la1ANIM *Ani )
{
  LA1_PrimFree(&Uni->Pr);
} /* End of 'LA1_AnimUnitClose' function */


/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitRender( la1UNIT_C *Uni, la1ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Uni->TextId);
  LA1_PrimDraw(&Uni->Pr);
} /* End of 'LA1_AnimUnitRender' function */

/* 
 * 
 * 
 * 
 */
la1UNIT * LA1_UnitCCreate( VOID )
{
  la1UNIT_C *Uni;

  if ((Uni = (VOID *)LA1_AnimUnitCreate(sizeof(la1UNIT_C))) == NULL)
    return NULL;
  Uni->Init = (VOID *)LA1_AnimUnitInit;
  Uni->Close = (VOID *)LA1_AnimUnitClose;
  Uni->Render = (VOID *)LA1_AnimUnitRender;
  return (la1UNIT *)Uni;
} /* End of 'LA1_UnitModelCreate' function */

/* END OF 'UMODEL.C' FILE */