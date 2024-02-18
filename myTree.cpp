#include "myTree.h"

using namespace std;


void TreeNode::printNode()
{
    cout << this->data;
}

void MyTree::createTreeFromPreOrder(TreeNode*& node, const char*& preOrder) {
    if (*preOrder == '@' || *preOrder == '\0') {
        node = nullptr;
        preOrder++;// 返回以结束递归
    }
    else {
        node = new TreeNode(*preOrder, nullptr, nullptr, Link, Link);
        preOrder++; // 移动指针到下一个字符

        // 传递指向左子节点指针
        createTreeFromPreOrder(node->leftChild, preOrder);

        // 传递指向右子节点指针
        createTreeFromPreOrder(node->rightChild, preOrder);
    }
}
void MyTree::copyTree(TreeNode* originNode, TreeNode*& newNode) {
    if (originNode == nullptr) {
        newNode = nullptr;
    }
    else {
        newNode = new TreeNode(originNode->data, nullptr, nullptr, originNode->lTag, originNode->rTag);
        copyTree(originNode->leftChild, newNode->leftChild);
        copyTree(originNode->rightChild, newNode->rightChild);
    }
}
void MyTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        // 如果不是线索化的左子节点，则递归地销毁之
        if (!node->lTag == Thread) {
            destroyTree(node->leftChild);
        }
        // 如果不是线索化的右子节点，则递归地销毁之
        if (!node->rTag == Thread) {
            destroyTree(node->rightChild);
        }
        delete node; // 释放当前节点的内存
    }
}
void MyTree::preOrderTraverseHelper(TreeNode* cur) {
    if (cur == nullptr)return;
    else {
        cur->printNode();
        preOrderTraverseHelper(cur->leftChild);
        preOrderTraverseHelper(cur->rightChild);
    }
    return;
}
void MyTree::preOrderTraverse() {
    //preOrderTraverseHelper(root);
    
    
    if (root == nullptr) {
        return;
    }
    
    
    // 使用栈模拟递归过程
    stack<TreeNode*> nodeStack;
    TreeNode* currentNode = root;

    while (currentNode || !nodeStack.empty()) {
        while (currentNode) {
            currentNode->printNode(); // 访问节点操作，这里打印节点数据
            nodeStack.push(currentNode);
            currentNode = currentNode->leftChild;
        }

        if (!nodeStack.empty()) {
            currentNode = nodeStack.top();
            nodeStack.pop();
            currentNode = currentNode->rightChild;
        }
    }
 
}
void MyTree::inOrderTraverse() {
    if (isThreadedTree()) {  // 处理线索化二叉树的逻辑
        TreeNode* current = root;
        // 找到最左侧的节点，这是中序遍历的起始点
        while (current != nullptr && current->lTag == Link) {
            current = current->leftChild;
        }

        while (current != nullptr) {
            current->printNode();  // 打印当前节点

            // 如果当前节点的右标记是线索，直接访问线索指向的节点
            if (current->rTag == Thread) {
                current = current->rightChild;
            }
            else { // 否则，访问右子树中的最左侧节点
                current = current->rightChild;
                while (current != nullptr && current->lTag == Link) {
                    current = current->leftChild;
                }
            }
        }
    }
    else { // 处理非线索化二叉树的逻辑
        if (root == nullptr) {
            return;
        }

        TreeNode* currentNode = root;
        stack<TreeNode*> nodeStack;

        while (currentNode || !nodeStack.empty()) {
            while (currentNode) {
                nodeStack.push(currentNode);
                currentNode = currentNode->leftChild;
            }

            if (!nodeStack.empty()) {
                currentNode = nodeStack.top();
                nodeStack.pop();
                currentNode->printNode(); // 打印节点数据
                currentNode = currentNode->rightChild;
            }
        }
    }
}
void MyTree::postOrderTraverse() {
    if (root == nullptr) {
        return;
    }

    stack<TreeNode*> nodeStack;
    TreeNode* currentNode = root;
    TreeNode* lastVisited = nullptr;

    while (currentNode || !nodeStack.empty()) {
        while (currentNode) {
            nodeStack.push(currentNode);
            currentNode = currentNode->leftChild;
        }

        currentNode = nodeStack.top();

        if (currentNode->rightChild && currentNode->rightChild != lastVisited) {
            currentNode = currentNode->rightChild;
        }
        else {
            currentNode = nodeStack.top();
            nodeStack.pop();
            currentNode->printNode(); // 打印节点数据
            lastVisited = currentNode;
            currentNode = nullptr;
        }
    }
}
int MyTree::countLeafHelper(TreeNode* currentNode) {
    if (currentNode == nullptr) {
        return 0;
    }

    if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr) {
        return 1; // 当前节点是叶子节点，返回1
    }

    // 递归计算左子树和右子树的叶子节点数量
    int leftLeaves = countLeafHelper(currentNode->leftChild);
    int rightLeaves = countLeafHelper(currentNode->rightChild);

    return leftLeaves + rightLeaves;
}
int  MyTree::countLeaf() {
    
    return countLeafHelper(root);
}
int MyTree::countHeightHelper(TreeNode* currentNode) {
    if (currentNode == nullptr) {
        return 0;
    }

    int leftHeight = countHeightHelper(currentNode->leftChild);
    int rightHeight = countHeightHelper(currentNode->rightChild);

    return 1 + max(leftHeight, rightHeight); // 当前节点的深度为左右子树深度的较大值加1
}
int  MyTree::countHeight() {
    return countHeightHelper(root);
}
bool MyTree::isThreadedTree() {
    TreeNode* prev = nullptr; // 用来跟踪中序遍历中上一个线索化的节点
    bool leftThreadExists = false; // 用于标记是否存在至少一个左线索
    bool rightThreadExists = false; // 用于标记是否存在至少一个右线索

    return isThreadedTreeHelper(root, prev, leftThreadExists, rightThreadExists) && (leftThreadExists || rightThreadExists);
}

bool MyTree::isThreadedTreeHelper(TreeNode* currentNode, TreeNode*& prev, bool& leftThreadExists, bool& rightThreadExists) {
    if (currentNode == nullptr) return true;

    // 检查左子树
    if (currentNode->lTag != Thread && !isThreadedTreeHelper(currentNode->leftChild, prev, leftThreadExists, rightThreadExists)) {
        return false;
    }

    // 检查左线索
    if (currentNode->lTag == Thread) {
        leftThreadExists = true; // 至少找到了一个左线索
        // 如果左线索不指向期望的前驱，则返回false
        if (currentNode->leftChild != prev && currentNode->leftChild != nullptr) {
            return false;
        }
    }

    // 更新prev节点
    prev = currentNode;

    // 检查右线索
    if (currentNode->rTag == Thread) {
        rightThreadExists = true; // 至少找到了一个右线索
    }

    // 检查右子树
    if (currentNode->rTag != Thread && !isThreadedTreeHelper(currentNode->rightChild, prev, leftThreadExists, rightThreadExists)) {
        return false;
    }

    return true;
}
void MyTree::inOrderThreadingHelper(TreeNode* currentNode, TreeNode*& pre) {
    if (currentNode == nullptr) {
        return;
    }

    inOrderThreadingHelper(currentNode->leftChild, pre);

    // 处理当前节点
    if (currentNode->leftChild == nullptr) {
        currentNode->lTag = Thread;
        currentNode->leftChild = pre;
    }
    if (pre != nullptr && pre->rightChild == nullptr) {
        pre->rTag = Thread;
        pre->rightChild = currentNode;
    }
    pre = currentNode;

    inOrderThreadingHelper(currentNode->rightChild, pre);
}
bool MyTree::inOrderThreading() {
    TreeNode* pre = nullptr; // 指向当前访问节点的前驱节点
    inOrderThreadingHelper(root, pre);
    // 在中序遍历结束时，最后一个节点的后继节点应为 nullptr
    if (pre != nullptr && pre->rTag == Thread) {
        pre->rightChild = nullptr;
    }
    isThread = true; // 标记为线索二叉树
    return true;
}
TreeNode& MyTree::preNode(const TreeNode& targetNode) {
    if (root == nullptr) throw std::logic_error("Tree is empty.");

    // 如果有线索，则直接返回线索节点
    if (targetNode.lTag == Thread) {
        return *(targetNode.leftChild);
    }

    // 否则按普通二叉树处理
    TreeNode* current = root;
    TreeNode* pre = nullptr;  // 用于追踪前驱

    while (current != nullptr && current != &targetNode) {
        if (targetNode.data < current->data) {
            current = (current->lTag == Link) ? current->leftChild : nullptr;
        }
        else {
            pre = current;
            current = (current->rTag == Link) ? current->rightChild : nullptr;
        }
    }

    if (current == nullptr) throw std::logic_error("Node not found in the tree.");

    // 如果找到节点且左子树存在，返回左子树的最右节点
    if (targetNode.lTag == Link && targetNode.leftChild != nullptr) {
        current = targetNode.leftChild;
        while (current->rTag == Link && current->rightChild != nullptr) {
            current = current->rightChild;
        }
        pre = current;
    }

    // 如果前驱不存在，表示该节点为最小节点，没有前驱
    if (pre == nullptr) throw std::logic_error("There is no predecessor for the given node.");

    return *pre;
}

TreeNode& MyTree::nextNode(const TreeNode& targetNode) {
    if (root == nullptr) throw std::logic_error("Tree is empty.");

    // 如果有线索，则直接返回线索节点
    if (targetNode.rTag == Thread) {
        return *(targetNode.rightChild);
    }

    // 否则按普通二叉树处理
    TreeNode* current = root;
    TreeNode* next = nullptr;  // 用于追踪后继

    while (current != nullptr && current != &targetNode) {
        if (targetNode.data < current->data) {
            next = current;
            current = (current->lTag == Link) ? current->leftChild : nullptr;
        }
        else {
            current = (current->rTag == Link) ? current->rightChild : nullptr;
        }
    }

    if (current == nullptr) throw std::logic_error("Node not found in the tree.");

    // 如果找到节点且右子树存在，返回右子树的最左节点
    if (targetNode.rTag == Link && targetNode.rightChild != nullptr) {
        current = targetNode.rightChild;
        while (current->lTag == Link && current->leftChild != nullptr) {
            current = current->leftChild;
        }
        next = current;
    }

    // 如果后继不存在，表示该节点为最大节点，没有后继
    if (next == nullptr) throw std::logic_error("There is no successor for the given node.");

    return *next;
}

TreeNode& MyTree::locateNode(const char& v) {
    TreeNode* current = root;
    stack<TreeNode*> stack;

    // 中序遍历以定位包含特定值的节点
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = (current->lTag == Link) ? current->leftChild : nullptr;
        }

        if (!stack.empty()) {
            current = stack.top();
            stack.pop();

            if (current->data == v) {
                return *current;
            }

            current = (current->rTag == Link) ? current->rightChild : nullptr;
        }
    }

    // 如果找不到则抛出异常
    throw std::logic_error("Node with the given value not found.");
}





