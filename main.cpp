#include "myTree.h"//
int main(){
    
     MyTree myTree("ABC@@DE@G@@F@@@");
     
    /* myTree.preOrderTraverse();//ABCDEGF
     cout<<endl;
     

     
     myTree.inOrderTraverse();//CBEGDFA
     cout<<endl;
     
     myTree.postOrderTraverse();//CGEFDBA
     cout<<endl;
     */
     
     //cout<<myTree.countLeaf()<<endl;//3
     //cout<<myTree.countHeight()<<endl;//5
     
    // MyTree myThreadedTree(myTree);

     //cout<<myThreadedTree.isThreadedTree()<<endl;//0
     //myThreadedTree.inOrderThreading();
    // cout<<myThreadedTree.isThreadedTree()<<endl;//1
     //myThreadedTree.inOrderTraverse();//CBEGDFA
     //cout<<endl;
 
    // TreeNode n = myThreadedTree.locateNode('G');
    // myThreadedTree.preNode(n).printNode();//E
   //  cout<<endl;
    // myThreadedTree.nextNode(n).printNode();//D
    // cout<<endl;
    
    int v[]={2,7,5,4};
    HuffmanTree hTree(4,v);
    hTree.printHuffmanCodes();
   
   /*
    7:0
    5:10
    4:111
    2:110
    */

    return 0;
}
// Created by 22128 on 2024/2/17.
//
