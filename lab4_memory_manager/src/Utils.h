#pragma once

#include <cstdint>

class Utils final
{
public:
	static size_t CalculateAlign(const size_t currentOffset, const size_t alignment = 16u)
	{
		return (currentOffset + alignment - 1u) & ~(alignment - 1u);
	}

	typedef struct
	{
		float x, y; // left-top corner
		float width, height;

	}Rectangle;

	bool RectanglesCollide(const Rectangle& r1, const Rectangle& r2) const
	{
		return (r1.x + r1.width < r2.x || r2.x + r2.width < r1.x
			|| r1.y + r1.height < r2.y || r2.y + r2.height < r1.y);

		/* 
			t1			t2
		l1		r1  l2		r2
			b1			b2
		
			t2			t1
		l2		r2  l1		r1
			b2			b1
		*/

	}
};