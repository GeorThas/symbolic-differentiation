#pragma once
#define MyFunctions __declspec(dllexport)

extern "C" {
	MyFunctions int SubNumbers(int a, int b);
}

extern "C" {
	MyFunctions int AddNumbers(int a, int b);
}

extern "C" {
	MyFunctions void GetValue(char* str, int strlen);
}