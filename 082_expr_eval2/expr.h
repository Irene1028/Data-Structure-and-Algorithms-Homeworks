#include <sstream>
#include <string>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};
class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;  //put number in stream, then return it
    return ss.str();
  }
  //virtual ~NumExpression() {}
};

class commonExpression : public Expression
{
 private:  //why not protected?
  Expression * leftop;
  Expression * rightop;
  const char * optr;  //what if it is not const?
 public:
  commonExpression(Expression * lhs, Expression * rhs, const char * op) :
      leftop(lhs),
      rightop(rhs),
      optr(op) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << leftop->toString() << *optr << rightop->toString() << ')';
    return ss.str();
  }
  virtual ~commonExpression() {
    delete leftop;
    delete rightop;
    //why not delete optr?
  }
};
class PlusExpression : public commonExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : commonExpression(lhs, rhs, "+") {}
};
class MinusExpression : public commonExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : commonExpression(lhs, rhs, "-") {}
};
class TimesExpression : public commonExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : commonExpression(lhs, rhs, "*") {}
};
class DivExpression : public commonExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : commonExpression(lhs, rhs, "/") {}
};
