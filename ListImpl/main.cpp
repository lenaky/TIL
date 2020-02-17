#include "SimpleList.h"
#include <iostream>
#include <list>

#define WIDTH  1920
#define HEIGHT 1080

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

int main()
{
	RGBImage rgb(WIDTH, HEIGHT);
	RGBImage out_rgb(WIDTH, HEIGHT);

	TestLibs::List lst(WIDTH * HEIGHT * 3, 10); // 100개짜리 heap array 만들기.

	std::cout << std::boolalpha << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Pop(out_rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	std::cout << lst.Push(rgb) << std::endl;
	return 0;
}