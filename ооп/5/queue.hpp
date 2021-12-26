#ifndef D_QUEUE_HPP_
#define D_QUEUE_HPP_ 1

#include <iterator>
#include <memory>
#include <utility>

namespace containers {

	template <class T>
	struct queue {
	private:
		struct element;
	public:
		queue() = default;

		struct forward_iterator	{
		public:
			using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

			forward_iterator(element *ptr);

			T& operator* ();
			forward_iterator& operator++ ();
			forward_iterator operator++ (int);

			bool operator== (const forward_iterator& o) const;
			bool operator!= (const forward_iterator& o) const;
		private:
			element* ptr_ = nullptr;

			friend queue;
		};

		forward_iterator begin();
		forward_iterator end();

		void insert(forward_iterator& it, const T& value);
		void insert_to_num(int pos, const T& value);
		void erase(forward_iterator& it);
		void erase_to_num(int pos);

		void pop();
		void push(const T& value);
		T& top();

	private:
		struct element {
			T value;
			std::unique_ptr<element> next_element = nullptr;
			forward_iterator next();
		};
		std::unique_ptr<element> first = nullptr;
	};

	template <class T>
	typename queue<T>::forward_iterator queue<T>::begin() {
		if (first == nullptr) {
			return nullptr;
		}
		return forward_iterator(first.get());
	}

	template <class T>
	typename queue<T>::forward_iterator queue<T>::end() {
		return forward_iterator(nullptr);
	}

    template <class T>
    void queue<T>::insert_to_num(int pos, const T& value) {
		forward_iterator iter = this->begin();
		for (int i = 0; i < pos; ++i) {
			if (i == pos) {
				break;
			}
			++iter;
		}
		this->insert(iter, value);
	}

	template <class T>
	void queue<T>::insert(containers::queue<T>::forward_iterator& ptr, const T& value) {
		auto val = std::unique_ptr<element>(new element{value});
		forward_iterator it = this->begin();
		if (ptr == this->begin()) {
			val->next_element = std::move(first);
			first = std::move(val);
			return;
		}
		while ((it.ptr_ != nullptr) && (it.ptr_->next() != ptr)) {
			++it;
		}
		if (it.ptr_ == nullptr) {
			throw std::logic_error ("ERROR");
		}
		val->next_element = std::move(it.ptr_->next_element);
		it.ptr_->next_element = std::move(val);
	}

	template <class T>
	void queue<T>::erase_to_num(int pos) {
		forward_iterator iter = this->begin();
		for (int i = 0; i < pos; ++i) {
			if (i == pos) {
				break;
			}
			++iter;
		}
		this->erase(iter);
	}

	template <class T>
	void queue<T>::erase(containers::queue<T>::forward_iterator& ptr) {
		forward_iterator it = this->begin(), end = this->end();
		if (ptr == end) {
			throw std::logic_error("ERROR");
		}
		if (ptr == it) {
			this->pop();
			return;
		}
		while ((it.ptr_ != nullptr) && (it.ptr_->next() != ptr)) {
			++it;
		}
		if (it.ptr_ == nullptr) {
			throw std::logic_error("ERROR");
		}
		it.ptr_->next_element = std::move(ptr.ptr_->next_element);
	}

	template <class T>
	void queue<T>::pop() {
		if (first == nullptr) {
			throw std::logic_error ("queue is empty");
		}
		first = std::move(first->next_element);
	}

	template <class T>
	void queue<T>::push(const T& value) {
		forward_iterator it(nullptr);
		insert(it, value);
	}

	template <class T>
	T& queue<T>::top() {
		if (first == nullptr) {
			throw std::logic_error("queue is empty");
		}
		return first->value;
	}

	template<class T>
    typename queue<T>::forward_iterator queue<T>::element::next() {
        return forward_iterator(this->next_element.get());
    }

    template<class T>
    queue<T>::forward_iterator::forward_iterator(containers::queue<T>::element *ptr) {
        ptr_ = ptr;
    }

    template<class T>
    T& queue<T>::forward_iterator::operator*() {
        return this->ptr_->value;
    }

    template<class T>
    typename queue<T>::forward_iterator& queue<T>::forward_iterator::operator++() {
        if (ptr_ == nullptr) throw std::logic_error ("out of queue borders");
        *this = ptr_->next();
        return *this;
    }

    template<class T>
    typename queue<T>::forward_iterator queue<T>::forward_iterator::operator++(int) {
        forward_iterator old = *this;
        ++*this;
        return old;
    }

    template<class T>
    bool queue<T>::forward_iterator::operator==(const forward_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    template<class T>
    bool queue<T>::forward_iterator::operator!=(const forward_iterator& other) const {
        return ptr_ != other.ptr_;
    }
}

#endif // D_CONTAINERS_QUEUE_HPP_