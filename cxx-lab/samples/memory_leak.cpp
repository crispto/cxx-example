#include <mutex>
#include <iostream>
#include <assert.h>

#define new new (__FILE__, __LINE__)
void *operator new(std::size_t size, const char *file, int line)
{
    std::cout << "size is " << size << "file: " << file << "line:" << line << std::endl;
};
// void* operator new[](std::size_t size, const char* file, int line);
class A{
  public:
  int age;
};

void func()
{
    A *a = new A();
    delete a;
    // A *b = new int[4];
    // delete[] b;
}

struct new_ptr_list_t {
    new_ptr_list_t *next;
    new_ptr_list_t *prev;
    std::size_t size;
    union {
        char file[200];

        void *addr;
    };
    unsigned line;
};

// static void *alloc_mem(std::size_t size, const char *file, int line, bool is_array)
// {
//     assert(line >= 0);

//     std::size_t s = size + ALIGNED_LIST_ITEM_SIZE;
//     new_ptr_list_t *ptr = (new_ptr_list_t *)malloc(s);
//     if (ptr == nullptr) {
//         std::unique_lock<std::mutex> lock(new_output_lock);
//         printf("Out of memory when allocating %lu bytes\n", (unsigned long)size);
//         abort();
//     }
//     void *usr_ptr = (char *)ptr + ALIGNED_LIST_ITEM_SIZE;

//     if (line) {
//         strncpy(ptr->file, file, _DEBUG_NEW_FILENAME_LEN - 1)[_DEBUG_NEW_FILENAME_LEN - 1] = '\0';
//     } else {
//         ptr->addr = (void *)file;
//     }

//     ptr->line = line;
//     ptr->is_array = is_array;
//     ptr->size = size;
//     ptr->magic = DEBUG_NEW_MAGIC;
//     {
//         std::unique_lock<std::mutex> lock(new_ptr_lock);
//         ptr->prev = new_ptr_list.prev;
//         ptr->next = &new_ptr_list;
//         new_ptr_list.prev->next = ptr;
//         new_ptr_list.prev = ptr;
//     }
//     total_mem_alloc += size;
//     return usr_ptr;
// }