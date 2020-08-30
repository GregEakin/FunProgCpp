#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <utility>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// struct A {
//    // A() = default;
//    // A(const A&) = default;
//    // A(A&&) = default;
//    // ~A() = default;
//    // A& operator=(const A&) = default;
//    // A& operator=(A&&) = default;
//
//    int a;
//    int b;
//    int c;
//    int d;
// };
//
// A* pa1 = nullptr;
// A* pa2 = nullptr;
//
// A create(int i) {
//    A a = { i, i + 1, i + 2, i + 3 };
//    pa1 = &a;
//    return a;
// }
//
// int main(int argc, char* []) {
//    auto a = create(argc);
//    pa2 = &a;
//
//    Assert::AreEqual((void*)pa1, (void*)pa2);
// }

namespace FunProgCpp
{
   template <class T>
   struct RList
   {
      RList() = delete;
      RList(const RList&) = delete;
      RList(RList&&) = delete;
      ~RList() = delete;

      RList& operator=(const RList&) = default;
      RList& operator=(RList&&) = default;

      struct Node
      {
         const T element_;
         const Node& next_;

         Node();
         Node(T element, const Node& next);
         Node(const Node&) = default;
         Node(Node&&) = default;
         ~Node() = default;

         Node& operator=(const Node&) = default;
         Node& operator=(Node&&) = default;
      };

      static const Node& Empty()
      {
         static const Node EMPTY;
         const auto p1 = &EMPTY;
         return EMPTY;
      }

      static bool isEmpty(const Node& list) { return &list == &Empty(); }
      static Node Cons(const T element, const Node list) { return new Node(element, list); }
      static T Head(const Node& list)
      {
         if (isEmpty(list)) throw runtime_error("Null list.");
         return list.element_;
      }

      static Node Tail(const Node& list)
      {
         if (isEmpty(list)) throw runtime_error("Null list.");
         return list.next_;
      }

      static Node Cat(const Node& list1, const Node& list2)
      {
         if (isEmpty(list1)) return list2;
         if (isEmpty(list2)) return list1;
         return Node(list1.element_, Cat(list1.next_, list2));
      }

      static Node Reverse(const Node& list)
      {
         if (isEmpty(list)) return Empty;
         if (isEmpty(list.Next)) return list;
         return Rev(list, Empty());
      }

      static Node Rev(const Node& listIn, const Node& listOut)
      {
         if (isEmpty(listIn)) return listOut;
         const Node next(Haed(listIn), listOut);
         return Rev(Tail(listIn), next);
      }
   };

   template <class T>
   RList<T>::Node::Node()
      : element_()
      , next_(*this)
   {
   }

   template <class T>
   RList<T>::Node::Node(T element, const Node& next)
      : element_(std::move(element))
      , next_(next)
   {
   }

   TEST_CLASS(FunProgCpp)
   {
   public:

      TEST_METHOD(IsEmptyTest)
      {
         const auto& list = RList<string>::Empty();
         Assert::IsTrue(RList<string>::isEmpty(list));

         //list = List<string>::Cons("A", list);
      }

      TEST_METHOD(EmptyTest)
      {
         const auto& list1 = RList<string>::Empty();
         const auto& list2 = RList<string>::Empty();
         // Assert::IsTrue(List<string>::isEmpty(list));
         const auto list3 = RList<int>::Empty();

         auto l1 = &list1;
         auto l2 = &list2;
         auto l3 = &list3;

         //list = List<string>::Cons("A", list);
      }
   };
}
