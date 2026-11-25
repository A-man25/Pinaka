/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Vector2D.cpp
 * Description : Vector Implementation
 * Author      : Aman Rajesh Choudhari
 * Created On  : 12/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#include "Vector2D.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
	std::pair<double, double> unitComponents(const pke::Vector2D& vector)
	{
		const double scale = (std::max)(std::fabs(vector.getXcomp()), std::fabs(vector.getYcomp()));
		if (scale == 0.0)
		{
			return { 0.0, 0.0 };
		}

		const double x = vector.getXcomp() / scale;
		const double y = vector.getYcomp() / scale;
		const double magnitude = std::hypot(x, y);
		return { x / magnitude, y / magnitude };
	}

	double normalizedDot(const pke::Vector2D& lhs, const pke::Vector2D& rhs)
	{
		const auto lhsUnit = unitComponents(lhs);
		const auto rhsUnit = unitComponents(rhs);
		return lhsUnit.first * rhsUnit.first + lhsUnit.second * rhsUnit.second;
	}
}

namespace pke
{
	Vector2D::Vector2D(double x, double y) :
		m_Xcomp(x),
		m_Ycomp(y)
	{

	}

	Vector2D::Vector2D(const Point2D& start, const Point2D& end) :
		m_Xcomp(end.x() - start.x()),
		m_Ycomp(end.y() - start.y())
	{

	}

	Vector2D Vector2D::operator+(const Vector2D& other) const
	{
		double resXComp = m_Xcomp + other.getXcomp();
		double resYComp = m_Ycomp + other.getYcomp();

		return Vector2D(resXComp, resYComp);
	}

	Vector2D Vector2D::operator-(const Vector2D& other) const
	{
		return Vector2D(m_Xcomp - other.m_Xcomp, m_Ycomp - other.m_Ycomp);
	}

	Vector2D Vector2D::operator -() const
	{
		return Vector2D(m_Xcomp * -1, m_Ycomp * -1);
	}

	Vector2D Vector2D::operator*(double scalar) const
	{
		return Vector2D(m_Xcomp * scalar, m_Ycomp * scalar);
	}

	Vector2D Vector2D::operator/(double scalar) const
	{
		if (scalar == 0.0)
		{
			throw std::invalid_argument("Cannot divide a Vector2D by zero.");
		}

		return Vector2D(m_Xcomp / scalar, m_Ycomp / scalar);
	}

	Vector2D& Vector2D::operator+=(const Vector2D& other)
	{
		m_Xcomp += other.getXcomp();
		m_Ycomp += other.getYcomp();
		return *this;
	}

	Vector2D& Vector2D::operator-=(const Vector2D& other)
	{
		m_Xcomp -= other.m_Xcomp;
		m_Ycomp -= other.m_Ycomp;
		return *this;
	}

	Vector2D& Vector2D::operator*=(double scalar)
	{
		m_Xcomp *= scalar;
		m_Ycomp *= scalar;
		return *this;
	}

	Vector2D& Vector2D::operator/=(double scalar)
	{
		if (scalar == 0.0)
		{
			throw std::invalid_argument("Cannot divide a Vector2D by zero.");
		}

		m_Xcomp /= scalar;
		m_Ycomp /= scalar;
		return *this;
	}

	bool Vector2D::operator==(const Vector2D& other) const
	{
		return (m_Xcomp == other.getXcomp() && m_Ycomp == other.getYcomp());
	}

	bool Vector2D::operator!=(const Vector2D& other) const
	{
		return m_Xcomp != other.getXcomp() || m_Ycomp != other.getYcomp();
	}

	bool Vector2D::isApproximatelyEqualTo(const Vector2D& other, double tolerance) const
	{
		return tolerance >= 0.0 &&
			std::fabs(m_Xcomp - other.m_Xcomp) <= tolerance &&
			std::fabs(m_Ycomp - other.m_Ycomp) <= tolerance;
	}

	double Vector2D::getXcomp() const
	{
		return m_Xcomp;
	}

	double Vector2D::getYcomp() const
	{
		return m_Ycomp;
	}

	void Vector2D::setXcomp(double x)
	{
		m_Xcomp = x;
	}

	void Vector2D::setYcomp(double y)
	{
		m_Ycomp = y;
	}

	double Vector2D::getMagnitude() const
	{
		return std::hypot(m_Xcomp, m_Ycomp);
	}

	double Vector2D::getSquaredMagnitude() const
	{
		return m_Xcomp * m_Xcomp + m_Ycomp * m_Ycomp;
	}

	bool Vector2D::isZero() const
	{
		return m_Xcomp == 0.0 && m_Ycomp == 0.0;
	}

	Vector2D Vector2D::normalize() const
	{
		const auto unit = unitComponents(*this);
		return Vector2D(unit.first, unit.second);
	}

	Vector2D Vector2D::reverseDirection() const
	{
		return -*this;
	}

	Vector2D Vector2D::projectOnto(const Vector2D& axis) const
	{
		if (axis.isZero())
		{
			throw std::invalid_argument("Cannot project onto a zero Vector2D.");
		}

		const auto unit = unitComponents(axis);
		const Vector2D unitAxis(unit.first, unit.second);
		return unitAxis * alignmentWith(unitAxis);
	}

	double Vector2D::alignmentWith(const Vector2D& other) const
	{
		return m_Xcomp * other.m_Xcomp + m_Ycomp * other.m_Ycomp;
	}

	double Vector2D::signedTurnTo(const Vector2D& other) const
	{
		return m_Xcomp * other.m_Ycomp - m_Ycomp * other.m_Xcomp;
	}

	double Vector2D::angleTo(const Vector2D& other) const
	{
		if (isZero() || other.isZero())
		{
			throw std::invalid_argument(
				"Cannot calculate angle with a zero vector");
		}

		const double cosine = std::clamp(normalizedDot(*this, other), -1.0, 1.0);
		return std::acos(cosine);
	}

	bool Vector2D::isParallelTo(const Vector2D& other) const
	{
		if (isZero() || other.isZero())
		{
			return false;
		}

		constexpr double tolerance = PKE_EPSILON;

		const Vector2D thisUnit = normalize();
		const Vector2D otherUnit = other.normalize();

		return std::fabs(thisUnit.signedTurnTo(otherUnit))
			<= tolerance;
	}

	bool Vector2D::isPerpendicularTo(const Vector2D& other) const
	{
		if (isZero() || other.isZero())
		{
			return false;
		}

		constexpr double tolerance = PKE_EPSILON;
		return std::fabs(normalizedDot(*this, other)) <= tolerance;
	}

	bool Vector2D::isSameDirectionAs(const Vector2D& other) const
	{
		return isParallelTo(other) && normalizedDot(*this, other) > 0.0;
	}

	bool Vector2D::isOppositeDirectionTo(const Vector2D& other) const
	{
		return isParallelTo(other) && normalizedDot(*this, other) < 0.0;
	}
}