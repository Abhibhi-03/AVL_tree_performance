#include "AVLTree.h"

const int NUM = 250000;
int treeHeight = 0;
std::ofstream outfile;
#include <string>
#include <random>
#include "timer.h"
#include "tester_windows.h"

int main()
{
	AVL<EmployeeInfo> t;
	int sinArray[NUM] = { 0 };
	for (int i = 0; i < NUM; ++i) sinArray[i] = 100000000 + i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(std::begin(sinArray), std::end(sinArray), g);	
	//	for (int i = 0; i < NUM; ++i) cout << "i:" << i << " sin:" << sinArray[i] << endl;
	for (int i = 0; i < NUM; ++i) {
		EmployeeInfo empl;
		empl.age = 25 + (i * 2) % 45;
		empl.salary = 50000 + (i * 10) % 100000;
		empl.emplNumber = i;
		empl.sin = sinArray[i];
		t.insert(empl,empl.sin);
	}

	outfile.open("inorder.txt");
	if (!outfile.is_open()) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1; // or handle the error appropriately
	}
	std::cout << "INORDER (NUM=" << NUM << ", height=" << t.GetRoot()->height << "): root node has sin:" << t.GetRoot()->data.sin << std::endl << std::endl;
	outfile << "INORDER (NUM=" << NUM << ", height=" << t.GetRoot()->height << "): root node has sin:" << t.GetRoot()->data.sin << std::endl << std::endl;
	t.display();
	std::cout << std::endl << "DONE" << std::endl << std::endl;
	int testOutcome = tester();
	outfile.close();
	return 0;
}