#define _CRT_SECURE_NO_WARNINGS 1
#pragma once 
#include<iostream>
using namespace std;
#include<string.h>
#include<assert.h>

//模拟实现一个完整的string
namespace wzy  //对于同一个命名空间，里面的类是会合并的
{
	class string
	{
	public:
		//迭代器是像指针一样的类型，但不一定是指针，但是他们的“用法”大多都一样
		//我们所认为的迭代器非常的高大上，其实不然，就是一种很好的封装，上层隐藏了具体信息
		typedef char* iterator;//目前在string里面就可以简单的认为迭代器就是char*的指针
		typedef const char* const_iterator;

		iterator begin() 
		{
			return _str;
		}

		iterator end() //可以理解为你的end就是指向的‘\0’的位置
		{
			return _str + _size;
		}

		const_iterator begin()const
		{
			return _str;
		}

		const_iterator end()const //可以理解为你的end就是指向的‘\0’的位置
		{
			return _str + _size;
		}

		string(const char* str)
		{
			//你会发现，如果你使用初始化列表，那么就要多次的写strlen(str),对于内置类型其实写在内部更好
			//提示：初始化列表的顺序并不是真的顺序，声明的顺序才是初始化列表的真实顺序
			_size = strlen(str);
			_capacity = _size;//这里的容量代表“能存多少个效字符” ‘\0’是标识符
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
		}

		//string(const string& s)
		//	:_str(new char[strlen(s._str) + 1])
		//{
		//	strcpy(_str, s._str);
		//}
		
		//现代写法的拷贝构造s2(s1)
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);
			//std::swap(_str, tmp._str);
			//std::swap(_size, tmp._size);
			//std::swap(_capacity, tmp._capacity);
			swap(tmp);
		}

		char& operator[](size_t i)
		{
			assert(i < _size);//越界会直接崩掉
			return _str[i];
		}

		const char& operator[](size_t i)const
		{
			assert(i < _size);//越界会直接崩掉
			return _str[i];
		}

		size_t size()const
		{
			return _size;
		}
		
		//赋值
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				delete[] _str;
				_str = new char[strlen(s._str) + 1];
				strcpy(_str, s._str);
			}
			return *this;
		}


		//赋值的现代写法 s1 = s3
		//string& operator=(string s)
		//{
		//	swap(s);
		//	/*std::swap(_str, s._str);
		//	std::swap(_size, s._size);
		//	std::swap(_capacity, s._capacity);*/
		//	return *this;
		//}

		//不管在任何时候插入的时候都要考虑空间是否足够的问题
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				//这里不要直接的扩二倍，要考虑长远一些，应为还需要实现一个reserve()接口
				reserve(2 * _capacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0'; //如果不加这一句，那么你放入的字符就会覆盖掉\0，那么他就不知道字符串何时结束，就会崩了
		}

		//相当于C语言的strcat，区别就是不用在考虑空间是否足够，因为他会自己增加 
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				//char* tmp = realloc(_str, n);
				char* tmp = new char[n+1];//这里最好写为new，第一是匹配前面的new，第二就是对于new来说是不需要检查的，开辟失败，会抛异常
				strcpy(tmp, _str); 
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		//开好空间，并且还会初始化
		//resize其实也会分很多种情况
		//假设这里n是10，那么我现在存入了5个有效的字符
		//reserve(2);   reverse(6);    reverse(8,'x');    reverse(12,'x');  这几种情况分别考虑，对于resize来说，默认的就是给'\0'
		void resize(size_t n,char ch = '\0')
		{
			//为了避免不停的因为预留空间缩小放大而申请释放空间,发生的抖动问题
			if (n < _capacity)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}

				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
		}

		//但是一般情况下是不见使用push_back 和 append的
		//直接上+=
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& operator+=(const string& s)
		{
			append(s._str);
			return *this;
		}

		//既然提供了一个全局swap()函数，为什么我还要自己在string里面实现一个swap()呢
		//swap(s1,s2);
		//s1.swap(s2);
		//是因为对于成员函数来说，交换的代价会很小，我只是把两个指针（是一种形象的描述）颠倒位置
		//但是全局的swap()函数来说，是一个函数模板，需要多次的实现深拷贝的过程，其实本质是十分浪费空间的
		void swap(string& s)
		{
			std::swap(_str,s._str); //前面没有给的时候，表示去全局域找,当然这里给一个std更加清楚
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		//但是不要随意的使用，因为insert在使用的时候会挪动数据，造成时间复杂度会很大
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				reserve(2 * _capacity);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end -1];
				--end;
			}
			_str[pos] = ch;
			_size++;
		}

		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			//此时空间已经够了
			size_t end = _size + len;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, _str, len);
			_size += len;
		}

		void earse(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos + len >= _size) //如果这里不单独判断这个len可能就会发生溢出的问题
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}

		const char* c_str()const
		{
			return _str;
		}

		size_t find(char ch,size_t pos = 0) //因为只能从右往左缺省
		{
			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}

		size_t find(const char* sub, size_t pos = 0)
		{
			const char* ret = strstr(_str + pos, sub);
			if (ret == nullptr)
			{
				return npos;
			}
			else
			{
				return ret - _str;
			}
		}

	private:
		//你会发现在windows下这里的成员变量还有一个char buff[16]，其实这里就是使用了一种空间换时间的方式，如果你的字符串比较短
		//就会直接的存储在buff里面，而不用在进行下面的开空间步骤了，但是如果字符串比较长，那么你的这个buff空间就直接浪费掉
		char* _str;
		int _size;
		int _capacity;
		static const size_t npos;
	};
	const size_t string::npos = -1;

	bool operator>(const string& s1, const string& s2)
	{
		//这里需要按照ASCII值去比较
		size_t i1 = 0, i2 = 0;
		while (i1 < s1.size() && i2 < s2.size())
		{
			if (s1[i1]> s2[i2])
			{
				return true;
			}
			else if (s1[i1] < s2[i2])
			{
				return false;
			}
			else
			{
				++i1;
				++i2;
			}
		}
		if (i1 < s1.size())
		{
			return true;
		}
		else if (i2 < s2.size())
		{
			return false;
		}
		else
		{
			//此时是相等的情况
			return false;
		}
	}

	bool operator==(const string& s1, const string& s2)
	{
		//这里需要按照ASCII值去比较
		size_t i1 = 0, i2 = 0;
		while (i1 < s1.size() && i2 < s2.size())
		{
			if (s1[i1]> s2[i2])
			{
				return false;
			}
			else if (s1[i1] < s2[i2])
			{
				return false;
			}
			else
			{
				++i1;
				++i2;
			}
		}
		if (i1 == s1.size() && i2 == s2.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//剩下复用上面的重载

	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}

	istream& operator>>(istream& in, string& s) //对于cin来说遇见换行和空格都会停止
	{
		s.resize(0);
		char ch;
		while (1)
		{
			in.get(ch);
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				s += ch;
			}
		}
		return in;
	}
};