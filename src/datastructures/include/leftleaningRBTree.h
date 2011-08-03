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
    Node() { color = !RED; }
    Node(T_Key k, T_Value v) {
      key = k;
      value = v;
      color = RED;
    };
    inline bool is_red() {return color;};
    inline void set_color_black() { color = !RED;};
    inline void split_if_4node() { 
      /*   if(this->left != NULL && this-> right != NULL 
	 && this->left->is_red() && this->right->is_red()) {
	this->set_color_red();
	this->
	}*/
    };
  };

  typedef Node* Link;
  
  LLRBTree() { root = NULL;};
  
  void insert(T_Key key, T_Value value){
    rb_insert(root, key, value);
    root->set_color_black();
  };

  T_Value find(T_Key key) const {
    T_Value i;
    return i;
  };
  private:
  static const bool RED = true;
  Link root;
  Compare_fn _compare_fn;

  void rb_insert(Link& head, T_Key key, T_Value value) { 
    if(head == NULL) {
      head = new Node(key, value);
      return;
    }
    head->split_if_4node();
  }
  };
}
