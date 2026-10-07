/*------------------------------------------------------------------------
 * Project     : PinakaEngine
 * File        : GeomEntity.h
 * Description : Geometric Entity : Base Entity
 *
 * Author      : Aman Rajesh Choudhari
 * Created On  : 20/09/2026
 *
 * Copyright (c) 2026 Aman Rajesh Choudhari
 * All rights reserved.
 *------------------------------------------------------------------------*/

#include <Pinaka/Core/Core.h>

namespace pke
{
	enum class Geom_Entity_type
	{
		Undefined = 0,
		Line,
		Point,
		Plane,
		Axis,
		Circle,
		Polygon,

	};

	class GeomEntity
	{
	public:
		virtual long entId() const = 0;
		virtual Geom_Entity_type getEntityType() const = 0;
	protected:
		static long m_entId;
	};
}