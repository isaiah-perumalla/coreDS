#include "assert.h"
#include <functional>
namespace datastructures {
  template <typename T_Key, typename T_Item, typename Compare_fn = std::less<T_Key> >  
    class LLRBTree  {

  public:
  LLRBTree() {};
    

  void insert(T_Key key, T_Item values){
  };

  T_Item find(T_Key key) const{
    T_Item i;
    return i;
  };


  private:
  Compare_fn _compare_fn;
  };
}
