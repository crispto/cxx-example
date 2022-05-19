
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/../install/lib
echo $LD_LIBRARY_PATH
cmd=$1
echo "cmd is $cmd"
case $cmd in
    rm|clean)
    rm -rf ./build
    ;;
    reb|build|rebuild)
    cd build && make
    ;;
    creb|crebuild)
    rm -rf ./build && mkdir build
    cd build && cmake .. && make -j 4
    ;;


esac