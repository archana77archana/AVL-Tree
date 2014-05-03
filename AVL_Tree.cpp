#include "AVL_Tree.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using std::ostream;
using std::cout;
using std::queue;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::clog;
using std::cerr;

bool AVL_Tree::deletion_flag = false;

void AVL_Tree::insert(int x)
{
    if(tree_size == 0)
    {
        /*Inserting my first node
        Parent of root node = NULL*/

        Node<int>* node=new Node<int>(x);
        root = node;
        ++tree_size;
    }

    else
    {
        /*Tree not empty*/
        Node<int>* node = new Node<int>(x);
        Node<int>* temp = root;

        while(1)
        {
            if(temp->get_data() > x)
            {
                /*Traversing the left sub tree*/
                if(temp->get_left_ptr() == NULL)
                {
                    /*OK. Left sub-tree is empty
                    So we can insert the node*/
                    temp->set_left_ptr(node);
                    node->set_parent(temp);
                    ++tree_size;

                    /*Rebalancing*/
                    update_height_after_insert(node);
                    rebalance_insert(node);

                    break;
                }

                else
                {
                    /*Left subtree not NULL*/
                    temp = temp->get_left_ptr();
                }
            }

            else if(temp->get_data() < x)
            {
                /*Traverse the right subtree*/
                if(temp->get_right_ptr() == NULL)
                {
                    /*Right subtree is empty. Insert node*/
                    temp->set_right_ptr(node);
                    node->set_parent(temp);
                    ++tree_size;

                    /*Rebalancing*/
                    update_height_after_insert(node);
                    rebalance_insert(node);

                    break;
                }

                else
                {
                    /*Right subtree not NULL*/
                    temp = temp->get_right_ptr();
                }
            }

            else
            {
                /*Data is already there*/
                return;
            }
        }

    }

    if(debug_flag)
        print_tree();

    return;
}

void AVL_Tree::update_height_after_insert(Node<int>* node)
{
    if(node == NULL)
        return;

    else if(node == root)
        return;

    else
    {
        Node<int>* temp_node_ptr = node->get_parent();
        size_t temp_height = 0;

        while((temp_node_ptr != NULL) && (temp_node_ptr->get_height() <= temp_height))
        {
            temp_node_ptr->set_height(temp_height + 1);
            temp_height = temp_height + 1;
            temp_node_ptr = temp_node_ptr->get_parent();
        }
    }
}

void AVL_Tree::rebalance_insert(Node<int> *node)
{
    if(debug_flag)
        clog << "Before rebalancing: ", print_tree();

    if(node == NULL)
        return;

    string curr_direction, prev_direction;
    Node<int> *temp_node = node->get_parent();
    int curr_bf = 0;

    if(is_left_child(node))
        curr_direction = ""L"";

    else if(is_right_child(node))
        curr_direction = "R";

    else
        curr_direction = "";

    while(temp_node != NULL)
    {
        curr_bf = balance_factor(temp_node);

        if(debug_flag)
            clog << "BF(" << temp_node->get_data() << "): " << curr_bf << endl;

        if(curr_bf == 0)
        {
            if(debug_flag)
                clog << "Rebalance complete. " << endl;
            break;
        }

        else if((curr_bf <= 1) && (curr_bf >= -1))
        {
            prev_direction = curr_direction;

            if(is_left_child(temp_node))
                curr_direction = "L";

            else if(is_right_child(temp_node))
                curr_direction = "R";

            else if(is_root(temp_node))
            {
                break;
            }

            else
            {
                cout << "Error: Not left, right or parent" << endl;
                assert(0);
            }

            temp_node = temp_node->get_parent();
        }

        else
        {
            if(debug_flag)
                clog << "Balance factor not within limits. " << endl;

            if((curr_direction == "L") && (prev_direction == "R"))
            {
                if(debug_flag)
                {
                    clog << "LR case. " << endl;
                    clog << "Doing left-rotation on " << temp_node->get_left_ptr()->get_data() << endl;
                }

                left_rotation(temp_node->get_left_ptr());

                if(debug_flag)
                    print_tree();

                if(debug_flag)
                    clog << "Doing right rotation on " << temp_node->get_data() << endl;

                right_rotation(temp_node);

                if(debug_flag)
                    print_tree();

                /*Moving up*/
                temp_node = temp_node->get_parent();
            }

            else if((curr_direction == "R") && (prev_direction == "L"))
            {
                if(debug_flag)
                {
                    clog << "RL case" << endl;
                    clog << "Doing right rotation " << temp_node->get_data() << endl;
                }

                right_rotation(temp_node->get_right_ptr());

                if(debug_flag)
                    clog << "Doing a left-rotation on " << temp_node->get_data() << endl;

                left_rotation(temp_node);
                if(debug_flag)
                    print_tree();

                temp_node = temp_node->get_parent();
            }

            else if((curr_direction == "R") && (prev_direction == "R"))
            {
                if(debug_flag)
                {
                    clog << "RR case " << endl;
                    clog <<"Doing left rotation on " << temp_node->get_data() << endl;
                }

                left_rotation(temp_node);
                if(debug_flag)
                    print_tree;

                temp_node = temp_node->get_parent();
            }

            else
            {
                cerr << "None of the cases matched " << endl;
                assert(false);
            }
        }
    }

    return;
}

void AVL_Tree::print_tree(ostream& out) const
{
    if(size() == 0)
        return;

    size_t temp_counter = 0;
    queue<Node<int>*> temp_q;
    vector<Node<int>*> temp_v;
    Node<int>* curr_node_ptr = NULL;
    temp_q.push(root), temp_counter += 1;
    vector<size_t> lr_node_count;
    size_t max_nodes = (size_t)pow(2.0, root->get_height() + 1.0) - 1;

    while(temp_counter <= max_nodes)
    {
        curr_node_ptr = temp_q.front(), temp_q.pop();
        temp_v.push_back(curr_node_ptr);
        ++temp_counter;

        if(curr_node_ptr != NULL)
        {
            if(curr_node_ptr->get_left_ptr() != NULL)
                temp_q.push(curr_node_ptr->get_left_ptr());

            else
                temp_q.push(NULL);
        }

        else
        {
            temp_q.push(NULL), temp_q.push(NULL);
        }
    }

    size_t h = root->get_height();

    vector<size_t> spaces;
    spaces.push_back(0);

    for(size_t i = 0; i <= h; i++)
    {
        spaces.push_back((spaces[i] + 1) * 2);
    }

    reverse(spaces.begin(), spaces.end());

    size_t counter = 0;

    for(size_t i = 0; i <= h; i++)
    {
        lr_node_count.clear();

        for(size_t k = 0; k < pow(2.0, i*1.0); k++)
        {
            if(counter > max_nodes)
                break;

            for(size_t j = 0; j < spaces[i]; j++)
                out << ' ';

            if(temp_v[counter] != NULL)
            {
                out << temp_v[counter]->get_data() << "," << temp_v[counter]->get_height();

                if(temp_v[counter]->get_left_ptr() != NULL)
                    lr_node_count.push_back(1);

                else
                    lr_node_count.push_back(0);

                if(temp_v[counter]->get_right_ptr() != NULL)
                    lr_node_count.push_back(1);

                else
                    lr_node_count.push_back(0);

                ++counter;
            }

            else
            {
                out << setw(3) << ' ';

                lr_node_count.push_back(0);
                lr_node_count.push_back(0);

                ++counter;
            }

            for(size_t j = 0; j < spaces[i] + 1; j++)
                out << ' ';
        }

        out << endl;

        if(counter > max_nodes)
            break;

        size_t count_1 = spaces[i], count_2 = 0, count_3 = 1;

        for(size_t j = 0; j < spaces[i]/2; j++)
        {
            for(size_t k = 0; k < pow(2.0, i * 1.0); k++)
            {
                for(size_t l = 0; l < count_1 - count_3; l++)
                    out << ' ';

                out << ((lr_node_count[k * 2] == 1) ? "/" : " ");

                for(size_t l = 0; l < (3 + count_2); l++)
                    out << ' ';

                out << ((lr_node_count[(k*2) + 1] == 1) ? "\\" : " ");

                for(size_t l = 0; l < count_1 - count_3; l++)
                        out << ' ';

                out << " ";
            }

            out << endl;
            count_2 += 2;
            count_3++;
        }
    }

    out << endl;
    return;
}

//	if(this->size()==0)
//	{
//		root=node;
//		root->set_left_ptr(NULL);
//		root->set_right_ptr(NULL);
//		Tree_size++;
//	}
//	else
//	{
//		Tree_size++;
//		int flag=0;
//		Node* prev=NULL;
//		Node* next=root;
//		while(next!=NULL)
//		{
//			prev=next;
//			if(x<next->get_data()){next=next->get_left();}
//			else if(x>next->get_data()){next=next->get_right();}
//			else{ flag=1;break;	}
//		}
//		if(flag==0)
//		{
//			if(x<prev->get_data())	prev->set_left_ptr(node);
//			else prev->set_right_ptr(node);
//		}
//	}
//}

//void Tree_Int::inorder(Node *node_ptr,ostream& out)const
//{
//	if(node_ptr==NULL) return;
//	inorder(node_ptr->get_left());
//	out<<node_ptr->get_data();
//	inorder(node_ptr->get_right());
//}
//void Tree_Int::inorder(ostream& out)const
//{
//	this->inorder(this->get_root());
//	out<<"\n";
//}
//void Tree_Int::preorder(Node *node_ptr,ostream& out)const
//{
//	if(node_ptr==NULL) return;
//	out<<node_ptr->get_data();
//	preorder(node_ptr->get_left());
//	preorder(node_ptr->get_right());
//}
//void Tree_Int::preorder(ostream& out)const
//{
//	this->preorder(this->get_root());
//	out<<"\n";
//}
//void Tree_Int::postorder(Node *node_ptr,ostream& out)const
//{
//	if(node_ptr==NULL) return;
//	postorder(node_ptr->get_left());
//	postorder(node_ptr->get_right());
//	out<<node_ptr->get_data();
//}
//void Tree_Int::postorder(ostream& out)const
//{
//	this->postorder(this->get_root());
//	out<<"\n";
//}
//void Tree_Int::levelorder(ostream& out)const
//{
//	this->levelorder(this->get_root());
//	out<<"\n";
//}
//void Tree_Int::levelorder(Node* node_ptr,ostream& out)const
//{
//	queue<Node*> q;
//	q.push(node_ptr);
//	while(!q.empty())
//	{
//		Node* temp=q.front();
//		if(temp->get_left()!=NULL)
//			q.push(temp->get_left());
//		if(temp->get_right()!=NULL)
//			q.push(temp->get_right());
//		cout<<temp->get_data();
//		q.pop();
//	}
//}
//Node* Tree_Int::Search(int key)
//{
//	Node* temp=this->get_root();
//	while(temp!=NULL)
//	{
//		if(key<temp->get_data())
//			temp=temp->get_left();
//		else if(key>temp->get_data())
//			temp=temp->get_right();
//		else return temp;
//	}
//	return NULL;
//}
//Node* Tree_Int::get_parent(Node* node)
//{
//	Node* prev=NULL;
//	Node* next=this->get_root();
//	while(next!=node)
//	{
//		prev=next;
//		if(node->get_data()<next->get_data())
//			next=next->get_left();
//		else
//			next=next->get_right();
//	}
//	return prev;
//}
//Node* Tree_Int::get_parent(int x)
//{
//	Node* temp=this->Search(x);
//	if(temp==NULL)
//		return NULL;
//	else
//		temp=this->get_parent(temp);
//	return temp;
//}
bool AVL_Tree::is_left_child (Node<int>* node)
{
	if(node == NULL)
        return false;

    if(is_root(node))
    {
        return false;
    }

    else
    {
        return (get_parent(node)->get_left_ptr() == node;)
    }
}

bool AVL_Tree::is_left_child(int value)
{
	Node<int>* node = search(value);
	return is_left_child(node);
}

bool Tree_Int::is_right_child (Node* node)
{
    if(node == NULL)
            return false;

        if(is_root(node))
        {
            return false;
        }

        else
        {
            return (get_parent(node)->get_right_ptr() == node;)
        }
}
bool Tree_Int::is_right_child (int value)
{
    Node<int>* node = search(value);
	return is_right_child(node);
}
//bool Tree_Int::has_two_siblings(Node* node)
//{
//	return(node->get_left()!=NULL&&node->get_right()!=NULL);
//}
//bool Tree_Int::has_two_siblings(int value)
//{
//	Node* node;
//	node=Search(value);
//	return(node->get_left()!=NULL&&node->get_right()!=NULL);
//}
//bool Tree_Int::has_only_one_siblings(Node* node)
//{
//	int flag=0;
//	if (node->get_left() != NULL)
//	{
//		flag++;
//	}
//	if (node->get_right() != NULL)
//	{
//		flag++;
//	}
//	return (flag==1);
//}
//bool Tree_Int::has_only_one_siblings(int value)
//{
//	Node* node;
//	node=Search(value);
//	int flag=0;
//	if (node->get_left() != NULL)
//	{
//		flag++;
//	}
//	if (node->get_right() != NULL)
//	{
//		flag++;
//	}
//	return (flag==1);
//}
//bool Tree_Int::is_leaf(Node* node)
//{
//	return(node->get_left()==NULL&&node->get_right()==NULL);
//}
//bool Tree_Int::is_leaf(int value)
//{
//	Node* node;
//	node=Search(value);
//	return(node->get_left()==NULL&&node->get_right()==NULL);
//}
//Node* Tree_Int::get_inorder_successor(Node *node)
//{
//	if(node==NULL)
//		return NULL;
//	else
//	{
//		if(node->get_right()!=NULL)
//		{
//			Node* curr_node=node->get_right();
//			while(curr_node->get_left()!=NULL)
//			{
//				curr_node=curr_node->get_left();
//			}
//			return curr_node;
//		}
//		else
//		{
//			Node* save_node=NULL;
//			Node* curr_node=this->get_root();
//			while(curr_node!=NULL)
//			{
//				if(node->get_data()<curr_node->get_data())
//				{
//					save_node=curr_node;
//					curr_node=curr_node->get_left();
//				}
//				else if(node->get_data()>curr_node->get_data())
//				{
//					curr_node=curr_node->get_left();
//				}
//				else
//					break;
//			}
//			return save_node;
//		}
//	}
//}
//Node* Tree_Int::get_inorder_successor(int value)
//{
//	Node* temp=Search(value);
//	return (this->get_inorder_successor(temp));
//}
//Node* Tree_Int::get_inorder_predecessor(Node *node)
//{
//	if(node==NULL)
//		return NULL;
//	else
//	{
//		if(node->get_left()!=NULL)
//		{
//			Node* curr_node=node->get_left();
//			while(curr_node->get_right()!=NULL)
//			{
//				curr_node=curr_node->get_right();
//			}
//			return curr_node;
//		}
//		else
//		{
//			Node* save_node=NULL;
//			Node* curr_node=this->get_root();
//			while(curr_node!=NULL)
//			{
//				if(node->get_data()<curr_node->get_data())
//				{
//					curr_node=curr_node->get_left();
//				}
//				else if(node->get_data()>curr_node->get_data())
//				{
//					save_node=curr_node;
//					curr_node=curr_node->get_left();
//				}
//				else
//					break;
//			}
//			return save_node;
//		}
//	}
//}
//Node* Tree_Int::get_inorder_predecessor(int value)
//{
//	Node* temp=Search(value);
//	return (this->get_inorder_predecessor(temp));
//}
//bool Tree_Int::delete_node(int value)
//{
//	Node* node;
//	node=Search(value);
//	return (this->delete_node(node));
//}
//bool Tree_Int::delete_node(Node* node)
//{
//	if(node==NULL)
//		return false;
//	else
//	{
//		// if the node is a leaf node
//		if(this->is_leaf(node))
//		{
//			if(node==this->get_root())
//				root=NULL;
//			else if(this->is_left_child(node))
//			{
//				Node* parent;
//				parent=this->get_parent(node);
//				parent->set_left_ptr(node->get_left());
//			}
//			else
//			{
//				Node* parent;
//				parent=this->get_parent(node);
//				parent->set_right_ptr(node->get_right());
//			}
//			delete node;
//			Tree_size--;
//			return true;
//		}
//
//		// if the node has only one siblings
//
//		else if(this->has_only_one_siblings(node))
//		{
//			if(node->get_left()!=NULL)
//			{
//				if (this->is_left_child(node))
//				{
//					Node* parent;
//					parent=this->get_parent(node);
//					parent->set_left_ptr(node->get_left());
//				}
//				else if (this->is_right_child(node))
//				{
//					Node* parent;
//					parent=this->get_parent(node);
//					parent->set_right_ptr(node->get_right());
//				}
//				else
//					root = node->get_left();
//				delete node;
//				Tree_size--;
//				return true;
//			}
//			else
//			{
//				if(this->is_left_child(node))
//				{
//					Node* parent;
//					parent=this->get_parent(node);
//					parent->set_left_ptr(node->get_left());
//				}
//				else if(this->is_right_child(node))
//				{
//					Node* parent;
//					parent=this->get_parent(node);
//					parent->set_right_ptr(node->get_right());
//				}
//				else
//					root=node->get_right();
//				delete node;
//				Tree_size--;
//				return true;
//			}
//		}
//
//		// if the node is has two child nodes
//
//		else
//		{
//			Node* inorder_pre_or_succ =NULL;
//			if(this->Deletion_flag==0)
//			{
//				this->Deletion_flag=1;
//			    inorder_pre_or_succ=this->get_inorder_predecessor(node);
//			}
//			else if(this->Deletion_flag==1)
//			{
//				this->Deletion_flag=0;
//				inorder_pre_or_succ=this->get_inorder_successor(node);
//			}
//			int temp= inorder_pre_or_succ->get_data();
//			this->delete_node(inorder_pre_or_succ);
//			node->set_data(temp);
//			return true;
//		}
//	}
//}
//void Tree_Int::clear()
//{
//	while (this->size()!=0)
//		this->clear(this->get_root());
//}
//void Tree_Int::clear(Node* node)
//{
//	assert(node != NULL);
//	this->delete_node(node);
//
//}













