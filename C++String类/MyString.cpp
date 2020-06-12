#include<iostream>
#include<cstring>

class MyString {
	
	public :
		//	construcotrs
		MyString (const char *src = nullptr);
		MyString (unsigned, char);
		~MyString ();
		
		//	copying member
		MyString (const MyString &);
		MyString & operator= (const MyString &);
		
		//	synergic functions
		size_t size () const;
		const char *get () const;
		void swap(MyString &);
		
		//	arithmetic operator
		MyString & operator+= (const MyString &);
		char &operator[] (size_t);
		
	private :
		char *c_str = nullptr;
		unsigned m_length = -1;
};

//	默认实参版——一举三得 
MyString::MyString (const char *src)
{
	if (src == nullptr)
	{
		c_str = new char[1];
		*c_str = '\0';
		m_length = 0;
		return ;
	}
	
	unsigned n = strlen(src);
	c_str = new char[n+1];	
	for (int i = 0; i < n; ++i)
		c_str[i] = src[i];
	c_str[n] = '\0';
	m_length = n;
}



MyString::MyString(unsigned n, char ch)
{
	c_str = new char[n+1];
	for (int i = 0; i < n; ++i)
		c_str[i] = ch;
	c_str[n] = '\0';
	m_length = n;
}

MyString::~MyString ()
{
	delete []c_str;
}


//	copying member
MyString::MyString (const MyString &src)
{
	c_str = new char[src.m_length + 1];
	strcpy(c_str, src.c_str);
	m_length = src.m_length;
}

void swap(MyString &, MyString &);

//	using copy and swap
MyString &
MyString::operator= (const MyString &src)
{
	if (this != &src)
	{
		using std::swap;
		MyString temp(src);
		//	注意：当名字查找规则 遇上 同名覆盖 
		swap(*this, temp);
	}
	return *this;
}

//	synergic member functions
MyString operator+ (const MyString &, const MyString &);

//	using copy and swap
MyString &
MyString::operator+= (const MyString &rhs)
{
	using std::swap;
	MyString temp(*this + rhs);
	swap(*this, temp);
	return *this;
}

char &
MyString::operator[] (size_t index)
{
	return c_str[index];
}


//	global overload function
MyString
operator+ (const MyString &lhs, const MyString &rhs)
{
	char buf[lhs.size() + rhs.size() + 1];
	strcpy(buf, lhs.get());
	strcat(buf, rhs.get());
	return MyString (buf);
}

//	input/output friend
//	white characters
#define WHITE (ch == '\12' || ch == '\11' || ch == '\40')

std::istream &
operator>> (std::istream &is, MyString &rhs)
{
	//	基础版本——使用有限大小的缓冲区 
	char buf[1024], ch;
	int i = 0;
	
	ch = getchar();
	while (WHITE)
		ch = getchar();
		
	while (!WHITE)
	{
		buf[i++] = ch;
		ch = getchar(); 
	}
	buf[i] = '\0';
	
	rhs = buf;
	
	return is;
}


std::ostream &
operator<< (std::ostream &os, const MyString &rhs)
{
	const char *p = rhs.get();
	const char *end = rhs.get() + rhs.size();
	
	while (os && p != end)
		os << *p++;
		
	return os;
		
}

//	synergic member 
const char *MyString::get () const
{
	return c_str;
}

size_t MyString::size () const
{
	return m_length;
}

void MyString::swap(MyString &rhs)
{
	using std::swap;
	swap(this->c_str, rhs.c_str);
	swap(this->m_length, rhs.m_length);
}

void swap (MyString &lhs, MyString &rhs)
{
	lhs.swap(rhs);
}




//	test case:
void test1 ()
{
	MyString s1 = "abcd";
	MyString s2 = s1;
	std::cout << s2 << std::endl;
}


//	main fun
int main()
{
	test1();
	return 0;
}
