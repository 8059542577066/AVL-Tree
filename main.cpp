// In order to use Tree class from tree.cpp
// you must define the data type you want to insert by

// #define Type <your type or class name>

// Also 2 operators: = (assignment), < (less than)
// have to be overridden before including "tree.cpp".
#define Type unsigned

#define Node NodeUnique
#define Tree TreeUnique
#include "tree.cpp"
// SHA-256 of the 2 source files.
// node.cpp  6FBFE3C53F6F899DE3FB4BECECCE423C27653C1C6210B0E9FDCE92B690A2A6DD
// tree.cpp  C931A68441BAC8F71C9AE96A1E9C39A1EBAD19C686A461E4D5243349EA8E0802
#undef NODE_CPP
#undef TREE_CPP
#undef Node
#undef Tree

#define Node NodeMulti
#define Tree TreeMulti
#define MULTI
#include "tree.cpp"
#undef NODE_CPP
#undef TREE_CPP
#undef Node
#undef Tree
#undef MULTI

#include <vector>
#include <cstdio>
#include <cstdlib>


bool inAscOrder(const std::vector<unsigned> &vector)
{
    bool check = true;

    for (std::size_t i = 1; i < vector.size(); ++i)
        check = check && (vector[i - 1] <= vector[i]);

    return check;
}

bool inDescOrder(const std::vector<unsigned> &vector)
{
    bool check = true;

    for (std::size_t i = 1; i < vector.size(); ++i)
        check = check && (vector[i - 1] >= vector[i]);

    return check;
}


int main()
{
    TreeUnique treeUnique;
    unsigned size = 16 * 1024 * 1024;

    // Test <1>
    //   Insert (2**24 - 1) items in ASCending order.
    //   The tree will be a perfect binary tree with depth of 24.
    std::printf("-----Test <1>-----\n");

    for (unsigned i = 1; i <= size - 1; ++i)
        treeUnique.push(i);

    std::printf("Size  (2**24 - 1): %d\n", treeUnique.getSize());
    std::printf("Depth        (24): %d\n", treeUnique.getDepth());
    std::system("pause");

    {
        // Test <2a>
        //   Delete items in DESCending order using iterator(Node *).
        //   The tree will be left with (2**22 - 1) items and 22 deep.
        //   Deleted items will be stored and tested for order.
        std::printf("\n\n\n\n-----Test <2a>-----\n");
        std::vector<unsigned> vector;

        NodeUnique *curr = treeUnique.find(size / 4 * 3),
                   *term = treeUnique.getMinNode()->getNextLeft(),
                   *next = curr->getNextLeft();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeUnique.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextLeft();
        }

        std::printf("In DESC order  (1): %d\n", inDescOrder(vector));
        std::printf("Size   (2**22 - 1): %d\n", treeUnique.getSize());
        std::printf("Depth         (22): %d\n", treeUnique.getDepth());
        std::system("pause");

        // Test <2b>
        //   Delete items in ASCending order using iterator(Node *).
        //   The tree will be left with 0 item.
        //   Deleted items will be stored and tested for order.
        std::printf("\n\n-----Test <2b>-----\n");
        vector.clear();

        curr = treeUnique.getMinNode();
        term = treeUnique.getMaxNode()->getNextRight();
        next = curr->getNextRight();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeUnique.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextRight();
        }

        std::printf("In ASC order  (1): %d\n", inAscOrder(vector));
        std::printf("Size          (0): %d\n", treeUnique.getSize());
        std::printf("Depth         (0): %d\n", treeUnique.getDepth());
    }

    std::printf("\n !!! Memory Cleared !!!\n");
    std::system("pause");

    {
        // Test <3a>
        //   Insert (2**20 - 1) even numbers in DESCending order.
        std::printf("\n\n\n\n-----Test <3a>-----\n");

        for (unsigned i = size / 16 - 1; i >= 1; --i)
            treeUnique.push(2 * i);

        std::printf("Size  (2**20 - 1): %d\n", treeUnique.getSize());
        std::printf("Depth        (20): %d\n", treeUnique.getDepth());

        NodeUnique *min = treeUnique.getMinNodeInc(1000000),
                   *max = treeUnique.getMaxNodeInc(1000000);
        std::printf("\nMIN value >= 10**6          (10**6): %u\n",
                    min->getValue());
        std::printf("MAX value <= 10**6          (10**6): %u\n",
                    max->getValue());

        min = treeUnique.getMinNodeInc(999999);
        max = treeUnique.getMaxNodeInc(999999);
        std::printf("\nMIN value >= 10**6 - 1      (10**6): %u\n",
                    min->getValue());
        std::printf("MAX value <= 10**6 - 1  (10**6 - 2): %u\n",
                    max->getValue());

        min = treeUnique.getMinNodeExc(1000000);
        max = treeUnique.getMaxNodeExc(1000000);
        std::printf("\nMIN value > 10**6       (10**6 + 2): %u\n",
                    min->getValue());
        std::printf("MAX value < 10**6       (10**6 - 2): %u\n",
                    max->getValue());

        min = treeUnique.getMinNodeExc(999999);
        max = treeUnique.getMaxNodeExc(999999);
        std::printf("\nMIN value > 10**6 - 1       (10**6): %u\n",
                    min->getValue());
        std::printf("MAX value < 10**6 - 1   (10**6 - 2): %u\n",
                    max->getValue());
        std::system("pause");

        // Test <3b>
        //   Copy all items to vector in ASCending order.
        std::printf("\n\n-----Test <3b>-----\n");
        std::vector<unsigned> vector;
        vector.resize(treeUnique.getSize());
        treeUnique.copyAllAsc(&vector[0]);
        std::printf("In ASC order  (1): %d\n", inAscOrder(vector));
        std::system("pause");

        // Test <3c>
        //   Copy all items to vector in DESCending order.
        std::printf("\n\n-----Test <3c>-----\n");
        vector.clear();
        treeUnique.copyAllDesc(&vector[0]);
        std::printf("In DESC order  (1): %d\n", inDescOrder(vector));
        std::system("pause");
    }

    // Test <4>
    //   Empty the tree.
    std::printf("\n\n\n\n-----Test <4>-----\n");
    treeUnique.empty();
    std::printf("Size   (0): %d\n", treeUnique.getSize());
    std::printf("Depth  (0): %d\n", treeUnique.getDepth());

    std::printf("\n !!! Memory Cleared !!!\n");
    std::system("pause");

    // Test <5>
    //   Insert (2**24 - 1) multi-valued(non-unique) items.
    std::printf("\n\n\n\n-----Test <5>-----\n");
    TreeMulti treeMulti;

    for (unsigned i = 1; i <= size - 1; ++i)
        treeMulti.push(i & 0xFF);

    std::printf("Size  (2**24 - 1): %d\n", treeMulti.getSize());
    std::printf("Depth        (24): %d\n", treeMulti.getDepth());
    std::system("pause");

    {
        // Test <6>
        //   Delete items in ranges.
        //   [LM] [->] [<-] [  ] [  ] [<-] [->] [RM]
        //   LM - LeftMost, RM - RightMost
        //   Arrow indicates iterator traversal direction.
        //   Each bin([  ]) indicates 1/8 of the entire tree.
        std::printf("\n\n\n\n-----Test <6>-----\n");
        std::vector<unsigned> vector;

        NodeMulti *curr = treeMulti.getMinNodeInc(32),
                  *term = treeMulti.getMinNodeExc(63),
                  *next = curr->getNextRight();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeMulti.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextRight();
        }

        std::printf("In ASC order   (1): %d\n", inAscOrder(vector));
        vector.clear();

        curr = treeMulti.getMaxNodeInc(95);
        term = treeMulti.getMaxNodeExc(64);
        next = curr->getNextLeft();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeMulti.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextLeft();
        }

        std::printf("In DESC order  (1): %d\n", inDescOrder(vector));
        vector.clear();

        curr = treeMulti.getMaxNodeInc(191);
        term = treeMulti.getMaxNodeExc(160);
        next = curr->getNextLeft();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeMulti.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextLeft();
        }

        std::printf("In DESC order  (1): %d\n", inDescOrder(vector));
        vector.clear();

        curr = treeMulti.getMinNodeInc(192);
        term = treeMulti.getMinNodeExc(223);
        next = curr->getNextRight();

        while (true)
        {
            vector.push_back(curr->getValue());
            treeMulti.pop(curr);

            if (next == term)
                break;

            curr = next;
            next = curr->getNextRight();
        }

        std::printf("In ASC order   (1): %d\n", inAscOrder(vector));
        std::printf("Size   (2**23 - 1): %d\n", treeMulti.getSize());
    }

    treeMulti.empty();
    std::printf("\n !!! Memory Cleared !!!\n");
    std::system("pause");

    return 0;
}