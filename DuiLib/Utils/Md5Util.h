/*******************************************************************************
*
* Copyright (C) 2013 - 2015, Jeffery Jiang, <china_jeffery@163.com>.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
*
* Expect bugs
*
* Please use and enjoy. Please let me know of any bugs/mods/improvements
* that you have found/implemented and I will fix/incorporate them into this
* file.
*
*******************************************************************************/
#pragma once

#include <string>
namespace Md5Util
{
	std::string GetStringMd5(const std::string& str);
	std::string GetStringMd5(const void* pData, unsigned int iDataSize);

	std::string GetFileMd5(const std::string& strFilePath);
	std::string GetFileMd5W(const std::wstring& strFilePath);
};