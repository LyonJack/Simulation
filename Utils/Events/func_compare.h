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
        // ���func_ptr���ʱ������ֱ���ж�����vtable[2]����
        return (pa->vt[2] == pb->vt[2]);
    }
    else {
        // ֻҪfunc_ptr����ȣ����Ǳ¹���������ʲô������ȥ������Ϣ���Ȳ���<lambda_
        bool al = std::string(a.target_type().name()).find(LAMBDANAME) != std::string::npos;
        bool bl = std::string(b.target_type().name()).find(LAMBDANAME) != std::string::npos;
        if (al != bl) // һ����lambda����һ������ʱ���Ͳ���Ҫ�Ƚ���
            return false;

        if (al) {
            // ��������lambdaʱ���Ƚ�vtable[2]
            return (pa->vt[2] == pb->vt[2]);
        }
        else {
            // �������Ǻ���ָ��ʱ���Ƚ�func_ptr
            return (pa->func_ptr == pb->func_ptr);
        }
    }
}