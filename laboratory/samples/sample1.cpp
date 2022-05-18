#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
void func(){
	auto_ptr<string> ps(new string("you"));
	cout << *ps << endl;
	cout << ps->size() << endl;
}

template <typename T>
typename T::value_type func3(const T& input ) { // 返回值的类型，根据传入的参数而定
	typename T::value_type x = input[0] + 1.0; // 用来分解一个模板类的模板参数
	return x;
}

// 模板类只是会在编译的时候生成不同实际参数类型的函数，因此所有的问题都会在编译时暴露出来。

typedef struct test{
	string name;
} test_t;

void func2(){
	vector<int> a{1,3,4};
	int v = func3(a);
	cout << "v is " << v << endl;

	vector<float> b {3.01, 4.32, 4.13};
	float v2 = func3(b);
	cout << "v is " << v2 << endl;

	vector<test_t>  c{test_t{"yang"}, test_t{"li"}};
	test_t v3 = func3(c);
	cout << "v3 is " << v3 << endl;


}
*/

int main()
{
	cout << "this is sample1" << endl;
	cout << "sample 1 is changed," << endl;
}
