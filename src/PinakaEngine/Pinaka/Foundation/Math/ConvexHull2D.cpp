
/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : ConvexHull2D.cpp
 * Description : Geometric Entity : ConvexHull2D Implementations
 * Author      : Aman Rajesh Choudhari
 * Created On  : 11/11/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#include "ConvexHull2D.h"
#include <limits>
#include <stdexcept>
#include <cmath>

namespace pke
{
    ConvexHull2D::ConvexHull2D(const Point2DList& inputList)
    {
        if (inputList.empty())
            throw std::runtime_error(
                "Can't create ConvexHull2D, No points.");

        for (const auto& point : inputList)
        {
            if (!std::isfinite(point.x()) ||
                !std::isfinite(point.y()))
                throw std::invalid_argument(
                    "Invalid point coordinates.");
        }

        m_lowerX = inputList.front();
        m_lowerY = inputList.front();
        m_upperX = inputList.front();
        m_upperY = inputList.front();

        registerExtentPolygon(inputList);
        processDimensions();
        processHull(inputList);
    }

    Point2DList ConvexHull2D::filterInsidePoints(const Point2DList& inputList) const
    {
        Point2DList exteriorPointList;
        Point2DList candidatePointList = filterExtentPoints(inputList);

        for (size_t i = 0; i < m_polygon.size(); i++)
        {
            const Point2D& start = m_polygon[i];
            const Point2D& end = m_polygon[(i + 1) % m_polygon.size()];

            Vector2D edgeVec = end - start;

            for (const auto& candidatePoint : candidatePointList)
            {
                if (!isPointOnInteriorSide(edgeVec, start, candidatePoint))
                {
                    if (!isInList(candidatePoint, exteriorPointList))
                        exteriorPointList.push_back(candidatePoint);
                }
            }
        }

        return exteriorPointList;
    }

    void ConvexHull2D::processHull(const Point2DList& inputPoints)
    {
        m_hullPoints.clear();

        if (m_polygon.size() == 1)
        {
            m_hullPoints.push_back(m_polygon.front());
            return;
        }

        Point2DList exteriorPoints = filterInsidePoints(inputPoints);

        for (size_t i = 0; i < m_polygon.size(); i++)
        {
            const Point2D& start = m_polygon[i];
            const Point2D& end = m_polygon[(i + 1) % m_polygon.size()];

            Point2DList edgeCandidates =
                filterExteriorPoints(start, end, exteriorPoints);

            processEdge(start, end, edgeCandidates);
        }
    }

    Point2DList ConvexHull2D::findFarthestExteriorPoint(const Point2D& start, const Point2D& end, const Point2DList& candidateList) const
    {
        double minSign = 0.0;
        Point2DList resPointList;

        Vector2D edgeVec = end - start;

        for (const auto& candidate : candidateList)
        {
            Vector2D candidateVec = candidate - start;

            double cross = edgeVec.signedTurnTo(candidateVec);

            if (!std::isfinite(cross))
                throw std::overflow_error("Invalid cross product.");

            if (cross < minSign)
            {
                minSign = cross;

                resPointList.clear();
                resPointList.push_back(candidate);
            }
            else if (cross == minSign && !resPointList.empty())
            {
                const Point2D& currentPoint = resPointList.front();

                // Handle points having equal perpendicular distance.

                if (candidate.x() < currentPoint.x() ||
                    (candidate.x() == currentPoint.x() &&
                        candidate.y() < currentPoint.y()))
                {
                    resPointList.front() = candidate;
                }
            }
        }

        return resPointList;
    }

    bool ConvexHull2D::isPointOnInteriorSide(const Vector2D& edgeVec, const Point2D& start, const Point2D& candidatePoint) const
    {
        Vector2D candidateVec = candidatePoint - start;

        double cross = edgeVec.signedTurnTo(candidateVec);

        if (!std::isfinite(cross))
            throw std::overflow_error("Invalid cross product.");

        if (cross >= 0.0)
            return true;

        return false;
    }

    void ConvexHull2D::processEdge(const Point2D& start, const Point2D& end, const Point2DList& exteriorPoints)
    {
        Point2DList farthestPointList =
            findFarthestExteriorPoint(start, end, exteriorPoints);

        // Base case: No exterior point exists.

        if (farthestPointList.empty())
        {
            m_hullPoints.push_back(start);
            return;
        }

        Point2D farthestPoint = farthestPointList.front();

        // Collect exterior candidates for the first new edge.

        Point2DList firstEdgeCandidates =
            filterExteriorPoints(start, farthestPoint, exteriorPoints);

        // Collect exterior candidates for the second new edge.

        Point2DList secondEdgeCandidates =
            filterExteriorPoints(farthestPoint, end, exteriorPoints);

        // Process the first new edge.

        processEdge(start, farthestPoint, firstEdgeCandidates);

        // Process the second new edge.

        processEdge(farthestPoint, end, secondEdgeCandidates);
    }

    Point2DList ConvexHull2D::filterExteriorPoints(const Point2D& start, const Point2D& end, const Point2DList& candidateList) const
    {
        Point2DList exteriorPointList;

        Vector2D edgeVec = end - start;

        for (const auto& candidatePoint : candidateList)
        {
            if (candidatePoint == start || candidatePoint == end)
                continue;

            if (!isPointOnInteriorSide(edgeVec, start, candidatePoint))
                exteriorPointList.push_back(candidatePoint);
        }

        return exteriorPointList;
    }

    Point2DList ConvexHull2D::filterExtentPoints(const Point2DList& inputList) const
    {
        Point2DList list;

        for (const auto& val : inputList)
        {
            if (m_lowerX == val || m_upperX == val ||
                m_lowerY == val || m_upperY == val)
                continue;

            list.push_back(val);
        }

        return list;
    }

    void ConvexHull2D::processDimensions()
    {
        m_length = m_upperX.x() - m_lowerX.x();
        m_width = m_upperY.y() - m_lowerY.y();

        if (!std::isfinite(m_length) ||
            !std::isfinite(m_width))
            throw std::overflow_error("Invalid hull dimensions.");
    }

    void ConvexHull2D::registerExtentPolygon(const Point2DList& inputList)
    {
        m_polygon.clear();

        for (const auto& currentPoint : inputList)
        {
            if (currentPoint.x() < m_lowerX.x() ||
                (currentPoint.x() == m_lowerX.x() &&
                    currentPoint.y() < m_lowerX.y()))
                m_lowerX = currentPoint;

            if (currentPoint.y() < m_lowerY.y() ||
                (currentPoint.y() == m_lowerY.y() &&
                    currentPoint.x() < m_lowerY.x()))
                m_lowerY = currentPoint;

            if (currentPoint.x() > m_upperX.x() ||
                (currentPoint.x() == m_upperX.x() &&
                    currentPoint.y() > m_upperX.y()))
                m_upperX = currentPoint;

            if (currentPoint.y() > m_upperY.y() ||
                (currentPoint.y() == m_upperY.y() &&
                    currentPoint.x() > m_upperY.x()))
                m_upperY = currentPoint;
        }

        // Anticlockwise polygon.

        Point2DList extentPoints =
        {
            m_upperY,
            m_lowerX,
            m_lowerY,
            m_upperX
        };

        // Remove duplicate extreme points.

        for (const auto& point : extentPoints)
        {
            if (!isInList(point, m_polygon))
                m_polygon.push_back(point);
        }
    }

    bool ConvexHull2D::isInList(const Point2D& point, const Point2DList& list) const
    {
        for (const auto& val : list)
        {
            if (val == point)
                return true;
        }

        return false;
    }

    const Point2DList& ConvexHull2D::getHullPoints() const
    {
        return m_hullPoints;
    }

    unsigned int ConvexHull2D::getPointCount() const
    {
        if (m_hullPoints.size() >
            (std::numeric_limits<unsigned int>::max)())
            throw std::overflow_error("Hull point count overflow.");

        return static_cast<unsigned int>(m_hullPoints.size());
    }

    double ConvexHull2D::getLength() const
    {
        return m_length;
    }

    double ConvexHull2D::getWidth() const
    {
        return m_width;
    }

    long ConvexHull2D::entId() const
    {
        return -1;
    }

    Geom_Entity_type ConvexHull2D::getEntityType() const
    {
        return Geom_Entity_type::Polygon;
    }

    Point2D ConvexHull2D::getVerticalMinExtent() const
    {
        return m_lowerY;
    }

    Point2D ConvexHull2D::getVerticalMaxExtent() const
    {
        return m_upperY;
    }

    Point2D ConvexHull2D::getHorizontalMinExtent() const
    {
        return m_lowerX;
    }

    Point2D ConvexHull2D::getHorizontalMaxExtent() const
    {
        return m_upperX;
    }
}
