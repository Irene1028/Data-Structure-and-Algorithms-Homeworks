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
class PlusExpression : public Expression
{
 private:  //why not protected?
  Expression * leftop;
  Expression * rightop;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : leftop(lhs), rightop(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << leftop->toString() << '+' << rightop->toString() << ')';
    return ss.str();
  }
  virtual ~PlusExpression() {
    delete leftop;
    delete rightop;
  }
};
