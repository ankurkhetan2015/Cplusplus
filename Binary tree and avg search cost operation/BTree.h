#include <iostream>
#include <queue>
#include <list>
#include <fstream>

using namespace std;

enum color {red, black};

template <typename T>
struct Node
{
	T value;
	Node<T>* left;
	Node<T>* right;
    Node<T>* parent;

    int search_time;
    color node_color; //don't need to worry about this for the regular BTree

    Node(T val = T(), Node<T>* l = NULL, Node<T>* r = NULL, Node<T>* p = NULL, color col = color::red)
		: value(val), left(l), right(r), parent(p), search_time(0), node_color(col) {}

	Node(const Node<T>* other)
	{
		value = other.value;
		node_color = other.node_color;
		search_time = other.search_time;
	}

	bool is_leaf(){return (left == 0 && right == 0);}
};

template <typename T>
struct BTree
{
protected:
	int size;
	
public:
	Node<T>* root;

    BTree() : root(NULL),size(0){}
	BTree(const BTree<T>& other);
	BTree<T>& operator=(const BTree<T>& other);
	//BTree<T>& operator=(const BTree<T> other);

	Node<T>* get_root(){return root;}
	const Node<T>* get_root() const {return root;} 
	virtual void insert(T obj);
	Node<T>* search(T obj);
	void update_search_times();
	float get_average_search_time();
    ostream& inorder(ostream& out);
    virtual ostream& print_level_by_level(ostream& out);
    
private:
	void deletetree(Node<T>* node); //to delete the original tree and help in copying a new one to it
	void copy_helper(Node<T>* copy_to, const Node<T>* copy_from) const;
	virtual Node<T>* insert_helper(T obj, Node<T>* node);
	ostream& inorder_helper(ostream& out, Node<T>* node);
	Node<T>* search_helper(T obj, Node<T>* node);
	void update_search_times_helper(Node<T>* node, int depth);
	T get_total_search_time(Node<T>* node);
	virtual void pretty_print_node(ostream& out,Node<T>* node);
	int height(Node<T>* node);
};

template <typename T>
ostream& operator<<(ostream& out, BTree<T>& tree)
{
	tree.inorder(out);
	cout << endl;
	out << "\nLevel by level output of the tree:" << endl;
	tree.print_level_by_level(out);
	return out;
}

template <typename T>
ostream& operator<<(ostream& out, Node<T> node)
{
	return out << "( " << node.value << ", " << node.search_time << ", " << node.node_color << " )";
}

template <typename T>
void BTree<T>::pretty_print_node(ostream& out,Node<T>* node)
{
	if( node->value == -1)
		out <<"X" <<" ";
	else
		out << node->value << "["<<node->search_time<<"] " << " ";
}

template <typename T>
istream& operator>>(istream& in, BTree<T>& tree)
{
	while(!in.eof())
	{
		T insertVal;
		in >> insertVal;
		tree.insert(insertVal);
	}
	return in;
}

template <typename T>
BTree<T>::BTree(const BTree<T>& other)
{
	root = NULL;
	root = new Node<T>;
    copy_helper(this->root, other.get_root());
}

template <typename T>
BTree<T>& BTree<T>::operator=(const BTree<T>& other)
{
	deletetree(root); root = NULL;

	root = new Node<T>;

	copy_helper(this->root, other.root);
	return *this;

}

template <typename T>
void BTree<T>::deletetree(Node<T>* node)
{
	while(node != NULL)
	{
		if (node->left != NULL)
			deletetree(node->left);
		if (node->right != NULL)
			deletetree(node->right);
	}
	delete node;
}



template <typename T>
void BTree<T>::copy_helper(Node<T>* copy_to, const Node<T>* copy_from) const
{
	if(copy_from == NULL)
	{
		copy_to = NULL;
	}

	else
	{
		copy_to->value = copy_from->value;
		copy_to->left = copy_from->left;
		copy_to->right = copy_from->right;
		copy_to->parent = copy_from->parent;
		copy_to->node_color = copy_from->node_color;
		copy_to->search_time = copy_from->search_time;
		copy_helper(copy_to->left, copy_from->left);
		copy_helper(copy_to->right, copy_from->right);
	}
}

template <typename T>
Node<T>* BTree<T>::insert_helper(T obj, Node<T>* curr)
{ 
	if (curr == NULL) 
		curr = new Node<T>(obj);

    else if (obj < curr->value)
	{
		Node<T> *lchild = insert_helper(obj, curr->left);
		curr->left = lchild;
		lchild->parent = curr;
	}

	else if (obj > curr->value)
	{
		Node<T> *rchild = insert_helper(obj, curr->right);
		curr->right = rchild;
		rchild->parent = curr;
	}

	return curr;
}

template <typename T>
void BTree<T>::insert(T obj)
{
    root = insert_helper(obj, root);
	update_search_times();
	size++;
}

template <typename T>
Node<T>* BTree<T>::search_helper(T obj, Node<T>* node)
{
	if(node != NULL)
	{ 
		if(obj == node->value)
			return node;
		if(obj < node->value)
			return search_helper(obj, node->left);
		else
			return search_helper(obj, node->right);
	}
	else
		return NULL;
}

template <typename T>
Node<T>* BTree<T>::search(T obj)
{
	return search_helper(obj, root);
}	

template <typename T>
void BTree<T>::update_search_times_helper(Node<T>* node, int depth)
{
	if(node->left !=NULL)
		update_search_times_helper(node->left, depth+1);
	if(node->right !=NULL)
		update_search_times_helper(node->right, depth+1);
	node->search_time = 1+ depth;
}

template <typename T>
void BTree<T>::update_search_times()
{
	update_search_times_helper(root, 0);
}

template <typename T>
ostream& BTree<T>::inorder_helper(ostream& out, Node<T>* node)
{
	if((size-1) < 16)
	{
		if(node == NULL)
			return out;

		inorder_helper(out, node->left);
		pretty_print_node(out, node);
		inorder_helper(out, node->right);
	}
	else
	{
		ofstream of;
		of.open("test.txt");
		of << node->value << "["<<node->search_time<<"] " << " ";
	}
	return out;
}

template <typename T>
ostream& BTree<T>::inorder(ostream& out)
{
	out << "\nIn Order Traversal:" << endl;
	out << "Value[Search Cost] format:" << endl;
	inorder_helper(out, root);
	return out;
}

//function to find the height of the tree. Helps in levelcby level printing
template <typename T>
int BTree<T>::height(Node<T>* node)
{
	if (node == nullptr)
		return 0;
	return 1 + max(height(node->left), height(node->right));
}


template <typename T>
ostream& BTree<T>::print_level_by_level(ostream& out)
{	
	if((size-1) < 16)
	{	
	queue<Node<T>*> q;
	Node<T> *p = new Node<T>(-1);
		int currlevelNodes = 0;
		int h = height(root); //stores the total height of the tree
		q.push(root);
		while(h > 0)
		{
			currlevelNodes = q.size();
		while(currlevelNodes > 0)
		{
			Node<T>* n = q.front();
			pretty_print_node(out, n);
			q.pop();
		
			if(n->left != NULL)
				q.push(n->left);
			else 
				q.push(p);
			
			if(n->right != NULL) 
				q.push(n->right);
			else
				q.push(p);

			currlevelNodes--;
		}
		h--;
		out << endl;
	}
}
    return out;
}

template <typename T>
T BTree<T>::get_total_search_time(Node<T>* node)
{
	if(node == NULL)
		return 0;
	return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);	
}

template <typename T>
float BTree<T>::get_average_search_time()
{
	cout << "\nTotal number of nodes:\t" << (size-1) << endl;  // because for some reason when I am reading the innput from the file, it is considering the last value twice.
	cout << "Total search cost:\t" << get_total_search_time(root);
    return ((float)get_total_search_time(root)/(size-1));
}