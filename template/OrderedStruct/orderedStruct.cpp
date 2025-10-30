/* ========================================================================
    -> Policy‑based ordered set and multiset
    ======================================================================== */
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template<class T, class C = std::less<T>>
using ordered_set = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;

template<class T, class C = std::less<T>>
using ordered_multiset = tree<std::pair<T, int>, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;