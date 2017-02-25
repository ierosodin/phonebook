typedef struct __MEMORY_POOL {
    char *next;
    char *head;
    char *tail;
} m_pool;

m_pool *pool_allocate(int size);
void *pool_access(m_pool *pool, int size);
void pool_free(m_pool *pool);
