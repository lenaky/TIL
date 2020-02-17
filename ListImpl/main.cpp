#include "SimpleList.h"
#include <list>

#define IMAGE_SIZE 1920 * 1080
struct RGB
{
	char r;
	char g;
	char b;
};

struct RGBImage
{
	RGBImage(int w, int h) : _w(w), _h(h) { 
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

	void SetImage( void* image )
	{
		memcpy( _rgb_array, image, _w * _h * 3 );
	}
	
	RGB* _rgb_array = nullptr;
	int _w = 0;
	int _h = 0;
};

int main()
{
	return 0;
}