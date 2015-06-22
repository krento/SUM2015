/***************************************************************
 * Copyright (C) 2015
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : NOISE.H
 * PURPOSE     : Perlin's noise support declaration module.
 * PROGRAMMER  : CGSG'1992-2015.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 17.06.2015.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __NOISE_H_
#define __NOISE_H_

#include <commondf.h>

/* Noise table initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NoiseInit( VOID );

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise1D( DBL X );

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise2D( DBL X, DBL Y );

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise3D( DBL X, DBL Y, DBL Z );

/* Continious random number generator function.
 * ARGUMENTS:
 *   - random parameters:
 *       DBL X, Y, Z, W;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Noise4D( DBL X, DBL Y, DBL Z, DBL W );

/* Turbulence 1D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb1D( DBL X, INT Oct );

/* Turbulence 2D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb2D( DBL X, DBL Y, INT Oct );

/* Turbulence 3D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y, Z;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb3D( DBL X, DBL Y, DBL Z, INT Oct );

/* Turbulence 4D function.
 * ARGUMENTS:
 *   - random parameter:
 *       DBL X, Y, Z, W;
 *   - number of octaves:
 *       INT Oct;
 * RETURNS:
 *   (DBL) random value.
 */
DBL Turb4D( DBL X, DBL Y, DBL Z, DBL W, INT Oct );

#endif /* __NOISE_H_ */

/* END OF 'NOISE.H' FILE */
