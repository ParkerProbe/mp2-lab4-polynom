
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
  int b = ((mnm.degree - c) / BASE) % BASE;
  int a = (( mnm.degree - b - c) / BASE / BASE);
  std::string out;

  if(a + b + c  ==  0) {
    os << std::to_string(mnm.coef);
    return os;
  }

  out += std::to_string(mnm.coef);
  
  if(a != 0)
     out += "x" + std::to_string(a);
  if(b != 0)
     out += "y" + std::to_string(b);
  if(c != 0)
     out += "z" + std::to_string(c);
  os << out;
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
    if(c == 'x' || c == 'y' || c == 'z')
      break;
    tmp += c;
    i++;
  }
  
  if (tmp ==  "-") {
    mnm.coef = -1.0;
  }
  else if (tmp.size() > 0) {
    mnm.coef = std::stod(tmp);
  }
  else {
    mnm.coef = 1.0;
  }

  // Search deg`s
  tmp.clear();


  if (smon.size() - i == 0)
    mnm.degree = 0;

  for(int j = i; j < smon.size(); j++) {
    if(smon[j] == 'x') {
      for (int k = j + 1; k < smon.size(); k++) {
        if (k < smon.size()) {
          if (smon[k] == 'y' || smon[k] == 'z') {
            break;
          }
          tmp += smon[k];
        }
      }
      if (!tmp.size()) {
        mnm.degree += 1 * BASE * BASE;
      }
      else {
        mnm.degree += std::stoi(tmp) * BASE * BASE;
        tmp.clear();
      }
    }

    else if(smon[j] == 'y') {
      for (int k = j + 1; k < smon.size(); k++) {
        if (k < smon.size()) {
          if (smon[k] == 'z') {
            break;
          }
          tmp += smon[k];
        }
      }
      if (!tmp.size()) {
        mnm.degree += 1 * BASE;
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
  std::istringstream is(polynom_str);
  operator>>(is, *this);
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
    if (it != pl.polynom.begin()) {
      if ((*it).GetCoef() > 0) {
        std::cout << "+";
      }
    }
    os << *it;
  }

  return os;
}

std::istream& operator>>(std::istream& is, Polynom& pl)
{
  std::string polynom_str;

  pl.polynom.EraseList();

  std::string tmp;
  while (is >> tmp) {
    polynom_str += tmp;
  }
  tmp.clear();


  // Delete spaces 
  polynom_str.erase(std::remove(polynom_str.begin(), polynom_str.end(), ' '), polynom_str.end());

  int i = 0;
  bool mflag = false;
  while (char c = polynom_str[i]) {
    if (c == '+') {
      if (i != 0) {
        if (mflag) {
          mflag = false;
          tmp.insert(0, std::string("-"));
        }
        std::istringstream istr(tmp);
        Monom tmon;
        operator>>(istr, tmon);
        pl.polynom.AddNode(tmon);
        tmp.clear();
      }
    }
    else if (c == '-') {
      if (i == 0) {
        mflag = true;
        i++;
        continue;
      }

      if (mflag) {
        tmp.insert(0, std::string("-"));
      }

      std::istringstream istr(tmp);
      Monom tmon;
      operator>>(istr, tmon);
      pl.polynom.AddNode(tmon);
      tmp.clear();
      mflag = true;
    }
    else {
      tmp += c;
    }
    i++;
  }
  if (mflag) {
    tmp.insert(0, std::string("-"));
  }
  std::istringstream istr(tmp);
  Monom tmon;
  operator>>(istr, tmon);
  pl.polynom.AddNode(tmon);

  pl.OptimizePolynom();
  return is;
}


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

void Polynom::OptimizePolynom()
{
  bool flag = false;
  TList<Monom>::iterator it3 = polynom.begin();
  for (TList<Monom>::iterator it1 = polynom.begin(); it1 != polynom.end(); ++it1) {

    if (flag) {
      polynom.Erase(it3);
      flag = false;
    }

    if (((*it1).GetCoef() < 0.002) && ((*it1).GetCoef() > -0.002)) {
      flag = true;
      it3 = it1;
      continue;
    }

    TList<Monom>::iterator it2 = it1;
    for (++it2; it2 != polynom.end(); ++it2) {
      if ((*it2).GetDegree() == (*it1).GetDegree()) {
        (*it2) += (*it1);
        if ((*it1).GetCoef() == -(*it2).GetCoef()) {
          polynom.Erase(it2);
        }
        it3 = it1;
        flag = true;
        break;
      }
    }
  }

  if (flag) {
    polynom.Erase(it3);
    flag = false;
  }

  if (polynom.GetSize() == 0)
    polynom.AddNode({ 0,0 });
}

Polynom& Polynom::operator+=(const Polynom& other)
{
  TList<Monom>::iterator iter_lhs = polynom.begin();
  TList<Monom>::iterator iter_rhs = other.polynom.begin();
  while (iter_rhs != other.polynom.end()) {
    polynom.AddNode(*iter_rhs);
    ++iter_rhs;
  }
  polynom = SortPolynom(*this).polynom;
  this->OptimizePolynom();
  return *this;
}

Polynom& Polynom::operator-=(Polynom& other)
{
  TList<Monom>::iterator iter_lhs = polynom.begin();
  TList<Monom>::iterator iter_rhs = other.polynom.begin();
  while (iter_rhs != other.polynom.end()) {
    polynom.AddNode((* iter_rhs)*(-1));
    ++iter_rhs;
  }
  polynom = SortPolynom(*this).polynom;
  this->OptimizePolynom();
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
  this->OptimizePolynom();
  return *this;
}

bool operator==(const Polynom& rhs, const Polynom& lhs)
{
  if (rhs.polynom.GetSize() != lhs.polynom.GetSize())
    return false;
  TList<Monom>::iterator iter_lhs = rhs.polynom.begin();
  TList<Monom>::iterator iter_rhs = lhs.polynom.begin();
  for (; iter_lhs != lhs.polynom.end() || iter_rhs != rhs.polynom.end(); ++iter_lhs, ++iter_rhs) {
    if (((*iter_lhs).GetDegree()) != ((*iter_rhs).GetDegree())) {
      return false;
    }
    if ((*iter_lhs).GetCoef() != (*iter_rhs).GetCoef()) {
      return false;
    }
  }
  return true;
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
  operator>>(in, *this);
  in.close();
}

double Polynom::CalculateInPoint(double x, double y, double z)
{
  if(polynom.GetSize() == 0) {
    throw(EqException(EqException::calcluate_empty_expression,
                      "Polynom is not set"));
  }

  int a, b, c;
  double result = 0;
  for(TList<Monom>::iterator it = polynom.begin(); it != polynom.end(); ++it) {
    c = (*it).GetDegree() % BASE;
    b = (((*it).GetDegree() - c)  / BASE) % BASE;
    a = ((((*it).GetDegree() - b - c) / BASE) / BASE);
    result += (*it).GetCoef() * pow(x, a) * pow(y, b) * pow(z, c);
  }
  return result;
}
