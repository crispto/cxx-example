#include <iostream>

class RingBuffer{
  public:
    RingBuffer(int cap);
    ~RingBuffer();
    //  push an element, 如果满了则覆盖最老的
    int push(int input);
    // 如果为空则直接返回  -1
    int pop(int &output);
    void print();
  private:
    int* data;
    int cap;
    int *start;
    int *end;
    bool empty;
};

RingBuffer::RingBuffer(int cap_): cap(cap_), empty(true){
  if (cap_ < 0)
    throw "invalid cap for buffer";
  start =nullptr;
  end= nullptr;
  data = new int[cap_];
}

RingBuffer::~RingBuffer(){
  delete[] data;
}

int RingBuffer::push(int input){
  end++;
  if (end == data+cap){
    end = data;
  }
  *end = input;
  if (empty)
    empty = false;
}

int RingBuffer::pop(int &output){
  if (empty)
    return -1;
  output = *start;
  start++;
  if (start == data+cap)
    start = data;
  if (start == end)
    empty = true;
  return 0;
}
void  RingBuffer::print(){
  std::cout << "[ ";
  int * tmp = start;
  while(tmp!= end){
    std::cout << *tmp << ", ";
    tmp++;
    if (tmp == data+cap)
      tmp = data;
  }
  std::cout << " ]"<<std::endl;

}



int main(){
  RingBuffer buffer(10);
  for (int i = 0; i < 11; i++){
    buffer.push(i);
    buffer.print();
  }
}