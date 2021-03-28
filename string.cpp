////ʵ��һ���򵥵�string�����stringֻ�л����Ĺ��죬�������������죬operator[]�ȹ���
//#include<iostream>
//using namespace std;
//namespace wzy
//{
//	class string
//	{
//	public:
//		//����ǵ����޲εĶ���
//		//string(const char* str)
//		//	:_str(new char[1])
//		//{
//		//	_str[0] = '\0';
//		//}
//		//�ٽ���дһ��ȫȱʡ�Ĺ��캯��
//		//�ڶ��������һ���ַ�����ʹ�ǿ��ַ���""����Ҳ��һ��Ĭ�ϵġ�\0��
//		string(const char* str = "")
//			:_str(new char[strlen(str)+1])
//		{
//			strcpy(_str, str);
//		}
//
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//
//		//s3(s1)
//		//��������
//		string(const string& s)
//			//���ڿ������캯����˵�����ֻ��ʵ�ּ򵥵�ǳ��������ô�ͻ���������ʱ�����������Ҫ���
//			//ʲô������أ��Լ����¿���һ���ռ䣬Ȼ����ָ����
//			:_str(new char[strlen(s._str) + 1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		//��д�����ʱ��Ҫ����������operator[]������Ҫʲô
//		char& operator[](size_t i)
//		{
//			return _str[i];
//		}
//
//		//���ֻ�Ǽ򵥵�ǳ������Ҳ����ֳ���������
//		//��ֵ������������������Ѿ������������ˣ� s3 = s1
//		//��ʱ���s3������Ҫ�����s1����һ���󣬵�������֪�����������ĸ���������ֱ�Ӱ�s3�Ŀռ��ͷŵ���Ȼ���s1����һ����ͺ���
//		//���Ǵ�ʱ����Ҫ�����Ƿ����Լ�����Լ���ֵ��?
//		//��ôΪʲô�ῼ����������أ�����Ϊ������Լ����Լ���ֵ�Ļ�������һ�������Ѿ��������οռ���ͷ���
//		//
//		string& operator=(const string& s)
//		{
//			if (this != &s)
//			{
//				delete[] _str;
//				_str = new char[strlen(s._str) + 1];
//				strcpy(_str, s._str);
//			}
//			return *this;
//		}
//
//		//����C��ʽ�ַ���
//		const char* c_str()
//		{
//			return _str;//�ٴ�˵�������ڳ�Ա������˵����Ա������������ĵ���
//		}
//	private:
//		char* _str;
//	};
//};
//
//int main()
//{
//	wzy::string s1;//�޲ε���
//	wzy::string s2("hello");//�вε���
//	wzy::string s3(s2);//��������
//	wzy::string s4("hello world!");
//	s2 = s4; //��ֵ
//
//
//	std::cout << s1.c_str() << std::endl;
//	std::cout << s2.c_str() << std::endl;
//	std::cout << s3.c_str() << std::endl;
//	std::cout << s4.c_str() << std::endl;
//
//	return 0;
//}
//��������򵥵�string��һ��debug��û���ҵ����Ȼ���Ҫ���»����ҵ���


//����Ϊ������õ����ӣ�ֻ��Ҫ����ȥ�ܹ����õ�ȥ���

#include"string.h"

void Print(const wzy::string& s)
{
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

int main()
{
	wzy::string s("1234");

	for (size_t i = 0; i < s.size(); i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;

	Print(s);

	wzy::string::iterator it = s.begin();
	//auto it = s.begin(); ����ʹ��autoȥ�����ͣ������㲻֪�������صľ������ͣ���ʵ�����Ǻܺ�
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//��Χfor��ԭ����ǵ�����
	for (auto& e : s)
	{
		e += 1;  
	}
	Print(s);

	s += 'x';
	s += "hello world";
	Print(s);

	return 0;
}

//string���ִ�д��---ʵ��һ���򵥵�д��
//ʲô���ִ�д���أ���ʵ˵��һЩ���ǿ��ռ����Щ�����Ҳ����Լ�ȥʵ���ˣ�����ȥ�ñ���ʵ�֣�Ȼ�����ٰѱ���ʵ�ֺõĸ��ù���
//��Щ���ʱ���ȥ�����Ͷ������ʣ���ֵ��
//#define _CRT_SECURE_NO_WARNINGS 1
//#include<string.h>
//#include<iostream>
//using namespace std;
//namespace wzy
//{
//	class string
//	{
//	public:
//		string(const char* str = "")
//			:_str(new char[strlen(str)+1])
//		{
//			strcpy(_str, str);
//		}
//
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//		//����������ִ�д��
//		//s2(s1)
//		//������ᷢ�֣������û�ж�s2���г�ʼ������ôswap()֮��tmp�ͻ������ָ��һ���ط�������������s2�������������
//		//��ʱ���ͻ�������ͷ�һ���ռ䣬����ͻ����
//		string(const string& s)
//			:_str(nullptr)//����һ������������˵������һ�����ǲ�����������
//		{
//			string tmp(s._str); //��Ϊ�����s._str��һ��char*��ָ�룬����ȥ����string�Ĺ��캯��
//			//��ʱtmpӵ�еĿռ��ֵ������_str��Ҫ��
//			swap(_str, tmp._str);
//		}
//
//		string& operator=(const string& s)
//			//�ٷ����Լ����Լ���ֵ
//			//���ͷ��Լ��Ŀռ�
//			//���ں�s��һ����Ŀռ䣬�ٰѿռ�����ݿ�������
//		{
//			if (this != &s)
//			{
//				string tmp(s._str);//���ù��캯��
//				//string tmp(s);���ÿ������캯��
//				swap(_str, tmp._str);//����ǳ��пᣬ������tmpȥ���ռ䣬���Ұ�_strԭ����Ҫ�Ŀռ�ֱ��˦����tmp
//				//���ҳ���������tmp���Լ���������������ֱ�Ӱ�ԭ�����Ƕοռ���ͷŵ�
//			}
//			return *this;
//		}
//		//��ֵ�������NB��д�� s3 = s1; ���ӵļ��
//		//s������s1������������ģ���ʱ�����s1��ͬ����Ŀռ�����ݣ�����������ݸպ�����s3��Ҫ�ģ�����ֱ�ӽ���
//		//string& operator=(string s)
//		//{
//		//	swap(_str, s._str);
//		//	return *this;
//		//}
//	private:
//		char* _str;
//	};
//};
//
//int main()
//{
//	wzy::string s1("hello");
//	wzy::string s2(s1);
//
//	//cout << s1 << endl;
//	//cout << s2 << endl;
//
//	swap(s1, s2);
//	s1.swap(s2);
//	return 0;
//}