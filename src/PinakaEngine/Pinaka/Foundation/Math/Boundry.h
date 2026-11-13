/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Boundry.h
 * Description : Geometric Entity : Boundry (Convex Hull Algorithm)
 * Author      : Aman Rajesh Choudhari
 * Created On  : 11/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/
#pragma once

#include <Pinaka/Core/Core.h>
#include <Pinaka/Core/PinakaEngineInc.h>
#include "GeomEntity.h"
#include "Point2D.h"

typedef std::vector<pke::Point2D> Point2DList;

namespace pke
{
	class Boundry : public GeomEntity
	{
		Boundry(Point2DList inputPointList);
		double getLength() const;
		double getWidth() const;
		unsigned int getPointCount() const;
		Point2D getVerticalMinExtent() const;
		Point2D getVerticalMaxExtent() const;
		Point2D getHorizontalMinExtent() const;
		Point2D getHorizontalMaxExtent() const;

	private:
		Point2DList m_pointList;
		double m_length;
		double m_width;
	};
}
