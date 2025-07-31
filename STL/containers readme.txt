1.  std::map
(i) Stores the values in sorted order. ( ascending to descending)
(ii) Stores only unique values.
(iii) Elements can only be inserted or deleted but cannot be modified.
(iv) We can erase more than 1 element by giving start iterator and end iterator position.
(v) Traversal using iterators.
(vi) Sets are implemented as Binary Search Tree.
-------------------------------
2.  std::multimap
(i) Stores elements in sorted order.
(ii) It allows storage of multiple elements.
(iii) We can erase more than 1 element by giving start iterator and end iterator.
(iv) Also implemented as a balanced binary search tree.
Note:- All other properties similar to set.
--------------------------
3. Unstd::unordered_map
(i) Elements can be stored in any order. ( no sorted order )
(ii) Stores only unique values.
(iii) Hash-table used to store elements.
(iv) We can erase only the element for which iterator position is given.
(v) Each key maps to a single value.
Note:- All other properties similar to set.
------------------------
4. Ustd::unordered_multimap
(i) Elements can be stored in any order.
(ii) Duplicate elements can be stored.
(iii) Hash-table used to store elements.
(iv) We can erase only the element for which iterator position is given.
(v) Each key can map to multiple values.
Note:- All other properties similar to set.
-----------------------------------------------------
Type	                Unique Keys	Sorted	Allows Duplicates	Underlying Structure
std::map	             Yes	       Yes	    No	              Tree
std::multimap          	No          	Yes	    Yes	                Tree
std::unordered_map  	Yes            	No	    No	                Hash Table
std::unordered_multimap	   No	        No	    Yes	                Hash Tabl