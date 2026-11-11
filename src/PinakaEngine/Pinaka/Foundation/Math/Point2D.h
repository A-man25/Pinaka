/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Point2D.h
 * Description : Geometric Entity : Point
 *
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

namespace pke
{
	class Point2D : public GeomEntity
	{
	public:

		Point2D();
		Point2D(double x, double y);
		Point2D(std::initializer_list<double> list);
		Point2D(const Point2D& other);
		Point2D(Point2D&& other);
		Point2D& operator = (const Point2D& other);
		Point2D& operator = (Point2D&& other);
		double x() const;
		double y() const;
		void setX(double x);
		void setY(double y);
		long entId() const;
		Geom_Entity_type getEntityType() const;
		double distance(const Point2D& other) const;
	private:
		double m_x;
		double m_y;
	};
}
