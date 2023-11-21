#include <co/fs.h>
#include <iostream>
/**
 * @brief 使用tensorrt加速模型推理
 *
 * @return int
 */
using namespace co;

int main()
{
    fastring filepath = "model/yolov8n.trt";
    if (!fs::exists(filepath)) {
        std::cout << "file not exists: " << filepath << std::endl;
        return 1;
    }
    size_t sz = fs::fsize(filepath);
    std::cout << "file size: " << sz << std::endl;
}
