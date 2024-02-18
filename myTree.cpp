#include "myTree.h"

using namespace std;


void TreeNode::printNode()
{
    cout << this->data;
}

void MyTree::createTreeFromPreOrder(TreeNode*& node, const char*& preOrder) {
    if (*preOrder == '@' || *preOrder == '\0') {
        node = nullptr;
        preOrder++;// �����Խ����ݹ�
    }
    else {
        node = new TreeNode(*preOrder, nullptr, nullptr, Link, Link);
        preOrder++; // �ƶ�ָ�뵽��һ���ַ�

        // ����ָ�����ӽڵ�ָ��
        createTreeFromPreOrder(node->leftChild, preOrder);

        // ����ָ�����ӽڵ�ָ��
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
        // ������������������ӽڵ㣬��ݹ������֮
        if (!node->lTag == Thread) {
            destroyTree(node->leftChild);
        }
        // ������������������ӽڵ㣬��ݹ������֮
        if (!node->rTag == Thread) {
            destroyTree(node->rightChild);
        }
        delete node; // �ͷŵ�ǰ�ڵ���ڴ�
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
    
    
    // ʹ��ջģ��ݹ����
    stack<TreeNode*> nodeStack;
    TreeNode* currentNode = root;

    while (currentNode || !nodeStack.empty()) {
        while (currentNode) {
            currentNode->printNode(); // ���ʽڵ�����������ӡ�ڵ�����
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
    if (isThreadedTree()) {  // �������������������߼�
        TreeNode* current = root;
        // �ҵ������Ľڵ㣬���������������ʼ��
        while (current != nullptr && current->lTag == Link) {
            current = current->leftChild;
        }

        while (current != nullptr) {
            current->printNode();  // ��ӡ��ǰ�ڵ�

            // �����ǰ�ڵ���ұ����������ֱ�ӷ�������ָ��Ľڵ�
            if (current->rTag == Thread) {
                current = current->rightChild;
            }
            else { // ���򣬷����������е������ڵ�
                current = current->rightChild;
                while (current != nullptr && current->lTag == Link) {
                    current = current->leftChild;
                }
            }
        }
    }
    else { // ��������������������߼�
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
                currentNode->printNode(); // ��ӡ�ڵ�����
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
            currentNode->printNode(); // ��ӡ�ڵ�����
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
        return 1; // ��ǰ�ڵ���Ҷ�ӽڵ㣬����1
    }

    // �ݹ��������������������Ҷ�ӽڵ�����
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

    return 1 + max(leftHeight, rightHeight); // ��ǰ�ڵ�����Ϊ����������ȵĽϴ�ֵ��1
}
int  MyTree::countHeight() {
    return countHeightHelper(root);
}
bool MyTree::isThreadedTree() {
    TreeNode* prev = nullptr; // �������������������һ���������Ľڵ�
    bool leftThreadExists = false; // ���ڱ���Ƿ��������һ��������
    bool rightThreadExists = false; // ���ڱ���Ƿ��������һ��������

    return isThreadedTreeHelper(root, prev, leftThreadExists, rightThreadExists) && (leftThreadExists || rightThreadExists);
}

bool MyTree::isThreadedTreeHelper(TreeNode* currentNode, TreeNode*& prev, bool& leftThreadExists, bool& rightThreadExists) {
    if (currentNode == nullptr) return true;

    // ���������
    if (currentNode->lTag != Thread && !isThreadedTreeHelper(currentNode->leftChild, prev, leftThreadExists, rightThreadExists)) {
        return false;
    }

    // ���������
    if (currentNode->lTag == Thread) {
        leftThreadExists = true; // �����ҵ���һ��������
        // �����������ָ��������ǰ�����򷵻�false
        if (currentNode->leftChild != prev && currentNode->leftChild != nullptr) {
            return false;
        }
    }

    // ����prev�ڵ�
    prev = currentNode;

    // ���������
    if (currentNode->rTag == Thread) {
        rightThreadExists = true; // �����ҵ���һ��������
    }

    // ���������
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

    // ����ǰ�ڵ�
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
    TreeNode* pre = nullptr; // ָ��ǰ���ʽڵ��ǰ���ڵ�
    inOrderThreadingHelper(root, pre);
    // �������������ʱ�����һ���ڵ�ĺ�̽ڵ�ӦΪ nullptr
    if (pre != nullptr && pre->rTag == Thread) {
        pre->rightChild = nullptr;
    }
    isThread = true; // ���Ϊ����������
    return true;
}
TreeNode& MyTree::preNode(const TreeNode& targetNode) {
    if (root == nullptr) throw std::logic_error("Tree is empty.");

    // �������������ֱ�ӷ��������ڵ�
    if (targetNode.lTag == Thread) {
        return *(targetNode.leftChild);
    }

    // ������ͨ����������
    TreeNode* current = root;
    TreeNode* pre = nullptr;  // ����׷��ǰ��

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

    // ����ҵ��ڵ������������ڣ����������������ҽڵ�
    if (targetNode.lTag == Link && targetNode.leftChild != nullptr) {
        current = targetNode.leftChild;
        while (current->rTag == Link && current->rightChild != nullptr) {
            current = current->rightChild;
        }
        pre = current;
    }

    // ���ǰ�������ڣ���ʾ�ýڵ�Ϊ��С�ڵ㣬û��ǰ��
    if (pre == nullptr) throw std::logic_error("There is no predecessor for the given node.");

    return *pre;
}

TreeNode& MyTree::nextNode(const TreeNode& targetNode) {
    if (root == nullptr) throw std::logic_error("Tree is empty.");

    // �������������ֱ�ӷ��������ڵ�
    if (targetNode.rTag == Thread) {
        return *(targetNode.rightChild);
    }

    // ������ͨ����������
    TreeNode* current = root;
    TreeNode* next = nullptr;  // ����׷�ٺ��

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

    // ����ҵ��ڵ������������ڣ�����������������ڵ�
    if (targetNode.rTag == Link && targetNode.rightChild != nullptr) {
        current = targetNode.rightChild;
        while (current->lTag == Link && current->leftChild != nullptr) {
            current = current->leftChild;
        }
        next = current;
    }

    // �����̲����ڣ���ʾ�ýڵ�Ϊ���ڵ㣬û�к��
    if (next == nullptr) throw std::logic_error("There is no successor for the given node.");

    return *next;
}

TreeNode& MyTree::locateNode(const char& v) {
    TreeNode* current = root;
    stack<TreeNode*> stack;

    // ��������Զ�λ�����ض�ֵ�Ľڵ�
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

    // ����Ҳ������׳��쳣
    throw std::logic_error("Node with the given value not found.");
}





