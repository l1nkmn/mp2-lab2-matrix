# CMake generated Testfile for 
# Source directory: C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix
# Build directory: C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(my_tests "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/build/Debug/my_tests.exe")
  set_tests_properties(my_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;54;add_test;C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(my_tests "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/build/Release/my_tests.exe")
  set_tests_properties(my_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;54;add_test;C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(my_tests "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/build/MinSizeRel/my_tests.exe")
  set_tests_properties(my_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;54;add_test;C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(my_tests "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/build/RelWithDebInfo/my_tests.exe")
  set_tests_properties(my_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;54;add_test;C:/Users/Николай/Desktop/lab_test/mp2-lab2-matrix/CMakeLists.txt;0;")
else()
  add_test(my_tests NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
