#include <iostream>
#include <queue>
using namespace std;


class node{
  public:
  node(int val_, node* left_ = nullptr,node* right=nullptr): val(val_), left(left_), right(right_){};
  private:
  int val;
  node* left;
  node* right;
};


void print_by_line(node* root){
  if (root == nullptr) return;
  queue<node*> q;
  q.push(root);
  node* end = root;
  node * mark = root;
  while(!q.empty()){
    node* cur = q.pop();
    if (cur->lef){
      q.push(cur->left);
      mark = cur->left;
    }
  if (cur->right){
      q.push(cur->right);
      mark = cur->right;
    }
    cout << cur->val;
    if (cur == end){
      cout << endl;
      end = mark;
    }
  }
}

node* build_tree(int i){
  if (i ==0) return nullptr;
  node *p = new node(i, build_tree)

}
int main(){
  for (int i = 0;i < 10;i++){

  }
}