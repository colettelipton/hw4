#include "avlbst.h"
#include <gtest/gtest.h>

#include <initializer_list>
#include <set>
#include <utility>

int main(){
	AVLTree<int, int> testTree;

	//testTree.insert(std::make_pair(95, 9));
	//testTree.print();

	//testTree.insert(std::make_pair(-27, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(-52, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(-18, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(-24, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(109, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(-58, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(-49, 9));
	//testTree.print();
	//testTree.insert(std::make_pair(127, 9));
	//testTree.print();
	//testTree.print();
	//testTree.insert(std::make_pair(9, 9)); 
	//testTree.print();
	/* testTree.insert(std::make_pair(-84, 9));
	testTree.print();
	//testTree.insert(std::make_pair(141, 9));
	//testTree.print();
	testTree.insert(std::make_pair(-38, 9));
	testTree.print();
	testTree.insert(std::make_pair(-12, 9));
	testTree.print();
	testTree.insert(std::make_pair(48, 9));
	testTree.print();
	testTree.insert(std::make_pair(-89, 9));
	testTree.print();
	testTree.insert(std::make_pair(61, 9));
	testTree.print();
	testTree.insert(std::make_pair(87, 9));
	testTree.print();
	testTree.insert(std::make_pair(11, 9));
	testTree.print();
	testTree.insert(std::make_pair(-35, 9));
	testTree.print();
	testTree.insert(std::make_pair(-87, 9));
	testTree.print();
	testTree.insert(std::make_pair(130, 9));
	testTree.print();
	testTree.insert(std::make_pair(72, 9));
	testTree.print();
	testTree.insert(std::make_pair(76, 9));
	testTree.print(); 
	testTree.insert(std::make_pair(-113, 9)); */
	testTree.print();
	testTree.insert(std::make_pair(20, 9));
	testTree.print();
	testTree.insert(std::make_pair(10, 9));
	testTree.print();
	testTree.insert(std::make_pair(30, 9));
	testTree.print();
	testTree.insert(std::make_pair(15, 9));
	testTree.print(); 
	//testTree.insert(std::make_pair(-125, 9));
	//testTree.print();

	testTree.clear();
	testTree.print(); 

	return 0;
}