//
// Created by student on 4/11/19.
//


#ifndef TWOTHREE_H
#define TWOTHREE_H
// 2-3 tree node implementation

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TTT {
	public:
		TTT();
		/*TTNode() { center = left = right = null; }
		TTNode(Key lk, E lv, Key rk, E rv, TTNode<Key, E> p1, TTNode<Key, E> p2, TTNode<Key, E> p3) {
			lkey = lk; rkey = rk;
			lval = lv; rval = rv;
			left = p1; center = p2; right = p3;
		}
		
	
		node* lchild() { return left; }
		node rchild() { return right; }
		node cchild() { return center; }
		string lkey() { return lkey; }  // Left key
		int lval() { return lval; }  // Left value
		string rkey() { return rkey; }  // Right key
		int rval() { return rval; }  // Right value
		*/


		void contains() const;
		bool isEmpty();
		void printTree(ostream& out = cout) const;
		void buildTree(ifstream & input, bool output);
		void searchAllTree(ifstream& input);

	private:
		struct node {
			node() {
				center = NULL;
				left = NULL;
				right = NULL;
			}
			node(const string& lk, const string& rk, node* l, node* c, node* r)
				: lkey(lk), rkey(rk), left(l), center(c), right(r) {
				llines.resize(0);
				rlines.resize(0);
			}
			string lkey;  // The node's left key
			string rkey; // The node's right key
			//dont use lval and rval because we're storing the line numbers int the vectors llines and rlines.
			//int lval;  // The left record
			//int rval;  // The right record
			node* left; // Pointer to left child
			node* center; // Pointer to middle child
			node* right; // Pointer to right child
			vector<int> llines; //lines that the left key is found on
			vector<int> rlines; //lines that the right key is found on

			void setLeft(string k) { lkey = k; }
			void setRight(string k) { rkey = k; }
			void setLeftChild(node* it) { left = it; }
			void setCenterChild(node* it)
			{
				center = it;
			}
			void setRightChild(node* it)
			{
				right = it;
			}
			bool isLeaf() { return left == NULL; }
			node* add(node* it) {
				if (rkey == "") { // Only one key, add here
					if (lkey.compare(it->lkey) < 0) {
						rkey = it->lkey; rlines = it->llines;
						center = it->left;
						right = it->center; 
					}
					else {
						rkey = lkey; rlines = llines; right = center;
						lkey = it->lkey; llines = it->llines;
						center = it->center; left = it->left;
					}
				
					return this;
				}//review here
				else if (lkey.compare(it->lkey) >= 0) { // Add left
					node* N1 = new node(lkey, "", it, this, NULL);
					N1->llines = llines;
					left = center; center = right; right = NULL;
					lkey = rkey; llines = rlines; rkey = ""; rlines.resize(0);
					return N1;
				}
				else if (rkey.compare(it->lkey) >= 0) { // Add center
					node* temp = new node(rkey, "", it->center, right, NULL);
					temp->llines = rlines;
					it->setCenterChild(temp);
					rkey = ""; rlines.resize(0); right = NULL; center = it->left;
					it->setLeftChild(this);
					return it;
				}
				else { // Add right
					node* N1 = new node(rkey, "", this, it, NULL);
					N1->llines = rlines;
					right = NULL; rkey = ""; rlines.resize(0);
					return N1;
				}
			}
		};

		node* root;
		bool findhelp(node* root, const string& k, vector<int>& lines) const;
		node* inserthelp(node *& rt, const string& k, int line, int& distWords);
		void printTreeHelper(node* t, ostream& out) const;
		int findHeight(node* t);
};

#endif //TWOTHREE_H

