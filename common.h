#pragma once
#include <cstdint>
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

struct RenderingContext {
	u32 bpp;
	u32 width;
	u32 height;
	u32 pitch;
	i32 textureSize;
	void* pixels;
};
struct Vec2 {
	i32 x,y;
	inline bool operator==(Vec2 const& rhs) {return this->x==rhs.x && this->y==rhs.y;}
	inline Vec2 operator+(Vec2 const& rhs) {
		return Vec2{this->x + rhs.x, this->y + rhs.y};
	}
	inline Vec2 operator-(Vec2 const& rhs){
		return Vec2{this->x - rhs.x, this->y - rhs.y};
	}
};
struct Vec2f{
	f32 x,y;
	inline bool operator==(Vec2f const& rhs) {return this->x==rhs.x && this->y==rhs.y;}
	inline Vec2f operator+(Vec2f const& rhs) {
		return Vec2f{this->x + rhs.x, this->y + rhs.y};
	}
	inline Vec2f operator-(Vec2f const& rhs){
		return Vec2f{this->x - rhs.x, this->y - rhs.y};
	}
	inline Vec2f operator +=(Vec2f const&rhs) {
		//return Vec2f{this->x + rhs.x, this->y + rhs.y};
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline Vec2f operator +=(f32 const&rhs) {
		//return Vec2f{this->x + rhs.x, this->y + rhs.y};
		this->x += rhs;
		this->y += rhs;
		return *this;
	}
	inline Vec2f operator -=(f32 const&rhs) {
		//return Vec2f{this->x + rhs.x, this->y + rhs.y};
		this->x -= rhs;
		this->y -= rhs;
		return *this;
	}
};
