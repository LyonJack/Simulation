#pragma once
#include <string>

struct __std_func_struct
{
    size_t* vt;
    void* func_ptr;
};
#define LAMBDANAME "<lambda_"
template<typename _Ty>
bool is_std_func_equal(_Ty& a, _Ty& b)
{
    __std_func_struct* pa = (__std_func_struct*)&a;
    __std_func_struct* pb = (__std_func_struct*)&b;

    if (pa->func_ptr == pb->func_ptr) {
        // 如果func_ptr相等时，我们直接判断两个vtable[2]即可
        return (pa->vt[2] == pb->vt[2]);
    }
    else {
        // 只要func_ptr不相等，我们甭管它保存了什么，都先去类型信息中先查找<lambda_
        bool al = std::string(a.target_type().name()).find(LAMBDANAME) != std::string::npos;
        bool bl = std::string(b.target_type().name()).find(LAMBDANAME) != std::string::npos;
        if (al != bl) // 一个是lambda而另一个不是时，就不需要比较了
            return false;

        if (al) {
            // 两个都是lambda时，比较vtable[2]
            return (pa->vt[2] == pb->vt[2]);
        }
        else {
            // 两个都是函数指针时，比较func_ptr
            return (pa->func_ptr == pb->func_ptr);
        }
    }
}