#pragma once

#include "eFenceType.h"

namespace lab5
{
	enum class eFenceInfo
	{
		FENCEUSECOUNT = 4,
	};

	class IFenceable
	{
	public:
		virtual unsigned int GetMinimumFencesCount() const = 0;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const = 0;
	};
}