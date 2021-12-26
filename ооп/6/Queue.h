#pragma once

#include <memory>
#include <exception>

namespace Containers {

    template <typename T, typename Allocator>
    class Queue;
    template <typename T>
    class QueueNode;
    template <typename T, typename Allocator>
    class QueueConstIterator;
    template <typename T, typename Allocator>
    class QueueIterator;

    //Implementation of QueueNode
    template <typename T>
    struct QueueNode {
        QueueNode() = default;
        QueueNode(T new_value) : value(new_value) {}
        T value;
        std::shared_ptr<QueueNode> next = nullptr;
        std::weak_ptr<QueueNode> prev;
    };

    //Implementation of Queue
    template<typename T, typename Allocator = std::allocator<T>>
    class Queue {

        friend QueueIterator<T, Allocator>;
        friend QueueConstIterator<T, Allocator>;

        using allocator_type = typename Allocator::template rebind<QueueNode<T>>::other;

        struct deleter {
            deleter(allocator_type* allocator) : allocator_(allocator) {}
            void operator() (QueueNode<T>* ptr) {
                if (ptr != nullptr) {
                    std::allocator_traits<allocator_type>::destroy(*allocator_,ptr);
                    allocator_->deallocate(ptr, 1);
                }
            }
        private:
            allocator_type* allocator_;
        };

    public:
        Queue() {
            QueueNode<T>* ptr = allocator_.allocate(1);
            std::allocator_traits<allocator_type>::construct(allocator_, ptr);
            std::shared_ptr<QueueNode<T>> new_elem(ptr, deleter(&allocator_));
            tail = new_elem;
            head = tail;
        }

        Queue(const Queue& q) = delete;
        Queue& operator = (const Queue&) = delete;
        void Pop() {
            if (Empty()) {
                throw std::out_of_range("Pop from empty queue");
            }
            head = head->next;
        }

        const T& Top() const {
            return head->value;
        }

        T& Top() {
            return head->value;
        }

        size_t Size() const {
            size_t size = 0;
            for (auto i : *this) {
                size++;
            }
            return size;
        }

        void Push(const T &value) {
            QueueNode<T>* ptr = allocator_.allocate(1);
            std::allocator_traits<allocator_type>::construct(allocator_, ptr, value);
            std::shared_ptr<QueueNode<T>> new_elem(ptr, deleter(&allocator_));
            if (Empty()) {
                head = new_elem;
                head->next = tail;
                tail->prev = head;
            } else {
                tail->prev.lock()->next = new_elem;
                new_elem->prev = tail->prev;
                new_elem->next = tail;
                tail->prev = new_elem;
            }
        }

        bool Empty() const {
            return head == tail;
        }

        QueueConstIterator<T, Allocator> begin() const {
            return QueueConstIterator<T, Allocator>(head, this);
        }

        QueueConstIterator<T, Allocator> end() const {
            return QueueConstIterator<T, Allocator>(tail, this);
        }

        QueueIterator<T, Allocator> begin() {
            return QueueIterator<T,Allocator>(head, this);
        }

        QueueIterator<T, Allocator> end() {
            return QueueIterator<T, Allocator>(tail, this);
        }

        void Erase(QueueIterator<T, Allocator> it) {
            if (it.collection != this) {
                throw std::runtime_error("Iterator does not belong to this collection");
            }
            std::shared_ptr<QueueNode<T>> it_ptr = it.node.lock();
            if (!it_ptr) {
                throw std::runtime_error("Iterator is corrupted");
            }
            if (it == end()) {
                throw std::runtime_error("Erase of end iterator");
            }
            if (it == begin()) {
                Pop();
            } else {
                std::weak_ptr<QueueNode<T>> prev_ptr = it_ptr->prev;
                std::shared_ptr<QueueNode<T>> next_ptr = it_ptr->next;
                prev_ptr.lock()->next = next_ptr;
                next_ptr->prev = prev_ptr;
            }
        }

        void Insert(QueueIterator<T, Allocator> it, const T& value) {
            if (it.collection != this) {
                throw std::runtime_error("Iterator does not belong to this collection");
            }
            std::shared_ptr<QueueNode<T>> it_ptr = it.node.lock();
            if (!it_ptr) {
                throw std::runtime_error("Iterator is corrupted");
            }
            if (it == end()) {
                Push(value);
                return;
            }
            QueueNode<T>* ptr = allocator_.allocate(1);
            std::allocator_traits<allocator_type>::construct(allocator_, ptr, value);
            std::shared_ptr<QueueNode<T>> new_elem(ptr, deleter(&allocator_));
            if (it == begin()) {
                new_elem->next = head;
                head->prev = new_elem;
                head = new_elem;
            } else {
                std::shared_ptr<QueueNode<T>> next_ptr = it_ptr;
                std::weak_ptr<QueueNode<T>> prev_ptr = it_ptr->prev;
                new_elem->prev = prev_ptr;
                prev_ptr.lock()->next = new_elem;
                new_elem->next = next_ptr;
                next_ptr->prev = new_elem;
            }

        }

    private:
        allocator_type allocator_;
        std::shared_ptr<QueueNode<T>> head;
        std::shared_ptr<QueueNode<T>> tail;
    };

    template<typename T, typename Allocator>
    class QueueIterator {
        friend Queue<T, Allocator>;
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        QueueIterator(std::shared_ptr<QueueNode<T>> init_ptr,const Queue<T, Allocator>* ptr) : node(init_ptr), collection(ptr) {}

        QueueIterator(const QueueIterator& other) : node(other.node), collection(other.collection) {}
        QueueIterator& operator = (const QueueIterator& other) {
            node = other.node;
            return *this;
        }

        bool operator == (const QueueIterator& other) const {
            auto lhs_l = node.lock(), rhs_l = other.node.lock();
            if (lhs_l && rhs_l) {
                return lhs_l.get() == rhs_l.get();
            }
            return false;
        }

        bool operator != (const QueueIterator& other) const {
            return !(*this == other);
        }

        QueueIterator& operator++() { // prefix
            std::shared_ptr<QueueNode<T>> temp = node.lock();
            if (temp) {
                if (temp->next == nullptr) {
                    throw std::out_of_range("Going out of container boundaries");
                }
                temp = temp->next;
                node = temp;
                return *this;
            } else {
                throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
            }

        }

        QueueIterator operator++(int) { //postfix
            QueueIterator result(*this);
            ++(*this);
            return result;
        }

        T& operator* () const {
            std::shared_ptr<QueueNode<T>> temp = node.lock();
            if (temp) {
                if (temp->next == nullptr) {
                    throw std::runtime_error("Dereferencing of end iterator");
                }
                return temp->value;
            } else {
                throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
            }
        }

    private:
        std::weak_ptr<QueueNode<T>> node;
        const Queue<T, Allocator>* collection;
    };

    template<typename T, typename Allocator>
    class QueueConstIterator {
        friend Queue<T, Allocator>;
    public:

        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        QueueConstIterator(std::shared_ptr<QueueNode<T>> init_ptr, const Queue<T, Allocator>* ptr) : node(init_ptr), collection(ptr) {}

        QueueConstIterator(const QueueConstIterator& other) : node(other.node), collection(other.collection) {}

        QueueConstIterator& operator = (const QueueConstIterator& other) {
            node = other.node;
            return *this;
        }

        bool operator == (const QueueConstIterator& other) const {
            auto lhs_l = node.lock(), rhs_l = other.node.lock();
            if (lhs_l && rhs_l) {
                return lhs_l.get() == rhs_l.get();
            }
            return false;
        }

        bool operator != (const QueueConstIterator& other) const {
            return !(*this == other);
        }

        QueueConstIterator& operator++() { // prefix
            std::shared_ptr<QueueNode<T>> temp = node.lock();
            if (temp) {
                if (temp->next == nullptr) {
                    throw std::out_of_range("Going out of container boundaries");
                }
                temp = temp->next;
                node = temp;
                return *this;
            } else {
                throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
            }

        }

        QueueConstIterator operator++(int) { //postfix
            QueueConstIterator result(*this);
            (*this)++;
            return result;
        }

        const T& operator* () const {
            std::shared_ptr<QueueNode<T>> temp = node.lock();
            if (temp) {
                if (temp->next == nullptr) {
                    throw std::runtime_error("Dereferencing of end iterator");
                }
                return temp->value;
            } else {
                throw std::runtime_error("Element pointed by this iterator doesnt exist anymore");
            }
        }

    private:
        std::weak_ptr<QueueNode<T>> node;
        const Queue<T, Allocator>* collection;
    };


}
