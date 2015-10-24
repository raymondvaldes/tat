//
//  no_execution_context.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

//#define BOOST_TEST_DYN_LINK
//#include <boost/test/unit_test.hpp>
//
//
//#include <boost/coroutine/all.hpp>
//#include <functional>
//#include <iostream>
//
//using boost::coroutines::coroutine;
//
//void cooperative( coroutine< int >::push_type &yield )
//{
//  auto i = 0u;
//  yield(i);
//  
//  std::cout << "Hello";
//  
//  yield(i);
//  
//  std::cout << "world";
//}
//
//
//
//void test()
//{
//  auto generator = coroutine< int >::pull_type(cooperative);
//
//  generator();
//  std::cout << ", ";
//  generator();
//  
//  std::cout << "!\t";
//
//}
//
//
//BOOST_AUTO_TEST_SUITE( boost )
//BOOST_AUTO_TEST_SUITE( context )
//
//BOOST_AUTO_TEST_CASE( coroutine_test )
//{
//  test();
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_SUITE_END()
