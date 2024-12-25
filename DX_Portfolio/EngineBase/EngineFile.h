#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>

#include "EnginePath.h"

const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
public:
	ENGINEAPI UEngineFile();

	ENGINEAPI UEngineFile(const std::string& _Path);
	ENGINEAPI UEngineFile(std::string_view _Path);
	ENGINEAPI UEngineFile(std::filesystem::path _Path);
	ENGINEAPI UEngineFile(const UEnginePath& _Path);
	ENGINEAPI ~UEngineFile();

	// Write
	void Write(class UEngineSerializer& _Ser);
	void Read(class UEngineSerializer& _Ser);

	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	ENGINEAPI void FileOpen(const char* _Mode);
	void Close();

	int GetFileSize();

	ENGINEAPI std::string GetAllFileText();

// 기능 클래스 랩핑
private:
	// 상수
	// _MAX_DIR 윈도우에 의존적인 프로그램
	FILE* File = nullptr;
};

