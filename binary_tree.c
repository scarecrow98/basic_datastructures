#include "stdio.h"
#include "stdlib.h"

typedef struct branch {
    int value;
    struct branch *left;
    struct branch *right;
} Branch;

typedef struct binary_tree {
    Branch *root;
    int size;
} BinaryTree;

BinaryTree *create_tree() {
    BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

Branch *create_branch(int value) {
    Branch *branch = (Branch *) malloc(sizeof(Branch));
    branch->value = value;
    branch->left = branch->right = NULL;

    return branch;
}

void add(BinaryTree *tree, int value) {

    Branch * new_branch = create_branch(value);

    if (!tree->root) {
        tree->root = new_branch;
    } else {
        Branch *act = tree->root;
        Branch *prev = NULL;

        while(act != NULL) {
            prev = act;

            if (value < act->value) {
                act = act->left;
            } else if (value > act->value) {
                act = act->right;
            }
        }

        if (value < prev->value) {
            prev->left = new_branch;
        } else if (value > prev->value) {
            prev->right = new_branch;
        }
    }

    tree->size++;
    printf("Value %d added to the tree.\n", value);
}

void preorder(Branch *branch) {
    if (branch) {
        printf("%d - ", branch->value);
        preorder(branch->left);
        preorder(branch->right);
    }
}

void inorder(Branch *branch) {
    if (branch) {
        inorder(branch->left);
        printf("%d - ", branch->value);
        inorder(branch->right);
    }
}

void postorder(Branch *branch) {
    if (branch) {
        postorder(branch->left);
        postorder(branch->right);
        printf("%d - ", branch->value);
    }
}

Branch *min_in_subset(Branch *root){
    Branch *act = root->right;

    while(act->left->left){
        act = act->left;
    }

    //actually returns the parent node of the minimum value node
    return act;
}

void delete_node(int side, Branch * parent_node, Branch * actual_node, Branch *value_to_set){
    if(side) {
        parent_node->right = value_to_set;
    } else {
        parent_node->left = value_to_set;
    }

    free(actual_node);
}

void delete(BinaryTree *tree, int value) {
    if (!tree->root) {
        return;
    }

    Branch *act = tree->root;
    Branch *prev = NULL;
    //boolean to keep track of which side of the parent node we are at
    int act_side = 0;

    while (act != NULL && act->value != value) {
        prev = act;
        if (value > act->value) {
            act = act->right;
            act_side = 1;
        } else if (value < act->value) {
            act = act->left;
            act_side = 0;
        } 
    }

    if (!act) {
        return;
    }

    if (!act->left && !act->right) {
        delete_node(act_side,prev,act, NULL);
    } else if(!act->left){
        Branch *temp = act->right;
        delete_node(act_side, prev, act, temp);
    } else if(!act->right){
        Branch *temp = act->left;
        delete_node(act_side, prev, act, temp);
    } else {
        Branch *min = min_in_subset(act);
        act->value = min->left->value;
        free(min->left);
        min->left = NULL;
    }

    tree->size--;
} 

int main() {
    BinaryTree *tree = create_tree();

    int num[] = {30, 21, 38, 25, 32, 20, 33, 26, 31, 29, 34, 22};

    for (int i = 0; i < 12; ++i) {
        add(tree, num[i]);
    }

    // printf("\nPreorder:\n");
    // preorder(tree->root);

    printf("\nInorder:\n");
    inorder(tree->root);
    printf("\nSize: %d\n", tree->size);

    delete(tree, 30);

    printf("\nInorder after delete:\n");
    inorder(tree->root);
    printf("\nSize: %d\n", tree->size);

    // printf("\nPostorder:\n");
    // postorder(tree->root);

    return 0;
}