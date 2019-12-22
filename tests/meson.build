all_test_deps = []
all_test_dep_libs = []
project_test_sources = []

boost_test_dep = dependency('boost', modules: ['unit_test_framework'])

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
