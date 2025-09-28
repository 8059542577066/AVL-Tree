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

    int getSize() const;
    int getDepth() const;
    Node *getMinNode() const;
    Node *getMaxNode() const;
    Node *getMinNodeInc(const Type &) const;
    Node *getMinNodeExc(const Type &) const;
    Node *getMaxNodeInc(const Type &) const;
    Node *getMaxNodeExc(const Type &) const;
#ifndef MULTI
    Node *find(const Type &) const;
#endif
    void copyAllAsc(Type *const) const;
    void copyAllDesc(Type *const) const;

    void push(const Type &);
#ifndef MULTI
    void pop(const Type &);
#endif
    void pop(Node *const);
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


int Tree::getSize() const
{
    return this->size;
}

int Tree::getDepth() const
{
    if (this->root == NULL)
        return 0;

    return this->root->getDepth();
}

Node *Tree::getMinNode() const
{
    if (this->root == NULL)
        return NULL;

    return this->root->getLeftMost();
}

Node *Tree::getMaxNode() const
{
    if (this->root == NULL)
        return NULL;

    return this->root->getRightMost();
}

Node *Tree::getMinNodeInc(const Type &value) const
{
    if (this->root == NULL)
        return NULL;

    return this->root->locateMinInc(value);
}

Node *Tree::getMinNodeExc(const Type &value) const
{
    if (this->root == NULL)
        return NULL;

    return this->root->locateMinExc(value);
}

Node *Tree::getMaxNodeInc(const Type &value) const
{
    if (this->root == NULL)
        return NULL;

    return this->root->locateMaxInc(value);
}

Node *Tree::getMaxNodeExc(const Type &value) const
{
    if (this->root == NULL)
        return NULL;

    return this->root->locateMaxExc(value);
}

#ifndef MULTI
Node *Tree::find(const Type &value) const
{
    if (this->root == NULL)
        return NULL;

    return this->root->locate(value);
}
#endif

void Tree::copyAllAsc(Type *const array) const
{
    if (this->root != NULL)
    {
        int index = 0;
        this->root->copyAsc(array, index);
    }
}

void Tree::copyAllDesc(Type *const array) const
{
    if (this->root != NULL)
    {
        int index = 0;
        this->root->copyDesc(array, index);
    }
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
        Node *const node = this->root->append(value);

        if (node != NULL)
        {
            ++this->size;
            this->root = node;
        }
    }
}

#ifndef MULTI
void Tree::pop(const Type &value)
{
    if (this->root == NULL)
        return;

    Node *const node = this->root->locate(value);

    if (node == NULL)
        return;

    --this->size;
    this->root = node->remove();
}
#endif

void Tree::pop(Node *const node)
{
    if (node == NULL)
        return;

    if (node->getRoot() != this->root)
        return;

    --this->size;
    this->root = node->remove();
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