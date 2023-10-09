
#include<bits/stdc++.h>
using namespace std;

to left child and a pointer to right child */
struct Node
{
	int data;
	struct Node* left, *right;
};

struct Node *newNode(int item)
{
	struct Node *temp = new Node;
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

struct Node* insert(struct Node* node, int key)
{

	if (node == NULL) return newNode(key);

	if (key < node->data)
		node->left = insert(node->left, key);
	else if (key > node->data)
		node->right = insert(node->right, key);
	return node;
}
using Morris Inorder traversal*/
int counNodes(struct Node *root)
{
	struct Node *current, *pre;

	int count = 0;

	if (root == NULL)
		return count;

	current = root;
	while (current != NULL)
	{
		if (current->left == NULL)
		{
			// Count node if its left is NULL
			count++;

			// Move to its right
			current = current->right;
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->left;

			while (pre->right != NULL &&
				pre->right != current)
				pre = pre->right;

			/* Make current as right child of its
			inorder predecessor */
			if(pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}

			/* Revert the changes made in if part to
			restore the original tree i.e., fix
			the right child of predecessor */
			else
			{
				pre->right = NULL;

				// Increment count if the current
				// node is to be visited
				count++;
				current = current->right;
			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */

	return count;
}


/* Function to find median in O(n) time and O(1) space
using Morris Inorder traversal*/
int findMedian(struct Node *root)
{
if (root == NULL)
		return 0;

	int count = counNodes(root);
	int currCount = 0;
	struct Node *current = root, *pre, *prev;

	while (current != NULL)
	{
		if (current->left == NULL)
		{
			// count current node
			currCount++;

			// check if current node is the median
			// Odd case
			if (count % 2 != 0 && currCount == (count+1)/2)
				return current->data;

			// Even case
			else if (count % 2 == 0 && currCount == (count/2)+1)
				return (prev->data + current->data)/2;

			// Update prev for even no. of nodes
			prev = current;

			//Move to the right
			current = current->right;
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->left;
			while (pre->right != NULL && pre->right != current)
				pre = pre->right;

			/* Make current as right child of its inorder predecessor */
			if (pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}

			/* Revert the changes made in if part to restore the original
			tree i.e., fix the right child of predecessor */
			else
			{
				pre->right = NULL;

				prev = pre;

				// Count current node
				currCount++;

				// Check if the current node is the median
				if (count % 2 != 0 && currCount == (count+1)/2 )
					return current->data;

				else if (count%2==0 && currCount == (count/2)+1)
					return (prev->data+current->data)/2;

			
				prev = current;
				current = current->right;
}
}

}
	 return count;

}
int main()
{

	/* Let us create following BST
				50
			/	 \
			30	 70
			/ \ / \
		20 40 60 80 */
	struct Node *root = NULL;
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);

	cout << "\nMedian of BST is "
		<< findMedian(root);
	return 0;
}
