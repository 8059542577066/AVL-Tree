#ifndef NODE_CPP
#define NODE_CPP


#ifndef NULL
#define NULL 0
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

    int getBalanceFactor();
    void updateParentDepth();
    Node *rotateLL();
    Node *rotateLR();
    Node *rotateRL();
    Node *rotateRR();
    Node *balancePush();
    Node *balancePull();
    Node *getNodeToDelete();

    friend class Tree;
    Node(const Type &);

    int getDepth();
    Node *getLeftMost();
    Node *getRightMost();
    Node *locate(const Type &);
    Node *locateMinInc(const Type &);
    Node *locateMinExc(const Type &);
    Node *locateMaxInc(const Type &);
    Node *locateMaxExc(const Type &);
    Node *append(const Type &);
    Node *remove();
    void copyAsc(Type *, int &);
    void copyDesc(Type *, int &);
    void purge();

public:
    Type getValue();
    Node *getNextLeft();
    Node *getNextRight();
};


int Node::getBalanceFactor()
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

Node *Node::rotateLL()
{
    Node *b = this,
         *a = this->parent,
         *bR = b->childRight;

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
    Node *c = this->childRight,
         *b = this,
         *a = this->parent,
         *cL = c->childLeft,
         *cR = c->childRight;

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
    Node *c = this->childLeft,
         *b = this,
         *a = this->parent,
         *cL = c->childLeft,
         *cR = c->childRight;

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
    Node *b = this,
         *a = this->parent,
         *bL = b->childLeft;

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
    Node *b = this,
         *a = this->parent;

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
        Node *b = this->childLeft;

        if (b->getBalanceFactor() < 0)
            a = b->rotateLL();
        else
            a = b->rotateLR();
    }
    else if (balA > 1)
    {
        Node *b = this->childRight;

        if (b->getBalanceFactor() < 0)
            a = b->rotateRL();
        else
            a = b->rotateRR();
    }

    if (a->parent == NULL)
        return a;

    return a->parent->balancePull();
}

Node *Node::getNodeToDelete()
{
    if (this->childLeft != NULL)
        return this->childLeft->getRightMost();

    if (this->childRight != NULL)
        return this->childRight;

    return this;
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


int Node::getDepth()
{
    if (this->depthLeft > this->depthRight)
        return this->depthLeft + 1;
    else
        return this->depthRight + 1;
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

Node *Node::locate(const Type &value)
{
    if (value == this->value)
        return this;

    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return NULL;

        return this->childLeft->locate(value);
    }
    else
    {
        if (this->childRight == NULL)
            return NULL;

        return this->childRight->locate(value);
    }
}

Node *Node::locateMinInc(const Type &value)
{
    if (value == this->value)
        return this;

    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return this;

        return this->childLeft->locateMinInc(value);
    }
    else
    {
        if (this->childRight == NULL)
            return this->getNextRight();

        return this->childRight->locateMinInc(value);
    }
}

Node *Node::locateMinExc(const Type &value)
{
    if (value == this->value)
        return this->getNextRight();

    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return this;

        return this->childLeft->locateMinExc(value);
    }
    else
    {
        if (this->childRight == NULL)
            return this->getNextRight();

        return this->childRight->locateMinExc(value);
    }
}

Node *Node::locateMaxInc(const Type &value)
{
    if (value == this->value)
        return this;

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
    if (value == this->value)
        return this->getNextLeft();

    if (value < this->value)
    {
        if (this->childLeft == NULL)
            return this->getNextLeft();

        return this->childLeft->locateMaxExc(value);
    }
    else
    {
        if (this->childRight == NULL)
            return this;

        return this->childRight->locateMaxExc(value);
    }
}

Node *Node::append(const Type &value)
{
    if (value == this->value)
        return NULL;

    if (value < this->value)
    {
        if (this->childLeft == NULL)
        {
            Node *node = new Node(value);
            this->childLeft = node;
            node->parent = this;
            this->depthLeft = 1;
            this->updateParentDepth();

            return this->balancePush();
        }

        return this->childLeft->append(value);
    }
    else
    {
        if (this->childRight == NULL)
        {
            Node *node = new Node(value);
            this->childRight = node;
            node->parent = this;
            this->depthRight = 1;
            this->updateParentDepth();

            return this->balancePush();
        }

        return this->childRight->append(value);
    }
}

Node *Node::remove()
{
    Node *node = this->getNodeToDelete(),
         *parent = node->parent;

    if (parent != NULL)
    {
        this->value = node->value;

        if (node == parent->childLeft)
        {
            if (node->childLeft != NULL)
            {
                parent->childLeft = node->childLeft;
                node->childLeft->parent = parent;
                parent->depthLeft = 1;
            }
            else
            {
                parent->childLeft = NULL;
                parent->depthLeft = 0;
            }
        }
        else
        {
            if (node->childLeft != NULL)
            {
                parent->childRight = node->childLeft;
                node->childLeft->parent = parent;
                parent->depthRight = 1;
            }
            else
            {
                parent->childRight = NULL;
                parent->depthRight = 0;
            }
        }
    }

    delete node;

    if (parent != NULL)
    {
        parent->updateParentDepth();

        return parent->balancePull();
    }

    return NULL;
}

void Node::copyAsc(Type *array, int &index)
{
    if (this->childLeft != NULL)
        this->childLeft->copyAsc(array, index);

    array[index++] = this->value;

    if (this->childRight != NULL)
        this->childRight->copyAsc(array, index);
}

void Node::copyDesc(Type *array, int &index)
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


Type Node::getValue()
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