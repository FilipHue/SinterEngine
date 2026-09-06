#pragma once

#if defined(SE_DLL)
	#if defined(SE_BUILD_DLL)
		#define SE_API __declspec(dllexport)
	#else
		#define SE_API __declspec(dllimport)
	#endif // defined(SE_BUILD_DLL)
#else
	#define SE_API
#endif // defined(SE_DLL)
