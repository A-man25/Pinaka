#include "Vector3D.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace pke
{
	Vector3D::Vector3D(double x, double y, double z) :
		m_i(x),
		m_j(y),
		m_k(z)
	{
	}

	Vector3D::Vector3D(const Point3D& start, const Point3D& end) :
		m_i(end.x() - start.x()),
		m_j(end.y() - start.y()),
		m_k(end.z() - start.z())
	{
	}

	Vector3D Vector3D::operator+(const Vector3D& other) const
	{
		return Vector3D(m_i + other.m_i, m_j + other.m_j, m_k + other.m_k);
	}

	Vector3D Vector3D::operator-(const Vector3D& other) const
	{
		return Vector3D(m_i - other.m_i, m_j - other.m_j, m_k - other.m_k);
	}

	Vector3D Vector3D::operator-() const
	{
		return Vector3D(-m_i, -m_j, -m_k);
	}

	Vector3D Vector3D::operator*(double scalar) const
	{
		return Vector3D(m_i * scalar, m_j * scalar, m_k * scalar);
	}

	Vector3D Vector3D::operator/(double scalar) const
	{
		if (scalar == 0.0)
		{
			throw std::invalid_argument("Cannot divide a Vector3D by zero.");
		}

		return Vector3D(m_i / scalar, m_j / scalar, m_k / scalar);
	}

	Vector3D& Vector3D::operator+=(const Vector3D& other)
	{
		m_i += other.m_i;
		m_j += other.m_j;
		m_k += other.m_k;
		return *this;
	}

	Vector3D& Vector3D::operator-=(const Vector3D& other)
	{
		m_i -= other.m_i;
		m_j -= other.m_j;
		m_k -= other.m_k;
		return *this;
	}

	Vector3D& Vector3D::operator*=(double scalar)
	{
		m_i *= scalar;
		m_j *= scalar;
		m_k *= scalar;
		return *this;
	}

	Vector3D& Vector3D::operator/=(double scalar)
	{
		if (scalar == 0.0)
		{
			throw std::invalid_argument("Cannot divide a Vector3D by zero.");
		}

		m_i /= scalar;
		m_j /= scalar;
		m_k /= scalar;
		return *this;
	}

	bool Vector3D::operator==(const Vector3D& other) const
	{
		return m_i == other.m_i && m_j == other.m_j && m_k == other.m_k;
	}

	bool Vector3D::operator!=(const Vector3D& other) const
	{
		return !(*this == other);
	}

	bool Vector3D::isApproximatelyEqualTo(const Vector3D& other, double tolerance) const
	{
		return tolerance >= 0.0 &&
			std::fabs(m_i - other.m_i) <= tolerance &&
			std::fabs(m_j - other.m_j) <= tolerance &&
			std::fabs(m_k - other.m_k) <= tolerance;
	}

	double Vector3D::getXcomp() const
	{
		return m_i;
	}

	double Vector3D::getYcomp() const
	{
		return m_j;
	}

	double Vector3D::getZcomp() const
	{
		return m_k;
	}

	void Vector3D::setXcomp(double x)
	{
		m_i = x;
	}

	void Vector3D::setYcomp(double y)
	{
		m_j = y;
	}

	void Vector3D::setZcomp(double z)
	{
		m_k = z;
	}

	double Vector3D::getMagnitude() const
	{
		return std::hypot(m_i, m_j, m_k);
	}

	double Vector3D::getSquaredMagnitude() const
	{
		return m_i * m_i + m_j * m_j + m_k * m_k;
	}

	bool Vector3D::isZero() const
	{
		return m_i == 0.0 && m_j == 0.0 && m_k == 0.0;
	}

	Vector3D Vector3D::normalize() const
	{
		const double magnitude = getMagnitude();
		if (magnitude == 0.0)
		{
			return Vector3D();
		}

		return *this / magnitude;
	}

	Vector3D Vector3D::reverseDirection() const
	{
		return -*this;
	}

	Vector3D Vector3D::projectOnto(const Vector3D& axis) const
	{
		const double axisSquaredMagnitude = axis.getSquaredMagnitude();
		if (axisSquaredMagnitude == 0.0)
		{
			throw std::invalid_argument("Cannot project onto a zero Vector3D.");
		}

		return axis * (alignmentWith(axis) / axisSquaredMagnitude);
	}

	double Vector3D::alignmentWith(const Vector3D& other) const
	{
		return m_i * other.m_i + m_j * other.m_j + m_k * other.m_k;
	}

	Vector3D Vector3D::crossProduct(const Vector3D& other) const
	{
		return Vector3D(
			m_j * other.m_k - m_k * other.m_j,
			m_k * other.m_i - m_i * other.m_k,
			m_i * other.m_j - m_j * other.m_i);
	}

	double Vector3D::angleTo(const Vector3D& other) const
	{
		const double magnitudeProduct = getMagnitude() * other.getMagnitude();
		if (magnitudeProduct == 0.0)
		{
			throw std::invalid_argument("Cannot calculate an angle involving a zero Vector3D.");
		}

		const double cosine = std::clamp(alignmentWith(other) / magnitudeProduct, -1.0, 1.0);
		return std::acos(cosine);
	}

	bool Vector3D::isParallelTo(const Vector3D& other, double tolerance) const
	{
		if (tolerance < 0.0 || isZero() || other.isZero())
		{
			return false;
		}

		return crossProduct(other).getMagnitude() <= tolerance * getMagnitude() * other.getMagnitude();
	}

	bool Vector3D::isPerpendicularTo(const Vector3D& other, double tolerance) const
	{
		if (tolerance < 0.0 || isZero() || other.isZero())
		{
			return false;
		}

		return std::fabs(alignmentWith(other)) <= tolerance * getMagnitude() * other.getMagnitude();
	}

	bool Vector3D::isSameDirectionAs(const Vector3D& other, double tolerance) const
	{
		return isParallelTo(other, tolerance) && alignmentWith(other) > 0.0;
	}

	bool Vector3D::isOppositeDirectionTo(const Vector3D& other, double tolerance) const
	{
		return isParallelTo(other, tolerance) && alignmentWith(other) < 0.0;
	}
}
