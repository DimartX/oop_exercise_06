#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE stack
#include <boost/test/unit_test.hpp>
#include "../include/stack.hpp"
#include "../include/triangle.hpp"
#include "../include/allocator.hpp"

#include <vector>

BOOST_AUTO_TEST_SUITE(stack)

constexpr size_t MAX_SIZE = 200;

BOOST_AUTO_TEST_CASE(push)
{
    bad::stack<int, my_allocator<int, MAX_SIZE> > st;
    std::vector<int> v = {5, 2, 4, 1, 3, 6};
    for (size_t i = 0; i < v.size(); i++) {
        st.push(v[i]);
        std::cout << "i = " << i << std::endl;
        for (const auto& tri : st) {
            std::cout << tri << ' ';
        }
        std::cout << std::endl;
        BOOST_CHECK_EQUAL(i + 1, st.size());
        BOOST_CHECK_EQUAL(st.top(), v[i]);
    }
}

BOOST_AUTO_TEST_CASE(pop)
{
    bad::stack<int, my_allocator<int, MAX_SIZE> > st;
    std::vector<int> v = {5, 2, 4, 1, 3, 6};
    for (size_t i = 0; i < v.size(); i++) {
        st.push(v[i]);
    }

    for (size_t i = v.size(); i > 0; i--) {
        BOOST_CHECK_EQUAL(i, st.size());
        BOOST_CHECK_EQUAL(st.top(), v[i-1]);
        st.pop();
    }
    BOOST_CHECK_THROW(st.pop(), int);    
}

void CreateTemplateStack(bad::stack<int, my_allocator<int, MAX_SIZE> >& st) {
    st.insert(st.begin() + 0, 1); // 1
    st.insert(st.begin() + 0, 2); // 2 1
    st.insert(st.begin() + 2, 3); // 2 1 3
    st.insert(st.begin() + 1, 4); // 2 4 1 3
    st.insert(st.begin() + 0, 5); // 5 2 4 1 3
    st.insert(st.begin() + 5, 6); // 5 2 4 1 3 6
}


BOOST_AUTO_TEST_CASE(insert)
{
    bad::stack<int, my_allocator<int, MAX_SIZE> > st;
    CreateTemplateStack(st);

    std::vector<int> v = {5, 2, 4, 1, 3, 6};    
    
    BOOST_CHECK_THROW(st.insert(st.begin() + 7, 10), int);

    for (size_t i = 0; i < v.size(); i++) {
        BOOST_CHECK_EQUAL(st.top(), v[i]);
        st.pop();
    }
}

void EraseElement(bad::stack<int, my_allocator<int, MAX_SIZE> >& st, std::vector<int> v, size_t id) {
    st.erase(st.begin() + id);
    v.erase(v.begin() + id);
    for (size_t i = 0; i < v.size(); i++) {
        BOOST_CHECK_EQUAL(st.top(), v[i]);
        BOOST_CHECK_EQUAL(v.size() - i, st.size());
        st.pop();
    }
}

BOOST_AUTO_TEST_CASE(erase)
{
    bad::stack<int, my_allocator<int, MAX_SIZE> > st;
    std::vector<int> v = {5, 2, 4, 1, 3, 6};
    CreateTemplateStack(st);
    EraseElement(st, v, 3);
    CreateTemplateStack(st);
    EraseElement(st, v, 0);
    CreateTemplateStack(st);
    EraseElement(st, v, 5);
    CreateTemplateStack(st);
    EraseElement(st, v, 2);
    CreateTemplateStack(st);
    EraseElement(st, v, 4);
    CreateTemplateStack(st);
    BOOST_CHECK_THROW(st.erase(st.begin() + 6), int);
}


BOOST_AUTO_TEST_SUITE_END()
