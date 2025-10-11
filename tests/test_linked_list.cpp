// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "singly_linked.hpp"
#include "doubly_linked.hpp"
#include "circularly_linked.hpp"


TEST_CASE("SinglyLinkedList: Rever") {
    dsa::list::SinglyLinkedList<int> list;
    
    SECTION("Reverse an empty list") {
        list.reverse();
        REQUIRE(list.empty());
    }

    SECTION("Reverse a single-element list") {
        list.push_back(10);
        list.reverse();
        REQUIRE(list.size() == 1);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 10);
    }

    SECTION("Reverse a multi-element list") {
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        
        list.reverse();
        
        REQUIRE(list.size() == 3);
        REQUIRE(list.front() == 30);
        REQUIRE(list.back() == 10);
        
 }
}

TEST_CASE("DoublyLinkedList: concatenate") {
    dsa::list::DoublyLinkedList<int> list1;
    dsa::list::DoublyLinkedList<int> list2;

    list1.push_back(100);
    list1.push_back(200);

    list2.push_back(300);
    list2.push_back(400);

    list1.concatenate(list2);

    REQUIRE(list1.size() == 4);
    REQUIRE(list1.front() == 100);
    REQUIRE(list1.back() == 400);

    // Check that list2 is now empty and valid
    REQUIRE(list2.empty());
    REQUIRE(list2.size() == 0);
    // Attempting to pop from the now-empty list should not crash
    REQUIRE_NOTHROW(list2.pop_front());

    // Check the order of the concatenated list
    list1.pop_front(); // 100
    REQUIRE(list1.front() == 200);
    list1.pop_front(); // 200
    REQUIRE(list1.front() == 300);
}

TEST_CASE("CircularlyLinkedList: splitEven") {
    dsa::list::CircularlyLinkedList<int> main_list;
    for (int i = 1; i <= 6; ++i) {
        main_list.push_back(i); // List: [1, 2, 3, 4, 5, 6]
    }

    dsa::list::CircularlyLinkedList<int> listA, listB;

    SECTION("Split an even-sized list") {
        main_list.splitEven(listA, listB);

        // Check original list
        REQUIRE(main_list.empty());
        
        // Check list A
        REQUIRE(listA.size() == 3);
        REQUIRE(listA.front() == 1);
        REQUIRE(listA.back() == 3);
        
        // Check list B
        REQUIRE(listB.size() == 3);
        REQUIRE(listB.front() == 4);
        REQUIRE(listB.back() == 6);
    }
    
    SECTION("Splitting an odd-sized list throws an error") {
        main_list.push_back(7); // Make the list size odd (7)
        REQUIRE_THROWS_AS(main_list.splitEven(listA, listB), std::logic_error);
    }
}