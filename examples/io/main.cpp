#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string path = "data/config.txt";
    ifstream input_stream;
    input_stream.open(path);
    if (!input_stream.is_open()) {
        exit(-1);
    }
    string line;
    int i = 0;
    while (!input_stream.eof()) {
        input_stream >> line;
        std::cout << i++ << ", " << line << std::endl;
    }
}
