#include "boost/cstdint.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/program_options.hpp"
#include <iostream>

namespace po = boost::program_options;
using std::cout;
using std::string;

int main(int ac, char **av)
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("compression", po::value<int>(), "set compression level")(
        "log_level", po::value<int>(), "日志级别")("json_path", po::value<string>(), "输入文件路径");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("json_path")) {
        cout << "Json path is " << vm["json_path"].as<string>() << ".\n";
    }

    std::cout << "int64_t  max:  " << (std::numeric_limits<boost::int64_t>::max)() << std::endl;
    std::cout << "uint64_t max: " << (std::numeric_limits<boost::uint64_t>::max)() << std::endl;
    std::cout << "int32_t max: " << std::numeric_limits<boost::int32_t>::max() << std::endl;
    boost::int64_t seconds_per_day = 60 * 60 * 24;
    boost::int64_t microsec_per_sec = 1000000;
    boost::int64_t microsec_per_day = seconds_per_day * microsec_per_sec;
    std::cout << "microsec per day: " << microsec_per_day << std::endl;
}
