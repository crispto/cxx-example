#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <iostream>


typedef pcl::PointXYZ PointT;

//////////////////////////////////////////////////
////////////////////  pcl load ///////////////////
int main(int argc, const char ** argv){
    if (argc < 2 ){
        std::cout << "please input point cloud path" << std::endl;
        return -1;
    }
    std::string point_path = argv[1];
    pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);

    int ret = pcl::io::loadPCDFile(point_path, *cloud);
    if (ret != 0){
        std::cout << "load point cloud failed" << std::endl;
        return -1;
    }


   std::cout << *cloud << std::endl;
   return 0;
}

