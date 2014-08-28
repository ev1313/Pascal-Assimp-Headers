//from version.h

// ---------------------------------------------------------------------------
  {** @brief Returns a string with legal copyright and licensing information 
   *  about Assimp. The string may include multiple lines.
   *  @return Pointer to static string.
   *}
function aiGetLegalString: PChar cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetLegalString' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Returns the current minor version number of Assimp.
   *  @return Minor version of the Assimp runtime the application was
   *    linked/built against
   *}
function aiGetVersionMinor: CUInt cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetVersionMinor' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Returns the current major version number of Assimp.
   *  @return Major version of the Assimp runtime the application was
   *    linked/built against
   *}
function aiGetVersionMajor: CUInt cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetVersionMajor' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Returns the repository revision of the Assimp runtime.
   *  @return SVN Repository revision number of the Assimp runtime the
   *          application was linked/built against.
   *}
function aiGetVersionRevision: CUInt cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetVersionRevision' {$ENDIF} {$ENDIF};

const
  //! Assimp was compiled as a shared object (Windows: DLL)
  ASSIMP_CFLAGS_SHARED         = $1;
  //! Assimp was compiled against STLport
  ASSIMP_CFLAGS_STLPORT        = $2;
  //! Assimp was compiled as a debug build
  ASSIMP_CFLAGS_DEBUG          = $4;

  //! Assimp was compiled with ASSIMP_BUILD_BOOST_WORKAROUND defined
  ASSIMP_CFLAGS_NOBOOST        = $8;
  //! Assimp was compiled with ASSIMP_BUILD_SINGLETHREADED defined
  ASSIMP_CFLAGS_SINGLETHREADED = $10;

// ---------------------------------------------------------------------------
  {** @brief Returns assimp's compile flags
   *  @return Any bitwise combination of the ASSIMP_CFLAGS_xxx constants.
   *}
function aiGetCompileFlags: CUInt cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetCompileFlags' {$ENDIF} {$ENDIF};
