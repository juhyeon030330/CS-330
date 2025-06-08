#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */



    RBTNode* lChild = (RBTNode*) y->get_left();
    RBTNode* grChild = (RBTNode*) lChild->get_right();
    RBTNode* parent = (RBTNode*) y->get_parent();

    y->add_left(grChild);
    if(grChild != sentinel) {
        grChild->add_parent(y);
    }

    lChild->add_parent(parent);
    if(parent == sentinel) {
        root = lChild;
    } else if(y == (RBTNode*)parent->get_right()) {
        parent->add_right(lChild);
    } else {
        parent->add_left(lChild);
    }

    lChild->add_right(y);
    y->add_parent(lChild);


}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* TODO */


    RBTNode* rChild = (RBTNode*) x->get_right();
    RBTNode* glChild = (RBTNode*) rChild->get_left();
    RBTNode* parent = (RBTNode*) x->get_parent();

    x->add_right(glChild);
    if(glChild != sentinel) {
        glChild->add_parent(x);
    }

    rChild->add_parent(parent);
    if(parent == sentinel) {
        root = rChild;
    } else if(x == (RBTNode*)parent->get_left()) {
        parent->add_left(rChild);
    } else {
        parent->add_right(rChild);
    }

    rChild->add_left(x);
    x->add_parent(rChild);

}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */

    // problem occurs when we insert into red
    while (in != (RBTNode*)root && ((RBTNode*)in->get_parent())->get_color() == RED) {
        RBTNode* parent = (RBTNode*)in->get_parent();
        RBTNode* grandparent = (RBTNode*)parent->get_parent();


        if (parent == (RBTNode*)grandparent->get_left()) {
            RBTNode* uncle = (RBTNode*)grandparent->get_right();

            // when uncle is red
            if (uncle->get_color() == RED) {
                parent->add_color(BLACK);
                uncle->add_color(BLACK);
                grandparent->add_color(RED);
                in = grandparent;
            }
            else {
                // when uncle is black and in is right child
                if (in == (RBTNode*)parent->get_right()) {
                    in = parent;
                    left_rotate(in);
                    parent = (RBTNode*)in->get_parent();
                    grandparent = (RBTNode*)parent->get_parent();
                }
                // when uncle is black and in is left child
                parent->add_color(BLACK);
                grandparent->add_color(RED);
                right_rotate(grandparent);
            }
        }
        
        // the other side
        else {
            RBTNode* uncle = (RBTNode*)grandparent->get_left();
            
            if (uncle->get_color() == RED) {
                parent->add_color(BLACK);
                uncle->add_color(BLACK);
                grandparent->add_color(RED);
                in = grandparent;
            }
            else {  

                if (in == (RBTNode*)parent->get_left()) {
                    in = parent;
                    right_rotate(in);
                    parent = (RBTNode*)in->get_parent();
                    grandparent = (RBTNode*)parent->get_parent();
                }
                
                parent->add_color(BLACK);
                grandparent->add_color(RED);
                left_rotate(grandparent);
            }
        }
    }


    ((RBTNode*)root)->add_color(BLACK);

}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */

    BST::insert_node(in, sentinel);

    in->add_left(sentinel);
    in->add_right(sentinel);
    in->add_color(RED);
    if(in->get_parent() == nullptr) {
        in->add_parent(sentinel);
    }

    rb_insert_fixup(in);

}

void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */

    RBTNode* w;

    while ((in != (RBTNode*)root) && (in->get_color() == BLACK)) {
        if (in == (RBTNode*) in->get_parent()->get_left()) {
            
            w = (RBTNode*) in->get_parent()->get_right(); // sibling

            // Case 1
            if (w->get_color() == RED) {
                w->add_color(BLACK);
                ((RBTNode*)in->get_parent())->add_color(RED);
                left_rotate((RBTNode*)in->get_parent());
                w = (RBTNode*) in->get_parent()->get_right();
            }

            // Case 2
            if (((RBTNode*)w->get_left())->get_color() == BLACK &&
                ((RBTNode*)w->get_right())->get_color() == BLACK) 
            {
                w->add_color(RED);
                in = (RBTNode*) in->get_parent();
                
            } else {

                // Case 3
                if (((RBTNode*)w->get_right())->get_color() == BLACK) {
                    ((RBTNode*)w->get_left())->add_color(BLACK);
                    w->add_color(RED);
                    right_rotate(w);
                    w = (RBTNode*) in->get_parent()->get_right();
                
                }

                // Case 4
                w->add_color(((RBTNode*)in->get_parent())->get_color());
                ((RBTNode*)in->get_parent())->add_color(BLACK);
                ((RBTNode*)w->get_right())->add_color(BLACK);
                left_rotate((RBTNode*)in->get_parent());
                in = (RBTNode*) root; 

            }
        }
        else {
            
            w = (RBTNode*) in->get_parent()->get_left();

            // Case 1 
            if (w->get_color() == RED) {
                w->add_color(BLACK);
                ((RBTNode*)in->get_parent())->add_color(RED);
                right_rotate((RBTNode*)in->get_parent());
                w = (RBTNode*) in->get_parent()->get_left();
            }

            // Case 2 
            if (((RBTNode*)w->get_left())->get_color() == BLACK &&
                ((RBTNode*)w->get_right())->get_color() == BLACK) 
            {
                w->add_color(RED);
                in = (RBTNode*) in->get_parent();
            
            } else {

                // Case 3
                if (((RBTNode*)w->get_left())->get_color() == BLACK) {
                    ((RBTNode*)w->get_right())->add_color(BLACK);
                    w->add_color(RED);
                    left_rotate(w);
                    w = (RBTNode*) in->get_parent()->get_left();
            
                }

                // Case 4 
                w->add_color(((RBTNode*)in->get_parent())->get_color());
                ((RBTNode*)in->get_parent())->add_color(BLACK);
                ((RBTNode*)w->get_left())->add_color(BLACK);
                right_rotate((RBTNode*)in->get_parent());
                in = (RBTNode*) root;

            }
        }
    }

    in->add_color(BLACK); 




}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */

    RBTNode* current;
    if( ((RBTNode*)out->get_left() == sentinel) || ((RBTNode*)out->get_right() == sentinel) ) {
        current = out;
    } else {
        current = get_succ(out);
    }

    Node_color original = current->get_color();

    RBTNode* child;
    RBTNode* parent = (RBTNode*) current->get_parent();
    if((RBTNode*)current->get_left() != sentinel) {
        child = (RBTNode*) current->get_left();
    } else {
        child = (RBTNode*) current->get_right();
    }

    child->add_parent(parent);
    if(parent == sentinel) {
        root = child;
    } else if(current == (RBTNode*) parent->get_left()) {
        parent->add_left(child);
    } else {
        parent->add_right(child);
    }

    if(current != out) {
        current->add_parent((RBTNode*)out->get_parent());
        if((RBTNode*)current->get_parent() == sentinel) {
            root = current;
        } else {
            if(out == (RBTNode*)out->get_parent()->get_left()) {
                current->get_parent()->add_left(current);
            } else {
                current->get_parent()->add_right(current);
            }
        }

        current->add_left((RBTNode*) out->get_left());
        current->add_right((RBTNode*) out->get_right());
        current->get_left()->add_parent(current);
        current->get_right()->add_parent(current);

        current->add_color(out->get_color());
    }

    delete out;

    if(original == BLACK) {
        rb_delete_fixup(child);
    }



}

// ---------------------------------------
