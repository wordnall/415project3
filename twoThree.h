//
// Created by student on 4/11/19.
//

#ifndef UNTITLED1_TWOTHREE_H
#define UNTITLED1_TWOTHREE_H
// 2-3 tree node implementation

class TTNode<Key extends Comparable<? super Key>,E> {
private E lval;        // The left record
private Key lkey;        // The node's left key
private E rval;        // The right record
private Key rkey;        // The node's right key
private TTNode<Key,E> left;   // Pointer to left child
private TTNode<Key,E> center; // Pointer to middle child
private TTNode<Key,E> right;  // Pointer to right child

public TTNode() { center = left = right = null; }
public TTNode(Key lk, E lv, Key rk, E rv,
        TTNode<Key,E> p1, TTNode<Key,E> p2,
        TTNode<Key,E> p3) {
lkey = lk; rkey = rk;
lval = lv; rval = rv;
left = p1; center = p2; right = p3;
}

private E findhelp(TTNode<Key,E> root, Key k);
private TTNode<Key,E> inserthelp(TTNode<Key,E> rt, Key k, E e);
public TTNode<Key,E> add(TTNode<Key,E> it);

public boolean isLeaf() { return left == null; }
public TTNode<Key,E> lchild() { return left; }
public TTNode<Key,E> rchild() { return right; }
public TTNode<Key,E> cchild() { return center; }
public Key lkey() { return lkey; }  // Left key
public E lval() { return lval; }  // Left value
public Key rkey() { return rkey; }  // Right key
public E rval() { return rval; }  // Right value
public void setLeft(Key k, E e) { lkey = k; lval = e; }
public void setRight(Key k, E e) { rkey = k; rval = e; }
public void setLeftChild(TTNode<Key,E> it) { left = it; }
public void setCenterChild(TTNode<Key,E> it)
{ center = it; }
public void setRightChild(TTNode<Key,E> it)
{ right = it; }


}

#endif //UNTITLED1_TWOTHREE_H
