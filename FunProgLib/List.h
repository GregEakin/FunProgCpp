#pragma once
namespace FunProgLib
{
   namespace Lists
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
   }
}