/* FILENAME: UMODEL.C
 * PROGRAMMER: LA1
 * PURPOSE: Model view unit handle module.
 * LAST UPDATE: 10.06.2015
 */


#include "anim.h"
#include "stdio.h"
/* полключание звука */
#include <al.h>
#include <alc.h>
#include <alut.h>


#pragma comment(lib, "alut")
#pragma comment(lib, "openal32")



typedef struct tagla1UNIT_MODEL
{
  LA1_UNIT_BASE_FIELDS;

  la1GEOM Model; 
  la1GEOM Geom;
  la1PRIM Pr;
  INT TextId;  
  INT ABuf[2], ASrc[2];
} la1UNIT_MODEL;

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitInit( la1UNIT_MODEL *Uni, la1ANIM *Ani )
{
  la1MATERIAL Mtl1 = LA1_MtlLib[0];
  INT format;
  UINT size, freq;
  VOID *mem;
  CHAR loop;

  /* Инициализация аудио системы */
  alutInit(NULL, 0);
  alGetError();
  
  
  LA1_RndPrimMatrConvert = MatrIdentity();
  Uni->Pr.o = 1;
  LA1_PrimCreateHeightField(&Uni->Pr, VecSet(500, 0, -500), VecSet(-750, 0, 0), VecSet(0, 0, 750), 180.0, "HeightFields\\HF1.BMP");
  Mtl1.TexId = LA1_TextureLoad("HeightFields\\HF1TEX.BMP");

  //LA1_PrimCreateHeightField(&Uni->Pr, VecSet(250, 0, -250), VecSet(-500, 0, 0), VecSet(0, 0, 500), 180.0, "E:\\SPR01\\HeightFields\\aaa.BMP");
  //Mtl.TexId = LA1_TextureLoad("E:\\SPR01\\HeightFields\\aa2.BMP");

  Uni->Pr.MtlNo = Uni->TextId = LA1_MtlAdd(&Mtl1);
 // HF = MatrScale(0.1, 0.1, 0.1);
 // LA1_RndPrimMatrConvert  = MatrMulMatr(LA1_RndPrimMatrConvert, MatrRotateY(90));
 // LA1_RndPrimMatrConvert  = MatrMulMatr(LA1_RndPrimMatrConvert, MatrTranslate(100, -100, 0)); 
  LA1_RndPrimMatrConvert = MatrMulMatr(MatrScale(0.5, 0.5, 0.5), MatrRotateX(-90));
  LA1_GeomLoad(&Uni->Geom, "Hell\\uh60.G3D");
  //LA1_GeomLoad(&Uni->Geom, "E:\\SPR01\\CPV\\CityPatrolVehicle.g3d");

  /****
   *  SOUND
   *
   ****/
  
  /* создаем буфера */
  alGenBuffers(2, Uni->ABuf);

  /* загружаем звук в буфер */
  alutLoadWAVFile("a1.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[0], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  alutLoadWAVFile("a.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[1], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  /* создаем источники звука и параметризируем их */
  alGenSources(2, Uni->ASrc);

  alSourcei(Uni->ASrc[0], AL_BUFFER, Uni->ABuf[0]); /* закрепляем буфер за источником */
  alSourcef(Uni->ASrc[0], AL_PITCH, 1);             /* скорость воспроизведения: 1.0 - обычная*/
  alSourcef(Uni->ASrc[0], AL_GAIN, 1);              /* громкость: 1.0 – обычная */
  alSourcei(Uni->ASrc[0], AL_LOOPING, 1);           /* флаг повтора: 0 – нет, 1 – бесконечно */

  alSourcePlay(Uni->ASrc[0]); /* запуск проигрывания */

  alSourcei(Uni->ASrc[1], AL_BUFFER, Uni->ABuf[1]); /* закрепляем буфер за источником */
  alSourcef(Uni->ASrc[1], AL_PITCH, 1);             /* скорость воспроизведения: 1.0 - обычная*/
  alSourcef(Uni->ASrc[1], AL_GAIN, 1);              /* громкость: 1.0 – обычная */
  alSourcei(Uni->ASrc[1], AL_LOOPING, 0);           /* флаг повтора: 0 – нет, 1 – бесконечно */

  alSourcePlay(Uni->ASrc[1]);
  //LA1_RndPrimMatrConvert = MatrScale(0.30, 0.30, 0.30);
  //LA1_GeomLoad(&Uni->Geom, "COW.G3D");
} /* End of 'LA1_AnimUnitInit' function */

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitResponse( la1UNIT_MODEL *Uni, la1ANIM *Ani )
{
  if (Ani->Keys[VK_ESCAPE])
    LA1_AnimDoExit();
  
  if (Ani->Keys[VK_DOWN])
    Ani->TZ += 10.5;;
  if (Ani->Keys[VK_UP])
    Ani->TZ -= 10.5;
  if (Ani->Keys[VK_LEFT])
    Ani->TX += 0.5;
  if (Ani->Keys[VK_RIGHT])
    Ani->TX -= 0.5; 
  if (Ani->Keys[VK_INSERT])
    Ani->TY -= 0.5;
  if (Ani->Keys[VK_DELETE])
    Ani->TY += 0.5; 

  
   if (Ani->JButsClick[0])
    alSourcePlay(Uni->ASrc[1]);


  if (Ani->Keys['D'])
    Ani->AY += 0.5;
  if (Ani->Keys['A'])
    Ani->AY -= 0.5;
  if (Ani->Keys['W'])
    Ani->AZ -= 0.5;
  if (Ani->Keys['S'])
    Ani->AZ += 0.5;  

  if (Ani->KeysClick['E'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (Ani->KeysClick['Q'])
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  

  /*
  if (Ani->JX < -0.000015 || Ani->JX > 0)
    Ani->TX += Ani->JX + 0.000015;
  if (Ani->JY < -0.000015 || Ani->JY > 0)
    Ani->TY += Ani->JY + 0.000015;
  if (Ani->JZ < -0.000015 || Ani->JZ > 0)
    Ani->TZ += Ani->JZ + 0.000015;

  if (Ani->JR < -0.000015 || Ani->JR > 0)
    Ani->AX += Ani->JR + 0.000015;
  if (Ani->JU < -0.000015 || Ani->JU > 0)
    Ani->AY += Ani->JU + 0.000015;
  if (Ani->JV < -0.000015 || Ani->JV > 0)
    Ani->AZ += Ani->JV + 0.000015;   */

} /* End of 'LA1_AnimUnitResponse' function */

/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitClose( la1UNIT_MODEL *Uni, la1ANIM *Ani )
{
  LA1_GeomFree(&Uni->Model);
  LA1_GeomFree(&Uni->Geom);
  LA1_PrimFree(&Uni->Pr);
} /* End of 'LA1_AnimUnitClose' function */


/* 
 * 
 * 
 * 
 */
static VOID LA1_AnimUnitRender( la1UNIT_MODEL *Uni, la1ANIM *Ani )
{
  INT i, j, h = 0;


/*  LA1_RndMatrView = MatrView(VecSet(Ani->TX, Ani->TY + 5, Ani->TZ + 17),
                             VecSet(Ani->TX, Ani->TY + 2, Ani->TZ - 4),
                             VecSet(0, 1, 0));
  */LA1_RndMatrView = MatrView(VecSet(0, 4, 17),
                             VecSet(0, 2, -5),
                             VecSet(0, 1, 0));

  

  
  for (i = 0; i < 1; i++)
    for (j = 0; j < 1; j++)
    {
      LA1_RndMatrWorld =
        MatrMulMatr(MatrMulMatr(MatrMulMatr(MatrMulMatr(MatrMulMatr(
          MatrRotateX(Ani->AX),
          MatrRotateY(Ani->AY + Ani->Time * 6)),
          MatrRotateZ(Ani->AZ)),
          MatrTranslate(Ani->TX, 0, 0)),
          MatrTranslate(0, Ani->TY, 0)),
          MatrTranslate(0, 0, Ani->TZ));
      glColor3d(i & 1, j & 1, 1 - ((i & 1) + (j & 1)) / 2);
      LA1_GeomDraw(&Uni->Model);
    }
 // LA1_RndMatrWorld = MatrRotateY(30 * Ani->Time);
  //MatrMulMatr(MatrRotateZ(30 * sin(Ani->Time * 3.0)), MatrRotateY(30 * Ani->Time));
  LA1_GeomDraw(&Uni->Geom);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Uni->TextId);

  Uni->Pr.o = 1;
  Uni->Pr.Mp = MatrMulMatr(MatrScale(0.5, 0.5, 0.5), MatrTranslate(0, -10, 0)), LA1_PrimDraw(&Uni->Pr);
} /* End of 'LA1_AnimUnitRender' function */

/* 
 * 
 * 
 * 
 */
la1UNIT * LA1_UnitModelCreate( VOID )
{
  la1UNIT_MODEL *Uni;

  if ((Uni = (VOID *)LA1_AnimUnitCreate(sizeof(la1UNIT_MODEL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)LA1_AnimUnitInit;
  Uni->Close = (VOID *)LA1_AnimUnitClose;
  Uni->Response = (VOID *)LA1_AnimUnitResponse;
  Uni->Render = (VOID *)LA1_AnimUnitRender;
  return (la1UNIT *)Uni;
} /* End of 'LA1_UnitModelCreate' function */

/* END OF 'UMODEL.C' FILE */