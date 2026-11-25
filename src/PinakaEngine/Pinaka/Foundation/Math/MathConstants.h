/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : MathConstants.h
 * Description : Mathematical constants and angle conversion factors.
 * Author      : Aman Rajesh Choudhari
 * Created On  : 25/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#pragma once

/*
 * Mathematical constant PI.
 */
#define PKE_PI 3.14159265358979323846

/*
 * Conversion factor from degrees to radians.
 */
#define PKE_DEG_TO_RAD (PKE_PI / 180.0)

/*
 * Conversion factor from radians to degrees.
 */
#define PKE_RAD_TO_DEG (180.0 / PKE_PI)

/*
 * Default tolerance for floating-point comparisons.
 */
#define PKE_EPSILON 1e-9