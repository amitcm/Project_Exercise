#include <iostream.h>
#include "bigint.h"
#include <string.h>
#include <stdlib.h>
#include "bool.h"


const int BASE = 10;

// author: Owen Astrachan
//
// BigInts are implemented using a AVector<char> to store
// the digits of a BigInt
// Currently a number like 1,234 is stored as the vector {4,3,2,1}
// i.e., the least significant digit is the first digit in the vector
// however all operations on digits should be done using private
// helper functions:
//
// int  getDigit(k)        -- return k-th digit
// void changeDigit(k,val) -- set k-th digit to val
// void addSigDigit(val)   -- add new most significant digit val
//
// by performing all ops in terms of these private functions we
// make implementation changes simpler
// 
// I/O operations are facilitated by the toString() member function
// which converts a BigInt to its string (ASCII) representation


static const int INITIAL_SIZE = 5;    // and now i just type over what is here already

BigInt::BigInt()
// postcodition: bigint initialized to 0
   : myIsNegative(false),
     myDigits(INITIAL_SIZE,0),
     myNumDigits(1)
{

#ifdef DEBUG
    cerr << "default constructor called" << endl;
#endif

}

BigInt::BigInt(int num)
// postcondition: bigint initialized to num
   : myIsNegative(false),
     myDigits(INITIAL_SIZE,0),
     myNumDigits(0)
{
#ifdef DEBUG    
    cerr << "int constructor called\t" << num << endl;
#endif
    
    // check if num is negative, change state and num accordingly
    
    if (num < 0)
    {
        myIsNegative = true;
        num = -1 * num;
    }

    // handle least-significant digit of num (handles num == 0)
    
    addSigDigit(num % BASE);
    num = num / BASE;
    
    // handle remaining digits of num
    if (num < 0)
    {
        myIsNegative = true;
        num = -1 * num;
    }
    
    while (num != 0)
    {
        addSigDigit(num % BASE);
        num = num / BASE;
    }
}

BigInt::~BigInt()
// postcondition:  digit sequence cleared
{

#ifdef DEBUG    
    cerr << "destructor called " << *this << endl;
#endif
    myNumDigits = 0;
}

BigInt::BigInt(const BigInt & big)
// copy constructor
// postcondition: bigint initialized to big

   : myIsNegative(big.myIsNegative),
     myDigits(big.myDigits),
     myNumDigits(big.myNumDigits)
{
    
#ifdef DEBUG    
    cerr << "\tcopy constructor called\t" << big << endl;
#endif

}

BigInt::BigInt(const string & s)
// precondition: s consists of digits only (no leading zeros)
// postcondition: bigint initialized to integer represented by s
  : myIsNegative(false),
    myDigits(s.length(),0),
    myNumDigits(0)
{

#ifdef DEBUG    
    cerr << "string constructor called\t" << s << endl;
#endif

    int k;
    int limit = 0;

    if (s.length() == 0)
    {
        myDigits.resize(INITIAL_SIZE);
        addSigDigit(0);
        return;
    }
    if (s[0] == '-')
    {
        myIsNegative = true;
        limit = 1;
    }
    // start at least significant digit
    
    for(k=s.length() - 1; k >= limit; k--)
    {
        addSigDigit(s[k]-'0');
    }
    Normalize();
}

BigInt & BigInt::operator = (const BigInt & big)
// postcondition: bigint is equal to big     
{

#ifdef DEBUG    
    cerr << "operator = called\t" << big << endl;
#endif
    
    if (this != &big)              // watch for aliasing
    {
        myDigits = big.myDigits;
        myIsNegative = big.myIsNegative;
        myNumDigits = big.myNumDigits;
    }
    return *this;
}

BigInt & BigInt::operator -=(const BigInt & rhs)
// precondition: bigint = a
// postcondition: bigint = a - rhs   
{
    int diff;
    int borrow = 0;

    int k;
    int len = size();

    if (this == &rhs)         // subtracting self?
    {
        *this = 0;
        return *this;
    }

    // signs opposite? then x - (-y) = x + y
    
    if (IsNeg() != rhs.IsNeg())
    {
        return operator +=(-1 * rhs);
    }
    // signs are the same, check which number is larger
    // since sign can change when subtracting
    // examples: 7 - 3 no sign change,     3 - 7 sign changes
    //          -7 - (-3) no sign change, -3 -(-7) sign changes
    if (! IsNeg() && (*this) < rhs ||
          IsNeg() && (*this) > rhs)
    {
        *this = rhs - *this;
        myIsNegative = ! myIsNegative;
        return *this;
    }
    for(k=0; k < len; k++)
    {
        diff = getDigit(k) - rhs.getDigit(k) - borrow;
        borrow = 0;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        changeDigit(k,diff);
    }
    Normalize();
    return *this;
}


BigInt & BigInt::operator +=(const BigInt & rhs)
// precondition: bigint = a
// postcondition: bigint = a + rhs, result returned
{

    int sum;
    int carry = 0;

    int k;
    int len = size();              // length of larger addend

    if (this == &rhs)              // to add self, multiply by 2
    {
        return operator *=(2);
    }
    
    if (IsNeg() != rhs.IsNeg())   // signs not the same, subtract
    {
        *this -= (-1 * rhs);
        return *this;
    }

    // process both numbers until one is exhausted

    if (len < rhs.size())
    {
        len = rhs.size();
    }
    for(k=0; k < len; k++)
    {
        sum = getDigit(k) + rhs.getDigit(k) + carry;
        carry = sum / BASE;
        sum = sum % BASE;

        if (k < myNumDigits)
        {
            changeDigit(k,sum);
        }
        else
        {
            addSigDigit(sum);
        }
    }
    if (carry != 0)
    {
        addSigDigit(carry);
    }
    return *this;    
}

BigInt operator +(const BigInt & lhs, const BigInt & rhs)
// postcondition: return bigint == lhs + rhs     
{
    BigInt result(rhs);
    result += lhs;
    return result;
}

BigInt operator -(const BigInt & lhs, const BigInt & rhs)
// postcondition: return bigint == lhs + rhs     
{
    BigInt result(lhs);
    result -= rhs;
    return result;
}

ostream & BigInt::Print(ostream & os) const
// postcondition: BigInt inserted onto stream os
{
    os << toString();
    return os;
}

string BigInt::toString() const
// postcondition: returns string equivalent of BigInt
{
    int k;
    int len = size();
    string s = "";
    if (IsNeg())
    {
        s = "-";
    }
    for(k=len-1; k >= 0; k--)
    {
        s += char('0'+getDigit(k));
    }
    return s;
}

ostream & operator <<(ostream & out, const BigInt & big)
// postcondition: digits printed most-to-least significant
{
    return big.Print(out);
}

istream & operator >> (istream & in, BigInt & big)
// postcondition: big extracted from input
//                MUST be whitespace delimited     
{
    string s;
    in >> s;
    big = BigInt(s);
    return in;
}

bool operator == (const BigInt & lhs, const BigInt & rhs)
// postcondition: returns true if lhs == rhs, else return false
{

    if (lhs.size() != rhs.size() || lhs.IsNeg() != rhs.IsNeg())
    {
        return false;
    }
    // assert: same sign, same number of digits;

    int k;
    int len = lhs.size();
    for(k=0; k < len; k++)
    {
        if (lhs.getDigit(k) != rhs.getDigit(k)) return false;
    }

    return true;
}

bool operator != (const BigInt & lhs, const BigInt & rhs)
// postcondition: returns true if lhs != rhs, else returns false     
{
    return ! (lhs == rhs);
}

bool operator < (const BigInt & lhs, const BigInt & rhs)
// postcondition: return true if lhs < rhs, else returns false     
{

    // if signs aren't equal, lhs < rhs only if lhs is negative
    
    if (lhs.IsNeg() != rhs.IsNeg())
    {
        return lhs.IsNeg();         
    }

    // if # digits aren't the same, lhs < rhs if lhs has fewer digits
    
    if (lhs.size() != rhs.size())
    {
        return (lhs.size() < rhs.size() && ! lhs.IsNeg()) ||
               (lhs.size() > rhs.size() && lhs.IsNeg());
    }

    // assert: # digits same, signs the same

    int k;
    int len = lhs.size();

    for(k=len-1; k >= 0; k--)
    {
        if (lhs.getDigit(k) < rhs.getDigit(k)) return ! lhs.IsNeg();
        if (lhs.getDigit(k) > rhs.getDigit(k)) return lhs.IsNeg();
    }
    return false;      // lhs == rhs
}

bool operator > (const BigInt & lhs, const BigInt & rhs)
// postcondition: return true if lhs > rhs, else returns false
{
    return rhs < lhs;    
}

bool operator <= (const BigInt & lhs, const BigInt & rhs)
// postcondition: return true if lhs <= rhs, else returns false
{
    return lhs == rhs || lhs < rhs;
}
bool operator >= (const BigInt & lhs, const BigInt & rhs)
// postcondition: return true if lhs >= rhs, else returns false
{
    return lhs == rhs || lhs > rhs;
}

BigInt & BigInt::operator %=(const BigInt & rhs)
// postcondition: returns BigInt % rhs after modification     
{
    BigInt quotient,remainder;
    bool resultNegative = (IsNeg() != rhs.IsNeg());
    myIsNegative = false;

    // DivideHelp does all the work
    
    if (rhs.IsNeg())
    {
        DivideHelp(*this,-1 * rhs,quotient,remainder);
    }
    else
    {
        DivideHelp(*this,rhs,quotient,remainder);       
    }
    *this = remainder;
    myIsNegative = resultNegative;        
    return *this;
}


void BigInt::DivideHelp(const BigInt & lhs, const BigInt & rhs,
                        BigInt & quotient, BigInt & remainder)
// postcondition: quotient = lhs / rhs
//                remainder = lhs % rhs     
{
    if (lhs < rhs)             // integer division yields 0
    {                          // so avoid work and return
        quotient = 0;        
        remainder = lhs;       // lhs, not rhs!  -- Mic
        return;
    }
    else if (lhs == rhs)       // again, avoid work in special case
    {
        quotient = 1;
        remainder = 0;
        return;
    }
    
    BigInt dividend(lhs);      // make copies because of const-ness
    BigInt divisor(rhs);
    quotient = remainder = 0;
    int k,trial;
    int zeroCount = 0;

    // pad divisor with zeros until # of digits = dividend
    
    while (divisor.size() < dividend.size())
    {
        divisor *= 10;
        zeroCount++;
    }

    // if we added one too many zeros chop one off
    
    if (divisor > dividend)
    {
        divisor /= 10;
        zeroCount--;
    }


    // algorithm: make a guess for how many times dividend part
    // goes into divisor, adjust the guess, subtract out and repeat
    
    int divisorSig = divisor.getDigit(divisor.size()-1);
    int dividendSig;
    BigInt hold;    
    for(k=0; k <= zeroCount; k++)
    {
        dividendSig = dividend.getDigit(dividend.size()-1);
        trial =
            (dividendSig*10 + dividend.getDigit(dividend.size()-2))
            /divisorSig;
        
        if (BASE <= trial)   // stay within base
        {
            trial = BASE-1;
        }
        while ((hold = divisor * trial) > dividend)
        {
            trial--;
        }

        // accumulate quotient by adding digits to quotient
        // and chopping them off of divisor after adjusting dividend
        
        quotient *= 10;
        quotient += trial;
        dividend -= hold;
        divisor /= 10;       
        divisorSig = divisor.getDigit(divisor.size()-1);        
    }
    remainder = dividend;
}

BigInt & BigInt::operator /=(const BigInt & rhs)
// postcondition: return BigInt / rhs after modification
{
    BigInt quotient,remainder;
    bool resultNegative = (IsNeg() != rhs.IsNeg());
    myIsNegative = false;       // force myself positive

    // DivideHelp does all the work
    
    if (rhs.IsNeg())
    {
        DivideHelp(*this,-1*rhs,quotient,remainder);
    }
    else
    {
        DivideHelp(*this,rhs,quotient,remainder);       
    }
    *this = quotient;
    myIsNegative = resultNegative;
    Normalize();
    return *this;
}

BigInt operator / (const BigInt & lhs, const BigInt & rhs)
// postcondition: return lhs / rhs
{
    BigInt result(lhs);
    result /= rhs;
    return result;
}

BigInt & BigInt::operator /=(int num)
// precondition: 0 < num < BASE     
// postcondition: returns BigInt/num after modification
{
    int carry = 0;
    int quotient;
    int k;
    int len = size();

    if (num > BASE)     // check precondition
    {
        return operator /= (BigInt(num));
    }
    if (0 == num)       // handle division by zero (not fully implemented)
    {
        myError = infinity;
    }
    else
    {
        for(k=len-1; k >= 0; k--)  // once for each digit
        {
            quotient = (10*carry + getDigit(k));
            carry = quotient % num;
            changeDigit(k, quotient / num);
        }
    }
    Normalize();
    return *this;
}

void BigInt::Normalize()
// postcondition: all leading zeros removed     
{
    int k;
    int len = size();
    for(k=len-1; k >= 0; k--)        // find a non-zero digit
    {
        if (getDigit(k) != 0) break;
        myNumDigits--;               // "chop" off zeros
    }
    if (k < 0)    // all zeros
    {
        myNumDigits = 1;
        myIsNegative = false;
    }
}


BigInt & BigInt::operator *=(int num)
// precondition: 0 <= num < BASE
// postcondition: returns num * value of BigInt after multiplication
// note: works for values of num as long as num * one digit
//       does not result in overflow, precondition is overly
//       restrictive     
{
    int carry = 0;
    int product;               // product of num and one digit + carry
    int k;
    int len = size();
    
    if (0 == num)              // treat zero as special case and stop
    {
        *this = 0;
        return *this;
    }

    if (BASE*BASE <= num)        // handle pre-condition failure
    {
        *this *= BigInt(num);
        return *this;
    }
    
    // make sure that my sign is properly set: positive/negative

    myIsNegative = (IsNeg() && 0 < num) || (! IsNeg() && num < 0);

    if (1 == num)              // treat one as special case, no work
    {
        return *this;
    }

    if (num < 0)               // sign already changed, make positive
    {
        num = -1 * num;
    }
    
    for(k=0; k < len; k++)     // once for each digit
    {
        product = num * getDigit(k) + carry;
        carry = product/BASE;
        changeDigit(k,product % BASE);
    }
    
    while (carry != 0)         // carry all digits
    {
        addSigDigit(carry % BASE);
        carry /= BASE;
    }
    return *this;
}


BigInt operator *(const BigInt & a, int num)
// postcondition: returns a * num     
{
    BigInt result(a);
    result *= num;
    return result;
}

BigInt operator /(const BigInt & a, int num)
// postcondition: returns a / num     
{
    BigInt result(a);
    result /= num;
    return result;
}

BigInt operator %(const BigInt & lhs, const BigInt & rhs)
// postcondition: returns lhs % rhs     
{
    BigInt result(lhs);
    result %= rhs;
    return result;
}

BigInt operator *(int num, const BigInt & a)
// postcondition: returns num * a     
{
    BigInt result(a);
    result *= num;
    return result;
}


BigInt & BigInt::operator *=(const BigInt & big)
// precondition: bigint = a
// postcondition: bigint = a*big     
{
    // uses standard "grade school method" for multiplyin
    
    myIsNegative = (IsNeg() != big.IsNeg());   // is result negative?
    BigInt self(*this);                        // copy of self
    BigInt sum(0);                             // to accumulate sum
    int k;
    int len = big.size();                      // # digits in multiplier
    
    for(k=0; k < len; k++)
    {
        sum += self * big.getDigit(k);         // k-th digit * self
        self *= 10;                            // add a zero
    }
    *this = sum;
    return *this;
}

BigInt operator *(const BigInt & lhs, const BigInt & rhs)
// postcondition: return bigint == lhs * rhs
{
    BigInt result(lhs);
    result *= rhs;
    return result;
}

int BigInt::size() const
// postcondition: returns # digits in BigInt
{
    return myNumDigits;
}

int BigInt::getDigit(int k) const
// precondition: 0 <= k < size()
// postcondition: returns k-th digit
//                (returns 0 if precondition is false)
{
    if (0 <= k && k < size())
    {
        return myDigits[k] - '0';
    }
    return 0;
}

void BigInt::changeDigit(int digit, int value)
// precondition: 0 <= digit < size()
// postcondition: digit-th digit changed to value     
{
    if (0 <= digit && digit < size())
    {
        myDigits[digit] = char('0' + value);
    }
    else
    {
        cout << "error change " << digit << " " << myNumDigits << endl;
    }
}

void BigInt::addSigDigit(int value)
// postcondition: value added to BigInt as most significant digit     
{
    if (myNumDigits >= myDigits.Length())
    {
        myDigits.resize(myDigits.Length() * 2);
    }
    myDigits[myNumDigits] = char('0' + value);
    myNumDigits++;
}

bool BigInt::IsNeg() const
// postcondition: returns true iff BigInt is negative
{
    return myIsNegative;
}
