#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
//Basic Binary Search Tree Implementation, Mr.Koumparakis' notes from Data Structures, modified
treeNode * newTreeNode(char * walletID, int amount){
	treeNode * node=malloc(sizeof(treeNode));
	node->amount=amount;
	node->walletID=malloc(sizeof(char)*(strlen(walletID)+1));
	strncpy(node->walletID, walletID, strlen(walletID)+1);
	node->left=NULL;
	node->right=NULL;
	return node;

}

/*treeNode * searchTree(treeNode * root, int bitcoinID ){
	if(root==NULL || root->bitcoinID==bitcoinID) return root;
	else if((root->bitcoinID) < bitcoinID ) return searchTree(root->left, bitcoinID);
	else searchTree(root->right, bitcoinID);
}
*/
treeNode * insertTree(treeNode * node,  char * walletID, int amount){
	if(node==NULL) return newTreeNode(walletID, amount);
	if(walletID == node->walletID ) return insertTree(node->right, walletID, amount);
	else if(walletID != node->walletID ) return insertTree(node->left, walletID, amount);
	return NULL;
}

void printPostorder(treeNode * node, int bitcoinID) 
{ 
    if (node == NULL) return;
    printPostorder(node->left, bitcoinID); 
    printPostorder(node->right, bitcoinID); 
    printf("user %s owns %d\n", node->walletID, node->amount); 
} 

void deleteTree(treeNode * node){
	if(node==NULL) return;
	deleteTree(node->left);
	deleteTree(node->right);
	free(node);
}