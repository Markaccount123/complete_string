#define _CRT_SECURE_NO_WARNINGS 1
#pragma once 
#include<iostream>
using namespace std;
#include<string.h>
#include<assert.h>

//ģ��ʵ��һ��������string
namespace wzy  //����ͬһ�������ռ䣬��������ǻ�ϲ���
{
	class string
	{
	public:
		//����������ָ��һ�������ͣ�����һ����ָ�룬�������ǵġ��÷�����඼һ��
		//��������Ϊ�ĵ������ǳ��ĸߴ��ϣ���ʵ��Ȼ������һ�ֺܺõķ�װ���ϲ������˾�����Ϣ
		typedef char* iterator;//Ŀǰ��string����Ϳ��Լ򵥵���Ϊ����������char*��ָ��
		typedef const char* const_iterator;

		iterator begin() 
		{
			return _str;
		}

		iterator end() //�������Ϊ���end����ָ��ġ�\0����λ��
		{
			return _str + _size;
		}

		const_iterator begin()const
		{
			return _str;
		}

		const_iterator end()const //�������Ϊ���end����ָ��ġ�\0����λ��
		{
			return _str + _size;
		}

		string(const char* str)
		{
			//��ᷢ�֣������ʹ�ó�ʼ���б���ô��Ҫ��ε�дstrlen(str),��������������ʵд���ڲ�����
			//��ʾ����ʼ���б��˳�򲢲������˳��������˳����ǳ�ʼ���б����ʵ˳��
			_size = strlen(str);
			_capacity = _size;//��������������ܴ���ٸ�Ч�ַ��� ��\0���Ǳ�ʶ��
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
		
		//�ִ�д���Ŀ�������s2(s1)
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
			assert(i < _size);//Խ���ֱ�ӱ���
			return _str[i];
		}

		const char& operator[](size_t i)const
		{
			assert(i < _size);//Խ���ֱ�ӱ���
			return _str[i];
		}

		size_t size()const
		{
			return _size;
		}
		
		//��ֵ
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


		//��ֵ���ִ�д�� s1 = s3
		//string& operator=(string s)
		//{
		//	swap(s);
		//	/*std::swap(_str, s._str);
		//	std::swap(_size, s._size);
		//	std::swap(_capacity, s._capacity);*/
		//	return *this;
		//}

		//�������κ�ʱ������ʱ��Ҫ���ǿռ��Ƿ��㹻������
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				//���ﲻҪֱ�ӵ���������Ҫ���ǳ�ԶһЩ��ӦΪ����Ҫʵ��һ��reserve()�ӿ�
				reserve(2 * _capacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0'; //���������һ�䣬��ô�������ַ��ͻḲ�ǵ�\0����ô���Ͳ�֪���ַ�����ʱ�������ͻ����
		}

		//�൱��C���Ե�strcat��������ǲ����ڿ��ǿռ��Ƿ��㹻����Ϊ�����Լ����� 
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
				char* tmp = new char[n+1];//�������дΪnew����һ��ƥ��ǰ���new���ڶ����Ƕ���new��˵�ǲ���Ҫ���ģ�����ʧ�ܣ������쳣
				strcpy(tmp, _str); 
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		//���ÿռ䣬���һ����ʼ��
		//resize��ʵҲ��ֺܶ������
		//��������n��10����ô�����ڴ�����5����Ч���ַ�
		//reserve(2);   reverse(6);    reverse(8,'x');    reverse(12,'x');  �⼸������ֱ��ǣ�����resize��˵��Ĭ�ϵľ��Ǹ�'\0'
		void resize(size_t n,char ch = '\0')
		{
			//Ϊ�˱��ⲻͣ����ΪԤ���ռ���С�Ŵ�������ͷſռ�,�����Ķ�������
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

		//����һ��������ǲ���ʹ��push_back �� append��
		//ֱ����+=
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

		//��Ȼ�ṩ��һ��ȫ��swap()������Ϊʲô�һ�Ҫ�Լ���string����ʵ��һ��swap()��
		//swap(s1,s2);
		//s1.swap(s2);
		//����Ϊ���ڳ�Ա������˵�������Ĵ��ۻ��С����ֻ�ǰ�����ָ�루��һ��������������ߵ�λ��
		//����ȫ�ֵ�swap()������˵����һ������ģ�壬��Ҫ��ε�ʵ������Ĺ��̣���ʵ������ʮ���˷ѿռ��
		void swap(string& s)
		{
			std::swap(_str,s._str); //ǰ��û�и���ʱ�򣬱�ʾȥȫ������,��Ȼ�����һ��std�������
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		//���ǲ�Ҫ�����ʹ�ã���Ϊinsert��ʹ�õ�ʱ���Ų�����ݣ����ʱ�临�ӶȻ�ܴ�
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
			//��ʱ�ռ��Ѿ�����
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
			if (len == npos || pos + len >= _size) //������ﲻ�����ж����len���ܾͻᷢ�����������
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

		size_t find(char ch,size_t pos = 0) //��Ϊֻ�ܴ�������ȱʡ
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
		//��ᷢ����windows������ĳ�Ա��������һ��char buff[16]����ʵ�������ʹ����һ�ֿռ任ʱ��ķ�ʽ���������ַ����Ƚ϶�
		//�ͻ�ֱ�ӵĴ洢��buff���棬�������ڽ�������Ŀ��ռ䲽���ˣ���������ַ����Ƚϳ�����ô������buff�ռ��ֱ���˷ѵ�
		char* _str;
		int _size;
		int _capacity;
		static const size_t npos;
	};
	const size_t string::npos = -1;

	bool operator>(const string& s1, const string& s2)
	{
		//������Ҫ����ASCIIֵȥ�Ƚ�
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
			//��ʱ����ȵ����
			return false;
		}
	}

	bool operator==(const string& s1, const string& s2)
	{
		//������Ҫ����ASCIIֵȥ�Ƚ�
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
	//ʣ�¸������������

	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}

	istream& operator>>(istream& in, string& s) //����cin��˵�������кͿո񶼻�ֹͣ
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