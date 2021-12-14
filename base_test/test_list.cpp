#include "gtest.h"
#include "../base/polynom.h"


// LIST TESTS

TEST(TList, can_create_list)
{
  ASSERT_NO_THROW(TList<int> List);
}

TEST(TList, can_push_back)
{
  TList<int> List;
  ASSERT_NO_THROW(List.AddNode(5));
}

TEST(TList, can_pop_front)
{
  TList<int> List;
  List.AddNode(5);
  ASSERT_NO_THROW(List.GetNode(0));
}

TEST(TList, can_compare_two_lists_by_value)
{
  TList<int> List1, List2;
  List1.AddNode(10);
  List2.AddNode(10);
  EXPECT_EQ(1, List1[0] == List2[0]);
}

TEST(TList, two_lists_with_different_size_are_not_equal)
{
  TList<int> List1, List2;

  List1.AddNode(1); List1.AddNode(2);
  List2.AddNode(1);

  EXPECT_FALSE(List1.GetNode(0) == List2.GetNode(0));
}

TEST(TList, can_create_copied_list)
{
  TList<int> List1, List2;
  List1.AddNode(5);
  List2 = List1;
  EXPECT_TRUE(List1[0] == List2[0]);
}

TEST(TList, can_assign_list)
{
  TList<int> List1, List2;
  List1.AddNode(5);
  ASSERT_NO_THROW(List2 = List1);
}

TEST(TList, method_get_return_value)
{
  TList<int> List;
  List.AddNode(10);
  EXPECT_EQ(10, List[0]);
}

TEST(TList, can_check_for_empty)
{
  TList<int> List;
  EXPECT_TRUE(List.IsEmpty());
}

TEST(TList, two_lists_with_different_sizes_are_not_equal)
{
  TList<int> List1, List2;
  List1.AddNode(1); List1.AddNode(1);
  List2.AddNode(1);
  EXPECT_FALSE(List1 == List2);
}

TEST(TList, two_lists_are_not_equal)
{
  TList<int> List1, List2;
  List1.AddNode(1);
  List2.AddNode(2);
  EXPECT_TRUE(List1 != List2);
}

TEST(TList, can_return_size_of_list)
{
  TList<int> List;
  for (int i = 0; i < 3; i++)
    List.AddNode(i);
  EXPECT_EQ(3, List.GetSize());
}

TEST(TList, method_del_delete_all_values_of_list)
{
  TList<int> List;
  for (int i = 0; i < 5; i++)
    List.AddNode(i);
  List.EraseList();
  EXPECT_TRUE(List.IsEmpty());
}

TEST(TList, can_erace_elem_by_iterator)
{
  TList<int> List;
  TList<int>::iterator i = List.begin();
  List.AddNode(10);
  ASSERT_NO_THROW(List.Erase(i));
}

TEST(TList, can_insert_elem_by_iterator)
{
  TList<int> List;
  TList<int>::iterator i = List.begin();
  List.Insert(i, 3);
  EXPECT_EQ(1, List.GetSize());
}

// ITERATOR TESTS

TEST(Iterator, can_create_iterator)
{
  TList<int> List;
  ASSERT_NO_THROW(TList<int>::iterator it = List.begin());
}

TEST(Iterator, can_create_copied_iterator)
{
  TList<int> List;
  TList<int>::iterator i1 = List.begin();
  ASSERT_NO_THROW(TList<int>::iterator i2(i1));
}

TEST(Iterator, can_assign_iterator)
{
  TList<int> List1, List2;
  TList<int>::iterator i1 = List1.begin();
  TList<int>::iterator i2 = List2.begin();
  ASSERT_NO_THROW(i2 = i1);
}

TEST(Iterator, can_dereference_iterator)
{
  TList<int> List;
  TList<int>::iterator i = List.begin();
  List.AddNode(1);
  EXPECT_EQ(1, *(i));
}

TEST(Iterator, can_increment_iterator)
{
  TList<int> List;
  List.AddNode(1);
  List.AddNode(2);
  TList<int>::iterator i = List.begin();
  ++i;
  EXPECT_EQ(2, *(i));
}
