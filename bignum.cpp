#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
class BigNum {
	vector<int> buf;
public:
	static const int w = 8;
	BigNum() {
		buf.push_back(0);
	}
	BigNum(int num) {
		int d = 1;
		for (size_t i = 0; i < w; i++)
		{
			d *= 10;
		}
		while (num) {
			buf.push_back(num%d);
			num = num / d;
		}
	}
	BigNum(const char* num) {
		string str(num);
		stringstream ss;
		int b = str.length();
		int e;
		while (b != 0)
		{
			e = b;
			b -= w;
			if (b < 0) {
				b = 0;
			}
			ss << str.substr(b, e - b);
			ss << " ";
			int val;
			ss >> val;
			buf.push_back(val);
		}
		if (buf.size() == 0) {
			buf.push_back(0);
		}
	}
	static BigNum add(const BigNum& _a, const BigNum& _b) {
		BigNum r;
		BigNum* result = &r;
		const BigNum* a = &_a;
		const BigNum* b = &_b;
		result->buf.clear();
		if (b->buf.size() > a->buf.size()) {
			const BigNum* temp = a;
			a = b;
			b = temp;
		}
		int out = 0;
		int d = 1;
		for (size_t i = 0; i < w; i++)
		{
			d *= 10;
		}
		for (int i = 0; i < a->buf.size(); ++i) {
			int a_num = a->buf[i];
			int b_num = 0;
			if (i < b->buf.size()) {
				b_num = b->buf[i];
			}
			int push = (a_num + b_num + out) % d;
			out = (a_num + b_num + out) / d;
			result->buf.push_back(push);
		}
		if (out) {
			result->buf.push_back(out);
		}
		return r;
	}
	static BigNum sub(const BigNum& _a, const BigNum& _b) {
		BigNum r;
		BigNum* result = &r;
		const BigNum* a = &_a;
		const BigNum* b = &_b;
		result->buf.clear();
		if (b->buf.size() > a->buf.size()) {
			const BigNum* temp = a;
			a = b;
			b = temp;
		}
		int out = 0;
		int d = 1;
		for (size_t i = 0; i < w; i++)
		{
			d *= 10;
		}
		for (int i = 0; i < a->buf.size(); ++i) {
			int a_num = a->buf[i];
			int b_num = 0;
			if (i < b->buf.size()) {
				b_num = b->buf[i];
			}
			int s = a_num - b_num + out;
			int push;
			if (s >= 0) {
				push = s;
				out = 0;
			}
			else {
				push = s + d;
				out = -1;
			}
			result->buf.push_back(push);
		}
		for (size_t i = result->buf.size()-1; i  > 0; i--)
		{
			if (result->buf[i] == 0) {
				result->buf.erase(result->buf.begin() + i);
			}
			else {
				break;
			}
		}
		return r;
	}
	string to_string(const char* str = "") {
		string result;
		stringstream ss;
		ss << buf[buf.size() - 1] << str;
		for (int i = buf.size() - 2; i >= 0; --i) {
			ss << setw(w) << setfill('0') << buf[i] << str;
		}
		ss >> result;
		return result;
	}
};
#include <iostream>
int main() {
	BigNum a(1000000000);
	//正数加法，大数不带符号
	a = BigNum::add(a, BigNum(999999999));
	cout << a.to_string() << endl;
	//减法，求出的是绝对值，即总是用大的减小的
	a = BigNum::sub(a, BigNum(999999999));
	cout << a.to_string() << endl;
	a = BigNum("123456789");
	cout << a.to_string();
	return 0;
}