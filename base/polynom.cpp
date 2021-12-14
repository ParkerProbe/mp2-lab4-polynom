
#include "polynom.h"
#include "eq_exception.h"
#include "list.h"
#include <fstream>
#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

Monom& Monom::operator+=(const Monom &other)
{
  if(degree != other.degree)
    throw(EqException(EqException::incorrect_operation,
                      "Degree`s are not equal"));
  coef += other.coef;
  return *this;
}

Monom& Monom::operator-=(const Monom &other)
{
  if(degree != other.degree)
    throw(EqException(EqException::incorrect_operation,
                      "Degree`s are not equal"));
  coef -= other.coef;
  return *this;
}

Monom& Monom::operator*=(const Monom &other)
{
  coef *= other.coef;
  degree += other.degree;
  return *this;
}

Monom& Monom::operator*=(double num)
{
  coef *= num;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Monom& mnm)
{
  int c = mnm.degree % BASE;
  int b = (mnm.degree / BASE) % BASE;
  int a = ((mnm.degree / BASE) / BASE) % BASE;
  std::string out;

  if(a == b == c == 0) {
    os << "0";
    return os;
  }
  out += std::to_string(mnm.coef);
  if(a != 0)
     out += "x" + std::to_string(a);
  if(b != 0)
     out += "x" + std::to_string(a);
  if(c != 0)
     out += "x" + std::to_string(a);
  os << out;
  os << "\n";
  return os;
}

std::istream& operator>>(std::istream& is,  Monom& mnm)
{
  std::string smon;
  is >> smon;
  int i = 0;
  std::string tmp;

  // Search coefficient
  while(char c = smon[i]) {
    if(c == 'x' || c =='y' || c== 'z')
      break;
    tmp += c;
    i++;
  }
  if(tmp.size() > 0)
    mnm.coef = std::stod(tmp);
  else {
    mnm.coef = 1.0;
  }

  // Search deg`s
  tmp.clear();

  for(int j = i; j < smon.size(); j++) {
    if(smon[j] == 'x') {
      for (int k = j + 1; k < smon.size(); k++) {
        if (k < smon.size()) {
          if (smon[k] != 'y') {
            break;
          }
          tmp += smon[k];
        }
      }
      if (!tmp.size()) {
        mnm.degree += 1;
      }
      else {
        mnm.degree += std::stoi(tmp) * BASE * BASE;
        tmp.clear();
      }
    }

    else if(smon[j] == 'y') {
      for (int k = j + 1; k < smon.size(); k++) {
        if (k < smon.size()) {
          if (smon[k] != 'y') {
            break;
          }
          tmp += smon[k];
        }
      }
      if (!tmp.size()) {
        mnm.degree += 1;
      }
      else {
        mnm.degree += std::stoi(tmp) * BASE;
        tmp.clear();
      }
    }

    else if (smon[j] == 'z') {
      for (int k = j + 1; k < smon.size(); k++) {
        tmp += smon[k];
      }
      if (!tmp.size()) {
        mnm.degree += 1;
      }
      else {
        mnm.degree += std::stoi(tmp);
      }
    }
  }
  return is;
}

Monom operator+(const Monom &lhs, const Monom &rhs)
{
  Monom tmp(lhs);
  return (tmp += rhs);
}

Monom operator-(const Monom &lhs, const Monom &rhs)
{
  Monom tmp(lhs);
  return (tmp -= rhs);
}

Monom operator*(const Monom &lhs, const Monom &rhs)
{
  Monom tmp(lhs);
  return (tmp *= rhs);
}

Monom operator*(double lhs, const Monom &rhs)
{
  Monom tmp(rhs);
  return (tmp *= lhs);
}

Monom operator*(const Monom &lhs, double rhs)
{
  Monom tmp(lhs);
  return (tmp *= rhs);
}

Monom operator/(const Monom &lhs, const Monom &rhs)
{
  Monom tmp(lhs);
  return (tmp *= rhs);
}

bool Monom::operator<(const Monom& other) const
{
  return degree < other.degree;
}

void Polynom::AddMonom(const Monom& monom)
{
  polynom.AddNode(monom);
}

Polynom::Polynom(std::string polynom_str)
{
  std::string tmp;
  int i = 0;
  while(char c = polynom_str[i]) {
    if(c == '+') {
      std::istringstream istr(tmp);
      Monom tmon;
      operator>>(istr,tmon);
      polynom.AddNode(tmon);
      tmp.clear();
    }
    else {
      tmp += c;
    }
    i++;
  }
  std::istringstream istr(tmp);
  Monom tmon;
  operator>>(istr, tmon);
  polynom.AddNode(tmon);
}

std::ostream& operator<<(std::ostream& os,  const Polynom& pl)
{
  if (pl.polynom.GetSize() == 0) {
    os << "0";
    return os;
  }

  int c = pl.polynom.GetSize();

  for(TList<Monom>::iterator it = pl.polynom.begin();
      it != pl.polynom.end(); ++it)
  {
    os << *it;
    c--;
    if(c)
      os << "+";
  }

  return os;
}

std::istream& operator>>(std::istream& is,  Polynom& pl)
{
  TList<Monom> Tpl;
  pl.polynom = Tpl;

  std::string tmp;
  while(is >> tmp) {
    if(tmp != "+") {
      std::istringstream istr(tmp);
      Monom tmon;
      operator>>(istr,tmon);
      pl.polynom.AddNode(tmon);
      tmp.clear();
    }
    else {
      tmp.clear();
    }
  }
  return is;
}

//Need to Optimize
Polynom Polynom::SortPolynom(const Polynom& pl) const
{
  std::vector<Monom> vec_tmp;
  for (TList<Monom>::iterator it = pl.polynom.begin();
       it != pl.polynom.end(); ++it)
  {
    vec_tmp.push_back(*it);
  }
  std::sort(vec_tmp.begin(), vec_tmp.end());
  Polynom tpoly;
  for (Monom& tmp : vec_tmp) {
    tpoly.AddMonom(tmp);
  }
  return tpoly;
}


Polynom& Polynom::operator+=(const Polynom& other)
{

  polynom = SortPolynom(*this).polynom;
  Polynom oth = SortPolynom(other);

  TList<Monom>::iterator iter_lhs = polynom.begin();
  TList<Monom>::iterator iter_rhs = oth.polynom.begin();
  while ((iter_lhs != polynom.end()) && (iter_rhs != oth.polynom.end())) {
    if ((*iter_lhs).GetDegree() > (*iter_rhs).GetDegree()) {
      ++iter_rhs;
      continue;
    }
    if (((*iter_lhs).GetDegree() == (*iter_rhs).GetDegree())) {
      if (((*iter_lhs).GetCoef() + (*iter_rhs).GetCoef()) != 0) {
        *iter_lhs += *iter_rhs;
        ++iter_rhs;
        ++iter_lhs;
        continue;
      }
    }
    if ((*iter_lhs).GetDegree() < (*iter_rhs).GetDegree()) {
      iter_lhs = polynom.Insert(iter_lhs, *iter_rhs);
      ++iter_rhs;
      ++iter_lhs;
    }
  }
  while (iter_rhs != oth.polynom.end()) {
    polynom.AddNode(*iter_rhs);
    ++iter_rhs;
  }
  return *this;
}

Polynom& Polynom::operator-=(Polynom& other)
{
  polynom = SortPolynom(*this).polynom;
  Polynom oth = SortPolynom(other);

  TList<Monom>::iterator iter_lhs = polynom.begin();
  TList<Monom>::iterator iter_rhs = oth.polynom.begin();

  while ((iter_lhs != polynom.end()) && (iter_rhs != oth.polynom.end())) {
    if ((*iter_lhs).GetDegree() > (*iter_rhs).GetDegree()) {
      ++iter_rhs;
      continue;
    }
    if (((*iter_lhs).GetDegree() == (*iter_rhs).GetDegree())) {
      if (((*iter_lhs).GetCoef() + (*iter_rhs).GetCoef()) != 0) {
        *iter_lhs += *iter_rhs;
        ++iter_rhs;
        ++iter_lhs;
        continue;
      }
    }
    if ((*iter_lhs).GetDegree() < (*iter_rhs).GetDegree()) {
      iter_lhs = polynom.Insert(iter_lhs, (*iter_rhs)*(-1));
      ++iter_rhs;
      ++iter_lhs;
    }
  }
  while (iter_rhs != oth.polynom.end()) {
    polynom.AddNode(*iter_rhs *(-1));
    ++iter_rhs;
  }
  return *this;
}

Polynom& Polynom::operator*=(const double num)
{
  for (TList<Monom>::iterator it = polynom.begin(); it != polynom.end(); ++it) {
    *it *= num;
  }
  return *this;
}

Polynom& Polynom::operator*=(const Polynom& other)
{
  Polynom out;
  TList<Monom>::iterator iter_lhs = polynom.begin();
  TList<Monom>::iterator iter_rhs = other.polynom.begin();
  while(iter_rhs != other.polynom.end()) {
    iter_lhs = polynom.begin();
    while(iter_lhs != polynom.end()) {
      out.polynom.AddNode(*iter_rhs * *iter_lhs);
      ++iter_lhs;
    }
    ++iter_rhs;
  }
  std::swap(*this, out);
  return *this;
}

Polynom operator+(const Polynom& lhs, const Polynom& rhs)
{
  Polynom temp(lhs);
  return temp += rhs;
}

Polynom operator-(Polynom& lhs, Polynom& rhs)
{
  Polynom temp(lhs);
  return temp -= rhs;
}

Polynom operator*(const Polynom& lhs, const Polynom& rhs)
{
  Polynom temp(lhs);
  return temp *= rhs;
}

Polynom operator*(const Polynom& lhs, double num)
{
  Polynom temp(lhs);
  return temp *= num;
}

Polynom operator*(double num, const Polynom& rhs)
{
  Polynom temp(rhs);
  return temp *= num;
}

void Polynom::WriteToFile(std::string path) const
{
  std::ofstream out;
  out.open(path);
  if(!out.is_open())
    throw(EqException(EqException::file_system_error,
                      "Incorrect path or filesystem error"));
  operator<<(out, *this);
  out.close();
}

void Polynom::ReadFromFile(std::string path)
{
  std::ifstream in;
  in.open(path);
  if(!in.is_open())
    throw(EqException(EqException::file_system_error,
                      "Incorrect path or filesystem error"));
  TList<Monom> Tpl;
  polynom = Tpl;

  std::string tmp;
  while(in >> tmp) {
    if(tmp != "+") {
      std::istringstream istr(tmp);
      Monom tmon;
      operator>>(istr,tmon);
      polynom.AddNode(tmon);
      tmp.clear();
    }
    else {
      tmp.clear();
    }
  }
  in.close();
}

double Polynom::CalculateInPoint(double x, double y, double z)
{
  if(x == y == z == 0) {
    return 0;
  }

  if(polynom.GetSize() == 0) {
    throw(EqException(EqException::calcluate_empty_expression,
                      "Polynom is not set"));
  }

  int a, b, c;
  double result = 0;
  for(TList<Monom>::iterator it = polynom.begin(); it != polynom.end(); ++it) {
    c = (*it).GetDegree() % BASE;
    b = ((*it).GetDegree() / BASE) % BASE;
    a = (((*it).GetDegree() / BASE) / BASE) % BASE;
    result += (*it).GetCoef() * pow(x, a) * pow(y, b) * pow(z, c);
  }
  return result;
}
