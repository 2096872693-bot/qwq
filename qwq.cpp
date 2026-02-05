#include <iostream>
using namespace std;
// 定义类模板
template<typename T=double>
class LimitValue {
private:
  //成员变量
    T current_value;
    const T min_value;
    const T max_value;
    //辅助函数以限制范围
    T clamp(T value)const
    {
       if (value < min_value)
          return min_value;
       if (value > max_value)
           return  max_value;
	 return value;
	} //这个函数只读取值，不修改任何成员变量
public:
    // 构造函数
    LimitValue(T current, T min_val, T max_val) :  min_value(min_val), max_value(max_val)
 //初始化列表：const在这里初始化
{
        current_value = clamp(current);
    }

    LimitValue& operator=(T value)
    {
        current_value = clamp(value);
        return *this;
    }

LimitValue& operator+=(T value) {
    current_value = clamp(current_value + value);
    return *this;
}

LimitValue& operator-=(T value) {
    current_value = clamp(current_value - value);
    return *this;
}

T val()const { return current_value; }

};