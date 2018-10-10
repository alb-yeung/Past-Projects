This program can be compiled with make

I used four extra classes, Item, ItemList, TreeNode, and PriorityQueue

ItemList holds an array of Item's, and is used to store the Items
PriorityQueue holds an array of TreeNodes and is used as a max heap and a priority queue to search nodes in a Best First order.

The sortArr in ItemList uses a bubble sort because I didn't want to write a better sort function so if there are a lot of items then it might take a while to run.