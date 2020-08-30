#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FunProgCpp
{
   template <class T>
   struct List
   {
      List() = delete;
      List(const List&) = delete;
      List(List&&) = delete;
      ~List() = delete;

      List& operator=(const List&) = delete;
      List& operator=(List&&) = delete;

      struct Node
      {
         const T element_;
         const shared_ptr<Node> next_;

         Node() = delete;
         Node(T element, shared_ptr<Node> next) : element_(std::move(element)), next_(std::move(next)) {}
         Node(const Node&) = default;
         Node(Node&&) = default;
         ~Node() = default;

         Node& operator=(const Node&) = default;
         Node& operator=(Node&&) = default;
      };

      static shared_ptr<Node> Empty()
      {
         return nullptr;
      }

      static bool isEmpty(const shared_ptr<Node>& list)
      {
         return list == nullptr;
      }

      static shared_ptr<Node> Cons(const T element, const shared_ptr<Node>& list)
      {
         return make_shared<Node>(element, list);
      }

      static T Head(const shared_ptr<Node>& list)
      {
         if (isEmpty(list)) throw runtime_error("Null list.");
         return list->element_;
      }

      static shared_ptr<Node> Tail(const shared_ptr<Node>& list)
      {
         if (isEmpty(list)) throw runtime_error("Null list.");
         return list->next_;
      }

      static shared_ptr<Node> Cat(const shared_ptr<Node>& list1, const shared_ptr<Node>& list2)
      {
         if (isEmpty(list1)) return list2;
         if (isEmpty(list2)) return list1;
         return make_shared<Node>(list1->element_, Cat(list1->next_, list2));
      }

      static shared_ptr<Node> Reverse(const shared_ptr<Node>& list)
      {
         if (isEmpty(list)) return Empty();
         if (isEmpty(list->next_)) return list;
         return Rev(list, Empty());
      }

      static shared_ptr<Node> Rev(const shared_ptr<Node>& listIn, const shared_ptr<Node>& listOut)
      {
         if (isEmpty(listIn)) return listOut;
         const auto next = make_shared<Node>(Head(listIn), listOut);
         return Rev(Tail(listIn), next);
      }
   };

   TEST_CLASS(CountedReferenceCpp)
   {
   public:

      TEST_METHOD(IsEmptyTest)
      {
         auto list = List<string>::Empty();
         Assert::IsTrue(List<string>::isEmpty(list));

         list = List<string>::Cons("A", list);
         Assert::IsFalse(List<string>::isEmpty(list));
      }

      TEST_METHOD(EmptyHeadTest)
      {
         const auto list = List<string>::Empty();
         Assert::ExpectException<runtime_error>([list] { List<string>::Head(list); });
      }

      TEST_METHOD(EmptyTailTest)
      {
         const auto list = List<string>::Empty();
         Assert::ExpectException<runtime_error>([list] { List<string>::Tail(list); });
      }

      TEST_METHOD(ReverseEmptyListTest)
      {
         const auto list = List<string>::Empty();
         Assert::IsTrue(List<string>::isEmpty(list));
      }

      TEST_METHOD(ReverseSingleListTest)
      {
         const auto list = List<string>::Cons("Wow", List<string>::Empty());
         const auto reverse = List<string>::Reverse(list);
         Assert::AreEqual((void*)list.get(), (void*)reverse.get());
      }

      vector<string> split(const string& s, char delim) const {
         vector<string> result;
         stringstream ss(s);
         string item;

         while (getline(ss, item, delim)) {
            result.push_back(item);
         }

         return result;
      }

      TEST_METHOD(ReverseListTest)
      {
         auto ww = split("How now, brown cow?", ' ');
         auto list = List<string>::Empty();
         for (auto && ww1 : ww)
            list = List<string>::Cons(ww1, list);

         const auto reverse = List<string>::Reverse(list);
         Assert::AreEqual("How", List<string>::Head(reverse).c_str());
         Assert::AreEqual("now,", List<string>::Head(List<string>::Tail(reverse)).c_str());
      }

      TEST_METHOD(CatBothEmptyTest)
      {
         const auto left = List<string>::Empty();
         const auto right = List<string>::Empty();
         const auto list = List<string>::Cat(left, right);
         Assert::IsTrue(List<string>::isEmpty(list));
      }

      TEST_METHOD(CatLeftEmptyTest)
      {
         const auto left = List<string>::Empty();

         auto right = List<string>::Empty();
         auto ww = split("How now, brown cow?", ' ');
         for (auto&& ww1 : ww)
            right = List<string>::Cons(ww1, right);

         const auto list = List<string>::Cat(left, right);
         Assert::AreEqual((void*)list.get(), (void*)right.get());
      }

      TEST_METHOD(CatRightEmptyTest)
      {
         auto left = List<string>::Empty();
         auto ww = split("How now, brown cow?", ' ');
         for (auto&& ww1 : ww)
            left = List<string>::Cons(ww1, left);

         const auto right = List<string>::Empty();

         const auto list = List<string>::Cat(left, right);
         Assert::AreEqual((void*)list.get(), (void*)left.get());
      }

      TEST_METHOD(CatTest)
      {
         auto left = List<string>::Empty();
         auto ww = split("How now,", ' ');
         for (auto&& ww1 : ww)
            left = List<string>::Cons(ww1, left);

         auto right = List<string>::Empty();
         auto wp = split("brown cow?", ' ');
         for (auto&& wp1 : wp)
            right = List<string>::Cons(wp1, right);

         const auto list = List<string>::Cat(left, right);
         Assert::AreEqual("now,", List<string>::Head(list).c_str());
         Assert::AreEqual("How", List<string>::Head(List<string>::Tail(list)).c_str());
      }
   };
}
