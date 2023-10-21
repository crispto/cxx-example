#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointXYZ PointT;



int main(int argc, const char** argv)
{
  if (argc !=2 ){
    std::cout <<"view_demo <path>" << std::endl;
    exit(-1);
  }
  std::string filename = argv[1];
  pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>());
  pcl::io::loadPCDFile(filename, *cloud);

  
  // 创建 场景 
  pcl::visualization::CloudViewer viewer("cloud viewer1");

  viewer.showCloud(cloud, "cloud number one");
  // while(!viewer.wasStopped()){
  // }
  return 0;

}