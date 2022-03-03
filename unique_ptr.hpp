#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

namespace mystl{
	template <class T>
	class unique_ptr{
		public:
			unique_ptr(T* pResource = nullptr):m_pResource(pResource){}
			~unique_ptr() 
			{
				del();
			}
		public:
			void reset(T* pResource)
			{
				del();
				m_pResource = pResource;
			}
			
			T* release()
			{
				T* pTemp = m_pResource;
				m_pResource = nullptr;
				return pTemp;
			}
			T* get() 
			{
				return m_pResource;
			}
		public:
			operator bool()
			{
				std::cout << "bool" << std::endl;
				return m_pResource != nullptr;
			}
			T& operator*()
			{
				return *m_pResource;
			}
			T* operator->()
			{
				return m_pResource;
			}
		private:
			void del()
			{
				if (m_pResource == nullptr) return;
				delete m_pResource;
				m_pResource = nullptr;
			}
		private:
			//forbidden;
			unique_ptr(const unique_ptr&) = delete;
			unique_ptr& operator=(const unique_ptr&)=delete;
		private:
			T* m_pResource;
	};
}

#endif