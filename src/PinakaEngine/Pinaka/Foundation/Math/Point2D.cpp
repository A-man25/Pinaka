/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Point2D.cpp
 * Description : Geometric Entity : Point Implementation
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 11/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/
#include "Point2D.h"

namespace pke
{
	Point2D::Point2D(): m_x(0.0),
						m_y(0.0)
	{
		m_entId++;
	}

	Point2D::Point2D(double x, double y): m_x(x),
									m_y(y)
	{
		m_entId++;
	}

	Point2D::Point2D(std::initializer_list<double> list)
	{
		Vector<double> coord = list;
		m_x = coord[0];
		m_y = coord[1];
	}

	Point2D::Point2D(const Point2D& other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
	}

	Point2D::Point2D(Point2D&& other)
	{
		*this = other;
	}

	Point2D& Point2D::operator = (const Point2D& other)
	{
		m_x = other.m_x;
		m_y = other.m_y;

		return *this;
	}

	Point2D& Point2D::operator = (Point2D&& other)
	{
		*this = other;
		return *this;
	}

	double Point2D::x() const
	{
		return m_x;
	}

	double Point2D::y() const
	{
		return m_y;
	}

	void Point2D::setX(double x)
	{
		m_x = x;
	}

	void Point2D::setY(double y)
	{
		m_y = y;
	}

	long Point2D::entId() const
	{
		return m_entId;
	}

	Geom_Entity_type Point2D::getEntityType() const
	{
		return Geom_Entity_type::Point;
	}

	double Point2D::distance(const Point2D& other) const
	{
		return std::hypot(other.m_x - m_x, other.m_y - m_y);
	}
}
