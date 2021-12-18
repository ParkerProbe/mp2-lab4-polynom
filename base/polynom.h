#ifndef _POLYNOM_H
#define _POLYNOM_H

#include <iostream>
#include <string>
#include <type_traits>
#include "algorithm"

#include "list.h"

#define BASE 10


class Monom
{
private:
  double coef;
  int degree;
public:
  Monom() : coef(0.0), degree(0)
    {}

  Monom(double _coef, int _degree) : coef(_coef), degree(_degree)
    {}

  Monom(const Monom& other) = default;

  friend std::ostream& operator<<(std::ostream& os,  const Monom& mnm);
  friend std::istream& operator>>(std::istream& is,  Monom& mnm);

  Monom& operator=(const Monom& other) = default;
  Monom& operator+=(const Monom& other);
  Monom& operator*=(double num);
  Monom& operator-=(const Monom& other);
  Monom& operator*=(const Monom& other);

  bool operator<(const Monom& other) const;

  inline int GetDegree() const
  {
    return degree;
  }

  inline double GetCoef() const
  {
    return coef;
  }
};

Monom operator+(const Monom& lhs, const Monom& rhs);
Monom operator*(const Monom& lhs, const Monom& rhs);
Monom operator*(double lhs, const Monom& rhs);
Monom operator*(const Monom& lhs, double rhs);
Monom operator-(const Monom& lhs, const Monom& rhs);


class Polynom
{
private:
  TList<Monom> polynom;

public:

  Polynom() : polynom() {}
  Polynom(const TList<Monom>& pl) : polynom(pl) {}
  Polynom(std::string  polynom_str);
  Polynom(const Polynom& other) = default;

  friend std::ostream& operator<<(std::ostream& os,  const Polynom& pl);
  friend std::istream& operator>>(std::istream& is,  Polynom& pl);
  friend bool operator==(const Polynom& rhs, const Polynom& lhs);


  void AddMonom(const Monom& monom);
  Polynom SortPolynom(const Polynom& pl) const;
  double CalculateInPoint(double x, double y, double z);
  void OptimizePolynom();

  
  Polynom& operator=(const Polynom& other) = default;
  Polynom& operator+=(const Polynom& other);
  Polynom& operator*=(const Polynom& other);
  Polynom& operator*=(double num);
  Polynom& operator-=(Polynom& other);

  void WriteToFile(std::string path) const;
  void ReadFromFile(std::string path);
};

bool operator==(const Polynom &rhs,const Polynom& lhs);
Polynom operator+(const Polynom& lhs, const Polynom& rhs);
Polynom operator*(const Polynom& lhs, const Polynom& rhs);
Polynom operator*(const Polynom& lhs, double num);
Polynom operator*(double, const Polynom& rhs);
Polynom operator-(Polynom& lhs, Polynom& rhs);
#endif
