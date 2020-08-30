// Fun Programming Data Structures 1.0
// 
// Copyright © 2020 Greg Eakin. 
//
// Greg Eakin <greg@eakin.dev>
//
// All Rights Reserved.
//

#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../FunProgLib/List.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FunProgLib::Lists;

namespace FunProgCpp
{
   TEST_CLASS(CountedReferenceCpp)
   {
   public:

      TEST_METHOD(IsEmptyTest)
      {
         auto list = FunProgLib::Lists::List<string>::Empty();
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
         Assert::AreEqual(static_cast<void*>(list.get()), static_cast<void*>(reverse.get()));
      }

      vector<string> split(const string& s, char delim) const {
         vector<string> result;
         stringstream ss(s);
         string item;

         while (getline(ss, item, delim))
            result.push_back(item);

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
         Assert::AreEqual(static_cast<void*>(list.get()), static_cast<void*>(right.get()));
      }

      TEST_METHOD(CatRightEmptyTest)
      {
         auto left = List<string>::Empty();
         auto ww = split("How now, brown cow?", ' ');
         for (auto&& ww1 : ww)
            left = List<string>::Cons(ww1, left);

         const auto right = List<string>::Empty();

         const auto list = List<string>::Cat(left, right);
         Assert::AreEqual(static_cast<void*>(list.get()), static_cast<void*>(left.get()));
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
