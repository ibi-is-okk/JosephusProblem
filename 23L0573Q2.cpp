#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template <typename T>
class bst {
	struct treeNode {
		T data;
		treeNode* left, * right;
		treeNode(const T& obj) {
			data = obj;
			left = right = nullptr;
		}
	};
	treeNode* root;

	//Search Parent Node
	bool getParentNode(const T& key, treeNode*& par) {
		//par = nullptr;
		treeNode* curr = root;
		while (curr != nullptr) {
			if (key == curr->data)
				return true;
			else if (key < curr->data) {
				par = curr;
				curr = curr->left;
			}
			else {
				par = curr;
				curr = curr->right;
			}
		}
		return false;
	}
	void printPreOrder(treeNode* curr) {
		if (curr)
		{
			cout << curr->data << " ";
			printPreOrder(curr->left);
			printPreOrder(curr->right);
		}
	}
	void printInOrder(treeNode* curr) {
		if (curr != nullptr) {
			//LNR
			printInOrder(curr->left);
			cout << (curr->data) << " ";
			printInOrder(curr->right);
		}
	}
	void printPostOrder(treeNode* curr) {
		if (curr != nullptr) {
			//LRN
			printPostOrder(curr->left);
			printPostOrder(curr->right);
			cout << (curr->data) << " ";
		}
	}
	void cleanup(treeNode* curr) {
		if (curr != nullptr) {
			//using post order technique i.e.,(start deletion from the last level)
			cleanup(curr->left);
			cleanup(curr->right);
			delete curr;
		}
	}
	void copy(treeNode*& curr, treeNode* objptr) {
		//Using Pre-order technique i.e., (start generating the tree from 1st level)
		if (objptr != nullptr) {
			curr = new treeNode(objptr->data);
			copy(curr->left, objptr->left);
			copy(curr->right, objptr->right);
		}
	}
	int numOfChild(treeNode* curr) { //if 0 child 1 child or 2
		if (curr == nullptr)
			return -1;
		else
			return
			int(curr->left != nullptr) +
			int(curr->right != nullptr);
	}
	int height(treeNode* curr)
	{
		if (curr)
		{
			int left_height = height(curr->left);
			int right_height = height(curr->right);

			return 1 + max(left_height, right_height);
		}
		return -1;
	}
	void erase(const T& key, treeNode*& curr)
	{
		//Search for element to be deleted
		if (curr == nullptr)
			return;
		else if (key > curr->data)
			erase(key, curr->right);
		else if (key < curr->data)
			erase(key, curr->left);
		else
		{
			//Case:0 (deleting a node with no child i.e., leaf node)
			if (numOfChild(curr) == 0)
			{
				//since pointer is passed by reference. So we don't need to set the parent pointer
				delete curr;
				curr = nullptr;
			}
			//Case:1 (deleting a node with 1 child)
			else if (numOfChild(curr) == 1)
			{
				if (curr->left)
				{
					treeNode* temp = curr;
					curr = curr->left;
					delete temp;
				}
				else
				{
					treeNode* temp = curr;
					curr = curr->right;
					delete temp;
				}
			}
			//Case:2 (deleting a node with 2 child nodes
			else
			{
				//1: Determine the successor Node. 
				treeNode* successor = curr->right;
				while (successor->left)
					successor = successor->left;
				//2: copy the data from successor to the node to be deleted.
				curr->data = successor->data;
				//3: delete the successor.
				erase(successor->data, curr->right);
			}
		}
	}

	int count(treeNode* curr) {
		if (curr != nullptr) {
			int l = count(curr->left);
			int r = count(curr->right);
			return 1 + l + r;
		}
		else
			return 0;
	}
	int median(treeNode* curr, int& count, int target) {
		if (curr == nullptr) {
			return -1; 
		}
		// Traverse the left subtree
		int leftResult = median(curr->left, count, target);
		if (leftResult != -1) { // Median found in the left subtree
			return leftResult;
		}

		// Increment count for the current node
		count++;
		if (count == target) { // Target node found
			return curr->data;
		}

		// Traverse the right subtree
		return median(curr->right, count, target);
	}
	void levelOrderInsert(treeNode* curr, bst& b) {
		if (curr != nullptr) {
			b.insert(curr->data);
			levelOrderInsert(curr->left, b);
			levelOrderInsert(curr->right, b);
		}
	}

	void merge(treeNode* a, bst& b) {
		if (a != nullptr) {
			levelOrderInsert(a, b);
		}
	}

public:
	float findMedian() {
		int size = count(root);
		int count = 0;
		int medianValue;
		if (size == 0)
			return -1;
		else if (size == 1)
			return root->data;
		else if (size != 0) {
		if (size % 2 == 0) {
			// For even-sized tree, average the two middle values
			medianValue = (median(root, count, size / 2) + median(root, count, size / 2 + 1)) / 2.0;
		}
		else {
			// For odd-sized tree, find the middle value directly
			medianValue = median(root, count, size / 2 + 1);
		}
		return medianValue;
		}
	}
	void merge(bst& other) {
		merge(root, other);  
	}
	//1: deletion
	void erase(const T& key)
	{
		erase(key, root); //pass the root by-reference
	}
	//2: copy constructor
	bst(const bst<T>& obj) {
		//copy constructor
		copy(root, obj.root);
	}
	//3: assignment operator
	const bst<T>& operator = (const bst<T>& obj) {
		cleanup(root);//uses post order
		copy(root, obj.root);//uses preorder
	}
	//4: insertion
	void insert(const T& data) {
		treeNode* par = nullptr;
		if (getParentNode(data, par) == false) {
			//add new node as a child of parent
			//par contains the parent pointer
			treeNode* temp = new treeNode(data);
			if (par == nullptr) {//tree is empty
				root = temp;
			}
			else {
				if (par->data < data) {
					par->right = temp;
				}
				else {
					par->left = temp;
				}
			}
		}
	}
	//5: inorder printing
	void printInOrder() {
		printInOrder(root);
	}
	//6: preorder printing
	void printPreOrder() {
		printPreOrder(root);
	}
	//7: post order printing
	void printPostOrder()
	{
		printPostOrder(root);
	}
	//8: search function
	bool search(const T& key)
	{
		treeNode* curr = root;
		while (curr != nullptr)
		{
			if (curr->data == key)
				return true;
			else if (curr->data < key)
				curr = curr->right;
			else
				curr = curr->left;
		}
		return false;
	}
	//9: Iterative inorder	
	void iterInOrder()
	{
		stack<treeNode*> s1;
		treeNode* curr = root;
		while (curr != nullptr || !s1.empty())
		{
			while (curr != nullptr) {
				s1.push(curr);
				curr = curr->left;
			}
			curr = s1.top();
			cout << curr->data << " ";
			s1.pop();
			curr = s1.top();
			curr = curr->right;
		}
	}
	//10: level order traversal (print the tree level by level using queue)
	void leveOrder()
	{
		treeNode* curr;
		queue<treeNode*> q1;
		q1.push(root);
		while (!q1.empty())
		{
			curr = q1.front();
			q1.pop();
			cout << curr->data << endl;

			if (curr->left)
				q1.push(curr->left);
			if (curr->right)
				q1.push(curr->right);
		}
	}
	//11: height of BST
	int height()
	{
		return height(root);
	}

	bst() {
		root = nullptr;
	}
	//14: destructor using clean-up function
	~bst() {
		cleanup(root);
	}
	

};

int main() {
	bst<int> t1;
	t1.insert(50);
	t1.insert(40);
	t1.insert(30);
	t1.insert(20);
	t1.insert(80);
	t1.insert(90);
	t1.insert(100);
	t1.insert(120);
	t1.insert(140);
	cout << "\n\n\tQ2 \n\tBST : ";
	t1.printInOrder();
	int med = t1.findMedian();
	cout << "\n\tMedian = " << med;
	bst<int> t2;
	t2.insert(8);
	t2.insert(12);
	t1.merge(t2);
	cout << "\n\tMerged tree (t2): ";
	t2.printInOrder();

}
