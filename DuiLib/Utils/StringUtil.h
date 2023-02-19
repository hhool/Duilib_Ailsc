#pragma once

#include <string>

const std::string WHITE_SPACE_CHAR_SET = "\t\n\v\f\r ";
const std::string ALPHA_NUM_CHAR_SET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

class StringUtil
{
public:
	static std::string& ltrim(std::string& str, const std::string& chars = WHITE_SPACE_CHAR_SET);
	static std::string& rtrim(std::string& str, const std::string& chars = WHITE_SPACE_CHAR_SET);
	static std::string& trim(std::string& str, const std::string& chars = WHITE_SPACE_CHAR_SET);

    static bool UnicodeToAnsi(const std::wstring &src, std::string &result);
    static bool AnsiToUnicode(const std::string &src, std::wstring &result);
    static bool UnicodeToUtf8(const std::wstring &src, std::string &result);
    static bool Utf8ToUnicode(const std::string &src, std::wstring &result);
    static bool AnsiToUtf8(const std::string &src, std::string &result);
    static bool Utf8ToAnsi(const std::string &src, std::string &result);
	static std::string Easy_UnicodeToAnsi(const std::wstring &src);
    static std::wstring Easy_AnsiToUnicode(const std::string &src);
    static std::string Easy_UnicodeToUtf8(const std::wstring &src);
    static std::wstring Easy_Utf8ToUnicode(const std::string &src);
    static std::string Easy_AnsiToUtf8(const std::string &src);
    static std::string Easy_Utf8ToAnsi(const std::string &src);

	static std::string UrlEncode(const std::string& str);
	static std::string UrlDecode(const std::string& str);

	static std::string UUIDString();
	static std::string RandomString(int len, unsigned int seed, const std::string& char_set = ALPHA_NUM_CHAR_SET);
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#define W2ASTR(wstr)	(StringUtil::Easy_UnicodeToAnsi(wstr))
#define W2ACSTR(wstr)	(StringUtil::Easy_UnicodeToAnsi(wstr).c_str())
#define A2WSTR(str)		(StringUtil::Easy_AnsiToUnicode(str))
#define A2WCSTR(str)	(StringUtil::Easy_AnsiToUnicode(str).c_str())
#define W2UTF8STR(str)	(StringUtil::Easy_UnicodeToUtf8(str))
#define W2UTF8CSTR(str)	(StringUtil::Easy_UnicodeToUtf8(str).c_str())
#define UTF82WSTR(str)	(StringUtil::Easy_Utf8ToUnicode(str))
#define UTF82WCSTR(str)	(StringUtil::Easy_Utf8ToUnicode(str).c_str())
#define A2UTF8STR(str)	(StringUtil::Easy_AnsiToUtf8(str))
#define A2UTF8CSTR(str)	(StringUtil::Easy_AnsiToUtf8(str).c_str())
#define UTF82ASTR(str)	(StringUtil::Easy_Utf8ToAnsi(str))
#define UTF82ACSTR(str)	(StringUtil::Easy_Utf8ToAnsi(str).c_str())
