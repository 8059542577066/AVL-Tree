#ifndef TREE_CPP
#define TREE_CPP

#include "node.cpp"


class Tree
{
private:
    int size;
    Node *root;

public:
    Tree();
    ~Tree();

    int getSize();
    int getDepth();
    bool find(const Type &);
    void push(const Type &);
    void pop(const Type &);
    void copyAllAsc(Type *);
    void copyAllDesc(Type *);
    void empty();
};


Tree::Tree()
{
    this->size = 0;
    this->root = NULL;
}

Tree::~Tree()
{
    if (this->root != NULL)
        this->root->purge();
}


int Tree::getSize()
{
    return this->size;
}

int Tree::getDepth()
{
    if (this->root == NULL)
        return 0;

    return this->root->getDepth();
}

bool Tree::find(const Type &value)
{
    if (this->root == NULL)
        return false;

    return this->root->locate(value) != NULL;
}

void Tree::push(const Type &value)
{
    if (this->root == NULL)
    {
        ++this->size;
        this->root = new Node(value);
    }
    else
    {
        Node *node = this->root->append(value);

        if (node != NULL)
        {
            ++this->size;
            this->root = node;
        }
    }
}

void Tree::pop(const Type &value)
{
    if (this->root == NULL)
        return;

    Node *node = this->root->locate(value);

    if (node == NULL)
        return;

    --this->size;
    this->root = node->remove();
}

void Tree::copyAllAsc(Type *array)
{
    if (this->root != NULL)
    {
        int index = 0;
        this->root->copyAsc(array, index);
    }
}

void Tree::copyAllDesc(Type *array)
{
    if (this->root != NULL)
    {
        int index = 0;
        this->root->copyDesc(array, index);
    }
}

void Tree::empty()
{
    if (this->root != NULL)
    {
        this->root->purge();
        this->size = 0;
        this->root = NULL;
    }
}


#endif