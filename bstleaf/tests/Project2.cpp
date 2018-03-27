#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BSTLEAF.h"
#include "BSTROOT.h"
#include "BSTRAND.h"
#include "AVL.h"
#include <stdexcept>

using namespace cop3530;

//compare
bool compare(const int &key1, const int &key2) {
	if (key1 < key2) {
		return true;
	}
	return false;
}
//equal
bool equals(const int &key1, const int &key2) {
	if (key1 == key2) {
		return true;
	}
	return false;
}

TEST_CASE("BSTLEAF") {
	bool passed = true;
	BSTLEAF<int, int, compare, equals> test;
	test.insert(4, 40);
	test.insert(2, 20);
	test.insert(1, 10);
	test.insert(9, 90);
	test.insert(6, 60);
	test.insert(7, 70);
	test.insert(5, 50);
	test.insert(3, 30);
	test.insert(8, 80);
	//Test overwrite and lookup
	test.insert(5, 100);
	REQUIRE(test.lookup(5) == 100);
	REQUIRE(test.lookup(8) == 80);
	try {
		test.lookup(1000);
		passed = false;
	}
	catch(std::runtime_error &e) {}
	//Test remove
	test.remove(3);
	test.remove(5);
	try {
		test.remove(5);
		passed = false;
	} catch(std::runtime_error &e) {}
	REQUIRE(passed == true);
}

TEST_CASE("BSTROOT") {
	bool passed = true;
	BSTROOT<int, int, compare, equals> test;
	test.insert(9, 90);
	test.insert(1, 10);
	test.insert(3, 30);
	test.insert(6, 60);
	test.insert(7, 70);
	test.insert(2, 20);
	test.insert(4, 40);
	test.insert(5, 50);
	test.insert(8, 80);
	//Test overwrite and lookup
	test.insert(5, 100);
	REQUIRE(test.lookup(5) == 100);
	REQUIRE(test.lookup(8) == 80);
	try {
		test.lookup(1000);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	//Test remove
	test.remove(3);
	test.remove(5);
	try {
		test.remove(5);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	REQUIRE(passed == true);
}

TEST_CASE("BSTRAND") {
	bool passed = true;
	BSTRAND<int, int, compare, equals> test;
	test.insert(9, 90);
	test.insert(1, 10);
	test.insert(3, 30);
	test.insert(6, 60);
	test.insert(7, 70);
	test.insert(2, 20);
	test.insert(4, 40);
	test.insert(5, 50);
	test.insert(8, 80);
	//Test overwrite and lookup
	test.insert(5, 100);
	REQUIRE(test.lookup(5) == 100);
	REQUIRE(test.lookup(8) == 80);
	try {
		test.lookup(1000);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	//Test remove
	test.remove(3);
	test.remove(5);
	try {
		test.remove(5);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	REQUIRE(passed == true);
}

TEST_CASE("AVL") {
	bool passed = true;
	AVL<int, int, compare, equals> test;
	test.insert(9, 90);
	test.insert(1, 10);
	test.insert(3, 30);
	test.insert(6, 60);
	test.insert(7, 70);
	test.insert(2, 20);
	test.insert(4, 40);
	test.insert(5, 50);
	test.insert(8, 80);
	//Test overwrite and lookup
	test.insert(5, 100);
	REQUIRE(test.lookup(5) == 100);
	REQUIRE(test.lookup(8) == 80);
	try {
		test.lookup(1000);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	//Test remove
	test.remove(3);
	test.remove(5);
	try {
		test.remove(5);
		passed = false;
	}
	catch (std::runtime_error &e) {}
	REQUIRE(passed == true);
}