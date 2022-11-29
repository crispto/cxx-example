#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

using namespace std;
class Processor{
        public:
        Processor(int batch_size, int64_t timeout);
        void submit(int frame_id,  int(*func)(int*) );

        private:
        int batch_size_;
        int64_t time_out_;
        queue<int> que;
        queue<int(*)(int*)> que_f;
        mutex mtx;
        thread monitor;
        int64_t timing;

        private:
        int* exe_batch();
};

Processor::Processor(int batch_size, int64_t timeout): batch_size_(batch_size), time_out_(timeout){
        monitor = thread([this](){
                while(true){
                        if (timing > time_out_){
                                mtx.lock();
                                exe_batch();
                                mtx.unlock();
                                timing = 0;
                        }else{
                                mtx.lock();
                                if(que.size() >= batch_size_){
                                        exe_batch();
                                        timing = 0;
                                }
                                mtx.unlock();
                                
                        }

                }
        });
};

void Processor::submit(int frame_id, int(*func)(int*)){
        lock_guard<mutex> k(mtx);
        que.push(frame_id);

}

int* Processor::exe_batch(int num){

}
