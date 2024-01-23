#include <cmath>

template<typename T>
class my_unique_ptr{
    public:
    my_unique_ptr(const my_unique_ptr& other) = delete;
    my_unique_ptr& operator = (const my_unique_ptr& other) =delete;

    my_unique_ptr(T* p): data(p){};

    my_unique_ptr& my_unique_ptr(my_unique_ptr&& other){
        data = other.data;
        other.data = nullptr;
    };

    my_unique_ptr& operator= (my_unique_ptr&& other){
        data = other.data;
        other.data = nullptr;
        
    };
    ~my_unique_ptr(){
        delete data;
    };
    private:
        T* data;
};

struct Dim{
    int dim1; // 
    int dim2;
    int dim2;
};

// dim1*dim2*dim2个 0  1 2,  ->   2, 1, 0
float * transpose(const float* data, Dim &dim, int array[3]){


}

int softmax(float scores[3]){
    float sum = 0.f;
    for (int i = 0;i < 3;i++){
        scores[i] =  expf(scores[i]);
        sum += scores[i];
    }
    for (int i = 0; i < 3;i++){
        scores[i] /= sum;
    }
}

// 矩阵乘

