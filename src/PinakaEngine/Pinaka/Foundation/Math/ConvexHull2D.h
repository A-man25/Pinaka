
/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : ConvexHull2D.h
 * Description : Geometric Entity : ConvexHull2D (Convex Hull Algorithm)
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
#include "Vector2D.h"

#include <vector>

typedef std::vector<pke::Point2D> Point2DList;

namespace pke
{
    class PK_API ConvexHull2D : public GeomEntity
    {
    public:
        ConvexHull2D(const Point2DList& inputPointList);

        Point2D getVerticalMinExtent() const;
        Point2D getVerticalMaxExtent() const;
        Point2D getHorizontalMinExtent() const;
        Point2D getHorizontalMaxExtent() const;

        double getLength() const;
        double getWidth() const;

        /*
         * Returns the convex hull vertices in
         * anticlockwise order.
         *
         * The starting point is not repeated
         * at the end of the list.
         */
        const Point2DList& getHullPoints() const;

        unsigned int getPointCount() const;

        long entId() const override;
        Geom_Entity_type getEntityType() const override;

    private:

        /*
         * Identifies the four extreme points and
         * constructs the initial polygon.
         */
        void registerExtentPolygon(const Point2DList& inputPointList);

        /*
         * Calculates the axis-aligned dimensions
         * of the input geometry.
         */
        void processDimensions();

        /*
         * Checks whether a point already exists
         * in the supplied point list.
         */
        bool isInList(const Point2D& point, const Point2DList& list) const;

        /*
         * Removes the four extreme points from
         * the input point list.
         */
        Point2DList filterExtentPoints(const Point2DList& inputList) const;

        /*
         * Removes points lying inside or on the
         * boundary of the initial polygon.
         */
        Point2DList filterInsidePoints(const Point2DList& inputList) const;

        /*
         * Determines whether a candidate point
         * lies on the interior side of a
         * directed anticlockwise polygon edge.
         */
        bool isPointOnInteriorSide(const Vector2D& edgeVec, const Point2D& start, const Point2D& candidatePoint) const;

        /*
         * Returns only the points lying outside
         * the specified directed edge.
         */
        Point2DList filterExteriorPoints(const Point2D& start, const Point2D& end, const Point2DList& candidateList) const;

        /*
         * Finds the farthest exterior point from
         * the line formed by the edge.
         *
         * Returns an empty list if no exterior
         * point exists, otherwise a single point.
         */
        Point2DList findFarthestExteriorPoint(const Point2D& start, const Point2D& end, const Point2DList& candidateList) const;

        /*
         * Processes all edges of the initial
         * polygon to construct the convex hull.
         */
        void processHull(const Point2DList& inputPoints);

        /*
         * Recursively subdivides an edge until
         * no exterior candidates remain.
         */
        void processEdge(const Point2D& start, const Point2D& end, const Point2DList& exteriorPoints);

    private:

        Point2DList m_hullPoints;
        Point2DList m_polygon;

        double m_length = 0.0;
        double m_width = 0.0;

        Point2D m_lowerX;
        Point2D m_upperX;
        Point2D m_lowerY;
        Point2D m_upperY;
    };
}
