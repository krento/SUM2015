/* FILENAME: MTLLIB.C
 * PROGRAMMER: LA1
 * PURPOSE: Material library support module.
 * LAST UPDATE: 15.06.2015
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "render.h"

INT LA1_MtlLibSize = 1;
la1MATERIAL LA1_MtlLib[LA1_MATERIAL_MAX] =
{
  {
    "Default",
    {0.1, 0.1, 0.1}, /* Ka */
    {0.9, 0.9, 0.9}, /* Kd */
    {0.5, 0.5, 0.5}, /* Ks */
    30.0,            /* Kp */
    1.0,             /* Kt */
    0                /* Texture id */
  }
};

/* 
 * 
 * 
 * 
 */
INT LA1_MtlAdd( la1MATERIAL *Mtl )
{
  if (LA1_MtlLibSize < LA1_MATERIAL_MAX)
  {
    LA1_MtlLib[LA1_MtlLibSize] = *Mtl;
    return LA1_MtlLibSize++;
  }
  return 0;
} /* End of 'LA1_MtlAdd' function */

/* 
 * 
 * 
 * 
 */
INT LA1_MtlFind( CHAR *Name )
{
  INT i;

  for (i = 0; i < LA1_MtlLibSize; i++)
    if (strcmp(Name, LA1_MtlLib[i].Name) == 0)
      return i;
  return 0;
} /* End of 'LA1_MtlFind' function */

/* 
 * 
 * 
 * 
 */
INT LA1_MtlLoad( CHAR *FileName )
{
  FILE *F;
  INT cnt = 0, i, j;
  la1MATERIAL Mtl = LA1_MtlLib[0];
  static CHAR
    Buf[1000], Name[_MAX_PATH],
    path_buffer[_MAX_PATH],
    drive[_MAX_DRIVE],
    dir[_MAX_DIR],
    fname[_MAX_FNAME],
    ext[_MAX_EXT];

  _splitpath(FileName, drive, dir, fname, ext);

  if ((F = fopen(FileName, "r")) == NULL)
    return 0;

  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    i = 0;
    while (Buf[i] != 0 && isspace(Buf[i]))
      i++;
    if (strncmp(Buf + i, "Ka", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Ka.X, &Mtl.Ka.Y, &Mtl.Ka.Z);
    else if (strncmp(Buf + i, "Kd", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Kd.X, &Mtl.Kd.Y, &Mtl.Kd.Z);
    else if (strncmp(Buf + i, "Ks", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Ks.X, &Mtl.Ks.Y, &Mtl.Ks.Z);
    else if (strncmp(Buf + i, "Ns", 2) == 0)
      sscanf(Buf + i + 3, "%f", &Mtl.Kp);
    else if (Buf[i] == 'D' || Buf[i] == 'd')
      sscanf(Buf + i + 2, "%f", &Mtl.Kt);
    else if (strncmp(Buf + i, "newmtl", 6) == 0)
    {
      j = 0;
      i += 7;
      while (j < sizeof(Name) - 1 && Buf[i] != 0 && Buf[i] != '\n')
        Name[j++] = Buf[i++];
      Name[j] = 0;

      if (cnt++ != 0)
        LA1_MtlAdd(&Mtl);
      Mtl = LA1_MtlLib[0];
      strcpy(Mtl.Name, Name);
    }
    else if (strncmp(Buf + i, "map_Kd", 6) == 0)
    {
      j = 0;
      i += 7;
      while (j < sizeof(Name) - 1 && Buf[i] != 0 && Buf[i] != '\n')
        Name[j++] = Buf[i++];
      Name[j] = 0;

      _makepath(path_buffer, drive, dir, Name, "");
      Mtl.TexId = LA1_TextureLoad(path_buffer);
    }
  }
  if (cnt != 0)
    LA1_MtlAdd(&Mtl);
  fclose(F);
  return cnt;
} /* End of 'LA1_MtlLoad' function */

/* END OF 'MTLLIB.C' FILE */