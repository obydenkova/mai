#pragma once

#include <memory>
#include <exception>

namespace Containers {

    template <typename T>
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
        std::weak_ptr<ListNode> prev;
    };

    template <typename T>
    struct ListIterator {
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        ListIterator(std::shared_ptr<ListNode<T>> ptr)
        : ptr_(ptr){}

        T& operator * () {
            std::shared_ptr<ListNode<T>> locked = ptr_.lock();
            if (!locked) {
                throw std::runtime_error("Iterator does not exist");
            }
            return locked->data;
        }

        T* operator -> () {
            std::shared_ptr<ListNode<T>> locked = ptr_.lock();
            if (!locked) {
                throw std::runtime_error("Iterator does not exist");
            }
            return &locked->data;
        }

        ListIterator& operator++() {
            std::shared_ptr<ListNode<T>> locked = ptr_.lock();
            if (!locked || locked->next == nullptr) {
                throw std::runtime_error("Out of bounds");
            }
            ptr_ = locked->next;
            return *this;
        }

        const ListIterator operator++(int) {
            auto copy = *this;
            ++(*this);
            return copy;
        }

        bool operator == (const ListIterator& other) const {
            return ptr_.lock() == other.ptr_.lock();
        }

        bool operator != (const ListIterator& other) const {
            return !(*this == other);
        }

        std::weak_ptr<ListNode<T>> ptr_;
    };

    template <typename T, typename Allocator = std::allocator<T>>
    class List {
    public:
        using allocator_type = typename Allocator::template rebind<ListNode<T>>::other;

        struct deleter {
            deleter(allocator_type* allocator) : allocator_(allocator) {}

            void operator() (ListNode<T>* ptr) {
                std::allocator_traits<allocator_type >::destroy(*allocator_, ptr);
                allocator_->deallocate(ptr,1);
            }

        private:
            allocator_type* allocator_;
        };

        List() {
            ListNode<T>* ptr = allocator_.allocate(1);
            std::allocator_traits<allocator_type >::construct(allocator_, ptr);
            std::shared_ptr<ListNode<T>> new_elem(ptr, deleter(&allocator_));
            tail = new_elem;
            head = tail;
            tail->next = nullptr;
        }

        List(const List&) = delete;
        List(List&&) = delete;

        bool Empty() const {
            return head == tail;
        }

        T& operator[] (size_t index) {
            if (index >= Size()) {
                throw std::out_of_range("Index too big");
            }
            auto it = begin();
            for (size_t i = 0; i < index; ++i) {
                ++it;
            }
            return *it;
        }

        ListIterator<T> begin() {
            return ListIterator<T>(head);
        }

        ListIterator<T> end() {
            return ListIterator<T>(tail);
        }

        void Insert(ListIterator<T> iter, T elem) {
            ListNode<T>* ptr = allocator_.allocate(1);
            std::allocator_traits<allocator_type>::construct(allocator_, ptr);
            std::shared_ptr<ListNode<T>> new_elem(ptr, deleter(&allocator_));
            new_elem->data = std::move(elem);
            if (iter == begin()) {
                new_elem->next = head;
                head->prev = new_elem;
                head = new_elem;
            } else {
                std::shared_ptr<ListNode<T>> cur_ptr = iter.ptr_.lock();
                std::shared_ptr<ListNode<T>> prev_ptr = iter.ptr_.lock()->prev.lock();
                prev_ptr->next = new_elem;
                cur_ptr->prev = new_elem;
                new_elem->next = cur_ptr;
                new_elem->prev = prev_ptr;
            }
        }

        void Erase(ListIterator<T> iter) {
            if (iter == end()) {
                throw std::runtime_error("Erasing end iterator");
            }
            std::shared_ptr<ListNode<T>> ptr = iter.ptr_.lock();
            if (iter == begin()) {
                head = head->next;
                ptr->next = nullptr;
            } else {
                std::shared_ptr<ListNode<T>> prev_ptr = ptr->prev.lock();
                std::shared_ptr<ListNode<T>> next_ptr = ptr->next;
                prev_ptr->next = next_ptr;
                next_ptr->prev = prev_ptr;
            }
        }

        size_t Size() const {
        size_t counter = 0;
        ListIterator<T> begin_it(head);
        ListIterator<T> end_it(tail);
        while(begin_it != end_it) {
        counter++;
        ++begin_it;
    }
return counter;
}
    private:
        allocator_type allocator_;
        std::shared_ptr<ListNode<T>> head;
        std::shared_ptr<ListNode<T>> tail;
    };

}