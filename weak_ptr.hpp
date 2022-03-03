#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "Counter.hpp"

template <class T>
class Shared_Ptr;

namespace mystl{
	template <class T>
	class Weak_Ptr{
		public:
			template<class U>
			friend class Shared_Ptr;
			Weak_Ptr():_ptr(0), cnt(0){}
			Weak_Ptr(const Shared_Ptr<T>& s):_ptr(s._ptr), cnt(s.cnt)//friend class
			{
				if (cnt) cnt->w++;
			}
			Weak_Ptr(const Weak_Ptr<T>& w):_ptr(w._ptr), cnt(w.cnt)
			{
				if (cnt) cnt->w++;
			}
			~Weak_Ptr()
			{
				release();
			}
			
			Weak_Ptr<T>& operator=(const Weak_Ptr<T>& w)
			{
				if (this != &w) {
					release();
					cnt = w.cnt;
					_ptr = w._ptr;
					if (cnt) cnt->w++;
				}
				return *this;
			}
			Weak_Ptr<T>& operator=(const Shared_Ptr<T>& s)
			{
				release();
				cnt = s.cnt;
				_ptr = s._ptr;//friend class
				if (cnt) cnt->w++;
				return *this;
			}
			Shared_Ptr<T> lock()
			{
				return Shared_Ptr<T>(*this);
			}
			
		private:
			void release()
			{
				if (cnt)
				{
					cnt->w--;
					if (cnt->w < 1 && cnt->s < 1)
					{
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