#ifndef __SIMPLE_LIST_H__
#define __SIMPLE_LIST_H__

namespace TestLibs
{
	template<typename T>
	class List
	{
	public:
		List( size_t count ) : _handling_count( count )
		{
			InitializeSRWLock( &_lock );
		}
		~List()
		{
			if( nullptr != _buffer )
			{
				delete[] _buffer;
			}
		}

		// 성공 true, 실패 false
		bool Push( T const& value )
		{
			AcquireSRWLockExclusive( _lock );
			if( _insert_index == _pop_index )
			{
				ReleaseSRWLockExclusive( _lock );
				return false;
			}
			_buffer[ _insert_index ] = value;
			_insert_index = ( _insert_index + 1 ) % _handling_count;
			if( -1 == _pop_index )
				_pop_index = 0; // 하나라도 들어가야.. 비로소 index 부여
			ReleaseSRWLockExclusive( _lock );
			return true;
		}

		// 성공 true, 실패 false
		bool Pop(OUT T& value)
		{
			AcquireSRWLockExclusive( _lock );
			if( _insert_index == _pop_index || -1 == _pop_index )
			{
				ReleaseSRWLockExclusive( _lock );
				return false;
			}
			value = buffer[ _pop_index ];
			_pop_index = ( _pop_index + 1 ) % _handling_count;
			ReleaseSRWLockExclusive( _lock );
			return t;
		}

	private:
		void _AllocMemory()
		{
			if( 0 == _handling_count )
			{
				return;
			}

			_buffer = new T[ _handling_count ];
		}

	private:
		T* _buffer = nullptr;
		int _insert_index = 0;
		int _pop_index = -1;
		size_t _handling_count = 0;

		SRWLOCK _lock;
	};
}


#endif
