/******************************************************************************/
/* Library functions for the pr sample programs.                              */
/******************************************************************************/
#ifndef __LIB__INCL
#define __LIB__INCL
/******************************************************************************/
#if defined WIN32
	#include <conio.h>
	#include <io.h>
#elif defined LINUX
	#include <unistd.h>
	#include <dirent.h>
	#include <sys/select.h>
#else
	#error OS or compiler error in __lib__.h
#endif
/******************************************************************************/
#include <sys/timeb.h>
#include <sys/stat.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4786)		/* truncated debug info */
#endif

using namespace std;
#if defined(GX_NAMESPACES) || defined(LINUX)
	using namespace gx;
#endif
/******************************************************************************/
/* Class for helper functions.                                                */
/******************************************************************************/
class Lib {
	int _loop_count;
	int _err_count;
	int _process_avg;

	timeb _start_, _stop_;
	timeb _process_start_, _process_stop_;

public:
	Lib(void): _loop_count(0), _err_count(0), _process_avg(0) {};

	/**************************************************************************/
	/* Converts int to string.                                                */
	/**************************************************************************/
	string itos(int i) {
		stringstream s;
		s << i;
		return s.str();
	}

	/**************************************************************************/
	/* Detects keyboard events.                                               */
	/**************************************************************************/
	bool KbHit(void) {
		#ifdef _MSC_VER
			return _kbhit() != 0;
		#elif defined WIN32
			return kbhit() != 0;
		#elif defined LINUX
			fd_set rfds;
			FD_ZERO(&rfds);
			FD_SET(STDIN_FILENO, &rfds);

			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = 0;

			return select(STDIN_FILENO+1, &rfds, NULL, NULL, &tv) > 0;
		#endif
	}

	/**************************************************************************/
	/* Displays the string and flushes the output stream.                     */
	/**************************************************************************/
	void Write(string str = "") {
		cout << str << flush;
	}

	/**************************************************************************/
	/* Displays the string.                                                   */
	/**************************************************************************/
	void WriteLine(string str = "") {
		cout << str << endl;
	}

	/**************************************************************************/
	/* Reads a string from the standard input.                                */
	/**************************************************************************/
	string ReadLine(string prompt = "") {
		string str;
		if (prompt != "") Write(prompt);
		cin >> str;
		return str;
	}

	/**************************************************************************/
	/* Displays the code and description of the underlying GX exception.      */
	/**************************************************************************/
	int DisplExcp(gxException& e) {
		if (e.GetErrorCode() != 0) {
			_err_count++;
			cerr << "Error (0x" << hex << setw(8) << setfill('0') << e.GetErrorCode() << "): " << e.GetErrorStringA() << endl;
		}
		return e.GetErrorCode();
	}

	/**************************************************************************/
	/* Displays the error message and exits the program.                      */
	/**************************************************************************/
	void Error(string str) {
		_err_count++;
		cerr << "Error: " << str << endl;
	}

	/**************************************************************************/
	/* Displays the start message and starts timer.                           */
	/**************************************************************************/
	void FunctionStart(string str = "") {
		Write(str + "... ");
		::ftime(&_start_);
	}

	/**************************************************************************/
	/* Displays the end message and returns the time elapsed in ms.           */
	/**************************************************************************/
	int FunctionEnd(void) {
		::ftime(&_stop_);
		int _function_time = (int)(_stop_.millitm + (_stop_.time - _start_.time) * 1000 - _start_.millitm);
		WriteLine("Done. (" + itos(_function_time) + " ms)");
		return _function_time;
	}

	/**************************************************************************/
	/* Displays the process start message and starts the process timer.       */
	/**************************************************************************/
	void ProcessStart(string str = "") {
		WriteLine("*** " + str + " [" + itos(++_loop_count) + "] ***");
		::ftime(&_process_start_);
	}

	/**************************************************************************/
	/* Displays the end message and returns the time elapsed in ms.           */
	/**************************************************************************/
	int ProcessEnd(void) {
		::ftime(&_process_stop_);
		int _process_time = (int)(_process_stop_.millitm + (_process_stop_.time - _process_start_.time) * 1000 - _process_start_.millitm);
		_process_avg = ((_loop_count-1) * _process_avg + _process_time) / _loop_count;
		WriteLine("*** Process time: " + itos(_process_time) + " ms, avg: " + itos(_process_avg) + "\n");
		return _process_time;
	}

	/**************************************************************************/
	/* Displays overall statistics.                                           */
	/**************************************************************************/
	int PrintStat(void) {
		WriteLine("\n*** Statistics ***\n");
		WriteLine("Number of loops : " + itos(_loop_count));
		WriteLine("Number of errors: " + itos(_err_count));
		WriteLine("Process average : " + itos(_process_avg) + " ms");
		WriteLine("");
		#ifdef WIN32
			system("pause");
		#endif
		return _loop_count;
	}

	/**************************************************************************/
	/* Saves binary data in file.                                             */
	/**************************************************************************/
	bool Save(string fn, void * data, int size) {
		FILE *fp;
		#if _MSC_VER >= 1400
			if (fopen_s(&fp, fn.c_str(), "wb")) fp = NULL;
		#else
			fp = fopen(fn.c_str(), "wb");
		#endif
		if (!fp) return false;
		if (fwrite(data, 1, size, fp) != (size_t)size) {
			fclose(fp);
			return false;
		} else {
			fclose(fp);
			return true;
		}
	}

	/**************************************************************************/
	/* Waits for a time specified in miliseconds.                             */
	/**************************************************************************/
	void Wait(int ms) {
		#if defined WIN32
			Sleep(ms);
		#elif defined LINUX
			sleep(ms/1000);
			usleep((ms%1000)*1000);
		#endif
	}

	/**************************************************************************/
	/* Waits for n seconds.                                                   */
	/**************************************************************************/
	void WaitForSec(int sec) {
		for (int i=sec; i>0; i--) {
			if (KbHit()) break;
			Write("\rWaiting for " + itos(i) + " sec...   ");
			Wait(1000);
		}
		Write("\r                                                             \r");
	}

	/**************************************************************************/
	/* Matches the entry against a mask.                                      */
	/**************************************************************************/
	bool Match(string entry, string mask) {
		if (entry == mask) return true;

		const char *s,*m;
		s = entry.c_str();
		m = mask.c_str();

		while (*s && *m) {
			// Continue on character match
			if (*s == *m) {s++; m++; continue;}

			// Continue on ? wildcard
			if (*m == '?') {s++; m++; continue;}

			// Check for * wildcard, recursively for each possible matching
			if (*m == '*') {
				m++;
				if (!*m) return true;
				while (*s && *m && *m != *s) s++;
				if (!*s) return false;
				if (Match(s,m)) return true;
				s++; m--;
				continue;
			}

			if (*m != *s) return false;
		}
		return (!*s && !*m);
	}

	/**************************************************************************/
	/* Checks if entry is a valid directory.                                  */
	/**************************************************************************/
	bool IsDir(string entry) {
		struct stat s;
		if (stat(entry.c_str(), &s)) return false;
		if (!(s.st_mode & S_IFDIR)) return false;
		return true;
	}

	/**************************************************************************/
	/* Checks if path is a regular file,                                      */
	/**************************************************************************/
	bool IsFile(string entry) {
		struct stat s;
		if (stat(entry.c_str(), &s)) return false;
		if (!(s.st_mode & S_IFREG)) return false;
		return true;
	}

	/**************************************************************************/
	/* Creates a list of filenames recursively browsing the subdirs too.      */
	/**************************************************************************/
	vector<string> FileList(string dirname, string mask) {
		vector<string> list;
		string dn;

		#if defined WIN32
			#if _MSC_VER >= 1400
				intptr_t d;
			#else
				int d;
			#endif
			struct _finddata_t de;
			#define DE_NAME de.name
		#elif defined LINUX
			DIR *d;
			struct dirent *de;
			#define DE_NAME de->d_name
		#endif

		if (!IsDir(dirname)) return list;

		#if defined WIN32
			dn = dirname + "\\*.*";
			#ifdef __BORLANDC__
				d = _findfirst((char*)dn.c_str(), &de);
			#else
				d = _findfirst(dn.c_str(), &de);
			#endif
			do {
		#elif defined LINUX
			d = opendir(dirname.c_str());
			if (!d) return list;
			while ((de = readdir(d))) {
		#endif
				if (!strcmp(DE_NAME, ".") || !strcmp(DE_NAME, "..")) continue;
				dn = dirname + "/" + DE_NAME;

				if (IsDir(dn)) {
					vector<string> _list = FileList(dn, mask);
					for (size_t i=0; i<_list.size(); i++) list.push_back(_list[i]);
				} else if (Match(DE_NAME, mask)) {
					list.push_back(dn);
				}
		#if defined LINUX
			}
			closedir(d);
		#elif defined WIN32
			} while (_findnext(d, &de) != -1);
			_findclose(d);
		#endif
		#undef DE_NAME

		return list;
	}
};
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(pop)
#endif
/******************************************************************************/
#endif /* __LIB__INCL */
/******************************************************************************/
