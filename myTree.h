#include <iostream>
#include <string.h>
#include <stack>
#include <stdexcept>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <functional>
using namespace std;

typedef enum{Link, Thread} NodeTag;

class TreeNode
{
private:
    char data;              //值
    TreeNode* leftChild;    //左孩子
    TreeNode* rightChild;   //右孩子
    NodeTag lTag, rTag;     //线索Tag

    friend class MyTree;    //树类
public:
    TreeNode(char d, TreeNode* l, TreeNode* r, NodeTag lt, NodeTag rt)
        : data(d), leftChild(l), rightChild(r), lTag(lt), rTag(rt) {}

    ~TreeNode() {}

    void printNode();
    
};

class MyTree
{
private:
     TreeNode* root;        //根指针
     bool isThread;         //线索二叉树标志
     int nodenum;
public:
    MyTree() : root(nullptr), isThread(false) {}

    MyTree(const char preOrder[]) : root(nullptr), isThread(false) {
        const char* preOrderPtr = preOrder;
        nodenum = 0;
        createTreeFromPreOrder(root, preOrderPtr);
    }

    MyTree(const MyTree& tree) : root(nullptr), isThread(false) {
        copyTree(tree.root, root);
    }

    ~MyTree() {
        destroyTree(root);
    }
    void createTreeFromPreOrder(TreeNode*& , const char*&);
    void copyTree(TreeNode* , TreeNode*& );
    void destroyTree(TreeNode*);
    void preOrderTraverse();    //前序遍历
    void preOrderTraverseHelper(TreeNode*);
    void inOrderTraverse();     //中序遍历
    void postOrderTraverse();   //后序遍历
    void inOrderThreadingHelper(TreeNode*, TreeNode*&);
    int countLeaf();            //叶结点计数
    int countLeafHelper(TreeNode*);
    int countHeight();          //计算树的深度
    int countHeightHelper(TreeNode*);
    bool isThreadedTree();      //判断是否为线索二叉树
    bool isThreadedTreeHelper(TreeNode* , TreeNode*& , bool& , bool& );
    bool inOrderThreading();    //线索化
    TreeNode& locateNode(const char&);  //结点定位
    TreeNode& preNode(const TreeNode&); //获取前驱结点
    TreeNode& nextNode(const TreeNode&);//获取后继结点

};


struct HuffmanNode {
    int value;
    HuffmanNode* left, * right;

    HuffmanNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        // Compare by node's value to put smaller values in the left subtree and larger values in the right subtree
        return l->value > r->value;
    }
};

class HuffmanTree {
private:
    HuffmanNode* root;

    // Recursive function to deallocate memory
    void freeMemory(HuffmanNode* node) {
        if (node != nullptr) {
            freeMemory(node->left);
            freeMemory(node->right);
            delete node;
        }
    }

    // Recursive function to print codes
    void printCodes(HuffmanNode* node, string code) {
        if (node != nullptr) {
            if (node->left == nullptr && node->right == nullptr) {
                cout << node->value << ":" << code << endl;
            }
            else {
                printCodes(node->left, code + "1");
                printCodes(node->right, code + "0");
            }
        }
    }

public:
    HuffmanTree(const int size, const int values[]) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

        for (int i = 0; i < size; ++i) {
            pq.push(new HuffmanNode(values[i]));
        }

        while (pq.size() > 1) {
            HuffmanNode* right = pq.top(); pq.pop();
            HuffmanNode* left = pq.top(); pq.pop();

            HuffmanNode* sum = new HuffmanNode(left->value + right->value);
            sum->left = left;
            sum->right = right;

            pq.push(sum);
        }

        root = pq.top();
    }

    ~HuffmanTree() {
        freeMemory(root);
    }

    void printHuffmanCodes() {
        printCodes(root, "");
    }
};