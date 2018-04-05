#include <iostream>

template<class c, class x, class y>
struct replace_type
{
	typedef c type;
};

template<class x, class y>
struct replace_type<x, x, y>
{
	typedef y type;
};

// 处理参数有x的函数
template<class x, class y, class Return, class...Args>
struct replace_type<Return(Args...), x, y>
{
	typedef typename replace_type<Return, x, y>::type type(typename replace_type<Args, x, y>::type...);
};

// 处理参数有x的模板
template<class x, class y, template<class...A> class obj, class...Args>
struct replace_type<obj<Args...>, x, y>
{
	typedef typename obj<typename replace_type<Args, x, y>::type...> type;
};

template<class c, class x, class y, size_t i>
struct replace_type<c [i], x, y>
{
	typedef typename replace_type<typename c, x, y>::type type[i];
};

template<class c, class x, class y>
struct replace_type<const c, x, y>
{
	typedef typename const replace_type<c, x, y>::type type;
};

template<class c, class x, class y>
struct replace_type<c *, x, y>
{
	typedef typename replace_type<c, x, y>::type * type;
};

template<class c, class x, class y>
struct replace_type<c &, x, y>
{
	typedef typename replace_type<c, x, y>::type &type;
};

template<class c, class x, class y>
struct replace_type<c &&, x, y>
{
	typedef typename replace_type<c, x, y>::type &&type;
};

int main()
{
	std::cout << typeid(replace_type<int*(*[3])(int *), int, float > ::type).name() << std::endl;
}
