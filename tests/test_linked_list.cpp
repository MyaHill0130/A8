// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "singly_linked.hpp"

namespace slist = dsa::list;


TEST_CASE("SinglyLinkedList: Basic Operations", "[singly_linked_list]") {
    slist::SinglyLinkedList<int> list;

    SECTION("New list is empty") {
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
    }

    SECTION("push_front correctly adds elements") {
        list.push_front(10);
        list.push_front(20);
        
        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 20);
        REQUIRE(list.back() == 10);
    }

    SECTION("push_back correctly adds elements") {
        list.push_back(10);
        list.push_back(20);

        REQUIRE(list.size() == 2);
        REQUIRE(list.front() == 10);
        REQUIRE(list.back() == 20);
    }
}