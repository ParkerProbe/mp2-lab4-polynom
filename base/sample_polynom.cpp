#include "eq_exception.h"
#include "polynom.h"
#include <cstdio>
#include <iostream>
#include <ostream>

int main()
{
  std::cout << "Welcome to the program for Analytical Transformations"
               "Polynomials From Several Variables";
  std::cout << std::endl;

c:
  try {
    std::string tmp1, tmp2;
    std::cout << "Enter first polynom:" << std::endl;
    std::getline(std::cin, tmp1);
    std::cout << "Enter second polynom:" << std::endl;
    std::getline(std::cin, tmp2);
    Polynom p1((std::string(tmp1)));
    Polynom p2((std::string(tmp2)));

    p2.CalculateInPoint(2.0, 3.0, 4.0);
    p1 += p1 + p2;

    std::string path;

f:
    try {

      std::cout << "Enter path for write to" << std::endl;
      std::getline(std::cin, path);
      p1.WriteToFile(path);
      std::cout << p1 << std::endl;
    }
    catch(EqException& e) {
      std::cout << "Warning:" << e.GetComment() << std::endl;
      std::cout << "Please enter another path" << std::endl;
      goto f;
    }
  }
  catch(EqException& e) {
    if(e.error == EqException::calcluate_empty_expression) {
      std::cout << "Warning:" << e.GetComment() << std::endl;
      std::cout << "Please enter polynom again" << std::endl;
      goto c;
    }

    if(e.error == EqException::incorrect_operation) {
      std::cout << "Error:" << e.GetComment() << std::endl;
      return 1;
    }

    if(e.error == EqException::out_of_range) {
      std::cout << "Error:" << e.GetComment() << std::endl;
      return 1;
    }
  }
  catch(std::bad_alloc& e) {
    std::cout << "Error:" << "Dynamic Memory allocation error" << std::endl;
    return 1;
  }

  return 0;
}
