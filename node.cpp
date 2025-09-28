#ifndef NODE_CPP
#define NODE_CPP


#ifndef NULL
#define NULL 0
#endif

#ifndef Type
#define Type unsigned
#endif


class Node
{
private:
    int depthLeft;
    int depthRight;
    Type value;
    Node *parent;
    Node *childLeft;
    Node *childRight;

    int getDepth() const;
    int getBalanceFactor() const;
    void updateParentDepth();
    void swap(Node *const);
    Node *rotateLL();
    Node *rotateLR();
    Node *rotateRL();
    Node *rotateRR();
    Node *balancePush();
    Node *balancePull();
    Node *getLeftMost();
    Node *getRightMost();
    Node *getNodeToSwap();
    Node *append(const Type &);
    Node *remove();

    friend class Tree;
    Node(const Type &);

    Node *getRoot();
#ifndef MULTI
    Node *locate(const Type &);
#endif
    Node *locateMinInc(const Type &);
    Node *locateMinExc(const Type &);
    Node *locateMaxInc(const Type &);
    Node *locateMaxExc(const Type &);
    void copyAsc(Type *const, int &) const;
    void copyDesc(Type *const, int &) const;
    void purge();

public:
    Type getValue() const;
    Node *getNextLeft();
    Node *getNextRight();
};


int Node::getDepth() const
{
    if (this->depthLeft > this->depthRight)
        return this->depthLeft + 1;
    else
        return this->depthRight + 1;
}

int Node::getBalanceFactor() const
{
    return this->depthRight - this->depthLeft;
}

void Node::updateParentDepth()
{
    if (this->parent == NULL)
        return;

    int depth = this->getDepth();

    if (this == this->parent->childLeft)
    {
        if (depth == this->parent->depthLeft)
            return;

        this->parent->depthLeft = depth;
    }
    else
    {
        if (depth == this->parent->depthRight)
            return;

        this->parent->depthRight = depth;
    }

    this->parent->updateParentDepth();
}

void Node::swap(Node *const node)
{
    if (this == node->parent)
    {
        node->parent = this->parent;
        this->parent = node;

        if (node->parent != NULL)
        {
            if (node->parent->childLeft == this)
                node->parent->childLeft = node;
            else
                node->parent->childRight = node;
        }

        if (this->childLeft == node)
        {
            this->childLeft = node->childLeft;
            node->childLeft = this;

            if (this->childLeft != NULL)
                this->childLeft->parent = this;

            node->childRight = this->childRight;
            this->childRight = NULL;

            if (node->childRight != NULL)
                node->childRight->parent = node;
        }
        else
        {
            this->childRight = NULL;
            node->childRight = this;
        }
    }
    else
    {
        Node *ptr = this->parent;
        this->parent = node->parent;
        node->parent = ptr;

        if (this->parent->childLeft == node)
            this->parent->childLeft = this;
        else
            this->parent->childRight = this;

        if (node->parent != NULL)
        {
            if (node->parent->childLeft == this)
                node->parent->childLeft = node;
            else
                node->parent->childRight = node;
        }

        ptr = this->childLeft;
        this->childLeft = node->childLeft;
        node->childLeft = ptr;

        if (this->childLeft != NULL)
            this->childLeft->parent = this;

        node->childLeft->parent = node;
        node->childRight = this->childRight;
        this->childRight = NULL;
        node->childRight->parent = node;
    }

    int depth = this->depthLeft;
    this->depthLeft = node->depthLeft;
    node->depthLeft = depth;
    depth = this->depthRight;
    this->depthRight = node->depthRight;
    node->depthRight = depth;
}

Node *Node::rotateLL()
{
    Node *const b = this;
    Node *const a = this->parent;
    Node *const bR = b->childRight;

    if (a->parent != NULL)
    {
        if (a == a->parent->childLeft)
            a->parent->childLeft = b;
        else
            a->parent->childRight = b;
    }

    b->parent = a->parent;
    b->childRight = a, a->parent = b;
    a->childLeft = bR;

    if (bR != NULL)
    {
        bR->parent = a;
        a->depthLeft = bR->getDepth();
    }
    else
        a->depthLeft = 0;

    b->depthRight = a->getDepth();
    b->updateParentDepth();

    return b;
}

Node *Node::rotateLR()
{
    Node *const c = this->childRight;
    Node *const b = this;
    Node *const a = this->parent;
    Node *const cL = c->childLeft;
    Node *const cR = c->childRight;

    if (a->parent != NULL)
    {
        if (a == a->parent->childLeft)
            a->parent->childLeft = c;
        else
            a->parent->childRight = c;
    }

    c->parent = a->parent;
    c->childLeft = b, b->parent = c;
    c->childRight = a, a->parent = c;
    b->childRight = cL;

    if (cL != NULL)
    {
        cL->parent = b;
        b->depthRight = cL->getDepth();
    }
    else
        b->depthRight = 0;

    a->childLeft = cR;

    if (cR != NULL)
    {
        cR->parent = a;
        a->depthLeft = cR->getDepth();
    }
    else
        a->depthLeft = 0;

    c->depthLeft = b->getDepth();
    c->depthRight = a->getDepth();
    c->updateParentDepth();

    return c;
}

Node *Node::rotateRL()
{
    Node *const c = this->childLeft;
    Node *const b = this;
    Node *const a = this->parent;
    Node *const cL = c->childLeft;
    Node *const cR = c->childRight;

    if (a->parent != NULL)
    {
        if (a == a->parent->childLeft)
            a->parent->childLeft = c;
        else
            a->parent->childRight = c;
    }

    c->parent = a->parent;
    c->childLeft = a, a->parent = c;
    c->childRight = b, b->parent = c;
    a->childRight = cL;

    if (cL != NULL)
    {
        cL->parent = a;
        a->depthRight = cL->getDepth();
    }
    else
        a->depthRight = 0;

    b->childLeft = cR;

    if (cR != NULL)
    {
        cR->parent = b;
        b->depthLeft = cR->getDepth();
    }
    else
        b->depthLeft = 0;

    c->depthLeft = a->getDepth();
    c->depthRight = b->getDepth();
    c->updateParentDepth();

    return c;
}

Node *Node::rotateRR()
{
    Node *const b = this;
    Node *const a = this->parent;
    Node *const bL = b->childLeft;

    if (a->parent != NULL)
    {
        if (a == a->parent->childLeft)
            a->parent->childLeft = b;
        else
            a->parent->childRight = b;
    }

    b->parent = a->parent;
    b->childLeft = a, a->parent = b;
    a->childRight = bL;

    if (bL != NULL)
    {
        bL->parent = a;
        a->depthRight = bL->getDepth();
    }
    else
        a->depthRight = 0;

    b->depthLeft = a->getDepth();
    b->updateParentDepth();

    return b;
}

Node *Node::balancePush()
{
    Node *const b = this;
    Node *const a = this->parent;

    if (a == NULL)
        return b;

    int balA = a->getBalanceFactor();

    if (balA < -1)
    {
        if (b->getBalanceFactor() < 0)
            return b->rotateLL()->balancePush();
        else
            return b->rotateLR()->balancePush();
    }
    else if (balA > 1)
    {
        if (b->getBalanceFactor() < 0)
            return b->rotateRL()->balancePush();
        else
            return b->rotateRR()->balancePush();
    }

    return a->balancePush();
}

Node *Node::balancePull()
{
    Node *a = this;
    int balA = a->getBalanceFactor();

    if (balA < -1)
    {
        Node *const b = this->childLeft;

        if (b->getBalanceFactor() < 0)
            a = b->rotateLL();
        else
            a = b->rotateLR();
    }
    else if (balA > 1)
    {
        Node *const b = this->childRight;

        if (b->getBalanceFactor() < 0)
            a = b->rotateRL();
        else
            a = b->rotateRR();
    }

    if (a->parent == NULL)
        return a;

    return a->parent->balancePull();
}

Node *Node::getLeftMost()
{
    if (this->childLeft == NULL)
        return this;

    return this->childLeft->getLeftMost();
}

Node *Node::getRightMost()
{
    if (this->childRight == NULL)
        return this;

    return this->childRight->getRightMost();
}

Node *Node::getNodeToSwap()
{
    if (this->childLeft != NULL)
        return this->childLeft->getRightMost();

    if (this->childRight != NULL)
        return this->childRight;

    return this;
}

Node *Node::append(const Type &value)
{
    if (value < this->value)
    {
        if (this->childLeft == NULL)
        {
            Node *const node = new Node(value);
            this->childLeft = node;
            node->parent = this;
            this->depthLeft = 1;
            this->updateParentDepth();

            return this->balancePush();
        }

        return this->childLeft->append(value);
    }
#ifndef MULTI
    else if (this->value < value)
#else
    else
#endif
    {
        if (this->childRight == NULL)
        {
            Node *const node = new Node(value);
            this->childRight = node;
            node->parent = this;
            this->depthRight = 1;
            this->updateParentDepth();

            return this->balancePush();
        }

        return this->childRight->append(value);
    }
#ifndef MULTI
    else
        return NULL;
#endif
}

Node *Node::remove()
{
    Node *node = this->getNodeToSwap();

    while (this != node)
    {
        this->swap(node);
        node = this->getNodeToSwap();
    }

    if (this->parent != NULL)
    {
        if (this == this->parent->childLeft)
        {
            this->parent->childLeft = NULL;
            this->parent->depthLeft = 0;
        }
        else
        {
            this->parent->childRight = NULL;
            this->parent->depthRight = 0;
        }

        Node *const parent = this->parent;
        delete this;
        parent->updateParentDepth();

        return parent->balancePull();
    }

    delete this;

    return NULL;
}


Node::Node(const Type &value)
{
    this->depthLeft = 0;
    this->depthRight = 0;
    this->value = value;
    this->parent = NULL;
    this->childLeft = NULL;
    this->childRight = NULL;
}


Node *Node::getRoot()
{
    if (this->parent == NULL)
        return this;

    return this->parent->getRoot();
}

#ifndef MULTI
Node *Node::locate(const Type &value)
{
    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return NULL;

        return this->childLeft->locate(value);
    }
    else if (this->value < value)
    {
        if (this->childRight == NULL)
            return NULL;

        return this->childRight->locate(value);
    }
    else
        return this;
}
#endif

Node *Node::locateMinInc(const Type &value)
{
    if (this->value < value)
    {
        if (this->childRight == NULL)
            return this->getNextRight();

        return this->childRight->locateMinInc(value);
    }
    else
    {
        if (this->childLeft == NULL)
            return this;

        return this->childLeft->locateMinInc(value);
    }
}

Node *Node::locateMinExc(const Type &value)
{
    return this->locateMaxInc(value)->getNextRight();
}

Node *Node::locateMaxInc(const Type &value)
{
    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return this->getNextLeft();

        return this->childLeft->locateMaxInc(value);
    }
    else
    {
        if (this->childRight == NULL)
            return this;

        return this->childRight->locateMaxInc(value);
    }
}

Node *Node::locateMaxExc(const Type &value)
{
    return this->locateMinInc(value)->getNextLeft();
}

void Node::copyAsc(Type *const array, int &index) const
{
    if (this->childLeft != NULL)
        this->childLeft->copyAsc(array, index);

    array[index++] = this->value;

    if (this->childRight != NULL)
        this->childRight->copyAsc(array, index);
}

void Node::copyDesc(Type *const array, int &index) const
{
    if (this->childRight != NULL)
        this->childRight->copyDesc(array, index);

    array[index++] = this->value;

    if (this->childLeft != NULL)
        this->childLeft->copyDesc(array, index);
}

void Node::purge()
{
    if (this->childLeft != NULL)
        this->childLeft->purge();

    if (this->childRight != NULL)
        this->childRight->purge();

    delete this;
}


Type Node::getValue() const
{
    return this->value;
}

Node *Node::getNextLeft()
{
    if (this->childLeft != NULL)
        return this->childLeft->getRightMost();

    if (this->parent == NULL)
        return NULL;

    if (this == this->parent->childRight)
        return this->parent;

    Node *child = this,
         *parent;

    while (true)
    {
        parent = child->parent;

        if (parent == NULL)
            return NULL;

        if (child == parent->childRight)
            return parent;

        child = parent;
    }
}

Node *Node::getNextRight()
{
    if (this->childRight != NULL)
        return this->childRight->getLeftMost();

    if (this->parent == NULL)
        return NULL;

    if (this == this->parent->childLeft)
        return this->parent;

    Node *child = this,
         *parent;

    while (true)
    {
        parent = child->parent;

        if (parent == NULL)
            return NULL;

        if (child == parent->childLeft)
            return parent;

        child = parent;
    }
}


#endif