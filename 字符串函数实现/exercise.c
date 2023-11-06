/*//1.1 计数器方法模拟实现strlen--->计算字符串长度；

int my_strlen(char* p)
{
	int count = 0;
	while (*p != '\0')
	{
		count++;
		p++;
	}
	return count;
}


//1.2用递归模拟实现strlen函数求字符串长度
int my_strlen(char* str1)
{
	if (*str1 == '\0')
		return 0;
	else
		return 1 + my_strlen(str1 + 1);

}

//1.3指针-指针的方式
int my_strlen(char *s)
{
       char *p = s;
       while(*p != ‘\0’ )
             p++;
       return p-s;
}


//2 模拟实现strcpy
char* my_strcpy(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest != NULL);
	assert(src != NULL);

	while ((*dest++ = *src++))
	{}
	return ret;
}

//3 模拟实现strcat


char* my_strcat(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest != NULL);
	assert(src != NULL);
	while (*dest!='\0')
	{
		dest++;
	}
	while ((*dest++ = *src++))
	{
		;
	}
	return ret;
}

//4 模拟实现strstr
char* strstr(const char* str1, const char* str2)
{
	char* cp = (char*)str1;
	char* s1, * s2;
	if (!*str2)
		return((char*)str1);
	while (*cp)
	{
		s1 = cp;
		s2 = (char*)str2;
		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;
		if (!*s2)
			return(cp);
		cp++;
	}
	return(NULL);
}
//5 模拟实现strcmp
int my_strcmp(const char* src, const char* dst)
{
	int ret = 0;
	assert(src != NULL);
	assert(dest != NULL);
	while (!(ret = *(unsigned char*)src - *(unsigned char*)dst) && *dst)
		++src, ++dst;
	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;
	return(ret);
}
//6 模拟实现memcpy
void* memcpy(void* dst, const void* src, size_t count)
{
	void* ret = dst;
	assert(dst);
	assert(src);
	while (count--) {
		*(char*)dst = *(char*)src;
		dst = (char*)dst + 1;
		src = (char*)src + 1;
	}
	return(ret);
}
//7 模拟实现memmove
void* memmove(void* dst, const void* src, size_t count)
{
	void* ret = dst;
	if (dst <= src || (char*)dst >= ((char*)src + count)) {
		while (count--) {
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else {
		dst = (char*)dst + count - 1;
		src = (char*)src + count - 1;
		while (count--) {
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return(ret);
}
//8 模拟实现memset
void* my_memset(void* e1, int val, size_t num)
{
	void* ret = e1;
	assert(e1 != NULL);
	while (num--)
	{
		*(char*)e1 = (char)val;
		e1 = (char*)e1 + 1;
	}
	return ret;
}
//9 模拟实现memcmp
int my_memcmp(const void* ptr1, const void* ptr2, size_t num)
{
	assert(ptr1 != NULL);
	assert(ptr2 != NULL);
	while (num--)
	{
		if (*(char*)ptr1 != *(char*)ptr2)
		{
			return *(char*)ptr1 - *(char*)ptr2;
		}
		ptr1 = (char*)ptr1 + 1;
		ptr2 = (char*)ptr2 + 1;
	}
	return 0;
}*/