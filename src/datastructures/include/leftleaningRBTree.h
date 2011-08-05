#include "assert.h"
#include <functional>
namespace datastructures {

template<typename T>
struct default_compare {
  int operator()(T a, T b) const{
    if(a > b) return 1;
    else if (a == b) return 0;
    else return -1;
  }
};
    
  template <typename T_Key, typename T_Value, typename Compare_fn = default_compare<T_Key> >  
    class LLRBTree   {
  public:
  struct Node {
    T_Key key;
    T_Value value;
    bool color;
    Node *left, *right;
    Node(T_Key k, T_Value v) {
      key = k;
      value = v;
      color = RED;
      left = right = NULL;
    };

    inline bool is_red() {return color;};
    inline void color_as_black() { color = !RED;};
    inline void color_as_red() { color = RED;};
    inline void split_if_4node() { 
      if(isRed(this->left) && isRed(this->right)) {
	this->color_as_red();
	this->left->color_as_black();
	this->right->color_as_black();
	}
    };
    inline bool has_red_leaning_right() { 
      return  !isRed(this->left) && isRed(this->right);
    };
    
  };

  typedef Node* Link;
  
  LLRBTree() { root = NULL;};
  ~LLRBTree() {
    //ToDo: post order traverse and delete nodes
  };

  void insert(T_Key key, T_Value value){
    rb_insert(root, key, value);
    root->color_as_black();
  };

  T_Value* find(T_Key key)  const{
    Link head = root;
    while(head != NULL) {
      int cmp = compare_fn(key, head->key); 
      if(cmp == 0) return &head->value;
      else if(cmp < 0) head = head->left;
      else head = head->right;
    }
    return NULL;
  };

  
  int assert_LLRBInvariants() { 

    return assertBlackHeight(root);
  }

  int static assertBlackHeight(Link h) {
    if(h == NULL) return 0;

    assert(!h->has_red_leaning_right());
    assert(!(isRed(h->left) && isRed(h->left->left)));

    int leftCount = assertBlackHeight(h->left);
    int rightCount = assertBlackHeight(h->right);
    if(!isRed(h->left)) leftCount++;
    if(!isRed(h->right)) rightCount++;
    assert(leftCount == rightCount);
       
    return leftCount;
  }
  private:
  static const bool RED = true;
  Link root;
  Compare_fn compare_fn;
  
  inline static bool  isRed(Link& h) { return h != NULL && h->is_red();};
  
  void rb_insert(Link& head, T_Key key, T_Value value) { 
    if(head == NULL) {
      head = new Node(key, value);
      return;
    }
    head->split_if_4node();
    int cmp = compare_fn(key, head->key); 
    if(cmp == 0) { head->value = value;}
    else if (cmp < 0) rb_insert(head->left, key, value);
    else rb_insert(head->right, key, value);
    
    rebalance(head);
  };
  
  inline void rebalance(Link& h) { 
    if(h->has_red_leaning_right()) rotate_left(h);
    if(isRed(h->left) && isRed(h->left->left)) rotate_right(h);
  };
  
  inline void rotate_left(Link& h) {
    Link newHead = h->right;
    h->right = newHead->left;
    newHead->left = h;
    newHead->color = h->color;
    h->color_as_red();
    h = newHead;
    
  };

  inline void rotate_right(Link& h) {
    Link newHead = h->left;
    h->left = newHead->right;
    newHead->right = h;
    newHead->color = h->color;
    h->color_as_red();
    h = newHead;
  };
    
  };


}
