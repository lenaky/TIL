#include "SimpleList.h"
#include <iostream>
#include <list>
#include <time.h>
#include <random>

#define WIDTH  1920
#define HEIGHT 1080

template < typename T >
T Random( T min_, T max_ )
{
	if( min_ >= max_ )
	{
		return max_;
	}

	static std::minstd_rand gen( ( unsigned int )time( NULL ) );
	std::uniform_int<T> dist( min_, max_ );
	return dist( gen );
}

struct RGB
{
	char r=55;
	char g=55;
	char b=55;
};

struct RGBImage
{
	explicit RGBImage(int w, int h) : _w(w), _h(h) { 
		_rgb_array = new RGB[ _w * _h ];
	}
	~RGBImage()	{
		if( nullptr != _rgb_array )
			delete[] _rgb_array;
	}

	RGBImage& operator=( RGBImage const& rhs )
	{
		if( nullptr != _rgb_array )
			delete[] _rgb_array;

		_w = rhs._w;
		_h = rhs._h;
		_rgb_array = new RGB[ _w * _h ];
		memcpy( _rgb_array, rhs._rgb_array, sizeof( _w * _h * sizeof( RGB ) ) );

		return *this;
	}

	operator void* () {
		return reinterpret_cast<void*>(_rgb_array);
	}

	void SetImage( void* image )
	{
		memcpy( _rgb_array, image, _w * _h * 3 );
	}

	size_t GetSize() const 
	{
		return _w * _h * sizeof(RGB);
	}
	
	RGB* _rgb_array = nullptr;
	int _w = 0;
	int _h = 0;
};

struct TestClass
{
	TestClass() { }
	TestClass(int val) : _value(val) { }
	operator void*( ) { 
		return reinterpret_cast< void* >(&_value);
	}
	int _value = 0;
};

int main()
{
	RGBImage rgb(WIDTH, HEIGHT);
	RGBImage out_rgb(WIDTH, HEIGHT);

	TestLibs::List lst(WIDTH * HEIGHT * 3, 10); // 100개짜리 heap array 만들기.

	TestLibs::List lst_2( sizeof( int ), 20 ); // 4바이트짜리 20개

	std::cout << std::boolalpha << std::endl;
	/*
	for( int i = 0; i < 100000; i++ )
	{
		int rand_val = Random<int>( 1, 1000 );
		if( rand_val % 2 == 0 )
		{
			std::cout << "push" << std::endl;
			lst.Push( rgb );
		}
		else
		{
			std::cout << "pop" << std::endl;
			lst.Pop( out_rgb );
		}
	}
	*/
	int test_index = 0;
	TestClass tc;
	for( int i = 0; i < 100000; i++ )
	{
		int rand_val = Random<int>( 1, 1000 );
		if( rand_val % 2 == 0 )
		{
			if( lst_2.Push( TestClass( test_index ) ) )
				test_index++;
		}
		else
		{
			if( lst_2.Pop( tc ) )
				std::cout << tc._value << std::endl;
		}
	}
	return 0;
}