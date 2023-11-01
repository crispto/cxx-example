#ifndef __log__
#define __log__
#define NONCOPYABLE(class_name)                                                                                                \
    class_name(const class_name &) = delete;                                                                                   \
    class_name &operator=(const class_name &) = delete

class People
{
public:
    NONCOPYABLE(People);
};
#endif
