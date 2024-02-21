#include <stdio.h>
#include <stdlib.h>
#define ORDER 3
// B树节点结构
struct BTreeNode {
    int leaf; // 是否是叶子节点
    int n;    // 当前节点包含的关键字数
    int keys[ORDER - 1]; // 关键字数组
    struct BTreeNode *children[ORDER]; // 子节点指针数组
};

// 函数声明
struct BTreeNode *createNode();
void insert(struct BTreeNode **root, int key);
void splitChild(struct BTreeNode *parent, int index);
void insertNonFull(struct BTreeNode *node, int key);
void printTree(struct BTreeNode *root, int level);
int main() {
    struct BTreeNode *root = NULL;
    // 插入关键字
    int keys[] = {3, 7, 1, 8, 4, 6, 2, 5};
    int i;
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        insert(&root, keys[i]);
        printf("Insert %d: ", keys[i]);
        printTree(root, 0);
        printf("\n");
    }
    // 输出最终的B树结构
    printf("\nFinal B-tree structure:\n");
    printTree(root, 0);
    return 0;
}

// 创建一个新的B树节点
struct BTreeNode *createNode() {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->leaf = 1;
    newNode->n = 0;
    int i;
    for (i = 0; i < ORDER; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// 在B树中插入关键字
void insert(struct BTreeNode **root, int key) {
    struct BTreeNode *node = *root;
    // 如果根节点为空，则创建一个新的根节点
    if (node == NULL) {
        *root = createNode();
        node = *root;
    }
    // 如果根节点已满，则分裂根节点
    if (node->n == ORDER - 1) {
        struct BTreeNode *newRoot = createNode();
        newRoot->leaf = 0;
        newRoot->children[0] = node;
        *root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(node, key);
    }
}

// 分裂节点的子节点
void splitChild(struct BTreeNode *parent, int index) {
    struct BTreeNode *child = parent->children[index];
    struct BTreeNode *newChild = createNode();
    newChild->leaf = child->leaf;
    newChild->n = ORDER / 2 - 1;
    int i;
    for (i = 0; i < ORDER / 2 - 1; i++) {
        newChild->keys[i] = child->keys[i + ORDER / 2];
    }
    if (!child->leaf) {
        for (i = 0; i < ORDER / 2; i++) {
            newChild->children[i] = child->children[i + ORDER / 2];
        }
    }
    child->n = ORDER / 2 - 1;
    for (i = parent->n; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;
    for (i = parent->n - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[ORDER / 2 - 1];
    parent->n++;
}

// 在非满节点中插入关键字
void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->n - 1;
    if (node->leaf) {
        // 如果是叶子节点，直接插入
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        // 如果不是叶子节点，递归向下插入
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->n == ORDER - 1) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// 打印B树
void printTree(struct BTreeNode *root, int level) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            printTree(root->children[i], level + 1);
            printf("%*s%d\n", level * 4, "", root->keys[i]);
        }
        printTree(root->children[i], level + 1);
    }
}