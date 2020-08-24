template <class T> struct Fraction {
	T num, den;
	Fraction() {
		num = 1, den = 1;
	}
	Fraction(T _num, T _den = 1) {
		num = _num, den = _den;
		T g = __gcd(num, den);
		num /= g, den /= g;
	}
	Fraction operator + (Fraction f) {
		Fraction ans(num * f.den + den * f.num, den * f.den);
		return ans;
	}
	Fraction operator - (Fraction f) {
		Fraction ans(num * f.den - den * f.num, den * f.den);
		return ans;
	}
	Fraction operator * (Fraction f) {
		Fraction ans(num * f.num, den * f.den);
		return ans;
	}
	Fraction operator / (Fraction f) {
		Fraction ans(num * f.den, den * f.num);
		return ans;
	}
	bool operator > (Fraction f) {
		return num * f.den > den * f.num;
	}
	bool operator < (Fraction f) {
		return num * f.den < den * f.num;
	}
	bool operator == (Fraction f) {
		return num * f.den == den * f.num;
	}
	friend ostream& operator << (ostream &out, const Fraction &f) {
		cout << f.num << "/" << f.den;
		return out;
	}
};
