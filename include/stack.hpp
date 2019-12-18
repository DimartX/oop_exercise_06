#pragma once

#include <memory>
#include <iterator>

namespace bad {
    
    template<class T, class Allocator = std::allocator<T>> 
    class stack{
    private:
        struct node;
        
    public:
        stack() = default;

        struct forward_iterator {

            using value_type = T;
            using reference = T &;
            using pointer = T *;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            forward_iterator(node* ptr) : ptr(ptr) {}; 

            T& operator* (); 
            forward_iterator& operator++ (); 
            forward_iterator operator++ (int);

            forward_iterator operator+ (int id) {
                if (id < 0) {
                    throw 9;
                }
                for (int i = 0; i < id; i++) {
                    if (*this == nullptr) {
                        throw 9;
                    }
                    (*this)++;
                }
                return *this;
            }
            
            
            bool operator== (const forward_iterator& o) const;
            bool operator!= (const forward_iterator& o) const;
            
        private:

            node *ptr;
            friend class stack;
        };
        
        forward_iterator begin(); 
        forward_iterator end();
        size_t size();
        
        void insert(const forward_iterator& it, const T& value); ///
        void erase(const forward_iterator& it); ///
        
        void push(const T& value); 
        void pop(); 
        T& top() const;
    
    private:
        using allocator_type = typename Allocator::template rebind<node>::other;

        struct deleter {
            deleter(allocator_type* allocator): allocator_(allocator) {}

            void operator() (node* ptr) {
                if(ptr != nullptr){
                    std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
                    allocator_->deallocate(ptr, 1);
                }
            }

        private:
            allocator_type* allocator_;

        };

        using unique_ptr = std::unique_ptr<node, deleter>;
        struct node{
            T value;
            unique_ptr nextNode{nullptr,deleter{&this->allocator_}};

            forward_iterator next();

            node(const T &value, unique_ptr next) : value(value), nextNode(std::move(next)) {};
            friend class stack;
        };
        
        allocator_type allocator_{};
        unique_ptr head{nullptr,deleter{&this->allocator_}};
        size_t size_;
    };

    
    template<class T, class Allocator>
    T& stack<T, Allocator>::forward_iterator::operator* () {
        return ptr->value;
    }

    template<class T, class Allocator>
    typename stack<T, Allocator>::forward_iterator& stack<T, Allocator>::forward_iterator::operator++ () {
        *this = ptr->next();
        return *this;
    }

    template<class T, class Allocator>
    typename stack<T, Allocator>::forward_iterator stack<T, Allocator>::forward_iterator::operator++ (int) {
        forward_iterator prev = *this;
        ++(*this);
        return prev;
    }
    


    template<class T, class Allocator>
    bool stack<T, Allocator>::forward_iterator::operator!= (const forward_iterator &o) const {
        return ptr != o.ptr;
    }

    template<class T, class Allocator>
    bool stack<T, Allocator>::forward_iterator::operator== (const forward_iterator &o) const {
        return ptr == o.ptr;
    }
    
    template<class T, class Allocator>
    typename stack<T, Allocator>::forward_iterator stack<T, Allocator>::begin() {
        return head.get();
    }

    template<class T, class Allocator>
    typename stack<T, Allocator>::forward_iterator stack<T, Allocator>::end() {
        return nullptr;
    }

    template<class T, class Allocator>
    size_t stack<T, Allocator>::size() {
        return size_;
    }
    
    template<class T, class Allocator>
    typename stack<T, Allocator>::forward_iterator stack<T, Allocator>::node::next() {
        return {nextNode.get()};
    }

    template<class T, class Allocator>
    void stack<T, Allocator>::insert(const forward_iterator& it, const T& value) {
        if (it == this->begin()) {
            this->push(value);
            return;
        }
        
        forward_iterator tmp = this->begin();
        while (tmp.ptr->next() != it) {
            tmp++;
        }
        
        node* newptr = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::
            construct(this->allocator_, newptr, value,
                      std::unique_ptr<node,deleter>(nullptr, deleter{&this->allocator_}));
        unique_ptr newNode(newptr, deleter{&this->allocator_});        

        newNode->nextNode = std::move(tmp.ptr->nextNode);
        tmp.ptr->nextNode = std::move(newNode);
        
        ++size_;
    }

    template<class T, class Allocator> 
    void stack<T, Allocator>::erase(const forward_iterator& it) {
        if (it == nullptr) {
            throw 11;
        }
        if (it == this->begin()) {
            head = std::move(head->nextNode);
            return;
        }

        forward_iterator tmp = this->begin();
        while (tmp.ptr->next() != it) {
            tmp++;
        }

        tmp.ptr->nextNode = std::move(it.ptr->nextNode);
    }

    template<class T, class Allocator>
    void stack<T, Allocator>::push(const T& value) {
        node* newptr = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::
            construct(this->allocator_, newptr, value,
                      std::unique_ptr<node,deleter>(nullptr, deleter{&this->allocator_}));
        unique_ptr newNode(newptr, deleter{&this->allocator_});
        if (size_ == 0) {
            head = std::move(newNode);
        }
        else {
            newNode->nextNode = std::move(head);
            head = std::move(newNode);
        }
        ++size_;
    }

    template<class T, class Allocator>
    void stack<T, Allocator>::pop() {
        if (size_ == 0) {
            throw 4;
        }
        head = std::move(head->nextNode);
        --size_;
    }

    template<class T, class Allocator>
    T& stack<T, Allocator>::top() const{
        if (size_ == 0) {
            throw 5;
        }
        return head->value;
    }
}



