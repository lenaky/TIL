#include <iostream>
#include <chrono>
#include <time.h>
#include <random>

int* g_arr = nullptr;

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

void CopyHeap( int const arr_src[], size_t const count )
{
	int* arr = new int[ count ];
	memcpy( arr, arr_src, sizeof( int ) * count );
	delete[] arr;
}

void CopyLocal( int const arr_src[], size_t const count )
{
	memcpy( g_arr, arr_src, sizeof( int ) * count );
}

int main()
{
	size_t const arr_size = 200000;
	int* arr = new int[ arr_size ];
	g_arr = new int[ arr_size ];
	
	for( int i = 0 ; i < arr_size; i++ )
	{
		arr[ i++ ] = Random<int>( 0, 10000 );
	}

	{
		auto now = std::chrono::system_clock::now();
		for( int i = 0; i < arr_size; i++ )
		{
			CopyHeap( arr, arr_size );
		}
		std::cout << "Alloc heap and Copy : " <<
			std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;
	}
	// ������ ��Ʈ�� ��û���� �߻��ϰ� ��. �ӵ��� ����
	
	{
		auto now = std::chrono::system_clock::now();
		for( int i = 0; i < arr_size; i++ )
		{
			CopyLocal( arr, arr_size );
		}
		std::cout << "Reuse buffer Copy : " <<
			std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;
	}
	// ������ ��Ʈ ���� �Ͼ�� �ʰ� �ӵ��� Heap �Ź� �Ҵ��ؼ� �����ϴ� �Ϳ� ���� ����
	
	delete[] g_arr;
	delete[] arr;

	return 0;
}