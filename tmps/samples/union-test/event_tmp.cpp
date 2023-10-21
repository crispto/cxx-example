#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <queue>
#include <mutex>
#include <thread>


typedef pcl::PointXYZ PointT;

bool closed = false;
std::mutex mtx;
// TODO  一个
std::conditional read_condi;
std::conditional write_condi;
void produce(std::queue<pcl::PointCloud<PointT>::ConstPtr> &que){
  char buf[100];
  for (int i = 2; i<100;i++){
    pcl::PointCloud<PointT>::Ptr cloud(new (pcl::PointCloud<PointT>));
    sprintf(buf, "/home/richard/data/4v2l/50/%06d.pcd", i);
    printf("read file %s\n", buf);
    pcl::io::loadPCDFile(std::string(buf), *cloud);
    std::lock_guard<std::mutex> g(mtx);
    que.emplace(cloud);
  }

  closed = true;
}


int main(int argc, const char **argv)
{
    std::string filename = argv[1];

    pcl::visualization::PCLVisualizer viewer("viewer");

    pcl::PointCloud<PointT>::Ptr cloud(new (pcl::PointCloud<PointT>));
    pcl::io::loadPCDFile(filename, *cloud);

    viewer.addPointCloud(cloud, "cloud");
    
    std::queue<pcl::PointCloud<PointT>::ConstPtr> que;


    std::thread t1(produce, std::ref(que));

    while (!viewer.wasStopped()) {
        viewer.spinOnce();
        std::lock_guard<std::mutex> g(mtx);
        // 这个线程持有锁，又陷入睡眠，这样就会造成死锁
        // TODO  释放锁，并等待信号量
        while(que.empty() && !closed){
          pcl_sleep(0.1);
        }
        if (closed){
          std::cout <<"closed and return" << std::endl;
          break;
        }
        auto cloud_t = que.front();
        viewer.updatePointCloud(cloud_t, "cloud");
        que.pop();
        pcl_sleep(0.5);
    }
    if (t1.joinable()){
      t1.join();
    }
    return 0;
}