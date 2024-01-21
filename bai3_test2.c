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

// Tra ve node chua gia tri nho nhat
TreeNode* FindMin(TreeNode* node) {
    if(node == NULL)
        return NULL;

	TreeNode* curr = node; 
	while (curr && curr->left != NULL) {
		curr = curr->left; 
	}
	return curr; 
}

TreeNode* Delete_recursive(TreeNode* node, int data) {
    if(search(node,data) == NULL)
    {
        return node;
    }

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

// Tim gia tri nho nhat cua mot binary search tree
int Min(TreeNode* node) {
    if(node == NULL)
        return -1;

	TreeNode* curr = node; 
	while (curr->left != NULL) {
		curr = curr->left; 
	}
	return curr->data; 
}

// Tim gia tri nho nhat BST bang de quy
int Min_recursive(TreeNode* node) {
    if(node == NULL)
        return -1;
    else if(node->left == NULL)
        return node->data;
    else
        return Min_recursive(node->left);
}

// Xoa node co gia tri nho nhat bang de quy
TreeNode* DeleteMin(TreeNode* node) {
    if(node == NULL)
        return NULL;
    else if(node->left == NULL)
    {
        TreeNode* temp = node->right;
        free(node);
        return temp;
    }
    else
    {
        node->left = DeleteMin(node->left);
        return node;
    }
}

// Tim chieu cao cua BST
int height(TreeNode* node) {
    if(node == NULL)
        return -1;
    else
    {
        int left_height = height(node->left);
        int right_height = height(node->right);
        if(left_height > right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

// Tim tong data trong nhanh dai nhat cua BST
int sumLongestBranch(TreeNode* node) {
    if(node == NULL)
        return 0;
    else
    {
        int left_height = height(node->left);
        int right_height = height(node->right);
        if(left_height > right_height)
            return node->data + sumLongestBranch(node->left);
        else
            return node->data + sumLongestBranch(node->right);
    }
}

// Tim tong data lon nhat trong tat ca cac nhanh cua BST
// int maxDataOfAllPath(TreeNode* node) {
//     if(node == NULL)
//         return 0;
//     else
//     {
//         int left_sum = maxDataOfAllPath(node->left);
//         int right_sum = maxDataOfAllPath(node->right);
//         if(left_sum > right_sum)
//             return node->data + left_sum;
//         else
//             return node->data + right_sum;
//     }
// }

// Tim tong data lon nhat trong tat ca cac nhanh cua BST
int maxDataOfAllBranch(TreeNode* node) {
    if (node == NULL)
        return 0;  // Sửa ở đây, trả về một giá trị không mong muốn
    else {
        int left_sum = maxDataOfAllBranch(node->left);
        int right_sum = maxDataOfAllBranch(node->right);
        if (left_sum > right_sum)
            return node->data + left_sum;
        else
            return node->data + right_sum;
    }
}



// Xoa tat cac cac tree node co data le trong BST khong dung ham Delete_recursive ma chi co 2 truong hop No child va one child
TreeNode* deleteOdd(TreeNode* node) {
    if(node == NULL)
        return NULL;
    else
    {
        node->left = deleteOdd(node->left);
        node->right = deleteOdd(node->right);
        if(node->data % 2 != 0)
        {
            if(node->left == NULL && node->right == NULL)
            {
                free(node);
                return NULL;
            }
            else if(node->left == NULL)
            {
                TreeNode* temp = node->right;
                free(node);
                return temp;
            }
            else if(node->right == NULL)
            {
                TreeNode* temp = node->left;
                free(node);
                return temp;
            }
        }
        return node;
    }
}

// Kiem tra cay co phai la BST hay khong
int isBST(TreeNode* node) {
    if(node == NULL)
        return 1;
    if(node->left != NULL && node->left->data > node->data)
        return 0;
    if(node->right != NULL && node->right->data < node->data)
        return 0;
    if(!isBST(node->left) || !isBST(node->right))
        return 0;
    return 1;
}

int main() {
    BinaryTree tree;

    init(&tree);
    
    tree.root = insert_recusive(tree.root, 4);
    tree.root = insert_recusive(tree.root, 2);
    tree.root = insert_recusive(tree.root, 8);
    tree.root = insert_recusive(tree.root, 1);
    tree.root = insert_recusive(tree.root, 3);
    tree.root = insert_recusive(tree.root, 5);
    tree.root = insert_recusive(tree.root, 28);
    tree.root = insert_recusive(tree.root, 6);
    tree.root = insert_recusive(tree.root, 7);
    print(tree.root);


    printf("\nTong data cua nhanh dai nhat: %d", sumLongestBranch(tree.root));
    printf("\nTong data lon nhat trong tat ca cac nhanh: %d",maxDataOfAllBranch(tree.root));
    printf("\n");
    tree.root = deleteOdd(tree.root);
    print(tree.root);
    return 0;
}

