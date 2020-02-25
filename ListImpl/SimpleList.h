#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

#include <iostream>
#include <windows.h>
#define OUT

namespace TestLibs
{
	template< typename T, 
			  size_t UnitSize = 100000, 
		      size_t ArrayLength = 10, 
		      typename = typename decltype(std::declval<T>().GetSize()) >
	class List
	{
	private:
		const size_t _array_length = ArrayLength;
		const size_t _unit_size = UnitSize;

	public:
		List()
		{
			InitializeSRWLock( &_lock );
			_AllocMemory();
		}

		~List()
		{
			if( nullptr != _buffer )
			{
				for (size_t i = 0; i < _array_length; i++)
					delete _buffer[i];
				delete[] _buffer;
			}
		}

		// ���� true, ���� false
		bool Push( T& value )
		{
			if( value.GetSize() > _unit_size )
			{
				return false;
			}

			AcquireSRWLockExclusive( &_lock );
			// ������ ���� �ε����� pop�ؾ��� �ε������ ���� �Ȼ������Ƿ� ����
			if (_insert_index == _pop_index && _pushed_count != 0)
			{
				ReleaseSRWLockExclusive( &_lock );
				return false;
			}
			memcpy(_buffer[_insert_index], value, value.GetSize());
			_insert_index = (_insert_index + 1) % _array_length;
			if (-1 == _pop_index)
				_pop_index = 0;
			_pushed_count++;
			ReleaseSRWLockExclusive( &_lock );
			return true;
		}

		// ���� true, ���� false
		bool Pop(OUT T& value)
		{
			if( _unit_size > value.GetSize() )
			{
				return false;
			}

			AcquireSRWLockExclusive( &_lock );
			if( -1 == _pop_index || (_insert_index == _pop_index && _pushed_count == 0))
			{
				ReleaseSRWLockExclusive( &_lock );
				return false;
			}
			memcpy(value, _buffer[_pop_index], _unit_size);
			_pop_index = ( _pop_index + 1 ) % _array_length;
			_pushed_count--;
			ReleaseSRWLockExclusive( &_lock );
			return true;
		}

	private:
		void _AllocMemory()
		{
			if( 0 == _array_length || 0 == _unit_size )
			{
				return;
			}

			_buffer = new char*[ _array_length ];
			for( size_t i = 0; i < _array_length; i++ )
			{
				_buffer[ i ] = new char[ _unit_size ];
			}
		}

	private:
		char** _buffer = nullptr;
		int _insert_index = 0; // �ֱ� push �� �ε���
		int _pop_index = -1; // pop �Ҷ� �����ؾ��� �ε���
		int _pushed_count = 0;
		SRWLOCK _lock;
	};
}

#endif
