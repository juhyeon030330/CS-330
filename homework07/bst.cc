#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
    key = 0;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Constructor
Node::Node(int in) {
// TODO: Implement this
    key = in;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Destructor
Node::~Node() {
// TODO: Implement this
    delete left;
    delete right;
}

// Add parent 
void Node::add_parent(Node* in) {
// TODO: Implement this
    parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
    left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
    right = in;
}

// Get key
int Node::get_key()
{
// TODO: Implement this
    return key;
}
// Get parent node
Node* Node::get_parent()
{
// TODO: Implement this
    return parent;
}
// Get left node
Node* Node::get_left()
{
// TODO: Implement this
    return left;
}
// Get right node
Node* Node::get_right()
{
// TODO: Implement this
    return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
    if(in != nullptr) {
        inorder_walk(in->get_left(), to);
        in->print_info(to);
        inorder_walk(in->get_right(), to);
    }
    
}
// Constructor
BST::BST()
{
// TODO: Implement this
    root = nullptr;
}
// Destructor
BST::~BST()
{
// TODO: Implement this
    delete root;
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
// TODO: Implement this
    Node* y = nullptr;
    Node* x = root;
    while(x != nullptr) {
        y = x;
        if(in->get_key() < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }

    in->add_parent(y);
    if(y == nullptr) {
        root = in;
    } else if(in->get_key() < y->get_key()) {
        y->add_left(in);
    } else {
        y->add_right(in);
    }
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
    Node* y;
    if (out->get_left() == nullptr || out->get_right() == nullptr) {
        y = out;
    } else {
        y = get_succ(out);
    }

    Node* x;
    if (y->get_left() != nullptr) {
        x = y->get_left();
    } else {
        x = y->get_right();
    }

    if (x != nullptr) {
        x->add_parent(y->get_parent());
    }

    if (y->get_parent() == nullptr) {
        root = x;
    } else if (y == y->get_parent()->get_left()) {
        y->get_parent()->add_left(x);
    } else {
        y->get_parent()->add_right(x);
    }

    if (y != out) {

        Node* out_parent = out->get_parent();
        if (out_parent == nullptr) {
            root = y;
        } else if (out == out_parent->get_left()) {
            out_parent->add_left(y);
        } else {
            out_parent->add_right(y);
        }
        y->add_parent(out_parent);

        y->add_left(out->get_left());
        if (out->get_left() != nullptr) {
            out->get_left()->add_parent(y);
        }

        y->add_right(out->get_right());
        if (out->get_right() != nullptr) {
            out->get_right()->add_parent(y);
        }

    }

    // Clean up y to avoid destructor deleting parts of the tree
    out->add_parent(nullptr);
    out->add_left(nullptr);
    out->add_right(nullptr);
    delete out;
}


// minimum key in the BST
Node* BST::tree_min()
{
// TODO: Implement this
    if(root == nullptr) {
        return nullptr;
    } else {
        return get_min(root);
    }
}
// maximum key in the BST
Node* BST::tree_max()
{
// TODO: Implement this
    if(root == nullptr) {
        return nullptr;
    } else {
        return get_max(root);
    }
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
// TODO: Implement this
    while(in->get_left() != nullptr) {
        in = in->get_left();
    }
    return in;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO: Implement this
    while(in->get_right() != nullptr) {
        in = in->get_right();
    }
    return in;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
// TODO: Implement this
    if(in->get_right() != nullptr) {
        return get_min(in->get_right());
    }

    Node* y = in->get_parent();
    while((y != nullptr) && (in == y->get_right())) {
        in = y;
        y = y->get_parent();
    }
    return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
// TODO: Implement this
    if(in->get_left() != nullptr) {
        return get_max(in->get_left());
    }

    Node* y = in->get_parent();
    while((y != nullptr) && (in == y->get_left())) {
        in = y;
        y = y->get_parent();
    }
    return y;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
// TODO: Implement this
    inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
// TODO: Implement this
    Node* x = root;
    while((x != nullptr) && (search_key != x->get_key())) {
        if(search_key < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    return x;
}
// ---------------------------------------
