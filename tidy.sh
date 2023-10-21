find modules/ examples/ -regextype posix-extended -regex ".*\.(c|h|hh|cpp|hpp)" |xargs -n 1 clang-format -i
