/***************************************************************
 * Copyright (C) 2015
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : NOISE.C
 * PURPOSE     : Perlin's noise support implementation module.
 * PROGRAMMER  : CGSG'1992-2015.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 17.06.2015.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <math.h>
#include <stdlib.h>

#include "noise.h"

/* Noise table size, mask and index remapping */
#define TAB_BITS 12
#define TAB_SIZE (1 << TAB_BITS)
#define TAB_MASK (TAB_SIZE - 1)
#define INDEX1(X) Perm[(INT)(X) & TAB_MASK]
#define INDEX2(X, Y) INDEX1(X + INDEX1(Y))
#define INDEX3(X, Y, Z) INDEX2(X, INDEX1(Y + INDEX1(Z)))
#define INDEX4(X, Y, Z, W) INDEX3(X, Y, INDEX1(Z + INDEX1(W)))

/* Noise table and value permutation */
static DBL Table[TAB_SIZE];
static INT Perm[TAB_SIZE];

/* Noise table initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NoiseInit( VOID )
{
  INT i, tmp, a, b;

  /* Fill increment order */
  for (i = 0; i < TAB_SIZE; i++)
    Perm[i] = i;

  /* Shuffle permutation table */
  for (i = 0; i < 2 * TAB_SIZE; i++)
  {
    a = rand() & TAB_MASK;
    b = rand() & TAB_MASK;
    COM_SWAP(Perm[a], Perm[b], tmp);
  }

  /* Fill noise table */
  for (i = 0; i < TAB_SIZE; i++)
    Table[i] = (DBL)rand() / RAND_MAX;
} /* End of 'NoiseInit' function */

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise1D( DBL X )
{
  INT ix, ix1;
  DBL fx;

  fx = X - floor(X);
  ix = (INT)X & TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  fx = fx * fx * (3 - 2 * fx);

  return Table[INDEX1(ix)] * (1 - fx) + Table[INDEX1(ix1)] * fx;
} /* End of 'Noise1D' function */

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise2D( DBL X, DBL Y )
{
  INT ix, ix1, iy, iy1;
  DBL fx, fy;

  fx = X - floor(X);
  ix = (INT)X & TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  fx = fx * fx * (3 - 2 * fx);

  fy = Y - floor(Y);
  iy = (INT)Y & TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;
  fy = fy * fy * (3 - 2 * fy);

  return
    Table[INDEX2(ix, iy)] * (1 - fx) * (1 - fy) +
    Table[INDEX2(ix1, iy)] * fx * (1 - fy) +
    Table[INDEX2(ix, iy1)] * (1 - fx) * fy +
    Table[INDEX2(ix1, iy1)] * fx * fy;
} /* End of 'Noise2D' function */

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise3D( DBL X, DBL Y, DBL Z )
{
  INT ix, ix1, iy, iy1, iz, iz1;
  DBL fx, fy, fz;

  fx = X - floor(X);
  ix = (INT)X & TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  fx = fx * fx * (3 - 2 * fx);

  fy = Y - floor(Y);
  iy = (INT)Y & TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;
  fy = fy * fy * (3 - 2 * fy);

  fz = Z - floor(Z);
  iz = (INT)Z & TAB_MASK;
  iz1 = (iz + 1) & TAB_MASK;
  fz = fz * fz * (3 - 2 * fz);

  return
    Table[INDEX3(ix, iy, iz)] * (1 - fx) * (1 - fy) * (1 - fz) +
    Table[INDEX3(ix1, iy, iz)] * fx * (1 - fy) * (1 - fz) +
    Table[INDEX3(ix, iy1, iz)] * (1 - fx) * fy * (1 - fz) +
    Table[INDEX3(ix1, iy1, iz)] * fx * fy * (1 - fz) +
    Table[INDEX3(ix, iy, iz1)] * (1 - fx) * (1 - fy) * fz +
    Table[INDEX3(ix1, iy, iz1)] * fx * (1 - fy) * fz +
    Table[INDEX3(ix, iy1, iz1)] * (1 - fx) * fy * fz +
    Table[INDEX3(ix1, iy1, iz1)] * fx * fy * fz;
} /* End of 'Noise3D' function */

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y, Z, W;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise4D( DBL X, DBL Y, DBL Z, DBL W )
{
  INT ix, ix1, iy, iy1, iz, iz1, iw, iw1;
  DBL fx, fy, fz, fw;

  fx = X - floor(X);
  ix = (INT)X & TAB_MASK;
  ix1 = (ix + 1) & TAB_MASK;
  fx = fx * fx * (3 - 2 * fx);

  fy = Y - floor(Y);
  iy = (INT)Y & TAB_MASK;
  iy1 = (iy + 1) & TAB_MASK;
  fy = fy * fy * (3 - 2 * fy);

  fz = Z - floor(Z);
  iz = (INT)Z & TAB_MASK;
  iz1 = (iz + 1) & TAB_MASK;
  fz = fz * fz * (3 - 2 * fz);

  fw = W - floor(W);
  iw = (INT)W & TAB_MASK;
  iw1 = (iw + 1) & TAB_MASK;
  fw = fw * fw * (3 - 2 * fw);

  return
    Table[INDEX4(ix, iy, iz, iw)] * (1 - fx) * (1 - fy) * (1 - fz) * (1 - fw) +
    Table[INDEX4(ix1, iy, iz, iw)] * fx * (1 - fy) * (1 - fz) * (1 - fw) +
    Table[INDEX4(ix, iy1, iz, iw)] * (1 - fx) * fy * (1 - fz) * (1 - fw) +
    Table[INDEX4(ix1, iy1, iz, iw)] * fx * fy * (1 - fz) * (1 - fw) +
    Table[INDEX4(ix, iy, iz1, iw)] * (1 - fx) * (1 - fy) * fz * (1 - fw) +
    Table[INDEX4(ix1, iy, iz1, iw)] * fx * (1 - fy) * fz * (1 - fw) +
    Table[INDEX4(ix, iy1, iz1, iw)] * (1 - fx) * fy * fz * (1 - fw) +
    Table[INDEX4(ix1, iy1, iz1, iw)] * fx * fy * fz * (1 - fw) +
    Table[INDEX4(ix, iy, iz, iw1)] * (1 - fx) * (1 - fy) * (1 - fz) * fw +
    Table[INDEX4(ix1, iy, iz, iw1)] * fx * (1 - fy) * (1 - fz) * fw +
    Table[INDEX4(ix, iy1, iz, iw1)] * (1 - fx) * fy * (1 - fz) * fw +
    Table[INDEX4(ix1, iy1, iz, iw1)] * fx * fy * (1 - fz) * fw +
    Table[INDEX4(ix, iy, iz1, iw1)] * (1 - fx) * (1 - fy) * fz * fw +
    Table[INDEX4(ix1, iy, iz1, iw1)] * fx * (1 - fy) * fz * fw +
    Table[INDEX4(ix, iy1, iz1, iw1)] * (1 - fx) * fy * fz * fw +
    Table[INDEX4(ix1, iy1, iz1, iw1)] * fx * fy * fz * fw;
} /* End of 'Noise4D' function */

/* Turbulence 1D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb1D( DBL X, INT Oct )
{
  INT i;
  DBL sum = 0, denum = 1, coef = 0;

  for (i = 0; i < Oct; i++)
    sum += Noise1D(X) / denum, coef += 1 / denum, denum *= 2, X = (X + 0.30) * 2;

  return sum / coef;
} /* End of 'Turb1D' function */

/* Turbulence 2D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb2D( DBL X, DBL Y, INT Oct )
{
  INT i;
  DBL sum = 0, denum = 1, coef = 0;

  for (i = 0; i < Oct; i++)
  {
    sum += Noise2D(X, Y) / denum;
    coef += 1 / denum;
    denum *= 2;
    X = (X + 0.30) * 2;
    Y = (Y + 0.36) * 2;
  }
  return sum / coef;
} /* End of 'Turb2D' function */

/* Turbulence 3D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y, Z;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb3D( DBL X, DBL Y, DBL Z, INT Oct )
{
  INT i;
  DBL sum = 0, denum = 1, coef = 0;

  for (i = 0; i < Oct; i++)
  {
    sum += Noise3D(X, Y, Z) / denum;
    coef += 1 / denum;
    denum *= 2;
    X = (X + 0.30) * 2;
    Y = (Y + 0.36) * 2;
    Z = (Z + 0.27) * 2;
  }
  return sum / coef;
} /* End of 'Turb3D' function */

/* Turbulence 4D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y, Z, W;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb4D( DBL X, DBL Y, DBL Z, DBL W, INT Oct )
{
  INT i;
  DBL sum = 0, denum = 1, coef = 0;

  for (i = 0; i < Oct; i++)
  {
    sum += Noise4D(X, Y, Z, W) / denum;
    coef += 1 / denum;
    denum *= 2;
    X = (X + 0.30) * 2;
    Y = (Y + 0.36) * 2;
    Z = (Z + 0.27) * 2;
    W = (W + 0.59) * 2;
  }
  return sum / coef;
} /* End of 'Turb4D' function */

/* END OF 'NOISE.C' FILE */
