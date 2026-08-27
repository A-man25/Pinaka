/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Algorithm.h
 * Description : Algorithm class
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 27/08/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 * ----------------------------------------------------------------------*/
#pragma once 
#include <Pinaka/Core/PinakaEngineInc.h>

namespace pke
{
	class Algorithm
	{
	public:
		static bool binarySearch(IntegerVector& ioVec);
		static bool bubbleSort(IntegerVector& ioVec);
		static bool insertionSort(IntegerVector& ioVec);
		static bool selectionSort(IntegerVector& ioVec);
		static bool mergeSort(IntegerVector& ioVec);
		static int findMaxValue(IntegerVector& ioVec);
		static int findMinValue(IntegerVector& ioVec);

	};
}