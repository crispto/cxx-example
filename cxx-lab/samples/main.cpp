#include <iostream>
#include <vector>
using namespace std;

int merge_vector(vector<int> &input, vector<int> &other){
  auto p1 = input.begin();
  auto p2 = other.begin();

  while(p2 != other.end()){
    auto tmp = p1;

    if(*tmp >= *p2){
      input.insert(tmp-1, *p2);
      tmp++;
    }else{
      p1++;
    }
  }
}

void show_vector(vector<int> &input{
}
int main(){
  vector<int> input{2,5,7,9};
  vector<int> other{1,3,5,7};
  merge_vector(input, other);
  show_vector(input);

}


// ## 请在下方进行输入 ( 支持Markdown、插入公式及 LaTex 数学公式，点击上方按钮“环境说明”查看详情 )
typedef struct TreeNode_ {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode_(int x) : val(x), left(nullptr), right(nullptr) {}
} TreeNode;

void dfs(TreeNode* root, vector<TreeNode*> paths, TreeNode* target){
  if(root == target)
    return;
  paths.emplace_back(root);
  if (root->left){
    root= root->left;
    dfs(root, paths, target);
  }
   if (root->right){
    root= root->right;
    dfs(root, paths, target);
  }
  paths.pop_back();
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  vector<TreeNode*> p1;
  vector<TreeNode*> p2;
  dfs(root, p1, p);
  dfs(root,p2, q);
  for (int i=p1.size()-1; i>=0; i--){
    for(int j= p2.size()-1; j>=0; j--){
      if(p1[i] == p2[i])
        return p1[i];
        }
  }
}

