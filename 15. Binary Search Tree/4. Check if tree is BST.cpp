#include<iostream>
#include<queue>
#include<climits>
using namespace std;

class node {
public:
	int data = 0;
	node* left = NULL;
	node* right = NULL;

	node(int d) {
		data = d;
	}
};

void printIn(node* root) {
	if (root == NULL) {
		return;
	}

	printIn(root->left);
	cout << root->data << " ";
	printIn(root->right);
}

void bfs(node* root) {
	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while (!q.empty()) {
		node* f = q.front();
		if (f == NULL) {
			cout << endl;
			q.pop();
			if (!q.empty()) {
				q.push(NULL);
			}
		} else {

			cout << f->data << " ";
			q.pop();

			if (f->left != NULL) q.push(f->left);
			if (f->right != NULL) q.push(f->right);
		}
	}

}

node* insertInBST(node* root, int d) {
	// Base Case
	if (root == NULL) {
		node* n = new node(d);
		return n;
	}

	if (d <= root->data) {
		root->left = insertInBST(root->left, d);
	} else {
		root->right = insertInBST(root->right, d);
	}

	return root;
}

node* buildBST() {

	int d; cin >> d;
	node* root = NULL;

	while (d != -1) {
		root = insertInBST(root, d);
		cin >> d;
	}

	return root;
}

node* minimum(node* root) {
	if (root->left) {
		return minimum(root->left);
	} else {
		return root;
	}
}
node* maximum(node* root) {
	if (root->right) {
		return maximum(root->right);
	} else {
		return root;
	}
}

node* deleteInBST(node* root, int key) {

	// Base Case
	if (root->data == key) {
		// no children
		if (root->left == NULL && root->right == NULL) {
			delete root;
			return NULL;
		}
		// 1 child
		if (root->left && root->right == NULL) {
			node* temp = root->left;
			delete root;
			return temp;
		}
		else if (root->right && root->left == NULL) {
			node* temp = root->right;
			delete root;
			return temp;
		}
		// 2 children
		else {
			// Find min of right subtree
			node* min = minimum(root->right);

			// node *min = root->right;
			// while(min->left){
			// 	min = min->left;
			// }


			root->data = min->data;
			// we know that min->left is already NULL (cz it is the smallest)
			root->right = deleteInBST(root->right, min->data);
			return root;
		}
	}

	if (key < root->data) {
		root->left = deleteInBST(root->left, key);
		return root;
	} else {
		root->right = deleteInBST(root->right, key);
		return root;
	}
}


bool isBST(node *root, int minV = INT_MIN, int maxV = INT_MAX) {

	// Base Case
	if (root == NULL) {
		return 1;
	}

	if (root->data >= minV && root->data < maxV && isBST(root->left, minV, root->data) && isBST(root-> right, root->data, maxV)) {
		return 1;
	}

	return 0;

}

node* buildTree() {
	int d; cin >> d;

	if (d == -1) {
		return NULL;
	}

	node *root = new node(d);
	root->left = buildTree();
	root->right = buildTree();
	return root;
}

int main() {
	node* root = buildTree();
	bfs(root); cout << endl;
	printIn(root); cout << endl;
	cout << isBST(root) << endl;
}

// 5 3 7 1 6 8 20 10 21 -1
// 10 5 20 4 9 15 25 13 16 12 14 17 18 -1
// 5 3 1 -1 -1 -1 8 7 4 -1 -1 -1 10 -1 -1