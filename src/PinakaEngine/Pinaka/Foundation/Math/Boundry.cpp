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
	Boundry::Boundry(Point2DList inputList) :
		m_lowerX(Point2D(DBL_MAX, DBL_MAX)),
		m_lowerY(Point2D(DBL_MAX, DBL_MAX)), 
		m_upperX(Point2D(DBL_MIN, DBL_MIN)),
		m_upperY(Point2D(DBL_MIN, DBL_MIN))
		
	{
		if (inputList.size() <= 0)
			throw std::runtime_error("Can't create Boundry, No points.");

		registerExtents(inputList);
		processDimensions();

	}

	void Boundry::processDimensions()
	{
		m_length = m_lowerX.distance(m_upperX);
		m_width = m_upperY.distance(m_lowerY);
	}
	
	void Boundry::registerExtents(Point2DList inputList)
	{
		Point2DList allPointList = inputList;

		for (int i = 0; i < allPointList.size(); i++)
		{
			Point2D currentPoint = allPointList[i];
			
			if (currentPoint.x() <= m_lowerX.x())
				m_lowerX = currentPoint;

			if (currentPoint.y() <= m_lowerY.y())
				m_lowerY = currentPoint;

			if (currentPoint.x() >= m_upperX.x())
				m_upperX = currentPoint;

			if (currentPoint.y() >= m_upperY.y())
				m_upperY = currentPoint;
		}
	}

	Point2D Boundry::getVerticalMinExtent() const 
	{
		return m_lowerY;
	}

	Point2D Boundry::getVerticalMaxExtent() const 
	{
		return m_upperY;
	}

	Point2D Boundry::getHorizontalMinExtent() const 
	{
		return m_lowerX;
	}

	Point2D Boundry::getHorizontalMaxExtent() const
	{
		return m_upperX;
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


	double Boundry::getLength() const
	{
		return m_length;
	}

	double Boundry::getWidth() const
	{
		return m_width;
	}



	long Boundry::entId() const
	{
		return -1;
	}

	Geom_Entity_type Boundry::getEntityType() const
	{
		return Geom_Entity_type::Polygon;
	}

}