#ifndef __UNITS_H__
#define __UNITS_H__

#include <math.h>

/** @file   units.h
 *  @brief  Helper API for physical unit conversion
 *
 *  Provides a small set of commonly used unit conversion functions 
 */
 
/** @name Simple Conversion factors */
//@{
/** @name Pressure */
//@{
#define mBAR_2_PSI(x) (x * 0.014503773773)
#define PSI_2_mBAR(x) (x/mBAR_2_PSI)
//@}

/** @name Length */
//@{
#define FT_2_M(x)  (x * 0.3048)
#define M_2_FT(x)  (x/FT_2_M)
//@}
 

/** @name Angle */
//@{
#define DEG_2_RAD(x)  (x * M_PI/180.0)
#define RAD_2_DEG(x)  (x * 180.0 / M_PI)
//@}
 
#endif
