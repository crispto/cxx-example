check_file_list=`find src/  -regextype posix-extended -regex ".*\.(c|h|hh|cpp|hpp)"`

clang-format ${check_file_list} -output-replacements-xml |grep offset |wc -l

clang-format -i ${check_file_list}