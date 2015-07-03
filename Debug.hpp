/*
 ----------------------------------------------------------------------------------
	Debug.h
	模块功能：调试组件
 ----------------------------------------------------------------------------------
 */
#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <string.h>
#include <crtdbg.h>
#include <strsafe.h>
#include <locale.h>
#include <string.h>


#ifndef _DEBUG

// 函数功能：输出（生成）调试信息
// 形参说明：__in_opt const TCHAR *fmt, ... - 可变形参，使用方法和printf相同
// 使用方法：此函数内部有封装机制，可以实现是否输出调试信息，默认DEBUG版本输出，Release版本不输出
size_t DebugPrintf(__in_opt const TCHAR *fmt, ...);
//////////////////////////////////////////////////////////////////////////

static size_t DebugPrintf(__in_opt const TCHAR *fmt, ...)
{
	TCHAR szBuffer[1024] = {0};
	va_list args;

	va_start(args, fmt);
	if (FAILED(StringCchVPrintf(szBuffer, 1023, fmt, args)))
	{
		va_end(args);
		return 0;
	}

	// 此处已经是成功取得的输出结果
	OutputDebugString(szBuffer);

	va_end(args);
	return _tcslen(szBuffer);
}
#else
	#define DebugPrintf(format, ...)
#endif

// 函数功能：输出（生成）调试信息
// 形参说明：__in_opt const TCHAR *fmt, ... - 可变形参，使用方法和printf相同
// 使用方法：此函数内部有封装机制，可以实现是否输出调试信息，默认DEBUG版本输出，Release版本不输出
size_t MessageBoxPrintf(__in const HWND hWnd, __in LPCTSTR lpszCaption, __in const UINT uType, __in_opt const TCHAR *fmt, ...);
//////////////////////////////////////////////////////////////////////////

static size_t MessageBoxPrintf(__in const HWND hWnd, __in LPCTSTR lpszCaption, __in const UINT uType, __in_opt const TCHAR *fmt, ...)
{
	TCHAR szBuffer[1024] = {0};
	va_list args;

	va_start(args, fmt);
	if (FAILED(StringCchVPrintf(szBuffer, 1023, fmt, args)))
	{
		OutputDebugString(_T("StringCchVPrintf failed."));
		va_end(args);
		return 0;
	}

	// 此处已经是成功取得的输出结果
	MessageBox(hWnd, szBuffer, lpszCaption, uType);

	va_end(args);
	return _tcslen(szBuffer);
}

// CRT 标准运行库中的字符串处理函数异常错误响应回调函数
void InvalidParameterHandle( LPCTSTR lpExpression, LPCTSTR lpFunction, LPCTSTR lpFile, UINT line, uintptr_t uip = NULL );

// CRT 标准运行库中的字符串处理函数异常错误响应回调函数
static void InvalidParameterHandle( LPCTSTR lpExpression, LPCTSTR lpFunction, LPCTSTR lpFile, UINT line, uintptr_t uip )
{
	TCHAR szErrorReason[BUFSIZ] = {0};
	switch( errno )
	{
	case E2BIG:StringCchCopy( szErrorReason, BUFSIZ - 1, _T("argument list too long") ); break;
	case EACCES: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("permission denied") ); break;
	case EADDRINUSE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("address in use") ); break;
	case EADDRNOTAVAIL: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("address not available") ); break;
	case EAFNOSUPPORT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("address family not supported") ); break;
	case EAGAIN: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("resource unavailable try again") ); break;
	case EALREADY: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("connection already in progress") ); break;
	case EBADF: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("bad file descriptor") ); break;
	case EBADMSG: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("bad message") ); break;
	case EBUSY: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("device or resource busy") ); break;
	case ECANCELED: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("operation canceled") ); break;
	case ECHILD: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no child process") ); break;
	case ECONNABORTED: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("connection aborted") ); break;
	case ECONNREFUSED: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("connection refused") ); break;
	case ECONNRESET: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("connection reset") ); break;
	case EDEADLK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("resource deadlock would occur") ); break;
	case EDESTADDRREQ: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("destination address required") ); break;
	case EDOM: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("argument out of domain") ); break;
	case EEXIST: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("file exists") ); break;
	case EFAULT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("bad address") ); break;
	case EFBIG: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("file too large") ); break;
	case EHOSTUNREACH: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("host unreachable") ); break;
	case EIDRM: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("identifier removed") ); break;
	case EILSEQ: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("illegal byte sequence") ); break;
	case EINPROGRESS: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("operation in progress") ); break;
	case EINTR: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("interrupted") ); break;
	case EINVAL: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("invalid argument") ); break;
	case EIO: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("io error") ); break;
	case EISCONN: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("already connected") ); break;
	case EISDIR: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("is a directory") ); break;
	case ELOOP: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("too many synbolic link levels") ); break;
	case EMFILE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("too many files open") ); break;
	case EMLINK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("too many links") ); break;
	case EMSGSIZE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("message size") ); break;
	case ENAMETOOLONG: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("filename too long") ); break;
	case ENETDOWN: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("network down") ); break;
	case ENETRESET: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("network reset") ); break;
	case ENETUNREACH: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("network unreachable") ); break;
	case ENFILE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("too many files open in system") ); break;
	case ENOBUFS: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no buffer space") ); break;
	case ENODATA: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no message available") ); break;
	case ENODEV: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no such device") ); break;
	case ENOENT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no such file or directory") ); break;
	case ENOEXEC: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("executable format error") ); break;
	case ENOLCK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no lock available") ); break;
	case ENOLINK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no link") ); break;
	case ENOMEM: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not enough memory") ); break;
	case ENOMSG: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no message") ); break;
	case ENOPROTOOPT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no protocol option") ); break;
	case ENOSPC: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no space on device") ); break;
	case ENOSR: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no stream resources") ); break;
	case ENOSTR: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not a stream") ); break;
	case ENOSYS: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("function not supported") ); break;
	case ENOTCONN: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not connected") ); break;
	case ENOTDIR: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not a directory") ); break;
	case ENOTEMPTY: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("directory not empty") ); break;
	case ENOTRECOVERABLE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("state not recoverable") ); break;
	case ENOTSOCK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not a socket") ); break;
	case ENOTSUP: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("not supported") ); break;
	case ENOTTY: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("inappropriate io control operation") ); break;
	case ENXIO: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no such device or address") ); break;
	case EOPNOTSUPP: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("operation not supported") ); break;
	case EOTHER: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("other") ); break;
	case EOVERFLOW: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("value too large") ); break;
	case EOWNERDEAD: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("owner dead") ); break;
	case EPERM: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("operation not permitted") ); break;
	case EPIPE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("broken pipe") ); break;
	case EPROTO: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("protocol error") ); break;
	case EPROTONOSUPPORT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("protocol not supported") ); break;
	case EPROTOTYPE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("wrong protocol type") ); break;
	case ERANGE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("result out of range") ); break;
	case EROFS: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("read only file system") ); break;
	case ESPIPE: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("invalid seek") ); break;
	case ESRCH: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("no such process") ); break;
	case ETIME: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("stream timeout") ); break;
	case ETIMEDOUT: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("timed out") ); break;
	case ETXTBSY: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("text file busy") ); break;
	case EWOULDBLOCK: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("operation would block") ); break;
	case EXDEV: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("cross device link") ); break;
	default: StringCchCopy( szErrorReason, BUFSIZ - 1, _T("unknow error") ); break;
	}

	TCHAR szPromptErrorMsg[BUFSIZ] = {0};
	StringCchPrintf( szPromptErrorMsg, BUFSIZ - 1, _T("程序出现异常。\n>错误原因：%s。\n"), szErrorReason );
#ifdef _DEBUG
	TCHAR szErrorStr[BUFSIZ] = {0};
	StringCchPrintf( 
		szErrorStr, 
		BUFSIZ - 1,
		_T(">错误文件：%s。\n>错误函数：%s。\n>错误位置：%d。\n"), 		
		lpFile, 
		lpFunction, 
		line );
	StringCchCat( szPromptErrorMsg, BUFSIZ - 1, szErrorStr );
#endif

	MessageBox( NULL, szPromptErrorMsg, _T("汗，竟然出错了......"), MB_OK | MB_ICONEXCLAMATION );
	// Sleep(5000);
	// exit(-255);
}
