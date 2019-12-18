all_test_deps = []
all_test_dep_libs = []
project_test_sources = []

boost_test_dep = dependency('boost')
#test_main = files('run_tests.cpp')

test_deps = [
    boost_test_dep 
]

test_dep_libs = [
    my_lib
]


# This executable contains all the tests
#project_test_sources += test_main
all_test_deps += test_deps
all_test_dep_libs += test_dep_libs

point_test     = ['point.hpp-test.cpp']
stack_test     = ['stack.hpp-test.cpp']
triangle_test  = ['triangle.hpp-test.cpp']
vector_test    = ['vector.hpp-test.cpp']
main_test      = ['main.cpp-test.cpp']

main_test = executable('main_test', 
    main_test, 
    include_directories : inc,
    dependencies : test_deps, 
    link_with : test_dep_libs)

test('Boost main_test', main_test)

vector_test = executable('vector_test', 
    vector_test, 
    include_directories : inc,
    dependencies : test_deps, 
    link_with : test_dep_libs)

test('Boost vector_test', vector_test)

triangle_test = executable('triangle_test', 
    triangle_test, 
    include_directories : inc,
    dependencies : test_deps, 
    link_with : test_dep_libs)

test('Boost triangle_test', triangle_test)

stack_test = executable('stack_test', 
    stack_test, 
    include_directories : inc,
    dependencies : test_deps, 
    link_with : test_dep_libs)

test('Boost stack_test', stack_test)

point_test = executable('point_test', 
    point_test, 
    include_directories : inc,
    dependencies : test_deps, 
    link_with : test_dep_libs)

test('Boost point_test', point_test)
