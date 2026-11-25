/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Boundry.cpp
 * Description : Geometric Entity : Boundry Implementations
 * Author      : Aman Rajesh Choudhari
 * Created On  : 11/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#include "Boundry.h"
#include <limits>

namespace pke
{
	Boundry::Boundry(Point2DList inputList) : m_lowerX(DBL_MAX)
	{
		if (inputList.size() <= 0)
			throw std::runtime_error("Can't create Boundry, No points.");

		Point2DList allPointList = inputList;

		for (int i = 0; i < allPointList.size(); i++)
		{
			if (allPointList[i].x() <= m_lowerX)
				m_lowerX = allPointList[i].x();


		}

	}

	double Boundry::getMininumValue(const std::vector<double>& inputlist)
	{
		double minVal = DBL_MAX;

		for (int i = 0; i < inputlist.size(); i++)
		{
			if (inputlist[i] < minVal)
			{
				minVal = inputlist[i];
			}	
		}

		return minVal;
	}

	long Boundry::entId() const
	{
		return -1;
	}

	Geom_Entity_type Boundry::getEntityType()
	{
		return Geom_Entity_type::Polygon;
	}

}