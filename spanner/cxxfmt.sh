check_file_list=`find src/ test/ -regextype posix-extended -regex ".*\.(c|h|hh|cpp|hpp)"`
clang-format ${check_file_list} -i -style=WebKit