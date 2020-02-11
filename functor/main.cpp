#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

struct SortFunctorClass
{
	template<typename T>
	bool operator()( T first, T second )
	{
		return first < second;
	}
} my_functor;

template<typename T>
inline bool bigger( T first, T second )
{
	return first < second;
}

int main()
{
	std::vector<int> vec_src( 100000 ); // 10만개 선언
	std::iota( vec_src.rbegin(), vec_src.rend(), 0 );
	auto vec = vec_src;

	auto now = std::chrono::system_clock::now();
	std::sort( vec.begin(), vec.end(), bigger<int> );
	std::cout << "Function Pointer = " << vec[0] << "," << vec[1] << "," << vec[2] << " >> " <<
		std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;

	vec = vec_src;

	now = std::chrono::system_clock::now();
	std::sort( vec.begin(), vec.end(), my_functor );
	std::cout << "Functor = " << vec[ 0 ] << "," << vec[ 1 ] << "," << vec[ 2 ] << " >> " <<
		std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;

	vec = vec_src;

	now = std::chrono::system_clock::now();
	std::sort( vec.begin(), vec.end(), []( int first, int second ) -> int {
		return first < second;
	} );
	std::cout << "Lambda = " << vec[ 0 ] << "," << vec[ 1 ] << "," << vec[ 2 ] << " >> " <<
		std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now() - now ).count() << std::endl;

	return 0;
}