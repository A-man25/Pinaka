/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : Vector2D.cpp
 * Description : Geometric Entity : Vector Header
 * Author      : Aman Rajesh Choudhari
 * Created On  : 12/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/
#pragma once

#include <Pinaka/Core/PinakaEngineInc.h>
#include "GeomEntity.h"
#include "Point2D.h"

#pragma once

#include "GeomEntity.h"

namespace pke
{
    class Point2D;

    class Vector2D : public GeomEntity
    {
    public:

        // ============================================================
        // CONSTRUCTORS & DESTRUCTOR
        // ============================================================

        /*
         * - Creates a zero vector (0, 0).
         */
        Vector2D();

        /*
         * - Creates a vector using X and Y components.
         * - Example: Vector2D(3, 4).
         */
        Vector2D(double x, double y);

        /*
         * - Creates a displacement vector from start to end.
         * - Direction is from the first point to the second.
         * - Components: (end.x - start.x, end.y - start.y).
         */
        Vector2D(const Point2D& start, const Point2D& end);

        /*
         * - Creates a new vector by copying another vector.
         */
        Vector2D(const Vector2D& other) = default;

        /*
         * - Creates a vector from another movable vector.
         * - Uses default move behavior.
         */
        Vector2D(Vector2D&& other) noexcept = default;

        /*
         * - Destroys the vector object.
         */
        ~Vector2D() = default;


        // ============================================================
        // ASSIGNMENT OPERATORS
        // ============================================================

        /*
         * - Copies another vector's components into this vector.
         * - Returns a reference to the current vector.
         */
        Vector2D& operator=(const Vector2D& other) = default;

        /*
         * - Move-assigns another vector to the current vector.
         * - Returns a reference to the current vector.
         */
        Vector2D& operator=(Vector2D&& other) = default;


        // ============================================================
        // ARITHMETIC OPERATORS
        // ============================================================

        /*
         * - Adds two vectors to produce a resultant vector.
         * - Does not modify either operand.
         * - Example: (3, 4) + (2, 1) = (5, 5).
         */
        Vector2D operator+(const Vector2D& other) const;

        /*
         * - Subtracts another vector from the current vector.
         * - Returns the difference vector.
         * - Does not modify either operand.
         * - Example: (5, 4) - (2, 1) = (3, 3).
         */
        Vector2D operator-(const Vector2D& other) const;

        /*
         * - Reverses the direction of the vector.
         * - Preserves its magnitude.
         * - Returns a new vector.
         * - Example: -(3, 4) = (-3, -4).
         */
        Vector2D operator-() const;

        /*
         * - Multiplies both components by a scalar.
         * - Scales the vector's magnitude.
         * - Negative scalars also reverse direction.
         * - Returns a new vector.
         */
        Vector2D operator*(double scalar) const;

        /*
         * - Divides both components by a scalar.
         * - Returns a new scaled vector.
         * - Division by zero must be handled.
         */
        Vector2D operator/(double scalar) const;

        /*
         * - Adds another vector to the current vector.
         * - Modifies the current vector.
         * - Returns a reference to the current vector.
         */
        Vector2D& operator+=(const Vector2D& other);

        /*
         * - Subtracts another vector from the current vector.
         * - Modifies the current vector.
         * - Returns a reference to the current vector.
         */
        Vector2D& operator-=(const Vector2D& other);

        /*
         * - Multiplies the current vector by a scalar.
         * - Modifies the current vector.
         * - Returns a reference to the current vector.
         */
        Vector2D& operator*=(double scalar);

        /*
         * - Divides the current vector by a scalar.
         * - Modifies the current vector.
         * - Returns a reference to the current vector.
         * - Division by zero must be handled.
         */
        Vector2D& operator/=(double scalar);


        // ============================================================
        // COMPARISON OPERATORS
        // ============================================================

        /*
         * - Checks whether both vectors have identical components.
         * - Performs exact floating-point comparison.
         */
        bool operator==(const Vector2D& other) const;

        /*
         * - Checks whether the vector components differ.
         * - Uses exact floating-point comparison.
         */
        bool operator!=(const Vector2D& other) const;

        /*
         * - Checks whether two vectors are approximately equal.
         * - Accounts for floating-point precision errors.
         * - Uses the specified absolute component tolerance.
         */
        bool isApproximatelyEqualTo(
            const Vector2D& other,
            double tolerance = 1e-9) const;


        // ============================================================
        // ENTITY PROPERTIES
        // ============================================================

        /*
         * - Returns the geometry entity type.
         * - Identifies this entity as a 2D vector.
         */
        Geom_Entity_type getEntityType() const override;

        /*
         * - Returns the X component of the vector.
         */
        double getXcomp() const;

        /*
         * - Returns the Y component of the vector.
         */
        double getYcomp() const;

        /*
         * - Updates the X component of the current vector.
         */
        void setXcomp(double x);

        /*
         * - Updates the Y component of the current vector.
         */
        void setYcomp(double y);


        // ============================================================
        // VECTOR PROPERTIES
        // ============================================================

        /*
         * - Calculates the length or magnitude of the vector.
         * - Formula: sqrt(x*x + y*y).
         * - Always returns a non-negative value.
         */
        double getMagnitude() const;

        /*
         * - Returns the squared magnitude of the vector.
         * - Formula: x*x + y*y.
         * - Useful for length comparisons without square roots.
         */
        double getSquaredMagnitude() const;

        /*
         * - Checks whether both vector components are zero.
         * - Uses exact zero comparison.
         */
        bool isZero() const;


        // ============================================================
        // VECTOR TRANSFORMATIONS
        // ============================================================

        /*
         * - Converts the vector into a unit vector.
         * - Preserves direction and sets magnitude to 1.
         * - Returns a new vector.
         * - Does not modify the original vector.
         * - Zero-length vectors require special handling.
         */
        Vector2D normalize() const;

        /*
         * - Reverses the vector's direction.
         * - Preserves its magnitude.
         * - Returns a new vector.
         * - Equivalent to applying unary minus.
         */
        Vector2D reverseDirection() const;

        /*
         * - Projects the current vector onto another vector.
         * - Returns the component along the specified axis.
         * - Useful for directional movement and geometry.
         * - Does not modify either vector.
         * - The projection axis must be non-zero.
         */
        Vector2D projectOnto(const Vector2D& axis) const;


        // ============================================================
        // SPATIAL RELATIONSHIPS
        // ============================================================

        /*
         * - Calculates the dot product of two vectors.
         * - Measures directional alignment.
         * - Positive: acute angle between vectors.
         * - Zero: perpendicular vectors.
         * - Negative: obtuse angle between vectors.
         * - Returns a scalar value.
         */
        double alignmentWith(const Vector2D& other) const;

        /*
         * - Calculates the signed 2D cross product.
         * - Determines the orientation from this vector
         *   to another vector.
         * - Positive: counterclockwise (left) turn.
         * - Negative: clockwise (right) turn.
         * - Zero: collinear directions.
         * - Returns a scalar, not an angle.
         * - Useful for convex hull and orientation tests.
         */
        double signedTurnTo(const Vector2D& other) const;

        /*
         * - Calculates the angle between two vectors.
         * - Returns the unsigned angle in radians.
         * - Result lies between 0 and PI.
         * - Requires both vectors to be non-zero.
         */
        double angleTo(const Vector2D& other) const;

        /*
         * - Checks whether two vectors are parallel.
         * - Includes vectors pointing in opposite directions.
         * - Requires non-zero vectors.
         * - Uses floating-point tolerance.
         */
        bool isParallelTo(const Vector2D& other) const;

        /*
         * - Checks whether two vectors are perpendicular.
         * - Their dot product should be approximately zero.
         * - Requires non-zero vectors.
         * - Uses floating-point tolerance.
         */
        bool isPerpendicularTo(const Vector2D& other) const;

        /*
         * - Checks whether two vectors point in the same direction.
         * - Magnitudes may differ.
         * - Requires parallel vectors with positive alignment.
         * - Zero vectors have no direction.
         */
        bool isSameDirectionAs(const Vector2D& other) const;

        /*
         * - Checks whether two vectors point in opposite directions.
         * - Magnitudes may differ.
         * - Requires parallel vectors with negative alignment.
         * - Zero vectors have no direction.
         */
        bool isOppositeDirectionTo(const Vector2D& other) const;


    private:

        // ============================================================
        // VECTOR DATA
        // ============================================================

        /*
         * - Horizontal component of the vector.
         */
        double m_Xcomp{ 0.0 };

        /*
         * - Vertical component of the vector.
         */
        double m_Ycomp{ 0.0 };
    };
}