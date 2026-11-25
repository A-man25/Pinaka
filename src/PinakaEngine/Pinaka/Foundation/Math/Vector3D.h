/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Vector3D.h
 * Description : Three-dimensional vector
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 03/10/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/
#pragma once

#include <Pinaka/Core/PinakaEngineInc.h>
#include "MathConstants.h"
#include "Point3D.h"

namespace pke
{
	class PK_API Vector3D
	{
	public:
		Vector3D() = default;
		Vector3D(double x, double y, double z);
		Vector3D(const Point3D& start, const Point3D& end);
		Vector3D(const Vector3D& other) = default;
		Vector3D(Vector3D&& other) noexcept = default;
		~Vector3D() = default;

		Vector3D& operator=(const Vector3D& other) = default;
		Vector3D& operator=(Vector3D&& other) noexcept = default;

		Vector3D operator+(const Vector3D& other) const;
		Vector3D operator-(const Vector3D& other) const;
		Vector3D operator-() const;
		Vector3D operator*(double scalar) const;
		Vector3D operator/(double scalar) const;
		Vector3D& operator+=(const Vector3D& other);
		Vector3D& operator-=(const Vector3D& other);
		Vector3D& operator*=(double scalar);
		Vector3D& operator/=(double scalar);

		bool operator==(const Vector3D& other) const;
		bool operator!=(const Vector3D& other) const;
		bool isApproximatelyEqualTo(const Vector3D& other, double tolerance = PKE_EPSILON) const;

		double getXcomp() const;
		double getYcomp() const;
		double getZcomp() const;
		void setXcomp(double x);
		void setYcomp(double y);
		void setZcomp(double z);

		double getMagnitude() const;
		double getSquaredMagnitude() const;
		bool isZero() const;

		Vector3D normalize() const;
		Vector3D reverseDirection() const;
		Vector3D projectOnto(const Vector3D& axis) const;

		double alignmentWith(const Vector3D& other) const;
		Vector3D crossProduct(const Vector3D& other) const;
		double angleTo(const Vector3D& other) const;
		bool isParallelTo(const Vector3D& other, double tolerance = PKE_EPSILON) const;
		bool isPerpendicularTo(const Vector3D& other, double tolerance = PKE_EPSILON) const;
		bool isSameDirectionAs(const Vector3D& other, double tolerance = PKE_EPSILON) const;
		bool isOppositeDirectionTo(const Vector3D& other, double tolerance = PKE_EPSILON) const;

	private:
		double m_i{ 0.0 };
		double m_j{ 0.0 };
		double m_k{ 0.0 };
	};
}