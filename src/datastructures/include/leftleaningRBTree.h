#include "assert.h"
#include <functional>
namespace datastructures {

    
  template <typename T_Key, typename T_Value, typename Compare_fn = std::less<T_Key> >  
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
      return this->right != NULL && this->right->is_red();
    };

  };

  typedef Node* Link;
  
  LLRBTree() { root = NULL;};
  
  void insert(T_Key key, T_Value value){
    rb_insert(root, key, value);
    root->color_as_black();
  };

  T_Value find(T_Key key) const {
    T_Value i;
    return i;
  };

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
  }
  inline void rebalance(Link& h) { 
    if(h->has_red_leaning_right()) rotate_left(h);
    if(isRed(h->left) && isRed(h->left->left)) rotate_right(h);
  };
  
  inline void rotate_left(Link& h) {
        
  }
  inline void rotate_right(Link& h) {
    
  }
    
  };
}