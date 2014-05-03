#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "Node.h"
#include<iostream>

using std::ostream;
using std::cout;

class AVL_Tree
{
    private:

        bool debug_flag;
        Node<int>* root;
        size_t tree_size;
        static bool deletion_flag;

        /*To get parent of node*/

        /*get parent by node*/
        Node<int>* AVL_Tree::get_parent(Node<int>* node);

        /*get parent by value*/
        Node<int>* AVL_Tree::get_parent(int value);

          bool is_left_child (Node<int>* node);         //by node
          bool is_left_child (int value);               //by value
          bool is_right_child (Node<int>* node);        //by node
          bool is_right_child (int value);              //by value

        void update_height_after_insert(Node<int>* node);

        void rebalance_insert(Node<int> *node);

    public:

        /*Constructor*/
        AVL_Tree(): root(NULL), tree_size(0), debug_flag(false) {}

        /*Destructor*/
        ~AVL_Tree()
        {
            clear();
        }


        bool empty() const
        {
            return (tree_size == 0);
        }
        size_t size() const
        {
            return tree_size;
        }

        void insert(int x);

        void print_tree(ostream &out = cout) const;

//        Node* get_root()const{ return root;}
//        void inorder(Node *node_ptr,ostream& out = cout)const;
//        void inorder(ostream& out = cout)const;
//        void preorder(Node *node_ptr,ostream& out = cout)const;
//        void preorder(ostream& out = cout)const;
//        void postorder(Node *node_ptr,ostream& out = cout)const;
//        void postorder(ostream& out = cout)const;
//        void levelorder(Node *node_ptr,ostream& out = cout)const;
//        void levelorder(ostream& out = cout)const;
//        Node* Search(int key);
//        Node* get_parent(Node* node);
//        Node* get_parent(int x);

//        bool is_root(Node* node){ return(this->get_root()==node);}
//        bool is_root(int value)
//        {
//            Node* node;
//            node=Search(value);
//            return(this->get_root()==node);
//        }
//        bool has_two_siblings(Node* node);
//        bool has_two_siblings(int value);
//        bool is_leaf(int value);
//        bool is_leaf(Node* node);
//        bool has_only_one_siblings(int value);
//        bool has_only_one_siblings(Node* node);
//        Node* get_inorder_successor(Node *node);
//        Node* get_inorder_successor(int value);
//        Node* get_inorder_predecessor(Node *node);
//        Node* get_inorder_predecessor(int value);
//        bool delete_node(int value);
//        bool delete_node(Node* node);
//
//        void clear();
//        void clear(Node* node);
};
#endif
