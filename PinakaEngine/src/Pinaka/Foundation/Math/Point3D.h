/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Point3D.h
 * Description : Geometric Entity : Point
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 03/10/2026
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
	class Point3D : public GeomEntity
	{      
	public:

		Point3D();
		Point3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}
		Point3D(std::initializer_list<double> list);
		Point3D(const Point3D& other);
		Point3D(Point3D&& other);
		Point3D& operator = (const Point3D& other);
		Point3D& operator = (Point3D&& other);
		double x() const;
		double y() const;
		double z() const;
		double setX(double x);
		double setY(double y);
		double setZ(double z);
		long entId() const;
		Geom_Entity_type getEntityType() const;
		double distance(const Point3D& other) const;
	private:
		double m_x;
		double m_y;
		double m_z;
	};
}