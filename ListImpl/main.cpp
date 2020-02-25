#include "SimpleList.h"
#include <iostream>
#include <list>
#include <time.h>
#include <random>
#include <chrono>

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

namespace SLL // simple linked list
{
	struct Node
	{
		bool _head = false;
		void* _data = nullptr;
		Node* pNext = nullptr;
	};

	Node* CreateHeadNode()
	{
		Node* node = new Node;
		node->_head = true;
		return node;
	}

	Node* CreateNode( void* data, size_t size )
	{
		Node* node = new Node;
		node->_data = new char[ size ];
		memcpy( node->_data, data, size );
		return node;
	}

	void InsertNode( Node** head, Node* node )
	{
		if( nullptr == head )
			return;
		
		if( nullptr == (*head)->pNext )
		{
			(*head)->pNext = node;
		}
		else
		{
			Node* chaser = (*head)->pNext;
			while( chaser->pNext != nullptr )
				chaser = chaser->pNext;
			chaser->pNext = node;
		}
	}

	Node* PopNode( Node* head )
	{
		if( nullptr == head->pNext )
			return nullptr;

		Node* temp = head->pNext;
		head->pNext = temp->pNext;
		return temp;
	}

	void ReleaseNode( Node* node )
	{
		if (nullptr != node )
			delete[] node;
	}
};

int main()
{
	std::cout << std::boolalpha << std::endl;
	std::cout << "Measuring Start..." << std::endl;

	TestLibs::List<RGBImage, WIDTH*HEIGHT * 3, 30> lst;	
	RGBImage rgb( WIDTH, HEIGHT );
	RGBImage out_rgb( WIDTH, HEIGHT );
	auto now = std::chrono::system_clock::now();
	for( int i = 0; i < 1000; i++ )
	{
		int rand_val = Random<int>( 1, 1000 );
		if( rand_val % 2 == 0 )
		{
			lst.Push( rgb );
		}
		else
		{
			lst.Pop( out_rgb );
		}
	}
	std::cout << "Static Copy : " <<
		std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;

	SLL::Node* pHead = SLL::CreateHeadNode();
	char* pData = new char[ WIDTH*HEIGHT * 3 ];

	now = std::chrono::system_clock::now();
	for( int i = 0; i < 1000; i++ )
	{
		int rand_val = Random<int>( 1, 1000 );
		if( rand_val % 2 == 0 )
		{
			SLL::Node* pNode = SLL::CreateNode( pData, WIDTH*HEIGHT * 3 );
			SLL::InsertNode( &pHead, pNode );
		}
		else
		{
			SLL::Node* pNode = SLL::PopNode( pHead );
			if( nullptr != pNode )
			{
				delete[]pNode->_data;
				delete pNode;
			}
		}
	}
	std::cout << "Heap Copy : " <<
		std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;

	delete[] pData;

	/*
	int test_index = 0;
	TestClass tc;
	TestLibs::List<TestClass> lst_2;
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
	*/

	return 0;
}