////////////////////////////////////////////////////////////////////////////////
//
// Written/Rewritten by Jeffery Jiang (china_jeffery@163.com)
//
// You may opt to use, copy, modify, merge, publish, distribute and/or sell
// copies of the Software, and permit persons to whom the Software is
// furnished to do so.
//
// Expect bugs.
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements
// that you have found/implemented and I will fix/incorporate them into this
// file.
//
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <windows.h>
#include <assert.h>
#include <vector>
#include "StringUtil.h"

#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

std::string& StringUtil::ltrim(std::string& str, const std::string& chars)
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

std::string& StringUtil::rtrim(std::string& str, const std::string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

std::string& StringUtil::trim(std::string& str, const std::string& chars)
{
	return ltrim(rtrim(str, chars), chars);
}

bool StringUtil::UnicodeToAnsi(const std::wstring &src, std::string & result)
{
    int ascii_size = ::WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
    if (ascii_size == 0)
    {
        return false;
    }

    std::vector<char> result_buf(ascii_size, 0);

	int result_size =::WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, &result_buf[0], ascii_size, NULL, NULL);
    if (result_size != ascii_size)
    {
        return false;
    }

    result = &result_buf[0];
    return true;
}

bool StringUtil::AnsiToUnicode(const std::string &src, std::wstring & result)
{
    int wide_size = ::MultiByteToWideChar (CP_ACP, 0, src.c_str(), -1, NULL, 0);
    if (wide_size == 0)
    {
        return false;
    }

    std::vector<wchar_t> result_buf(wide_size, 0);
		
	int result_size = MultiByteToWideChar (CP_ACP, 0, src.c_str(), -1, &result_buf[0], wide_size);
    if (result_size != wide_size)
    {
        return false;
    }

    result = &result_buf[0];
    return true;
}

bool StringUtil::UnicodeToUtf8(const std::wstring &src, std::string & result)
{
    int utf8_size = ::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8_size == 0)
    {
        return false;
    }

    std::vector<char> result_buf(utf8_size, 0);

    int result_size = ::WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, &result_buf[0], utf8_size, NULL, NULL);
    if (result_size != utf8_size)
    {
        return false;
    }

    result = &result_buf[0];
    return true;
}

bool StringUtil::Utf8ToUnicode(const std::string &src, std::wstring & result)
{
    int wide_size = ::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
    if (wide_size == 0)
    {
        return false;
    }

    std::vector<wchar_t> result_buf(wide_size, 0);

    int result_size = ::MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, &result_buf[0], wide_size);
    if (result_size != wide_size)
    {
        return false;
    }

    result = &result_buf[0];
    return true;
}

bool StringUtil::AnsiToUtf8(const std::string& src, std::string &result)
{
    std::wstring wstr;
    if(!AnsiToUnicode(src, wstr))
        return false;

    return UnicodeToUtf8(wstr, result);
}

bool StringUtil::Utf8ToAnsi(const std::string& src, std::string &result)
{
    std::wstring wstr;
    if(!Utf8ToUnicode(src, wstr))
        return false;

    return UnicodeToAnsi(wstr, result);
}

std::string StringUtil::Easy_UnicodeToAnsi(const std::wstring &src)
{
    std::string strRet;
    if(!UnicodeToAnsi(src, strRet))
        return "";

    return strRet;
}

std::wstring StringUtil::Easy_AnsiToUnicode(const std::string &src)
{
    std::wstring strRet;
    if(!AnsiToUnicode(src, strRet))
        return L"";

    return strRet;
}

std::string StringUtil::Easy_UnicodeToUtf8(const std::wstring &src)
{
    std::string strRet;
    if(!UnicodeToUtf8(src, strRet))
        return "";

    return strRet;
}

std::wstring StringUtil::Easy_Utf8ToUnicode(const std::string &src)
{
    std::wstring strRet;
    if(!Utf8ToUnicode(src, strRet))
        return L"";

    return strRet;
}

std::string StringUtil::Easy_AnsiToUtf8(const std::string &src)
{
    std::string strRet;
    if(!AnsiToUtf8(src, strRet))
        return "";

    return strRet;
}

std::string StringUtil::Easy_Utf8ToAnsi(const std::string &src)
{
    std::string strRet;
    if(!Utf8ToAnsi(src, strRet))
        return "";

    return strRet;
}

unsigned char ToHex( unsigned char x )
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex( unsigned char x )
{
	unsigned char y=' ';  
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;  
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;  
	else if (x >= '0' && x <= '9') y = x - '0';  
	else assert(0);  
	return y;
}

std::string StringUtil::UrlEncode( const std::string& str )
{
	std::string strTemp = "";  
	size_t length = str.length();  
	for (size_t i = 0; i < length; i++)  
	{  
		if (isalnum((unsigned char)str[i]) ||   
			(str[i] == '-') ||  
			(str[i] == '_') ||   
			(str[i] == '.') ||   
			(str[i] == '~'))  
			strTemp += str[i];  
// 		else if (str[i] == ' ')  
// 			strTemp += "+";  
		else  
		{  
			strTemp += '%';  
			strTemp += ToHex((unsigned char)str[i] >> 4);  
			strTemp += ToHex((unsigned char)str[i] % 16);  
		}  
	}  
	return strTemp;
}

std::string StringUtil::UrlDecode( const std::string& str )
{
	std::string strTemp = "";  
	size_t length = str.length();  
	for (size_t i = 0; i < length; i++)  
	{  
		if (str[i] == '+') strTemp += ' ';  
		else if (str[i] == '%')  
		{  
			assert(i + 2 < length);  
			unsigned char high = FromHex((unsigned char)str[++i]);  
			unsigned char low = FromHex((unsigned char)str[++i]);  
			strTemp += high*16 + low;  
		}  
		else strTemp += str[i];  
	}  
	return strTemp;
}

std::string StringUtil::UUIDString()
{
    GUID guid = { 0 };
	if (S_OK== ::CoCreateGuid(&guid))
    {
        wchar_t szBuf[64] = L"";
        StringFromGUID2(guid, &szBuf[0], 64);

        return Easy_UnicodeToAnsi(szBuf);
    }
    return "";
}
std::string StringUtil::RandomString(int len, unsigned int seed, const std::string& char_set)
{
	size_t nchars = char_set.length();
	if (len == 0 || nchars == 0)
	{
		return "";
	}

	char* buf = new char[len];
	if (buf == NULL)
	{
		return "";
	}

	if (seed > 0)
	{
		srand(seed);
	}

	for (int i = 0; i < len; ++i)
	{
		buf[i] = char_set[rand() % nchars];
	}

	std::string result(buf, len);
	delete[] buf;

	return result;
}
