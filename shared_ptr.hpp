#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H

#include "Counter.hpp"
template <class T>
class Weak_Ptr;

namespace mystl{
	
	template <class T>
	class Shared_Ptr{
		public:
			template <class U>
			friend class Weak_Ptr;
			Shared_Ptr(T* p = 0):_ptr(p) 
			{
				cnt = new Counter();
				if (p) cnt->s = 1;
			}
			
			Shared_Ptr(const Shared_Ptr<T>& s) : _ptr(s._ptr), cnt(s.cnt)
			{
				if (cnt) cnt->s++;
			}
			Shared_Ptr(const Weak_Ptr<T>& w) : _ptr(w._ptr), cnt(w.cnt)//friend class
			{
				if (cnt) cnt->s++;
			}
			Shared_Ptr& operator=(const Shared_Ptr<T> &s)
			{
				if (this != &s) {
					release();
					cnt = s.cnt;
					_ptr = s._ptr;
					if (cnt) cnt->s++;
				}
				return *this;
			}
			Shared_Ptr& operator=(const Weak_Ptr<T> &s)
			{
				release();
				cnt = s.cnt;
				_ptr = s._ptr;
				if (cnt) cnt->s++;
				return *this;
			}
			~Shared_Ptr()
			{
				release();
			}
			
		public:
			T& operator*()
			{
				return *_ptr;
			}
			T* operator->()
			{
				return _ptr;
			}
		private:
			void release()
			{
				cnt->s--;
				if (cnt->s < 1) {
					delete _ptr;
					_ptr = NULL;
					if (cnt->w < 1) {
						delete cnt;
						cnt = NULL;
					}
				}
			}
		private:
			T* _ptr;
			mystl::Counter* cnt;
	};
}

#endif