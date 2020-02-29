#ifndef f7e7cac2_e432_52fc_4d79_ef383db318b0
#define f7e7cac2_e432_52fc_4d79_ef383db318b0

#if defined(LOTUSVFS_DLL) || defined(LOTUSVFS_AS_DLL)
	#ifdef LOTUSVFS_AS_DLL
		#ifdef _WIN32
			#define LOTUSVFS_API __declspec(dllimport)
		#else
			#define LOTUSVFS_API
		#endif
		#define LOTUSVFS_LOCAL
	#else
		#ifdef _WIN32
			#define LOTUSVFS_API __declspec(dllexport)
			#define LOTUSVFS_LOCAL
		#elif (defined(__GNUC__) && (__GNUC__ >= 4))
			#define LOTUSVFS_API __attribute__ ((visibility("default")))
			#define LOTUSVFS_LOCAL __attribute__ ((visibility("hidden")))
		#endif
	#endif
#else
	#define LOTUSVFS_API
	#define LOTUSVFS_LOCAL
#endif

#endif // f7e7cac2_e432_52fc_4d79_ef383db318b0
