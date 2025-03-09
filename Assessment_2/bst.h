typedef int ElementType;


#ifndef _BST_H
#define _BST_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty( SearchTree T );
Position Find( ElementType X, SearchTree T );
Position FindMin( SearchTree T );
Position FindMax( SearchTree T );
SearchTree Insert( ElementType X, SearchTree T );
SearchTree Delete( ElementType X, SearchTree T );
ElementType Retrieve( Position P );

void PrintTree(SearchTree T);

/* New function prototypes - Sava Question 4*/  
Position findMin_K(SearchTree T, ElementType K); 
ElementType numLeafNodes(SearchTree T);
ElementType* levelOrder(SearchTree T);
void countNodes(SearchTree T,  ElementType* counter); 

#endif  /* _BST_H */
