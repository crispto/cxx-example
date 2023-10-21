#include <iostream>
#include <semaphore.h>
#include <pthread.h>


using namespace std;


class Solution{
    private:
        pthread_mutex_t l1 = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_t l2 = PTHREAD_MUTEX_INITIALIZER;
        int n_ =0;
    public:
        Solution(int n): n_(n){
            pthread_mutex_lock(&l2);
        };
    
        void print_foo(){
            for(int i =0;i<n_;i++){
                pthread_mutex_lock(&l1);
                cout << "foo";
                pthread_mutex_unlock(&l2);
            }
        };
        
        void print_bar(){
            for(int i =0;i<n_;i++){
                pthread_mutex_lock(&l2);
                cout << "bar" << endl;
                pthread_mutex_unlock(&l1);
            }
        }
};

void print(){
    cout << "this is a good way" << endl;

}
void* print_foo_wrap(void *obj){
    Solution* p = static_cast<Solution*>(obj);
    p->print_foo();
    return nullptr;
}

void* print_bar_wrap(void *obj){
    Solution* p = static_cast<Solution*>(obj);
    p->print_bar();
    return nullptr;
}


int main(){
            Solution s(10);
            pthread_t t1, t2;

            pthread_create(&t1, nullptr, print_foo_wrap, &s);
            pthread_create(&t2, nullptr, print_bar_wrap, &s);
            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
    return 0;
}

