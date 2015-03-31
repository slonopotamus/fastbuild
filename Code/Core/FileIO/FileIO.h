// FileIO.h
//------------------------------------------------------------------------------
#pragma once
#ifndef CORE_FILEIO_FILEIO_H
#define CORE_FILEIO_FILEIO_H

// Includes
//------------------------------------------------------------------------------
#include "Core/Containers/Array.h"
#include "Core/Strings/AString.h"

// Defines
//------------------------------------------------------------------------------
#define MAX_PATH 260

// FileIO
//------------------------------------------------------------------------------
class FileIO
{
public:
	static bool FileExists( const char * fileName );
	static bool FileDelete( const char * fileName );
	static bool FileCopy( const char * srcFileName, const char * dstFileName, bool allowOverwrite = true );
	static bool FileMove( const AString & srcFileName, const AString & dstFileName );

	// directory listing
	static bool GetFiles( const AString & path,
						  const AString & wildCard,
						  bool recurse,
						  Array< AString > * results );
	struct FileInfo
	{
		AString		m_Name;
		uint32_t	m_Attributes;
		uint64_t	m_LastWriteTime;
		uint64_t	m_Size;

		bool		IsReadOnly() const;
	};
	static bool GetFilesEx( const AString & path,
							const AString & wildCard,
							bool recurse,
							Array< FileInfo > * results );
	static bool GetFileInfo( const AString & fileName, FileInfo & info );

	static bool GetCurrentDir( AString & output );
	static bool SetCurrentDir( const AString & dir );
	static bool GetTempDir( AString & output );
	static bool DirectoryCreate( const AString & path );
	static bool DirectoryExists( const AString & path );
	static bool EnsurePathExists( const AString & path );

	static bool CreateTempPath( const char * tempPrefix, AString & path );

	static uint64_t GetFileLastWriteTime( const AString & fileName );
	static bool		SetFileLastWriteTime( const AString & fileName, uint64_t fileTime );

	static bool		SetReadOnly( const char * fileName, bool readOnly );
	static bool		GetReadOnly( const AString & fileName );

    #if defined( __WINDOWS__ )
        static void		WorkAroundForWindowsFilePermissionProblem( const AString & fileName );
    #else
        FORCE_INLINE static void WorkAroundForWindowsFilePermissionProblem( const AString & ) {}
    #endif

private:
	static void GetFilesRecurse( AString & path, 
								 const AString & wildCard,
								 Array< AString > * results );
	static void GetFilesNoRecurse( const char * path, 
								   const char * wildCard,
								   Array< AString > * results );
	static void GetFilesRecurseEx( AString & path, 
								 const AString & wildCard,
								 Array< FileInfo > * results );
	static void GetFilesNoRecurseEx( const char * path, 
								   const char * wildCard,
								   Array< FileInfo > * results );
};

//------------------------------------------------------------------------------
#endif // CORE_FILEIO_FILEIO_H