#include <stdio.h>
#include <stdlib.h>

// Khoi tao node tree
typedef struct NodeType {
    int data;
    struct NodeType* left, * right;
} TreeNode;

// Khoi tao binary Tree
typedef struct BinaryTreeType {
    struct NodeType* root;
} BinaryTree;

// Tao nodetree moi
TreeNode* makeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// In Binary Tree
void print(TreeNode* node) {
    if (node == NULL)
        return;
    printf("%d\n", node->data);
    print(node->left);
    print(node->right);
}

// Tim kiem va tra ve Node co gia tri val, khong co tra NULL
TreeNode* search(TreeNode* node, int val) {
        if (node == NULL || node->data == val)
            return node;
        else if (val < node->data)
            return search(node->left, val);
        else if (val > node->data)
            return search(node->right, val);
}

// Khoi tao Binary Tree
void init(BinaryTree* tree) {
    tree->root = NULL;
}

// Chen BinaryTree thong thuong
void insert(BinaryTree* tree, int data) {
    TreeNode* node = makeNode(data);
    if (tree->root == NULL) // empty tree
        tree->root = node;
    else {
        TreeNode* curr = tree->root;
        TreeNode* prev = NULL;
        while (curr != NULL) {
            prev = curr;
            if (curr->data > data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (prev->data > data)
            prev->left = node;
        else
            prev->right = node;
    }
}

// Chen BinaryTree bang de quy
TreeNode* insert_recusive(TreeNode* node, int val) 
{
    if(node == NULL)
    {
        node = makeNode(val);
    }
    else if(node->data > val)
    {
        node->left = insert_recusive(node->left,val);
    }
    else
    {
        node->right = insert_recusive(node->right,val);
    }
    
    return node;
}



int isLeaf(TreeNode* node)
{
    return (node->left) == NULL && (node->right) == NULL;
}


void delete(BinaryTree* tree, int val) {
    // Khong tim thay val thi ket thuc luon
    if(search(tree->root,val) == NULL)
    {
        return;
    }

    TreeNode* curr = tree->root;
    TreeNode* prev = NULL;
    while (1) {
        if (curr == NULL)    // not found
            return;
        if (curr->data == val) {    // found
            // delete the curr node

            // case 1: no child / leaf
            if (curr->left == NULL && curr->right == NULL) {
                free(curr);
                if (prev == NULL) {
                    tree->root = NULL;
                }
                else {
                    if (prev->data > val) {
                        prev->left = NULL;
                    }
                    else {
                        prev->right = NULL;
                    }
                }
                return;
            }
            // case 2: one child
            if (curr->left == NULL) {
                if (prev == NULL) {
                    printf("\nDelete at root");
                    tree->root = curr->right;
                }
                else {
                    if (prev->data > val) {
                        prev->left = curr->right;
                    }
                    else {
                        prev->right = curr->right;
                    }
                }
                free(curr);
                return;
            } 
            if (curr->right == NULL) {
                if (prev == NULL) {
                    printf("\nDelete at root");
                    tree->root = curr->left;
                }
                else {
                    if (prev->data > val) {
                        prev->left = curr->left;
                    }
                    else {
                        prev->right = curr->left;
                    }
                }
                free(curr);
                return;
            }

            // case 3: 2 children (leafs)
            if (isLeaf(curr->left) && isLeaf(curr->right)) {
                // copy data from the right
                curr->data = curr->right->data;
                free(curr->right);
                curr->right = NULL;
                return;
            }
            // case 4: curr->right is not a leaf
            if (!isLeaf(curr->right)) {
                TreeNode* leftMost = curr->right;
                TreeNode* parent = NULL;
                while (!isLeaf(leftMost)) {
                    parent = leftMost;
                    leftMost = leftMost->left;
                }
                printf("\nLeaf data %d", leftMost->data);
                curr->data = leftMost->data;
                free(leftMost);
                parent->left = NULL;
                return;
            }
        }
        prev = curr;
        if (curr->data > val) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}

TreeNode* FindMin(TreeNode* node) {
	TreeNode* curr = node; 
	while (curr && curr->left != NULL) {
		curr = curr->left; 
	}
	return curr; 
}

TreeNode* Delete_recursive(TreeNode* node, int data) {
    if(node == NULL)
        return node;
    else if(data < node->data)
        node->left = Delete_recursive(node->left, data);
    else if (data > node->data)
        node->right = Delete_recursive(node->right, data);
    else {// Wohoo... I found you, Get ready to be deleted
        if(node->left == NULL && node->right == NULL) { // Case 1: No child 
            free(node);
            node = NULL;
        }
        //Case 2: One child
        else if(node->left == NULL) {
            TreeNode *temp = node;
            node = node->right;
            free(temp);
        }
        else if(node->right == NULL) {
            TreeNode *temp = node;
            node = node->left;
            free(temp);
        }
        else { // case 3: 2 children
            TreeNode *temp = FindMin(node->right);
            node->data = temp->data;
            node->right = Delete_recursive(node->right, temp->data);
        }
    }

    return node;
}

int main() {
    BinaryTree tree;

    init(&tree);
    
    tree.root = insert_recusive(tree.root, 50);
    tree.root = insert_recusive(tree.root, 25);
    tree.root = insert_recusive(tree.root, 10);
    tree.root = insert_recusive(tree.root, 33);
    tree.root = insert_recusive(tree.root, 60);
    tree.root = insert_recusive(tree.root, 11);
    tree.root = insert_recusive(tree.root, 56);
    tree.root = insert_recusive(tree.root, 61);
    print(tree.root);

    tree.root = Delete_recursive(tree.root, 61);
    printf("\n");
    print(tree.root);
    return 0;
}