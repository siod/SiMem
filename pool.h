namespace SiLib {
	namespace SiMem {
	class PoolAllocator {
		class AlignedObj {
			float aligned;
		};
		public:
			PoolAllocator(int size = 10000):m_pPool(0),m_pFreeList(0),m_Size(size),m_FreeIndex(size-1) {
				m_pPool = new AlignedObj[size];
				m_pFreeList = new int[size];
				for (int i(0);i != size;++i)
					m_pFreeList[i] = i;
			}

			~PoolAllocator() {
				delete[] m_pFreeList;
				delete[] m_pPool;
			}

			void Free(void* addr) {
				int index(((AlignedObj*)addr - m_pPool)/sizeof(AlignedObj));
				m_pFreeList[++m_FreeIndex] = index;
			}

			void Clear() {
				m_FreeIndex = m_Size-1;
				for (int i(0);i != m_Size;++i)
					m_pFreeList[i] = i;
			}

			void* Allocate() {
				return (void*)&m_pFreeList[m_FreeIndex--];
			}


		private:
			AlignedObj* m_pPool;
			int* m_pFreeList;
			int m_Size;
			int m_FreeIndex;
	};

	};
};
