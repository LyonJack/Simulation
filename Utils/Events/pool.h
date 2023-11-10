#include "../threadpool/threadpool.h"
#include <future>

class pool
{
public:
    // 提交一个任务
    // 调用.get()获取返回值会等待任务执行完,获取返回值
    // 有两种方法可以实现调用类成员，
    // 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
    // 一种是用   mem_fn： .commit(std::mem_fn(&Dog::sayHello), this)
    template <class F, class... Args>
    auto commit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        return _pool.commit(f, args...);
    }

private:
    std::threadpool _pool;

public:
    /**
     * @brief 获取实例对象
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