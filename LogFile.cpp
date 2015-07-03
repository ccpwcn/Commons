#include "stdafx.h"

#include <Windows.h>
#include <tchar.h>
#include "LogFile.h"

// 写入日志的条目数，静态成员变量
ULONG LOGFILE::m_ulLogItemCounts = 0;

// 构造函数：构造一个日志文件对象，创建一个日志文件
// 形参列表：LPCTSTR 日志名称， BOOL日志写入模式，默认值为假，即不覆盖原有日志（追加模式）
LOGFILE::LogFile( __in LPCTSTR lpLogFilename, BOOL bMode )
{
	m_isOverWriteLog = bMode;
	m_ulLogFileSize = 0;

	// 此日志文件可以被继承的应用程序对象读取
	_SECURITY_ATTRIBUTES logFileSa;
	logFileSa.nLength = sizeof(_SECURITY_ATTRIBUTES);
	logFileSa.lpSecurityDescriptor = NULL;
	logFileSa.bInheritHandle = TRUE;

	if ( bMode )
	{
		// 覆盖模式创建日志文件
		m_hLogFile = CreateFile( lpLogFilename, GENERIC_WRITE, FILE_SHARE_READ, &logFileSa, CREATE_ALWAYS | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
	else
	{
		// 追加模式创建日志文件
		m_hLogFile = CreateFile( lpLogFilename, FILE_APPEND_DATA, FILE_SHARE_READ, &logFileSa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
}

// 标准析构函数
LOGFILE::~LogFile()
{
	// 关闭日志文件
	CloseHandle( m_hLogFile );
}

// 函数功能：创建日志文件
// 形参列表：LPCTSTR日志文件名称
// 返回值：创建成功返回真，创建失败返回假
BOOL LOGFILE::CreateLogFile( __in LPCTSTR lpLogFilename )
{
	// 此日志文件可以被继承的应用程序对象读取
	_SECURITY_ATTRIBUTES logFileSa;
	logFileSa.nLength = sizeof(_SECURITY_ATTRIBUTES);
	logFileSa.lpSecurityDescriptor = NULL;
	logFileSa.bInheritHandle = TRUE;

	if ( m_isOverWriteLog )
	{
		// 覆盖模式创建日志文件
		m_hLogFile = CreateFile( lpLogFilename, GENERIC_WRITE, FILE_SHARE_READ, &logFileSa, CREATE_ALWAYS | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
	else
	{
		// 追加模式创建日志文件
		m_hLogFile = CreateFile( lpLogFilename, FILE_APPEND_DATA, FILE_SHARE_READ, &logFileSa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}

	return m_hLogFile != INVALID_HANDLE_VALUE;
}

// 函数功能：向日志文件写入日志信息
// 形参列表：LPCTSTR将要写入日志的数据
// 返回值：写入成功返回真，失败返回假
// 注意事项：此函数目前有三个重载项，支持Unicode日志信息写入，ANSI日志信息写入，无符号char日志信息写入
BOOL LOGFILE::WriteLogInfo( __in LPCTSTR lpLogString )
{
	if ( _tcslen(lpLogString) >= MAX_BUFF - 1 )
	{
		return FALSE;
	}
	
	GetTimeInfo( m_szLogStringBuffer );
	TCHAR szTemp[MAX_BUFF] = {0};
	_stprintf_s( szTemp, MAX_BUFF, _T("[%s]%ld-> %s\t%s\r\n"), szTitle, m_ulLogItemCounts++, m_szLogStringBuffer, lpLogString );

	DWORD NumberOfBytesWritten = 0;
	DebugInfo.PrintDbgInfo( szTemp );
	char szWriteBuf[MAX_BUFF] = {0};
	ConvertStr_U2A( szTemp, szWriteBuf );
	WriteFile( m_hLogFile, szWriteBuf, strlen(szWriteBuf), &NumberOfBytesWritten, NULL );

	memset( m_szLogStringBuffer, 0, sizeof(m_szLogStringBuffer) );
	return NumberOfBytesWritten != 0;
}
BOOL LOGFILE::WriteLogInfo( __in LPCSTR lpLogString )
{
	return FALSE;
}
BOOL LOGFILE::WriteLoginfo( __in LPBYTE lpLogString )
{
	return FALSE;
}

// 函数功能：获取当前时间信息，日志信息写入时会优先写入此项，便于用户查看。
// 形参列表：LPTSTR输出参数，获取到的时间信息存储在此参数中
// 返回值：获取成功返回真，获取失败返回假
BOOL LOGFILE::GetTimeInfo( __out LPTSTR lpTimeInfoString )
{
	if ( lpTimeInfoString == NULL )
	{
		return FALSE;
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
	_stprintf_s( lpTimeInfoString, 50, _T("%02d:%02d:%02d.%03d"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds );

	return TRUE;
}

// 函数功能：关闭日志文件
// 返回值：关闭成功返回TRUE，失败返回FALSE
BOOL LOGFILE::CLoseLogFile()
{
	HRESULT fnRet0 = 0;
	fnRet0 = CloseHandle( m_hLogFile );
	return fnRet0 == S_OK;
}