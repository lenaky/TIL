#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

#include <iostream>
#include <windows.h>
#define OUT

namespace TestLibs
{
	class List
	{
	public:
		explicit List( size_t const item_size, size_t const count ) : _item_size( item_size ), _handling_count( count )
		{
			InitializeSRWLock( &_lock );
			_AllocMemory();
		}

		~List()
		{
			if( nullptr != _buffer )
			{
				for (size_t i = 0; i < _handling_count; i++)
					delete _buffer[i];
				delete[] _buffer;
			}
		}

		// 성공 true, 실패 false
		bool Push( void const* value )
		{
			AcquireSRWLockExclusive( &_lock );
			// 다음번 넣을 인덱스가 pop해야할 인덱스라면 아직 안빼갔으므로 실패
			if (_insert_index == _pop_index && _pushed_count != 0)
			{
				ReleaseSRWLockExclusive( &_lock );
				return false;
			}
			memcpy(_buffer[_insert_index], value, _item_size);
			_insert_index = (_insert_index + 1) % _handling_count;
			if (-1 == _pop_index)
				_pop_index = 0;
			_pushed_count++;
			ReleaseSRWLockExclusive( &_lock );
			return true;
		}

		// 성공 true, 실패 false
		bool Pop(OUT void* value)
		{
			AcquireSRWLockExclusive( &_lock );
			if( -1 == _pop_index || (_insert_index == _pop_index && _pushed_count == 0))
			{
				ReleaseSRWLockExclusive( &_lock );
				return false;
			}
			std::cout << "Poped data. at index[" << _pop_index << "]" << std::endl;
			memcpy(value, _buffer[_pop_index], _item_size);
			_pop_index = ( _pop_index + 1 ) % _handling_count;
			_pushed_count--;
			ReleaseSRWLockExclusive( &_lock );
			return true;
		}

	private:
		void _AllocMemory()
		{
			if( 0 == _handling_count )
			{
				return;
			}

			_buffer = new char* [_handling_count];
			for (size_t i = 0; i < _handling_count; i++)
			{
				_buffer[i] = new char[_item_size];
			}
		}

	private:
		char** _buffer = nullptr;
		int _insert_index = 0; // 최근 push 한 인덱스
		int _pop_index = -1; // pop 할때 접근해야할 인덱스
		int _pushed_count = 0;
		size_t _handling_count = 0;
		size_t _item_size = 0;
		SRWLOCK _lock;
	};
}

#endif
