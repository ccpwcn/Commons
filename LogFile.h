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

// ��־�ļ���
typedef class LogFile
{
public:
	// ���캯����������־�ļ�
	LogFile( __in LPCTSTR lpLogFilename, BOOL bMode = FALSE );

	// ��������
	~LogFile();

	// ������־�ļ�
	BOOL CreateLogFile( __in LPCTSTR lpLogFilename );

	// ����־�ļ�д����־��Ϣ
	BOOL WriteLogInfo( __in LPCTSTR lpLogString );
	BOOL WriteLogInfo( __in LPCSTR lpLogString );
	BOOL WriteLoginfo( __in LPBYTE lpLogString );

	// ������־д��ģʽ
	void SetWriteLogMode( BOOL bMode );

	// ��ȡ��־�ļ��Ĵ�С
	ULONG GetLogFileSize();

	// �ر���־�ļ�
	BOOL CLoseLogFile();
private:
	// ��־�ļ�����
	TCHAR m_szLogFilename[MAX_PATH];

	// ��־�ļ�������Ϣ������
	TCHAR m_szLogStringBuffer[MAX_BUFF];

	// ��־�ļ�����Ϣ��Ŀ��������
	static ULONG m_ulLogItemCounts;

	// ��־�ļ�д��ģʽ��Ϊ��ʱִ�и��Ǹ�ʽ��Ϊ��ʱִ��׷��ģʽ
	BOOL m_isOverWriteLog;

	// ��־�ļ���С
	ULONG m_ulLogFileSize;

	// ��־�ļ����
	HANDLE m_hLogFile;

	// ��ȡ��־д��ʱ��ʱ����Ϣ
	BOOL GetTimeInfo( __out LPTSTR lpTimeInfoString );
}LOGFILE, *LPLOGFILE;





