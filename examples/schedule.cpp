/* 
  你必须定义一个 `main()` 函数入口。
  you must define a `main()` function entry.
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

// - A computational graph, usually represented as a DAG (directed acyclic graph), is a very common abstraction to represent a set of computational tasks and their dependencies
// - In the graph, we usually represent tasks as vertices and their dependencies as directed edges. An edge from A to B means that task B depends on task A, i.e., B can only start after A finishes. A task can depend on multiple tasks and a task can be depended upon by multiple tasks
// - Your task is to implement a scheduler that schedules all the tasks represented by a given computational graph onto a cluster of workers
struct Task {
  // Upstream tasks that need to be finished before this task
  std::vector<Task *> prereqs;
  // Downstream tasks that depend on this task
  std::vector<Task *> dependents;
  // Estimated computational time, in milliseconds
  int64_t time;
  int64_t time_total;
};
// a - b - c -e 
        // - d 
struct Graph {
  std::string name;
  // All tasks, not in any particular order
  std::vector<Task> tasks;
};

class Cluster {
 public:
  // Total number of workers in the cluster
  int GetTotalWorkers();
  // Number of available workers in the cluster. A worker became available
  // only *after* its finished task has been polled
  int GetAvailableWorkers();
  // Schedule the task onto a worker. Return true if the task is successfully
  // scheduled, false otherwise. Not blocking
  bool Schedule(const Task &task);
  // Query the cluster for finished tasks. Return a finished task, if any. 
  // Return nullptr, if none. Not blocking
  Task* Poll();
};

class Scheduler {
 public:
  explicit Scheduler(Graph &graph, Cluster &cluster)
      : graph_(graph), cluster_(cluster){};

  void Run() {
    // TODO: Run all tasks on the cluster. Blocking
    vector<Task*> roots;
    set<Task*> finished;
    for(auto t : graph_.tasks){
      if(t.prereqs.empty()) roots.push_back(&t);
    }
    for(auto t : roots){
      getTotalTimeDfs(t);
    }

    
    
  }
  private: 
    void getTotalTimeDfs(Task* task) {
      set<Task*> visited;
      dfs(task, visited);
    };
  void dfs(Task* task, set<Task*> &visited){
    visited.insert(task);
     if (task->dependents.empty()){
          task->time_total = task->time;
          return;
        }
        int64_t max_time = -1;
        for (auto child : task->dependents){
          if (visited.find(child) == visited.end()){
            visited.insert(child);
            dfs(child, visited);
          }
        }
      for (auto child : task->dependents){
        if (child->time_total > max_time) {
          max_time = child->time_total;
        }
      }
    task->time_total += max_time;
    
  }

 private:
  Graph graph_;
  Cluster cluster_;
};

int main()
{
  cout << "Talk is cheap. Show me the code." << endl;
  return 0;
}
