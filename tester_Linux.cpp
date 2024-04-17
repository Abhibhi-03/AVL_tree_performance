#include "tester_Linux.h"


int tester(void) {
	TestPtr runTest[numTests] = { test1, test2, test3, test4, test5,
							   test6, test7, test8, test9, test10,
	};
	std::string msg;
	bool result = true;
	int numPassed = 0;

	std::string* keys = new std::string[maxRecords];        //list of test cases. 
	int* data = new int[maxRecords];

	Timer t;
	double times[numTests];
	for (int i = 0; result && i < numTests; i++) {
		t.reset();
		t.start();
		result = runTest[i](maxRecords);
		t.stop();
		times[i] = t.currtime();
		if (!result) {
			std::cout << "Test " << i + 1 << " failed!" << std::endl;
		}
		else {
			numPassed++;
			std::cout << "Test " << i + 1 << "  passed!" << std::endl;
		}
	}
	if (numPassed == numTests) {
		std::cout << std::endl;
		std::cout << "  Test Number  |    Time     " << std::endl;
		std::cout << "---------------|-------------" << std::endl;

		for (int i = 0; i < numTests; i++) {
			std::cout << "   Test ";
			std::cout.width(2);
			std::cout << i + 1;
			std::cout << "     |  " << times[i] << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Congratulations! You have passed testing for A3 Linux Testing" << std::endl;
		return 0;
	}
	else {
		std::cout << std::endl;
		std::cout << "Looks like you still have some work left to do" << std::endl;
		return 1;
	}
}



// Testing for maximum size of map
bool test1(int max) {
	std::cout << "====Testing for MAP============" << std::endl;
	std::cout << "Test 1: Checking for maximum size." << std::endl;
	std::map<int, EmployeeInfo> testMap; // Key is SIN
	size_t count = 0;
	try {
		for (; count < max; ++count) {
			EmployeeInfo emp = { rand() % 100000, rand() % 100, static_cast<int>(count), static_cast<int>(count) };
			testMap[emp.sin] = emp;
		}
	}
	catch (const std::exception& e) {
		std::cout << "Reached maximum size at count = " << count << " with exception: " << e.what() << std::endl;
		std::cout << "Max_size() == " << testMap.max_size();
		return false;
	}
	return true;
}

//testing for load 
bool test2(int max) {
	std::cout << "Test 2: Testing for load." << std::endl;
	std::map<int, EmployeeInfo> testMap;
	const int iterations = 100000;
	int uniqueSinCounter = 1;

	for (int i = 0; i < iterations; ++i) {
		int operation = rand() % 3;
		int sin = uniqueSinCounter++;

		switch (operation) {
		case 0: {
			EmployeeInfo emp = { rand() % 100000, rand() % 100, sin, sin };
			testMap[sin] = emp;
			break;
		}
		case 1: {
			if (!testMap.empty()) {
				testMap.erase(testMap.begin()->first);
			}
			break;
		}
		case 2: {
			int sinToFind = rand() % sin + 1;
			auto it = testMap.find(sinToFind);
			break;
		}
		}
	}
	return true;
}

// test for memory leak 
bool test3(int max) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::cout << "Test 3: Testing for memory leak." << std::endl;
	for (int i = 0; i < max; ++i) {
		std::map<int, EmployeeInfo> testMap; // Stack allocation
		EmployeeInfo emp = { rand() % 100000, rand() % 100, 0, 0 };
		testMap[0] = emp;
	}
	return true;
}


bool test4(int max) {
	std::cout << "Test 4: Testing for Speed of Search." << std::endl;
	std::map<int, EmployeeInfo> testMap;
	// Populate the map
	for (int i = 0; i < max; ++i) {
		EmployeeInfo emp = { rand() % 100000, rand() % 100, i, i };
		testMap[i] = emp;
	}

	// Assume the last element is the worst case
	int worstCaseKey = max - 1;

	auto it = testMap.find(worstCaseKey);;
	return true;
}

AVL<EmployeeInfo> tree;

void Createdata(int max) {
	const int NUM = 2500;  // for some reason I couldn't just use max instead of NUM
	for (int i = 0; i < max; ++i) {
		EmployeeInfo empl;
		empl.age = 25 + (i * 2) % 45;
		empl.salary = 50000 + (i * 10) % 100000;
		empl.emplNumber = i;
		empl.sin = i;
		tree.insert(empl, empl.sin);

	}
}

bool test5(int max) {
	std::cout << "==========AVL Tree Testing==========" << std::endl;
	std::cout << "Test 5: Testing for correct insertion" << std::endl;
	Createdata(max);
	for (int i = 0; i < max; ++i) {
		node<EmployeeInfo>* found = tree.Find(tree.GetRoot(), i); // Search for the node by 'sin'
		if (!found || found->data.sin != i) {
			// If the node wasn't found or the 'sin' doesn't match, the test fails
			std::cout << "Failed to find inserted employee with SIN: " << i << std::endl;
			return false; // Test fails
		}
	}
	return true;
}



bool test6(int max) {
	std::cout << "Test 6: Testing for correct deletion" << std::endl;
	// Delete each element and check if it is really gone
	for (int i = 0; i < max; ++i) {
		tree.remove(i);
		node<EmployeeInfo>* found = tree.Find(tree.GetRoot(), i); // Search for the node by 'sin'
		// After deletion, verify the node is not present
		if (found != NULL) { // If found is not NULL, deletion failed
			std::cout << "Deletion test failed for SIN: " << i << std::endl;
			return false;
		}
	}
	return true;
}




bool test7(int max) {
	std::cout << "Test 7: Testing for Maximum Size" << std::endl;
	int count = 0;
	try {
		for (; count < max; ++count) {
			EmployeeInfo emp = { rand() % 100000, rand() % 100, static_cast<int>(count), static_cast<int>(count) };
			tree.insert(emp, emp.sin);
		}
	}
	catch (const std::exception& e) {
		std::cout << "Reached maximum size at count = " << count << " with exception: " << e.what() << std::endl;
		return false;
	}
	std::cout << "addded " << count << " elements" << std::endl;

	return true;
}

bool test8(int max) {
	std::cout << "Test 8: Testing for load" << std::endl;
	const int iterations = 10000;
	int uniqueSinCounter = 1;

	for (int i = 0; i < iterations; ++i) {
		EmployeeInfo emp = { rand() % 100000, rand() % 100, uniqueSinCounter, uniqueSinCounter };
		tree.insert(emp, emp.sin);
		if (i % 10 == 0) { // For every 10th iteration, perform a delete
			tree.remove(emp.sin);
		}
		tree.Find(tree.GetRoot(), emp.sin); // Perform a search

		uniqueSinCounter++;
	}
	return true;
}


bool test9(int max) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::cout << "Test 9: Testing for memory leak." << std::endl;
	for (int i = 0; i < max; ++i) {
		std::map<int, EmployeeInfo> testMap; // Stack allocation
		EmployeeInfo emp = { rand() % 100000, rand() % 100, 0, 0 };
		testMap[0] = emp;
	}
	return true;
}

bool test10(int max) {
	std::cout << "Test 10: Testing for Speed of Search." << std::endl;
	for (int i = 0; i < max; ++i) {
		EmployeeInfo emp = { rand() % 100000, rand() % 100, i, i }; // Assuming SIN is i for uniqueness
		tree.insert(emp, emp.sin);
	}
	// Perform searches for a range of SIN values, possibly targeting deeper nodes
	for (int i = 0; i < 1000; ++i) {  // The number of searches can be adjusted based on needs
		int targetSin = rand() % max;  // Randomly choose a SIN value to search for
		node<EmployeeInfo>* found = tree.Find(tree.GetRoot(), targetSin);
		if (!found) {
			std::cout << "Search failed for SIN: " << targetSin << std::endl;
			return false;  // If any search fails, the test is considered failed
		}
	}
	return true;  // Return true if all searches were successful
}





