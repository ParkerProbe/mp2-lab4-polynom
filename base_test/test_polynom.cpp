#include "gtest.h"
#include "../base/polynom.h"




TEST(Monom, can_add_monoms)
{
  Monom m(2, 123);
  ASSERT_NO_THROW(m + m);
}

TEST(Monom, can_sub_monoms)
{
  Monom m1(10 ,14);
  Monom m2(9, 14);

  Monom res = m1 - m2;

  ASSERT_EQ(1, res.GetCoef());
}

TEST(Monom, can_multiply_monoms)
{
  Monom m1(10, 14);
  Monom m2(10, 14);

  Monom res = m1 * m2;

  ASSERT_EQ(100, res.GetCoef());
}

TEST(Monom, can_multiply_monom_by_const)
{
  Monom m1(10, 14);

  Monom res = m1 * 6;

  ASSERT_EQ(60, res.GetCoef());
}


TEST(Polynom, can_create_polinom)
{
  ASSERT_NO_THROW(Polynom p("x+y"));
}

TEST(Polynom, can_assign_polinoms)
{
  Polynom p1("x+y");
  Polynom p2("x+y+z");
  ASSERT_NO_THROW(p2 = p1);
}

TEST(Polynom, can_add_pol)
{
  std::string pol1 = "-14.88x2y5";
  std::string pol2 = "-14.88x2y5+2";

  Polynom p1(pol1);
  Polynom p2(pol2);

  ASSERT_NO_THROW(p1 + p2);
}

TEST(Polynom, can_sub_pol)
{
  std::string pol1 = "-14.88x2y5";
  std::string pol2 = "-14.88x2y5+2";

  Polynom p1(pol1);
  Polynom p2(pol2);

  ASSERT_NO_THROW(p1 - p2);
}

TEST(polynomial, can_myltiply_pol)
{
  std::string pol1 = "-14.88x2y5";
  std::string pol2 = "-14.88x2y5+2";

  Polynom p1(pol1);
  Polynom p2(pol2);

  ASSERT_NO_THROW(p1 * p2);
}

TEST(polynomial, can_multiply_pol_on_const)
{
  std::string pol1 = "-14.88x2y5";

  Polynom p1(pol1);

  ASSERT_NO_THROW(p1 * 3);
}
