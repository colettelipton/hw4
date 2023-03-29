#ifndef AVLBST_H
#define AVLBST_H

//#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
	return;
}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key, Value>* a);
    void rotateLeft(AVLNode<Key, Value>* a);
    void help(const std::pair<const Key, Value> &keyValuePair, AVLNode<Key, Value>* prev, AVLNode<Key, Value>* root, int lr);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
		void removeFix(AVLNode<Key, Value>* n, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{

	// if the tree is empty
    if(this->root_ == nullptr){
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        ((AVLNode<Key, Value>*)this->root_)->setBalance(0);
    }

    else{
        help(new_item, nullptr, (AVLNode<Key, Value>*)this->root_, -1);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::help(const std::pair<const Key, Value> &keyValuePair, AVLNode<Key, Value>* prev, AVLNode<Key, Value>* root, int lr){

	// add the node
	while(root != nullptr){
        // if the keys are equal, replaces the value
        if(keyValuePair.first == root->getKey()){
            root->setValue(keyValuePair.second);
            return;
        }

        // left if val is less than node (0 = left)
        else if(keyValuePair.first < root->getKey()){
            prev = root;
            root = root->getLeft();
            lr = 0;
        }

        // right if val is greater than node (1 = right)
        else {
            prev = root;
            root = root->getRight();
						lr = 1;
        }
    }

    // if the BST is not empty
    root = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, prev);
		root->setBalance(0);

		int prevBal = 0;
    if(lr == 0){
        prev->setLeft(root);
				prevBal = prev->getBalance();
    } 
    else if(lr == 1){
        prev->setRight(root);
				prevBal = prev->getBalance();
    } 

		// KEEP TRACING HERE
    if(prevBal == -1 || prevBal == 1){
        root->getParent()->setBalance(0);
        return;
    }
    else {
          if(root->getParent()->getRight() == root){
              root->getParent()->updateBalance(1);
          }
          else{
              root->getParent()->updateBalance(-1);
          }
          insertFix(root->getParent(), root);
        }
	}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* a){
    // get all nodes
    AVLNode<Key, Value>* b = a->getRight();
		AVLNode<Key, Value>* x = b->getLeft();
		AVLNode<Key, Value>* p = a->getParent();

		// rotate
		if(a == (AVLNode<Key, Value>*)this->root_) this->root_ = b;
    if(a->getParent() == nullptr){
        b->setParent(nullptr);
    }
		else if(a->getParent()->getRight() == a){
				p->setRight(b);
        b->setParent(p);
		}
		else{
			p->setLeft(b);
      b->setParent(p);
		}
		b->setLeft(a);
		a->setParent(b);
		if(a != nullptr) a->setRight(x);
		if(a != nullptr && x != nullptr) x->setParent(a);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* a){
    // get all nodes
    AVLNode<Key, Value>* b = a->getLeft();
		AVLNode<Key, Value>* y = b->getRight();
		AVLNode<Key, Value>* p = a->getParent();

		// rotate
		if(a == (AVLNode<Key, Value>*)this->root_) this->root_ = b;
		if(p == nullptr){
      b->setParent(nullptr);
    }
		else if(p->getRight() == a){
			p->setRight(b);
      b->setParent(p);
		}
		else{
			p->setLeft(b);
      b->setParent(p);
		}
		b->setRight(a);
		a->setParent(b);
		a->setLeft(y);
		if(a != nullptr && y != nullptr) y->setParent(a);
		//this->root_ = b;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n){
	
    // returns is parent or grandparent are null
    if(p == nullptr || p->getParent() == nullptr){
        return;
    }

    AVLNode<Key, Value> * g = p->getParent();

    // if p is left child of g
    if(g->getLeft() == p){
        // updates g's balance
        g->updateBalance(-1);

        if(g->getBalance() == 0){
          return;
        }

        else if(g->getBalance() == -1){
          insertFix(g, p);
        }

        else if(g->getBalance() == -2){
            // if zig zig then rotateRight
            if(p->getBalance() == -1){
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }

            // if zig zag then rotate left
            else if(p->getBalance() == 1){
                rotateLeft(p);
                rotateRight(g);
                if(n->getBalance() == -1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
            
        }
    }
    // if p is right child of g
    else if(g->getRight() == p){
        // updates g's balance
        g->updateBalance(1);

        if(g->getBalance() == 0){
            return;
        }

        else if(g->getBalance() == 1){
          insertFix(g, p);
        }

        else if(g->getBalance() == 2){
            // if zig zig then rotate Left
            if(p->getBalance() == 1){
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }

            // if zig zag then rotate right
            else if(p->getBalance() == -1){
                rotateRight(p);
                rotateLeft(g);
                if(n->getBalance() == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
	// finds the node to be removed
	AVLNode<Key, Value>* cur = (AVLNode<Key, Value>*)(BinarySearchTree<Key, Value>::internalFind(key));
	
	
	// if that node isn't found, returns
	if(cur == nullptr){
		return;
	}

	// if cur is the only node
		if(cur == this->root_ && cur->getLeft() == nullptr && cur->getRight() == nullptr){
			this->root_ = nullptr;
			delete cur;
			return;
		}

		// if n has 2 children
		if(cur->getLeft() != nullptr && cur->getRight() != nullptr){
			AVLNode<Key, Value>* pred = (AVLNode<Key, Value>*)(BinarySearchTree<Key, Value>::predecessor(cur));
			nodeSwap(pred, cur);
		}

			int diff = 0;
			AVLNode<Key, Value>* p = cur->getParent();
			if(p != nullptr){
				if(cur == p->getLeft()){
					diff += 1;
				}
				else if(cur == p->getRight()){
					diff -= 1;
				}
			}

			// if current has no children, remove
			if(cur->getLeft() == nullptr && cur->getRight() == nullptr){
				if(diff == 1){
					p->setLeft(nullptr);
					delete cur;
				}
				else if(diff == -1){
					p->setRight(nullptr);
					delete cur;
				}
				else{
					delete cur;
					this->root_ = nullptr;
				}
			}

			// if current has exactly one child, promote and remove

			// if has a left child
			else if(cur->getLeft() != nullptr){
				AVLNode<Key, Value>* child = cur->getLeft();

				// if cur is a left child
				if(p != nullptr && diff == 1){
					child->setParent(p);
					p->setLeft(child);
					delete cur;
				}

				// if cur is a right child
				else if(p != nullptr && diff == -1){
					child->setParent(p);
					p->setRight(child);
					delete cur;
				}

				// if cur is the root
				else if(p == nullptr){
					child->setParent(nullptr);
					this->root_ = child;
					delete cur;
				}
			}

			// if has a right child
			else if(cur->getRight() != nullptr){
				AVLNode<Key, Value>* child = cur->getRight();

				// if cur is a left child
				if(p != nullptr && diff == 1){
					child->setParent(p);
					p->setLeft(child);
					delete cur;
				}

				// if cur is a right child
				else if(p != nullptr && diff == -1){
					child->setParent(p);
					p->setRight(child);
					delete cur;
				}

				// if cur is the root
				else if(p == nullptr){
					child->setParent(nullptr);
					this->root_ = child;
					delete cur;
				}
			}

			//delete cur;
			removeFix(p, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff){
	if(n == nullptr){
		return;
	}

	AVLNode<Key, Value>* p = n->getParent();
	int nextdiff = 0;

	if(p != nullptr){
		// if n is a left child
		if(p->getLeft() == n){
			nextdiff = 1;
		}

		// if n is a right child
		if(p->getRight() == n){
			nextdiff = -1;
		}
	}

	// if n is a right child
	if(diff == -1){
		// case 1
		if((n->getBalance() + diff) == -2){
			AVLNode<Key, Value>* c = n->getLeft();

			// COMMENTTHIS OUT?
			if(c == nullptr){
				n->setBalance(0);
				return;
			}

			// zig zig
			if(c->getBalance() == -1){
				rotateRight(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, nextdiff);
				return;
			}
			else if(c->getBalance() == 0){
				rotateRight(n);
				n->setBalance(-1);
				c->setBalance(1);
				return;
			}
			else if(c->getBalance() == 1){
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c);
				rotateRight(n);
				if(g->getBalance() == 1){
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if(g->getBalance() == -1){
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, nextdiff);
			}
		}
		else if(n->getBalance() + diff == -1){
				n->setBalance(-1);
				return;
		}
		else if(n->getBalance() + diff == 0){
			n->setBalance(0);
			removeFix(p, nextdiff);
		}
	}

	// if n is a left child
	else if(diff == 1){
		if(n->getBalance() + diff == 2){
		// case 1
			AVLNode<Key, Value>* c = n->getRight();
			// COMMENTTHIS OUT?
			if(c == nullptr){
				n->setBalance(0);
				return;
			}

			// zig zig
			if(c->getBalance() == 1){
				rotateLeft(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, nextdiff);
				return;
			}
			else if(c->getBalance() == 0){
				rotateLeft(n);
				n->setBalance(1);
				c->setBalance(-1);
				return;
			}
			else if(c->getBalance() == -1){
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(c);
				rotateLeft(n);
				if(g->getBalance() == -1){
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if(g->getBalance() == 1){
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, nextdiff);
			}
		}
		else if(n->getBalance() + diff == 1){
				n->setBalance(1);
				return;
		}
		else if(n->getBalance() + diff == 0){
			n->setBalance(0);
			removeFix(p, nextdiff);
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
