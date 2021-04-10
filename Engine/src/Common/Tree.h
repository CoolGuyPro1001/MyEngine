#ifndef TREE_H
#define TREE_H

template<typename T>
struct BinaryNode
{
    BinaryNode(T data)
    {
        this->data = data;
    }

    BinaryNode(T data, BinaryNode* left, BinaryNode* right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    BinaryNode* left;
    BinaryNode* right;
    T data;
};

template<typename T>
struct QuadNode
{
    QuadNode(T data)
    {
        this->data = data;
    }

    QuadNode(T data, QuadNode* top_left, QuadNode* top_right, QuadNode* bottom_left, QuadNode* bottom_right)
    {
        this->data = data;
        this->top_left = top_left;
        this->top_right = top_right;
        this->bottom_left = bottom_left;
        this->bottom_right = bottom_right;
    }

    QuadNode* top_left;
    QuadNode* top_right;
    QuadNode* bottom_left;
    QuadNode* bottom_right;

    T data;
};

template<typename T>
struct OctNode
{
    OctNode* top_forward_left;
    OctNode* top_forward_right;
    OctNode* top_back_left;
    OctNode* top_back_right;
    OctNode* bottom_forward_left;
    OctNode* bottom_forward_right;
    OctNode* bottom_back_left;
    OctNode* bottom_back_right;

    T data;
};
#endif