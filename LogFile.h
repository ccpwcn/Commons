#pragma once

#include <Windows.h>
#include <tchar.h>

#ifndef MAX_BUFF
	#define MAX_BUFF 2048
#endif

#ifndef MAX_LOADSTRING
	#define MAX_LOADSTRING 100
#endif

extern TCHAR szTitle[MAX_LOADSTRING];

// 日志文件类
typedef class LogFile
{
public:
	// 构造函数，创建日志文件
	LogFile( __in LPCTSTR lpLogFilename, BOOL bMode = FALSE );

	// 析构函数
	~LogFile();

	// 创建日志文件
	BOOL CreateLogFile( __in LPCTSTR lpLogFilename );

	// 向日志文件写入日志信息
	BOOL WriteLogInfo( __in LPCTSTR lpLogString );
	BOOL WriteLogInfo( __in LPCSTR lpLogString );
	BOOL WriteLoginfo( __in LPBYTE lpLogString );

	// 设置日志写入模式
	void SetWriteLogMode( BOOL bMode );

	// 获取日志文件的大小
	ULONG GetLogFileSize();

	// 关闭日志文件
	BOOL CLoseLogFile();
private:
	// 日志文件名称
	TCHAR m_szLogFilename[MAX_PATH];

	// 日志文件数据信息缓冲区
	TCHAR m_szLogStringBuffer[MAX_BUFF];

	// 日志文件中信息条目数量计数
	static ULONG m_ulLogItemCounts;

	// 日志文件写入模式，为真时执行覆盖格式，为假时执行追加模式
	BOOL m_isOverWriteLog;

	// 日志文件大小
	ULONG m_ulLogFileSize;

	// 日志文件句柄
	HANDLE m_hLogFile;

	// 获取日志写入时的时间信息
	BOOL GetTimeInfo( __out LPTSTR lpTimeInfoString );
}LOGFILE, *LPLOGFILE;





