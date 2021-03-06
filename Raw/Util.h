#pragma once
#include <cmath>

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;
	Vector2() {}
	Vector2(float X, float Y) 
	{
		x = X;
		y = Y;
	}
	~Vector2() {}

	D2D1_POINT_2F ToRenderPoint()
	{
		D2D1_POINT_2F out;
		out.x = this->x;
		out.y = this->y;
		return out;
	}
	static D2D1_POINT_2F* ToRenderPoints(Vector2* points, int num)
	{
		D2D1_POINT_2F* out = new D2D1_POINT_2F[num];
		for (int i = 0; i < num; i++)
		{
			*(out + i) = (points + i)->ToRenderPoint();
		}
		return out;
	}

	float Distance(Vector2 other) {
		float dX = x - other.x;
		float dY = y - other.y;
		return std::sqrt(dX*dX + dY*dY);
	}

	Vector2 operator+ (Vector2 const& other)
	{
		Vector2 res;
		res.x = x + other.x;
		res.y = y + other.y;
		return res;
	}
	Vector2 operator- (Vector2 const& other)
	{
		Vector2 res;
		res.x = x - other.x;
		res.y = y - other.y;
		return res;
	}
	Vector2 operator* (Vector2 const& other)
	{
		Vector2 res;
		res.x = x * other.x;
		res.y = y * other.y;
		return res;
	}
	Vector2 operator/ (Vector2 const& other)
	{
		Vector2 res;
		res.x = x / other.x;
		res.y = y / other.y;
		return res;
	}
	Vector2 operator+= (Vector2 const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2 operator-= (Vector2 const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

private:

};

class GeoLine
{
public:
	GeoLine() {}
	GeoLine(Vector2 b, Vector2 e) {
		begin = b;
		end = e;
	}
	~GeoLine() {}
	float Length() {
		return begin.Distance(end);
	}
	Vector2 begin;
	Vector2 end;
private:

};

struct Color
{
	unsigned char Red = 0;
	unsigned char Green = 0;
	unsigned char Blue = 0;
	short H = 0;
	short S = 0;
	short V = 0;
	char Hex[3];
	Color() {}
	Color(unsigned char r, unsigned char g, unsigned char b)
	{
		Red = r;
		Green = g;
		Blue = b;

	}
};
