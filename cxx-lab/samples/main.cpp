struct Tree {
	int x;
	Tree* left;
	Tree* right;
	Tree(int val) : x(val), left(nullptr), right(nullptr) {}
};
Tree* process(Tree* root, Tree* x1, Tree* x2){
	if (root == x1 || root == x2 || !root) {
		return root;
	}
	Tree* left = process(root->left, x1, x2);
	Tree* right = process(root->right, x1, x2);
	if (left && right) return root;
	else if (!left && right) return right;
	else if (left && !right) return left;
	
	return nullptr;

}