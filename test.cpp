#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"


TEST_CASE("Tree functionality") {
    Tree<int> intTree;

    SUBCASE("Add root and children") {
        intTree.add_root(1);
        CHECK_NOTHROW(intTree.add_sub_node(1, 2));
        CHECK_NOTHROW(intTree.add_sub_node(1, 3));
        CHECK_NOTHROW(intTree.add_sub_node(2, 4));
        CHECK_NOTHROW(intTree.add_sub_node(2, 5));
        CHECK_NOTHROW(intTree.add_sub_node(3, 6));
        CHECK_NOTHROW(intTree.add_sub_node(3, 7));
    }

    SUBCASE("Pre-Order Traversal") {
        intTree.add_root(1);
        intTree.add_sub_node(1, 2);
        intTree.add_sub_node(1, 3);
        intTree.add_sub_node(2, 4);
        intTree.add_sub_node(2, 5);
        intTree.add_sub_node(3, 6);
        intTree.add_sub_node(3, 7);

        auto it = intTree.begin_pre_order();
        CHECK(*it == 1); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 4); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 6); ++it;
        CHECK(*it == 7);
    }

    SUBCASE("Post-Order Traversal") {
        intTree.add_root(1);
        intTree.add_sub_node(1, 2);
        intTree.add_sub_node(1, 3);
        intTree.add_sub_node(2, 4);
        intTree.add_sub_node(2, 5);
        intTree.add_sub_node(3, 6);
        intTree.add_sub_node(3, 7);

        auto it = intTree.begin_post_order();
        CHECK(*it == 4); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 6); ++it;
        CHECK(*it == 7); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 1);
    }

    SUBCASE("In-Order Traversal") {
        intTree.add_root(1);
        intTree.add_sub_node(1, 2);
        intTree.add_sub_node(1, 3);
        intTree.add_sub_node(2, 4);
        intTree.add_sub_node(2, 5);
        intTree.add_sub_node(3, 6);
        intTree.add_sub_node(3, 7);

        auto it = intTree.begin_in_order();
        CHECK(*it == 4); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 1); ++it;
        CHECK(*it == 6); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 7);
    }

    SUBCASE("BFS Traversal") {
        intTree.add_root(1);
        intTree.add_sub_node(1, 2);
        intTree.add_sub_node(1, 3);
        intTree.add_sub_node(2, 4);
        intTree.add_sub_node(2, 5);
        intTree.add_sub_node(3, 6);
        intTree.add_sub_node(3, 7);

        auto it = intTree.begin_bfs();
        CHECK(*it == 1); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 4); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 6); ++it;
        CHECK(*it == 7);
    }

    SUBCASE("DFS Traversal") {
        intTree.add_root(1);
        intTree.add_sub_node(1, 2);
        intTree.add_sub_node(1, 3);
        intTree.add_sub_node(2, 4);
        intTree.add_sub_node(2, 5);
        intTree.add_sub_node(3, 6);
        intTree.add_sub_node(3, 7);

        auto it = intTree.begin_dfs();
        CHECK(*it == 1); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 4); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 6); ++it;
        CHECK(*it == 7);
    }

    SUBCASE("Heap Iterator") {
        intTree.add_root(5);
        intTree.add_sub_node(5, 2);
        intTree.add_sub_node(5, 8);
        intTree.add_sub_node(2, 1);
        intTree.add_sub_node(2, 3);
        intTree.add_sub_node(8, 7);
        intTree.add_sub_node(8, 10);

        auto it = intTree.begin_heap();
        CHECK(*it == 1); ++it;
        CHECK(*it == 2); ++it;
        CHECK(*it == 3); ++it;
        CHECK(*it == 5); ++it;
        CHECK(*it == 7); ++it;
        CHECK(*it == 8); ++it;
        CHECK(*it == 10);
    }
}