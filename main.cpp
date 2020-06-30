/* In order to use Tree class from tree.cpp
   you must define the data type you want to insert by
   
   #define Type <your type or class name>

   Also 3 operators: = (assignment), < (less than), == (equals to)
   have to be overridden before including "tree.cpp".
*/
#define Type unsigned long long
#include "tree.cpp"
/* SHA-256 of the 2 source files.
   node.cpp  F3D02FB0D6E5FE54FFB563ACC931EC1046A7D75EF105E4BA0A7EFB54F1E13517
   tree.cpp  9B1638A52FC8F9692D6398B20C1E9B9A62D0973F166B2BAB0E3D33119D917444
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>


int main()
{
   Tree tree;
   int size = 16 * 1024 * 1024;

   /* Test <1a>

       Insert (2**24 - 1) items from the largest to the smallest.
       Because I insert them sequentially
       the tree structure should be of exactly 24 depths.
   */
   for (int i = size; i-- != 1;)
      tree.push(i);

   printf("Size(2**24 - 1): %d\n", tree.getSize());
   printf("Depth(24):       %d\n", tree.getDepth());
   system("pause");

   /* Test <1b>

       Insert 1 more new item to the tree from <1a>.
       Now this should be +1 depth which is 25 depths.

       In addition to this,
       I will try inserting millions of duplicates
       that are already in the tree.

       Duplicates should be ignored and not inserted.
       So measuring in Mega Bytes, the memory usage
       MUST NOT seem to increase.
   */
   for (int i = 0; i != size / 4; ++i)
      tree.push(i);

   printf("\n\n+1 item & millions of duplicates are inserted.\n");
   printf("Size(2**24): %d\n", tree.getSize());
   printf("Depth(25):   %d\n", tree.getDepth());
   system("pause");

   /* Test <2a>
       
       I will delete the first 7/8 items from the tree.

       After the deletion if balancing worked properly
       the tree should be smaller by 3 depths.

       After this memory usage MUST decrease to roughly 1/8
       which means deleted nodes' memory have been released.
   */
   for (int i = size / 8 * 7; i--;)
      tree.pop(i);

   printf("\n\n7/8 smallest items are deleted.\n");
   printf("Size(2**21): %d\n", tree.getSize());
   printf("Depth(22):   %d\n", tree.getDepth());
   system("pause");

   /* Test <2b>
    
       I will delete all items from the tree except the last 3.

       Valid AVL rebalancing has to keep any possible
       configurations of 3-node trees to have depths of 2.

       While doing this, I will also try to delete items
       that are not on the tree, and these should be ignored.
   */
   for (int i = size - 3; i-- != size / 4 * 3;)
      tree.pop(i);

   printf("\n\n3 items left in tree.\n");
   printf("Size(3):  %d\n", tree.getSize());
   printf("Depth(2): %d\n", tree.getDepth());
   system("pause");

   /* Test <2c>

       Using empty() function to clear out the tree.
       Unlike the destructor though, the same tree should be usable.
       
       I will test it by first calling empty() function,
       then repeat <1a> process to reinsert items to the same tree.
   */
   tree.empty();
   printf("\n\nTree is emptied.\n");
   printf("Size(0):  %d\n", tree.getSize());
   printf("Depth(0): %d\n", tree.getDepth());

   for (int i = size; i--;)
      tree.push(i);

   printf("Tree is refilled with 2**24 items.\n");
   system("pause");

   /* Test <3a>

       I will copy all items from the tree to a vector
       in ASCending order, then compare it with a sorted vector.
   */
   std::vector<Type> array1;

   for (int i = 0; i != size; ++i)
      array1.push_back(i);

   std::vector<Type> array2;
   array2.resize(size);
   tree.copyAllAsc(&array2[0]);
   printf("\n\nCopying tree to vector Asc(1): %d\n", array1 == array2);
   system("pause");

   /* Test <3b>

       I will copy all items from the tree to a vector
       in DESCending order, then compare it with a sorted vector.
   */
   std::reverse(array1.begin(), array1.end());
   tree.copyAllDesc(&array2[0]);
   printf("\n\nCopying tree to vector Desc(1): %d\n", array1 == array2);
   system("pause");

   return 0;
}