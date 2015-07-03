#include "stdafx.h"

#include <Windows.h>
#include <tchar.h>
#include "LogFile.h"

// д����־����Ŀ������̬��Ա����
ULONG LOGFILE::m_ulLogItemCounts = 0;

// ���캯��������һ����־�ļ����󣬴���һ����־�ļ�
// �β��б�LPCTSTR ��־���ƣ� BOOL��־д��ģʽ��Ĭ��ֵΪ�٣���������ԭ����־��׷��ģʽ��
LOGFILE::LogFile( __in LPCTSTR lpLogFilename, BOOL bMode )
{
	m_isOverWriteLog = bMode;
	m_ulLogFileSize = 0;

	// ����־�ļ����Ա��̳е�Ӧ�ó�������ȡ
	_SECURITY_ATTRIBUTES logFileSa;
	logFileSa.nLength = sizeof(_SECURITY_ATTRIBUTES);
	logFileSa.lpSecurityDescriptor = NULL;
	logFileSa.bInheritHandle = TRUE;

	if ( bMode )
	{
		// ����ģʽ������־�ļ�
		m_hLogFile = CreateFile( lpLogFilename, GENERIC_WRITE, FILE_SHARE_READ, &logFileSa, CREATE_ALWAYS | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
	else
	{
		// ׷��ģʽ������־�ļ�
		m_hLogFile = CreateFile( lpLogFilename, FILE_APPEND_DATA, FILE_SHARE_READ, &logFileSa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
}

// ��׼��������
LOGFILE::~LogFile()
{
	// �ر���־�ļ�
	CloseHandle( m_hLogFile );
}

// �������ܣ�������־�ļ�
// �β��б�LPCTSTR��־�ļ�����
// ����ֵ�������ɹ������棬����ʧ�ܷ��ؼ�
BOOL LOGFILE::CreateLogFile( __in LPCTSTR lpLogFilename )
{
	// ����־�ļ����Ա��̳е�Ӧ�ó�������ȡ
	_SECURITY_ATTRIBUTES logFileSa;
	logFileSa.nLength = sizeof(_SECURITY_ATTRIBUTES);
	logFileSa.lpSecurityDescriptor = NULL;
	logFileSa.bInheritHandle = TRUE;

	if ( m_isOverWriteLog )
	{
		// ����ģʽ������־�ļ�
		m_hLogFile = CreateFile( lpLogFilename, GENERIC_WRITE, FILE_SHARE_READ, &logFileSa, CREATE_ALWAYS | TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}
	else
	{
		// ׷��ģʽ������־�ļ�
		m_hLogFile = CreateFile( lpLogFilename, FILE_APPEND_DATA, FILE_SHARE_READ, &logFileSa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_ARCHIVE, NULL );
	}

	return m_hLogFile != INVALID_HANDLE_VALUE;
}

// �������ܣ�����־�ļ�д����־��Ϣ
// �β��б�LPCTSTR��Ҫд����־������
// ����ֵ��д��ɹ������棬ʧ�ܷ��ؼ�
// ע������˺���Ŀǰ�����������֧��Unicode��־��Ϣд�룬ANSI��־��Ϣд�룬�޷���char��־��Ϣд��
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

// �������ܣ���ȡ��ǰʱ����Ϣ����־��Ϣд��ʱ������д���������û��鿴��
// �β��б�LPTSTR�����������ȡ����ʱ����Ϣ�洢�ڴ˲�����
// ����ֵ����ȡ�ɹ������棬��ȡʧ�ܷ��ؼ�
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

// �������ܣ��ر���־�ļ�
// ����ֵ���رճɹ�����TRUE��ʧ�ܷ���FALSE
BOOL LOGFILE::CLoseLogFile()
{
	HRESULT fnRet0 = 0;
	fnRet0 = CloseHandle( m_hLogFile );
	return fnRet0 == S_OK;
}