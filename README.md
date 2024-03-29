AVL-Tree
========

An VL Tree is a self balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most 1.

It all take O(log2 n) in both average and worst cases, where n is the number of nodes in the tree. Insertions and deletions may require the tree to be rebalanced by one or more tree rotations. 

The AVL tree is named after its two Soviet inventors, G. M. Adelson-Velskii and E. M. Landis, who published it in their 1962 paper "An algorithm for the organization of information". 

• AVL trees are often compared with red-black trees because they support the same set of operations and because red-black trees also take O(log n) time for the basic operations. 

• Because AVL trees are more rigidly balanced, they are faster than red-black trees for lookup-intensive applications.

• Basic operations of an AVL tree involve carrying out the same actions as would be carried out on an unbalanced binary search tree. 

• But modifications are followed by zero or more operations called tree rotations, which help to restore the height balance of the subtrees.
