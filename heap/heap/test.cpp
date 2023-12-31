#include "heap.h"
#include <catch.hpp>

TEST_CASE("TEST_3: Push Multiple Elements Test") {
  PriorityQueue<int> pq;
  pq.Push(5);
  pq.Push(10);
  pq.Push(3);
  REQUIRE(pq.Front() == 10); // Top should be 10 (max heap)
  pq.Pop();
  REQUIRE(pq.Front() == 5); // After popping, top should be 5
  pq.Pop();
  REQUIRE(pq.Front() == 3); // After popping, top should be 3
}

TEST_CASE("Test Push Single Element") {
  PriorityQueue<int> pq;
  pq.Push(5);
  REQUIRE(pq.Front() == 5);
}

TEST_CASE("Test Push Multiple Elements") {
  PriorityQueue<int> pq;
  pq.Push(5);
  pq.Push(10);
  pq.Push(3);
  REQUIRE(pq.Front() == 10); // Top should be 10 (max heap)
  pq.Pop();
  REQUIRE(pq.Front() == 5); // After popping, top should be 5
  pq.Pop();
  REQUIRE(pq.Front() == 3); // After popping, top should be 3
}

TEST_CASE("Test Custom Comparison - Min Heap") {
  PriorityQueue<int, std::greater<int>> pq; // Using std::greater for a min heap
  pq.Push(5);
  pq.Push(10);
  pq.Push(3);
  REQUIRE(pq.Front() == 3); // Top should be 3 (min heap)
}

TEST_CASE("Test Custom Comparison - Custom Object") {
  struct Person {
    int age;
    std::string name;
    bool operator<(const Person &other) const { return age < other.age; }
  };
  PriorityQueue<Person> pq;
  pq.Push(Person{25, "Alice"});
  pq.Push(Person{30, "Bob"});
  pq.Push(Person{20, "Charlie"});
  REQUIRE(pq.Front().age == 30); // Top should be Bob (max age)
}

TEST_CASE("Test Large Number of Elements") {
  PriorityQueue<int> pq;
  const int totalElements = 10000;
  for (int i = totalElements; i > 0; --i) {
    pq.Push(i);
  }
  std::vector<int> sorted;
  for (int i = 0; i < totalElements; ++i) {
    sorted.push_back(pq.Front());
    pq.Pop();
  }
  std::vector<int> expected(totalElements);
  std::iota(expected.rbegin(), expected.rend(),
            1);                // Fill expected vector with 1 to totalElements
  REQUIRE(sorted == expected); // Ensure elements are retrieved in sorted order
}

TEST_CASE("Test Huge Number of Elements - Shuffled Input") {
  PriorityQueue<int> pq;
  size_t TEN_MILLION = 10'000'000;

  // Create a vector with numbers from 1 to 10 million
  std::vector<int> shuffledNumbers(TEN_MILLION);
  std::iota(shuffledNumbers.begin(), shuffledNumbers.end(), 1);
  std::random_shuffle(shuffledNumbers.begin(),
                      shuffledNumbers.end()); // Shuffle the numbers

  // Insert the shuffled numbers into the PriorityQueue
  for (const auto &num : shuffledNumbers) {
    pq.Push(num);
  }

  // Extract elements from the PriorityQueue and compare with sorted expected
  // result
  std::vector<int> sortedExpected(TEN_MILLION);
  std::iota(sortedExpected.rbegin(), sortedExpected.rend(), 1);

  std::vector<int> sortedExtracted;
  while (!pq.Empty()) {
    sortedExtracted.push_back(pq.Front());
    pq.Pop();
  }
  REQUIRE(sortedExtracted ==
          sortedExpected); // Ensure elements are retrieved in sorted order
}
