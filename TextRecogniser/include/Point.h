#pragma once
struct Point {
	int x;
	int y;
	Point(int _x, int _y) :x(_x), y(_y) {};
	Point(const Point& a) :x(a.x), y(a.y) {};

	inline Point Up()
	{
		auto target = *this;
		target.y - 1;
		return target;
	}
	inline Point UpRight()
	{
		auto target = *this;
		target.x + 1, target.y - 1;
		return target;
	}
	inline Point Right()
	{
		auto target = *this;
		target.x + 1;
		return target;
	}
	inline Point DownRight()
	{
		auto target = *this;
		target.x + 1, target.y + 1;
		return target;
	}
	inline Point Down()
	{
		auto target = *this;
		target.y + 1;
		return target;
	}
	inline Point DownLeft()
	{
		auto target = *this;
		target.x - 1, target.y + 1;
		return target;
	}
	inline Point Left()
	{
		auto target = *this;
		target.x - 1;
		return target;
	}
	inline Point UpLeft()
	{
		auto target = *this;
		target.x - 1, target.y - 1;
		return target;
	}
};