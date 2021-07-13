#include "sequoia.h"

/*Function call: sequoia.insert(x);
Description: Calls the function to insert a node to the tree*/
void Sequoia::insert(int x)
{
	if (size != 0) //Checks if the tree does not have size 0
		root->insert(x); //Calls insert in the root node
	else
		root = new SequoiaNode(x); //If the size is zero creates the root node
	size++; //Updates the size of the tree

	while (root->parent != nullptr) //Loop to update the root node if it has been changed
		root = root->parent;
}

/*Function call: sequoia.remove(x);
Description: Finds and removes a node from the tree*/
void Sequoia::remove(int x)
{
	if (root == nullptr) //Checks if the root is nullptr
		return;
	SequoiaNode* victim = root->search(x); //Calls the search function and creates a new node object
	if (victim == nullptr) //Checks if the search function found the node
		return;

	if (victim == root) //Checks if the node to be removed is the root node
		root = victim->remove(); //If victim is the root, update root with the returned velue from victim
	else
		victim = victim->remove(); //Calls the remove function if victim is not the root
}

/*Function call: sequoiaNode.serch(x);
Description: Finds the node with value x by calling the functions in the proper child node*/
SequoiaNode* SequoiaNode::search(int x)
{
	if (x == value) //Base case, if the node has value x
		return this; //Returns the current node
	else if (x < value) //Checks if the value is smaller than the node value
	{
		if (left != nullptr) //Checks if the left child is not nullptr
			return left->search(x); //Calls search in the left child
		else
			return nullptr; //The tree has reached an end and the node was not found
	}
	else
	{
		if (right != nullptr) //Checks if the right child is not nullptr
			return right->search(x); //Calls search in the right child
		else 
			return nullptr; //The tree has reached an end and the node was not found
	}
}

/*Function call: sequoiaNode.insert(x);
Description: Inserts a node with value x in the proper position*/
void SequoiaNode::insert(int x)
{
	if (x < value) //Checks if x is smaller than the current value
	{
		if (left != nullptr) //Checks if the left child is not nullptr
			left->insert(x); //Calls insert in the left child
		else
		{
			left = new SequoiaNode(x); //Create a new node with value x and sets it as the left child
			left->parent = this; //Sets the parent of the new node to the current node
			this->fixBalance(); //Calls the function to fix balance after insertion
		}
	}
	else
	{
		if (right != nullptr) //Checks if the right child is not nullptr
			right->insert(x); //Calls insert in the rifht child
		else
		{
			right = new SequoiaNode(x); //Create a new node with value x and sets it as the right child
			right->parent = this; //Sets the parent of the new node to the current node
			this->fixBalance(); //Calls the function to fix balance after insertion
		}
	}
}

/*Function call: sequoiaNode.remove()
Description: Removes the current node*/
SequoiaNode* SequoiaNode::remove()
{
	if (parent != nullptr) //Checks if parent is not nullptr (Checks if it is the root node)
	{
		if (left == nullptr && right == nullptr) //Checks if there are no children
		{
			if (parent->left == this) //Checks if the parent left child is the current node (Checks if it is a left child)
				parent->left = nullptr; //Sets the parents left child to nullptr
			else if (parent->right == this) //Checks if the parent right child is the current node (Checks if it is a right child)
				parent->right == nullptr; //Sets the parents right child to nullptr
			parent->fixBalance(); //Fix the trees balances starting by the father
			return this; //Returns the removed node;
		}
		else if (left != nullptr && right == nullptr) //Checks if there is a left child only
		{
			left->parent = parent; //Makes the parent of the left child the current nodes parent
			if (parent->left == this) //Checks if the parents left child is the current node (Checks if it is a left child)
				parent->left = left; //Sets the parents left child to the current nodes left child
			else
				parent->right = left; //Makes the parent of the right child the current nodes parent
			parent->fixBalance(); //Fix the trees balances starting by the father
			left = right = nullptr; //Sets both children to nullptr
			return this; //Returns the current node
		}
		else if (left == nullptr && right != nullptr) //Checks if the is a right child only
		{
			right->parent = parent; //Makes the parent of the right child the current nodes parent
			if (parent->left == this) //Checks if the parents left child is the current node (Checks if it is a left child)
				parent->left = right; //Sets the parents left child to the current nodes right child
			else
				parent->right = right; //Sets the parents left child to the current nodes right child
			parent->fixBalance(); //Fix the trees balances starting by the father
			left = right = nullptr; //Sets both children to nullptr
			return this; //Returns the current node
		}
		else
		{
			SequoiaNode* swap = left; //Creates a copy of the left child
			while (swap->right != nullptr) //Loops to find the biggest value in the left subtree
				swap = swap->right; //Updates the swap to the right child
			value = swap->value; //Updates the current value to the swap value
			swap->remove(); //Calls remove in the swap node
			swap->parent->fixBalance(); //Fix the trees balances starting by the father
			return this; //Returns the updated current node
		}
	}
	else
	{
		if (left == nullptr && right == nullptr) //Checks if there are no children
		{
			return nullptr; //Returns nullptr (There is only the root)
		}
		else if (left != nullptr && right == nullptr) //Checks if there is a left child only
		{
			left->parent = nullptr; //Makes the left childs parent nullptr
			left->fixBalance(); //Fix the trees balances starting by the current node
			return left; //Returns the new root
		}
		else if (left == nullptr && right != nullptr) //Checks if the is a right child only
		{
			right->parent = nullptr; //Makes the right childs parent nullptr
			right->fixBalance(); //Fix the trees balances starting by the current node
			return right; //Returns the new root
		}
		else
		{
			SequoiaNode* swap = left; //Creates a copy of the left child
			while (swap->right != nullptr) //Loops to find the biggest value in the left subtree
				swap = swap->right; //Updates the swap to the right child
			value = swap->value; //Updates the current value to the swap value
			swap->remove(); //Calls remove in the swap node
			swap->parent->fixBalance(); //Fix the trees balances starting by the father
			return this; //Returns the new root
		}
	}
}

/*Function call: sequoiaNode.fixBalanceInsert();
Description: Checks and fixes if the nodes above have the tall property*/
void SequoiaNode::fixBalance()
{
	updateHeight(); //Updates the height of the current node
	if (left != nullptr && right != nullptr) //Checks if there are two children
	{
		if (left->height >= 2 * right->height) //Checks if the node has the tall property (left > right)
			if (parent != nullptr) //Checks if the parent is not nullptr
				parent->fixBalance(); //Calls the function to fix balance in the parent
			else
				return; //Returns if the property is present and the node is the root (no parent node)
		else if (right->height >= 2 * left->height) //Checks if the node has the tall property (right > left)
			if (parent != nullptr) //Checks if the parent is not nullptr
				parent->fixBalance(); //Calls the function to fix balance in the parent
			else
				return; //Returns if the property is present and the node is the root (no parent node)
		else
			if (left->height >= right->height) //Cehcks if the left subtre is bigger
			{
				right->rotateLeft(); //Rotate right child to the left
			}
			else if (right->height > left->height) //Checks if the right subtree is bigger
			{
				left->rotateRight(); //Rotate left child to the right
			}
	}
	else
	{
		if (parent != nullptr) //Cehcks if there is a parent node
			parent->fixBalance(); //Calls the function to fix balance in the parent node
	}
	updateHeight(); //Updates height of the current node
}

/*Function call: sequoiaNode.rotateRight();
Description: Rotates the current node right*/
void SequoiaNode::rotateRight()
{
	parent->left = right; //Makes the parent left child the current nodes right child
	if (right != nullptr) //Checks if the right child is nullptr
		right->parent = parent; //Updates the right child parent to the current nodes parent
	right = parent; //Makes the right child the parent node
	parent = parent->parent; //Makes parent the current node parents parent.
	if (right->parent != nullptr) //Checks if the right parent is not the nullptr
		if (right == right->parent->left) //Checks if the right child is equal to the left child of the right child parent
			parent->left = this; //Makes the parent left child the current node
		else
			parent->right = this; //Makes the parent right child the current node
	else
		parent = nullptr; //Makes the parent the nullptr
	right->parent = this; //Makes the parent of the right child the current node
}

/*Function call:
Description:*/
void SequoiaNode::rotateLeft()
{
	parent->right = left; //Makes the parent right child the current nodes left child
	if (left != nullptr) //Checks if the left child is nullptr
		left->parent = parent; //Updates the left child parent to the current nodes parent
	left = parent; //Makes the left child the parent node
	parent = parent->parent; //Makes parent the current node parents parent.
	if (left->parent != nullptr) //Checks if the left parent is not the nullptr
		if (left == left->parent->left) //Checks if the left child is equal to the left child of the left child parent
			parent->left = this; //Makes the parent left child the current node
		else
			parent->right = this; //Makes the parent right child the current node
	else
		parent = nullptr; //Makes the parent the nullptr
	left->parent = this; //Makes the parent of the right child the current node
}

/*Function call: sequoiaNode.updateHeight();
Description: Updates the height of the current node*/
void SequoiaNode::updateHeight()
{
	if (left == nullptr && right == nullptr) //Checks if there are no children
		height = 1; //Sets height to one
	else if (left != nullptr && right == nullptr) //Checks if there is a left child only
		height = left->height + 1; //Sets height to the left child height plus one
	else if (left == nullptr && right != nullptr) //Cehcks if there is a right child only
		height = right->height + 1; //Sets height to the right child height plus one
	else
		height = max(left->height, right->height) + 1; //Sets the height to maximum value between both childs heights plus one
	if (parent != nullptr) //Checks if the parent is not nullptr (root node)
		parent->updateHeight(); //Calls the function to update the height of the parent
}