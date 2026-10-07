/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Point3D.cpp
 * Description : Geometric Entity : Point Implementation
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 03/10/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/
#include "Point3D.h"

namespace pke
{
	Point3D::Point3D(): m_x(0.0),
						m_y(0.0),
						m_z(0.0) 
	{
		m_entId++;
	}

	Point3D::Point3D(double x, double y, double z): m_x(x),
													m_y(y),
													m_z(z)
	{
		m_entId++;
	}

	Point3D::Point3D(std::initializer_list<double> list)
	{
		Vector<double> coord = list;
		m_x = coord[0];
		m_y = coord[1];
		m_z = coord[2];
	}

	Point3D::Point3D(const Point3D& other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
	}

	Point3D::Point3D(Point3D&& other)
	{
		*this = other;
	}

	Point3D& Point3D::operator = (const Point3D& other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;

		return *this;
	}

	Point3D& Point3D::operator = (Point3D&& other)
	{
		*this = other;
		return *this;
	}

	double Point3D::x() const
	{
		return m_x;
	}
	double Point3D::y() const
	{
		return m_y;
	}
	double Point3D::z() const
	{
		return m_z;
	}

	double Point3D::setX(double x)
	{
		m_x = x;
	}

	double Point3D::setY(double y)
	{
		m_y = y;
	}
	double Point3D::setZ(double z)
	{
		m_z = z;
	}

	long Point3D::entId() const
	{
		return m_entId;
	}

	Geom_Entity_type Point3D::getEntityType() const
	{
		return Geom_Entity_type::Point;
	}

	double Point3D::distance(const Point3D& other) const
	{
		return std::hypot(other.m_x - m_x, other.m_y - m_y, other.m_z - m_z);
	}
}