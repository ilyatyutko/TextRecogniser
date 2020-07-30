#pragma once
struct Point {
	int offset_x;
	int offset_y;
	Point(int _x, int _y) :offset_x(_x), offset_y(_y) {};
	Point(const Point& a) :offset_x(a.offset_x), offset_y(a.offset_y) {};
	inline Point operator- (Point a)
	{
		return Point(offset_x - a.offset_x, offset_y - a.offset_y);
	}
	inline Point operator+ (Point a)
	{
		return Point(offset_x + a.offset_x, offset_y + a.offset_y);
	}

	inline Point Up()
	{
		auto target = *this;
		target.offset_y -= 1;
		return target;
	}
	inline Point UpRight()
	{
		auto target = *this;
		target.offset_x += 1, target.offset_y -= 1;
		return target;
	}
	inline Point Right()
	{
		auto target = *this;
		target.offset_x += 1;
		return target;
	}
	inline Point DownRight()
	{
		auto target = *this;
		target.offset_x += 1, target.offset_y += 1;
		return target;
	}
	inline Point Down()
	{
		auto target = *this;
		target.offset_y += 1;
		return target;
	}
	inline Point DownLeft()
	{
		auto target = *this;
		target.offset_x -= 1, target.offset_y += 1;
		return target;
	}
	inline Point Left()
	{
		auto target = *this;
		target.offset_x -= 1;
		return target;
	}
	inline Point UpLeft()
	{
		auto target = *this;
		target.offset_x -= 1, target.offset_y -= 1;
		return target;
	}
};