/*
* BigInt Template (Arbitrary Precision Integer)
 *
 * Features:
 *  - Handles integers beyond 64-bit limits
 *  - Supports: addition, subtraction, multiplication, division, modulo
 *  - Comparison operators (==, !=, <, <=, >, >=)
 *  - Bitwise operations (^, &, |, <<, >>) via base conversion
 *  - Power, GCD, LCM, Square root, and base conversion
 *  - Built-in like usage: increment/decrement, I/O operators, compound operators (+=, -=, etc.)
 *
 * Usage Examples:
 *  BigInt a = 1234567890123456789LL;
 *  BigInt b("999999999999999999999999");
 *  BigInt c = a + b;
 *  BigInt d = pow(a, 10);         // Exponentiation
 *  BigInt g = gcd(a, b);          // Greatest common divisor
 *  BigInt s = sqrt(c);            // Square root
 *
 * Utility:
 *  int BtoI(BigInt x);            // Convert to int (risk of overflow!)
 *  BigInt CB(x, fromBase, toBase); // Change base (max base = 10)
 *  x.popcount();                  // Count 1s in binary representation
 *  x.ctz();                       // Count trailing zeros in binary
 *
 * Input/Output:
 *  cin >> a;
 *  cout << a;
 *
 * Notes:
 *  - Internally stored as deque of digits (base 10 by default)
 *  - Negative numbers supported via `sign` field
 *  - Be mindful of efficiency in tight loops (not optimized like GMP)
 *
 */


// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/BigInt/bigint.cpp
const int Dig = 10;
 
struct BigInt {
	deque<int> num;
	int sign = 1;
 
	//constructor
	BigInt() {
	}
	BigInt(long long x) {
		num.clear();
		if (x < 0)
			sign = -1, x = -x;
		if (x == 0)
			num.push_back(x);
		while (x > 0) {
			num.push_back(x % Dig);
			x /= Dig;
		}
	}
	BigInt(int x) {
		num.clear();
		if (x < 0)
			sign = -1, x = -x;
		if (x == 0)
			num.push_back(x);
		while (x > 0) {
			num.push_back(x % Dig);
			x /= Dig;
		}
	}
	BigInt(string &s) {
		toBig(s);
	}
	BigInt(const BigInt &x) {
		sign = x.sign;
		num = x.num;
	}
 
	// change to int
	friend int BtoI(const BigInt &x) {
		int res = 0, t = 1;
		for (int i = 0; i < x.num.size(); i++)
			res += t * x.num[i];
		return res;
 
	}
 
	//absolut
	friend BigInt abs(const BigInt &x) {
		BigInt res = x;
		res.sign = 1;
		return res;
	}
 
	//clear 0
	void clr() {
		while (!num.empty() and !num.back())
			num.pop_back();
	}
 
	//normalize
	void normalize() {
		(*this).clr();
		int carry = 0;
		for (int i = 0; i < num.size(); i++) {
			int t = num[i] + carry;
			if (t < 0) {
				t += Dig;
				carry = -1;
				num[i] = t;
			}
			else {
				num[i] = t % Dig;
				carry = t / Dig;
			}
		}
		if (carry > 0)
			num.push_back(carry);
		if (carry < 0) {
			sign *= -1;
			num.push_back(-carry);
		}
		(*this).clr();
		if (num.empty())
			sign = 1;
 
	}
 
	//is 0
	bool isZero() {
		(*this).normalize();
		return num.empty();
	}
 
	//compare operators
	bool operator<(const BigInt &x) const {
		BigInt a = (*this);
		BigInt b = x;
		a.normalize();
		b.normalize();
		if (a.sign != b.sign)
			return a.sign < b.sign;
		bool res = false, flag = false;
		if (a.num.size() != b.num.size()) {
			res = (a.num.size() < b.num.size());
			flag = true;
		}
		else {
			for (int i = a.num.size() - 1; i >= 0; i--)
				if (a.num[i] != b.num[i]) {
					flag = true;
					res = (a.num[i] < b.num[i]);
					break;
				}
		}
		if (!flag)
			return false;
		if (sign == -1)
			return !res;
		return res;
	}
	bool operator==(const BigInt &x) const {
		BigInt a = (*this);
		BigInt b = x;
		a.normalize();
		b.normalize();
		if (a.sign == b.sign and a.num.size() == b.num.size()) {
			bool res = true;
			for (int i = 0; i < a.num.size() and res; i++)
				if (a.num[i] != b.num[i])
					res = false;
			return res;
		}
		else
			return false;
	}
	bool operator<=(const BigInt &x) const {
		return (((*this) < x) or ((*this) == x));
	}
	bool operator>(const BigInt &x) const {
		return (!((*this) <= x));
	}
	bool operator>=(const BigInt &x) const {
		return (!((*this) < x));
	}
	bool operator!=(const BigInt &x) const {
		return (!((*this) == x));
	}
	friend BigInt max(BigInt &x, BigInt &y) {
		return (x > y? x: y);
	}
	friend BigInt min(BigInt &x, BigInt &y) {
		return (x < y? x: y);
	}
 
	//math operators
	BigInt operator+(const BigInt &x) const {
		if (sign == x.sign) {
			BigInt res;
			res.sign = sign;
			for (int i = 0; i < max(x.num.size(), num.size()); i++) {
				int t = (i >= num.size()? 0: num[i]) + (i >= x.num.size()? 0: x.num[i]);
				res.num.push_back(t);
			}
			res.normalize();
			return res;
		}
		if (sign == -1)
			return x - abs(*this);
		else
			return (*this) - abs(x);
	}
	BigInt operator-(const BigInt &x) const {
		if (sign == x.sign) {
			BigInt res, a = abs(*this), b = abs(x);
			a.clr();
			b.clr();
			if (a == b) {
				res = 0;
				return res;
			}
			if (b < a) {
				for (int i = 0; i < a.num.size(); i++) {
					int t = a.num[i] - (i >= b.num.size()? 0: b.num[i]);
					res.num.push_back(t);
				}
				res.normalize();
			}
			else {
				for (int i = 0; i < b.num.size(); i++) {
					int t = b.num[i] - (i >= a.num.size()? 0: a.num[i]);
					res.num.push_back(t);
				}
				res.normalize();
				res.sign *= -1;
			}
			if (sign == -1)
				res.sign *= -1;
			return res;
		}
		if (sign == -1) {
			BigInt res = abs(*this) + x;
			res.sign *= -1;
			return res;
		}
		else
			return (*this) + abs(x);
	}
	void operator+=(const BigInt &x) {
		(*this) = (*this) + x;
	}
	void operator-=(const BigInt &x) {
		(*this) = (*this) - x;
	}
	void operator++() {
		(*this) += 1;
	}
	BigInt operator++(int) {
		BigInt res;
		++(*this);
		return res;
	}
	void operator--() {
		(*this) -= 1;
	}
	BigInt operator--(int) {
		BigInt res;
		--(*this);
		return res;
	}
	BigInt operator*(const BigInt &x) const {
		BigInt res;
		BigInt a = (*this), b = x;
		if (a.isZero() or b.isZero())
			return 0;
		a.clr();
		b.clr();
		for (int i = 0; i < b.num.size(); i++) {
			BigInt t;
			for (int j = 1; j <= i; j++)
				t.num.push_back(0);
			for (int j = 0; j < a.num.size(); j++)
				t.num.push_back(a.num[j] * b.num[i]);
			t.normalize();
			res += t;
		}
		res.normalize();
		res.sign = a.sign * b.sign;
		return res;
	}
	void operator*=(const BigInt &x) {
		(*this) = (*this) * x;
	}
	friend pair<BigInt, BigInt> dmod(const BigInt &x, const BigInt &y) {
		BigInt res, a = abs(x), b = abs(y), carry;
		res.sign = y.sign * x.sign;
		a.clr();
		b.clr();
		if (b.isZero())
			return {-1, -1};
		if (a < b) {
			return {0, x};
		}
		int cnt = a.num.size() - 1;
		for (int i = a.num.size() - 1; carry < b; i--) {
			carry.num.push_front(a.num[i]);
			cnt = i - 1;
		}
		for (int i = 1; i <= 10; i++) {
			BigInt t = b * i;
			if (t > carry) {
				res.num.push_front(i - 1);
				t -= b;
				carry -= t;
				break;
			}
		}
		for (int i = cnt; i >= 0; i--) {
			carry.num.push_front(a.num[i]);
			carry.normalize();
			if (carry >= b) {
				for (int j = 1; j <= 10; j++) {
					BigInt t = b * j;
					if (t > carry) {
						res.num.push_front(j - 1);
						t -= b;
						carry -= t;
						break;
					}
				}
			}
			else {
				res.num.push_front(0);
			}
		}
		res.normalize();
		if (res.sign == -1)
			carry = y - x;
		return {res, carry};
 
	}
	BigInt operator/(const BigInt &x) const {
		pair<BigInt, BigInt> res = dmod((*this), x);
		return res.first;
	}
	void operator/=(const BigInt &x) {
		(*this) = (*this) / x;
	}
	BigInt operator%(const BigInt &x) const {
		pair<BigInt, BigInt> res = dmod((*this), x);
		return res.second;
	}
	void operator%=(const BigInt &x) {
		(*this) = (*this) % x;
	}
	friend BigInt pow(const BigInt &x, const BigInt &y) {
		BigInt tmp = y;
		if (tmp.isZero())
			return 1;
		BigInt res = 1, t = y, a = x;
	       	pair<BigInt, BigInt> dm;
		while (t > 0) {
			if ((t % 2) == 1)
				res = res * a;
			a *= a;
			t /= 2;
		}
		return res;
	}
	friend BigInt gcd(BigInt x, BigInt y) {
		return (y.isZero()? x: gcd(y, x % y));
	}
	friend BigInt lcm(const BigInt &x, const BigInt &y) {
		return (x * y) / gcd(x, y);
	}
	friend BigInt sqrt(const BigInt &x) {
		if (x.sign == -1)
			return -1;
		BigInt carry, res, lef;
		deque<pair<int, int>> t;
		for (int i = 0; i < x.num.size(); i += 2) {
			if (i + 1 == x.num.size())
				t.push_front({x.num[i], 1});
			else
				t.push_front({x.num[i] + x.num[i + 1] * 10, 2});
		}
		for (int i = 0; i < t.size(); i++) {
			if (t[i].second == 1)
				carry.num.push_front(t[i].first);
			else
				carry.num.push_front(t[i].first / 10), carry.num.push_front(t[i].first % 10);
			carry.normalize();
			lef.num.push_front(0);
			for (int i = 1; i <= 10; i++) {
				lef.num[0] = i;
				BigInt tmp = (lef) * i;
				if (tmp > carry) {
					lef.num[0] = i - 1;
					tmp = lef * (i - 1);
					carry -= tmp;
					lef += (i - 1);
					res.num.push_front(i - 1);
					break;
				}
			}
		}
		res.normalize();
		return res;
	}
 
	//string to bigint and bigint to string
	void toBig(string &s) {
		if (s[0] == '-') {
			sign = -1;
			s = s.substr(1);
		}
		else
			sign = 1;
		reverse(s.begin(), s.end());
		num.clear();
		for (int i = (s[0] == '-'); i < s.size(); i += Dig / 10) {
			string sp;
			for (int j = i; j < i + (Dig / 10); j++)
				sp += s[j];
			long long t = stol(sp);
			num.push_back(t);
		}
	}
	friend string to_string(const BigInt &x) {
		string res;
		if (x.num.empty()) {
			res += '0';
			return res;
		}
		if (x.sign == -1)
			res += '-';
		for (int i = x.num.size() - 1; i >= 0; i--) {
			string t = to_string(x.num[i]);
			reverse(t.begin(), t.end());
			res += t;
		}
		return res;
	}
	//change base
	friend BigInt change_base(const BigInt &a, const int y, const int x) {
		if (y == x)
			return a;
		BigInt res, t = change_base_rev(a, y, 10);
		t.normalize();
		while (t > 0) {
			res.num.push_back(BtoI(t % x));
			t /= x;
		}
		return res;
	}
	friend BigInt change_base_rev(const BigInt &a, const int y, const int x) {
		if (y == x)
			return a;
		if (x == 10) {
			BigInt res, t = 1, b = a;
			b.clr();
			for (int i = 0; i < b.num.size(); i++)
				res += t * b.num[i], t *= y;
			return res;
		}
		BigInt t = change_base_rev(a, y, 10);
		return change_base(t, 10, x);
 
	}
	friend BigInt CB(const BigInt &a, int y, int x) {
		if (x > y)
			return change_base_rev(a, y, x);
		return change_base(a, y, x);
	}
 
	//bitwise operator
	BigInt operator^(const BigInt &x) const {
		BigInt res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 ^ d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	BigInt operator&(const BigInt &x) const {
		BigInt res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 & d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	BigInt operator|(const BigInt &x) const {
		BigInt res, a = change_base(*this, 10, 2), b = change_base(x, 10, 2);
		for (int i = 0; i < max(a.num.size(), b.num.size()); i++) {
			int d1 = 0, d2 = 0;
			if (i < a.num.size())
				d1 = a.num[i];
			if (i < b.num.size())
				d2 = b.num[i];
			res.num.push_back(d1 | d2);
		}
		res.clr();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	void operator^=(const BigInt &x) {
		(*this) = (*this) ^ x;
	}
	void operator&=(const BigInt &x) {
		(*this) = (*this) & x;
	}
	void operator|=(const BigInt &x) {
		(*this) = (*this) | x;
	}
	BigInt operator<<(const BigInt &x) {
		BigInt res = change_base((*this), 10, 2);
		for (BigInt i = 0; i < x; i++)
			res.num.push_front(0);
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
	}
	BigInt operator>>(const BigInt &x) {
		BigInt res = change_base((*this), 10, 2);
		BigInt t = (int)res.num.size();
		for (BigInt i = 0; i < min(x, t); i++)
			res.num.pop_front();
		res = change_base_rev(res, 2, 10);
		res.normalize();
		return res;
 
	}
	void operator>>=(const BigInt &x) {
		(*this) = (*this) >> x;
	}
	void operator<<=(const BigInt &x) {
		(*this) = (*this) << x;
	}
 
	//builtin fuctions
	int popcount() {
		int res = 0;
		BigInt tmp = *this;
		tmp = CB(tmp, 10, 2);
		for (auto i : tmp.num)
			res += i;
		return res;
	}
	int ctz() {
		BigInt tmp = *this;
		tmp = CB(tmp, 10, 2);
		for (int i = 0; i < tmp.num.size(); i++)
			if (tmp.num[i])
				return i;
                return 1;
 
	}
 
	//cin and cout
	friend istream& operator>>(istream &stream, BigInt &x) {
		string s;
		stream >> s;
		x.toBig(s);
		x.normalize();
		return stream;
	}
	friend ostream& operator<<(ostream &stream, BigInt &x) {
		if (x.num.empty()) {
			stream << 0;
			return stream;
		}
		if (!x.num.empty() and x.sign == -1)
			stream << '-';
		stream << (x.num.empty() ? 0 : x.num.back());
		for (int i = (int) x.num.size() - 2; i >= 0; i--)
			stream  << x.num[i];
		return stream;
	}
 
};
 
//tutorial :
//everything is similar to using int exept a few functions
//BtoI(bigint x) : returns x to int (becareful with overflow)
//CB(bigint x, int a, int b) : get a bigint in base a and returns a bigint in base b (a, b <= 10)
//x.popcount() : returns number of 1 in binary form of x
//x.ctz() : returns number of 0 before the rightmost 1 in binary form of x
