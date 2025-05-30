
#include "pch.h"
#include "../lab2/Array.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ArrayTests, ArrayCapacityTest) {
	Array<int> arr = Array<int>();
	for (int i = 0; i < 20; i++)
	{
		arr.push_back(i);
	}
	EXPECT_EQ(arr.capacity(), 32);
	EXPECT_EQ(arr[19], 19);
}

TEST(ArrayTests, InsertTest) {
	Array<int> arr = Array<int>();
	arr.insert(0, 1);
	arr.insert(-1, 2);
	ASSERT_EQ(arr[1], 2);
	EXPECT_EQ(arr[0], 1);
}

TEST(ArrayTests, ForwardIteratorsTest) {
	Array<int> arr = Array<int>();
	for (int i = 0; i < 20; i++)
	{
		arr.push_back(i);
	}
	int i = 0;
	for (auto it = arr.iterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ(it.get(), i);
		i++;
	}
}

TEST(ArrayTests, ReverseIteratorsTest) {
	Array<int> arr = Array<int>();
	for (int i = 0; i < 20; i++)
	{
		arr.push_back(i);
	}
	int i = 19;
	for (auto it = arr.reverseIterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ(it.get(), i);
		i--;
	}
}

TEST(ArrayTests, ComplexObjectCopy) {
	Array<std::string> arr = Array<std::string>();
	arr.push_back(std::string("privet"));
	
	Array<std::string> copy;
	copy = arr;

	EXPECT_EQ(*copy[0].c_str(), *arr[0].c_str());
	EXPECT_NE(copy[0].c_str(), arr[0].c_str());
}