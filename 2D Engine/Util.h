#pragma once

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
	~GeoLine() {}
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
