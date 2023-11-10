#include "../threadpool/threadpool.h"
#include <future>

class pool
{
public:
    // �ύһ������
    // ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
    // �����ַ�������ʵ�ֵ������Ա��
    // һ����ʹ��   bind�� .commit(std::bind(&Dog::sayHello, &dog));
    // һ������   mem_fn�� .commit(std::mem_fn(&Dog::sayHello), this)
    template <class F, class... Args>
    auto commit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        return _pool.commit(f, args...);
    }

private:
    std::threadpool _pool;

public:
    /**
     * @brief ��ȡʵ������
     *
     * @return pool*
     */
    static pool *getInstance()
    {
        if (instance == nullptr)
            instance = new pool();
        return instance;
    }

private:
    static pool *instance;
    pool(const pool &) {}
    pool() {}
};