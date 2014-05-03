
#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

template <class type>
class Node
{
	type data;
	size_t height;
	Node<type>* left;
	Node<type>* right;
	Node<type>* parent;

public:
	Node(): data(), height(0), left(NULL), right(NULL), parent(NULL){}
	Node(type d): data(d), height(0), left(NULL),right(NULL), parent(NULL){}

	/*Getter functions*/

	type get_data() const
	{
	    return data;
    }

	size_t get_height() const
	{
        return height;
	}

	Node<type>* get_left_ptr() const
	{
	    return left;
    }

	Node* get_right_ptr() const
	{
	    return right;
    }

    Node<type>* get_parent() const
    {
        return parent;
    }

    /*Setter functions*/

	void set_data(type d)
	{
	    data = d;
	    return;
    }

	void set_left_ptr(Node<type>* ptr)
	{
	    left = ptr;
	    return;
    }

	void set_right_ptr(Node<type>* ptr)
	{
	    right = ptr;
	    return;
    }

    void set_height(size_t h)
    {
        height = h;
        return;
    }

    void set_parent(Node<type>* ptr)
    {
        parent = ptr;
        return;
    }

};

#endif
