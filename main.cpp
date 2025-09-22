/* In order to use Tree class from tree.cpp
   you must define the data type you want to insert by

   #define Type <your type or class name>

   Also 2 operators: = (assignment), < (less than)
   have to be overridden before including "tree.cpp".
*/
#include "tree.cpp"
/* SHA-256 of the 2 source files.
   node.cpp  1EDD6975EC90595D54607C06A8C8A9859F2D89F124097FA45611FAFDB7A98C36
   tree.cpp  F37D71951CF453FB6579E7822BBD39B8AB4C7B51F331D147944959A1D88ACD9F
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
   printf("-----Test <1a>-----\n");

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
   printf("\n\n-----Test <1b>-----\n");

   for (int i = 0; i != size / 4; ++i)
      tree.push(i);

   printf("+1 item & millions of duplicates are inserted.\n");
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
   printf("\n\n-----Test <2a>-----\n");

   for (int i = size / 8 * 7; i--;)
      tree.pop(i);

   printf("7/8 smallest items are deleted.\n");
   printf("Size(2**21): %d\n", tree.getSize());
   printf("Depth(22):   %d\n", tree.getDepth());
   system("pause");

   /* Test <2b>

       I will delete all items from the tree except the last 3.

       Valid AVL rebalancing has to keep any possible
       configurations of 3-node trees to have depths of 2.

       While doing this, I will also try to delete items
       that are not in the tree, and these should be ignored.
   */
   printf("\n\n-----Test <2b>-----\n");

   for (int i = size - 3; i-- != size / 4 * 3;)
      tree.pop(i);

   printf("3 items are left in tree.\n");
   printf("Size(3):  %d\n", tree.getSize());
   printf("Depth(2): %d\n", tree.getDepth());
   system("pause");

   /* Test <2c>

       Using empty() function to clear out the tree.
       Unlike the destructor though, the same tree should be usable.

       I will test it by first calling empty() function,
       then repeat <1a> process to reinsert items to the same tree.
   */
   printf("\n\n-----Test <2c>-----\n");
   tree.empty();
   printf("Tree is emptied.\n");
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
   printf("\n\n-----Test <3a>-----\n");
   std::vector<Type> array1;

   for (int i = 0; i != size; ++i)
      array1.push_back(i);

   std::vector<Type> array2;
   array2.resize(size);
   tree.copyAllAsc(&array2[0]);
   printf("Copying tree to vector Asc(1): %d\n", array1 == array2);
   system("pause");

   /* Test <3b>

       I will copy all items from the tree to a vector
       in DESCending order, then compare it with a sorted vector.
   */
   printf("\n\n-----Test <3b>-----\n");
   std::reverse(array1.begin(), array1.end());
   tree.copyAllDesc(&array2[0]);
   printf("Copying tree to vector Desc(1): %d\n", array1 == array2);
   array1.clear();
   array2.clear();
   system("pause");

   /* Test <3c>

       I will delete items using iterator (Node *) as param.
       Deleting the middle 1/3 of the tree in DESCending order
       WILL inevitably invoke node replacement then deletion.
       Also because AVL tree's L-R imbalance ratio can't exceed
       1:1.618(or 1.618:1), in this deletion loop
       there WILL be case(s) where the root node is deleted as well.

       Then I will delete the rest of the tree using iterator traversal
       but in ASCending order to make sure calling iterator deletion
       works safely until all the items are deleted.
   */
   printf("\n\n-----Test <3c>-----\n");
   Node *curr = tree.getMaxNodeInc(size / 3 * 2),
        *term = tree.getMaxNodeExc(size / 3),
        *next = curr->getNextLeft();

   while (true)
   {
      tree.pop(curr);

      if (next == term)
         break;

      curr = next;
      next = curr->getNextLeft();
   }

   printf("1/3 middle items are deleted in Desc order.\n");
   curr = tree.getMinNode();
   term = NULL;
   next = curr->getNextRight();

   while (true)
   {
      tree.pop(curr);

      if (next == term)
         break;

      curr = next;
      next = curr->getNextRight();
   }

   printf("All remaining items are deleted in Asc order.\n");
   printf("Size(0):  %d\n", tree.getSize());
   printf("Depth(0): %d\n", tree.getDepth());
   system("pause");

   /* Test <4a>

       I will fill the tree up with even numbers.
       In version 1.2, class structures have been modified
       and position iterators and traversing functions have been added.

       First, all the iterator functions will be tested to see
       if they return the correct node positions.
   */
   printf("\n\n-----Test <4a>-----\n");

   for (int i = size; i != 2; i -= 2)
      tree.push(i);

   printf("Even numbers are inserted.\n");
   Node *min = tree.getMinNodeInc(1000000),
        *max = tree.getMaxNodeInc(1000000);
   printf("\nSmallest value greater than or equal to 10**6(10**6): %u\n",
          min->getValue());
   printf("Largest value less than or equal to 10**6(10**6):     %u\n",
          max->getValue());

   min = tree.getMinNodeInc(999999);
   max = tree.getMaxNodeInc(999999);
   printf("\nSmallest value greater than or equal to 10**6 - 1(10**6): %u\n",
          min->getValue());
   printf("Largest value less than or equal to 10**6 - 1(10**6 - 2): %u\n",
          max->getValue());

   min = tree.getMinNodeExc(1000000);
   max = tree.getMaxNodeExc(1000000);
   printf("\nSmallest value greater than 10**6(10**6 + 2): %u\n",
          min->getValue());
   printf("Largest value less than 10**6(10**6 - 2):     %u\n",
          max->getValue());

   min = tree.getMinNodeExc(999999);
   max = tree.getMaxNodeExc(999999);
   printf("\nSmallest value greater than 10**6 - 1(10**6): %u\n",
          min->getValue());
   printf("Largest value less than 10**6 - 1(10**6 - 2): %u\n",
          max->getValue());
   system("pause");

   /* Test <4b>

       Copying all items to vector, but this time it's done using iterator.
       Starting from the minimum and traverse all the way up.
   */
   printf("\n\n-----Test <4b>-----\n");

   for (int i = 4; i <= size; i += 2)
      array1.push_back(i);

   array2.resize(array1.size());
   Type *pointer = &array2[0];

   for (Node *iter = tree.getMinNode(); iter != NULL;)
   {
      *pointer++ = iter->getValue();
      iter = iter->getNextRight();
   }

   printf("Traversing and copying Asc(1): %d\n", array1 == array2);
   system("pause");

   /* Test <4c>

       Copying all items to vector, but this time it's done using iterator.
       Starting from the maximum and traverse all the way down.
   */
   printf("\n\n-----Test <4c>-----\n");
   std::reverse(array1.begin(), array1.end());
   pointer = &array2[0];

   for (Node *iter = tree.getMaxNode(); iter != NULL;)
   {
      *pointer++ = iter->getValue();
      iter = iter->getNextLeft();
   }

   printf("Traversing and copying Desc(1): %d\n", array1 == array2);
   system("pause");

   return 0;
}