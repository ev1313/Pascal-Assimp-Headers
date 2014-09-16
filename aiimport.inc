//from cimport.h

type
  TaiLogStreamCallback = procedure(const a: PChar {* message *}; b: PChar {* user *});

// --------------------------------------------------------------------------------
  {** C-API: Represents a log stream. A log stream receives all log messages and
   *  streams them _somewhere_.
   *  @see aiGetPredefinedLogStream
   *  @see aiAttachLogStream
   *  @see aiDetachLogStream *}
// --------------------------------------------------------------------------------
  TaiLogStream = record
	{** callback to be called *}
	callback: TaiLogStreamCallback;

	{** user data to be passed to the callback *}
	user: PChar;
  end;
  PaiLogStream = ^TaiLogStream;

// --------------------------------------------------------------------------------
  {** C-API: Represents an opaque set of settings to be used during importing.
   *  @see aiCreatePropertyStore
   *  @see aiReleasePropertyStore
   *  @see aiImportFileExWithProperties
   *  @see aiSetPropertyInteger
   *  @see aiSetPropertyFloat
   *  @see aiSetPropertyString
   *  @see aiSetPropertyMatrix
   *}
// --------------------------------------------------------------------------------
  TaiPropertyStore = record
    sentinel: Char; 
  end;
  PaiPropertyStore = ^TaiPropertyStore;

const
  AI_FALSE = 0;
  AI_TRUE = 1;

type
  {** Our own C boolean type *}
  TaiBool = Integer;

// --------------------------------------------------------------------------------
{** Reads the given file and returns its content.
 * 
 * If the call succeeds, the imported data is returned in an aiScene structure. 
 * The data is intended to be read-only, it stays property of the ASSIMP 
 * library and will be stable until aiReleaseImport() is called. After you're 
 * done with it, call aiReleaseImport() to free the resources associated with 
 * this file. If the import fails, NULL is returned instead. Call 
 * aiGetErrorString() to retrieve a human-readable error text.
 * @param pFile Path and filename of the file to be imported, 
 *   expected to be a null-terminated c-string. NULL is not a valid value.
 * @param pFlags Optional post processing steps to be executed after 
 *   a successful import. Provide a bitwise combination of the 
 *   #aiPostProcessSteps flags.
 * @return Pointer to the imported data or NULL if the import failed. 
 *}
function aiImportFile(const pFile: PChar; pFlags: CUInt): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportFile' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Reads the given file using user-defined I/O functions and returns 
 *   its content.
 * 
 * If the call succeeds, the imported data is returned in an aiScene structure. 
 * The data is intended to be read-only, it stays property of the ASSIMP 
 * library and will be stable until aiReleaseImport() is called. After you're 
 * done with it, call aiReleaseImport() to free the resources associated with 
 * this file. If the import fails, NULL is returned instead. Call 
 * aiGetErrorString() to retrieve a human-readable error text.
 * @param pFile Path and filename of the file to be imported, 
 *   expected to be a null-terminated c-string. NULL is not a valid value.
 * @param pFlags Optional post processing steps to be executed after 
 *   a successful import. Provide a bitwise combination of the
 *   #aiPostProcessSteps flags.
 * @param pFS aiFileIO structure. Will be used to open the model file itself
 *   and any other files the loader needs to open.  Pass NULL to use the default
 *   implementation.
 * @return Pointer to the imported data or NULL if the import failed.  
 * @note Include <aiFileIO.h> for the definition of #aiFileIO.
 *}
function aiImportFileEx(const pFile: PChar; pFlags: CUInt; pFS: PaiFileIO): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportFileEx' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Same as #aiImportFileEx, but adds an extra parameter containing importer settings.
 *
 * @param pProps #aiPropertyStore instance containing import settings. 
 * @see aiImportFileEx
 *}
function aiImportFileExWithProperties(const pFile: PChar; pFlags: CUInt; pFS: PaiFileIO; const pProps: PaiPropertyStore): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportFileExWithProperties' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Reads the given file from a given memory buffer,
 * 
 * If the call succeeds, the contents of the file are returned as a pointer to an
 * aiScene object. The returned data is intended to be read-only, the importer keeps 
 * ownership of the data and will destroy it upon destruction. If the import fails, 
 * NULL is returned.
 * A human-readable error description can be retrieved by calling aiGetErrorString(). 
 * @param pBuffer Pointer to the file data
 * @param pLength Length of pBuffer, in bytes
 * @param pFlags Optional post processing steps to be executed after 
 *   a successful import. Provide a bitwise combination of the 
 *   #aiPostProcessSteps flags. If you wish to inspect the imported
 *   scene first in order to fine-tune your post-processing setup,
 *   consider to use #aiApplyPostProcessing().
 * @param pHint An additional hint to the library. If this is a non empty string,
 *   the library looks for a loader to support the file extension specified by pHint
 *   and passes the file to the first matching loader. If this loader is unable to 
 *   completely the request, the library continues and tries to determine the file
 *   format on its own, a task that may or may not be successful. 
 *   Check the return value, and you'll know ...
 * @return A pointer to the imported data, NULL if the import failed.
 *
 * @note This is a straightforward way to decode models from memory
 * buffers, but it doesn't handle model formats that spread their 
 * data across multiple files or even directories. Examples include
 * OBJ or MD3, which outsource parts of their material info into
 * external scripts. If you need full functionality, provide
 * a custom IOSystem to make Assimp find these files and use
 * the regular aiImportFileEx()/aiImportFileExWithProperties() API.
 *}
function aiImportFileFromMemory(const pBuffer: PChar; pLength: CUInt; pFlags: CUInt; const pHint: PChar): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportFileFromMemory' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Same as #aiImportFileFromMemory, but adds an extra parameter containing importer settings.
 *
 * @param pProps #aiPropertyStore instance containing import settings. 
 * @see aiImportFileFromMemory
 *}
function aiImportFileFromMemoryWithProperties(const pBuffer: PChar; pLength: CUInt; pFlags: CUInt; const pHint: PChar; const pProps: PaiPropertyStore): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportFileFromMemoryWithProperties' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Apply post-processing to an already-imported scene.
 *
 * This is strictly equivalent to calling #aiImportFile()/#aiImportFileEx with the
 * same flags. However, you can use this separate function to inspect the imported 
 * scene first to fine-tune your post-processing setup. 
 * @param pScene Scene to work on.
 * @param pFlags Provide a bitwise combination of the #aiPostProcessSteps flags.
 * @return A pointer to the post-processed data. Post processing is done in-place,
 *   meaning this is still the same #aiScene which you passed for pScene. However,
 *   _if_ post-processing failed, the scene could now be NULL. That's quite a rare
 *   case, post processing steps are not really designed to 'fail'. To be exact, 
 *   the #aiProcess_ValidateDS flag is currently the only post processing step 
 *   which can actually cause the scene to be reset to NULL.
 *}
function aiApplyPostProcessing(const pScene: PaiScene; pFlags: CUInt): PaiScene cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiApplyPostProcessing' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Get one of the predefine log streams. This is the quick'n'easy solution to 
 *  access Assimp's log system. Attaching a log stream can slightly reduce Assimp's
 *  overall import performance. 
 *
 *  Usage is rather simple (this will stream the log to a file, named log.txt, and
 *  the stdout stream of the process:
 *  @code
 *    struct aiLogStream c;
 *    c = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"log.txt");
 *    aiAttachLogStream(&c);
 *    c = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
 *    aiAttachLogStream(&c);
 *  @endcode
 *
 *  @param pStreams One of the #aiDefaultLogStream enumerated values. 
 *  @param file Solely for the #aiDefaultLogStream_FILE flag: specifies the file to write to.
 *    Pass NULL for all other flags.
 *  @return The log stream. callback is set to NULL if something went wrong.
 *}
function aiGetPredefinedLogStream(pStreams: TaiDefaultLogStream; const file_: PChar): TaiLogStream cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetPredefinedLogStream' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Attach a custom log stream to the libraries' logging system.
 *
 *  Attaching a log stream can slightly reduce Assimp's overall import
 *  performance. Multiple log-streams can be attached. 
 *  @param stream Describes the new log stream.
 *  @note To ensure proepr destruction of the logging system, you need to manually
 *    call aiDetachLogStream() on every single log stream you attach. 
 *    Alternatively (for the lazy folks) #aiDetachAllLogStreams is provided.
 *}
procedure aiAttachLogStream(const stream: PaiLogStream) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiAttachLogStream' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Enable verbose logging. Verbose logging includes debug-related stuff and
 *  detailed import statistics. This can have severe impact on import performance
 *  and memory consumption. However, it might be useful to find out why a file
 *  didn't read correctly.
 *  @param d AI_TRUE or AI_FALSE, your decision.
 *}
procedure aiEnableVerboseLogging(d: TaiBool) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiEnableVerboseLogging' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Detach a custom log stream from the libraries' logging system.
 *
 *  This is the counterpart of #aiAttachPredefinedLogStream. If you attached a stream,
 *  don't forget to detach it again.
 *  @param stream The log stream to be detached.
 *  @return AI_SUCCESS if the log stream has been detached successfully.
 *  @see aiDetachAllLogStreams
 *}
function aiDetachLogStream(const stream: PaiLogStream): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiDetachLogStream' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Detach all active log streams from the libraries' logging system.
 *  This ensures that the logging system is terminated properly and all
 *  resources allocated by it are actually freed. If you attached a stream,
 *  don't forget to detach it again.
 *  @see aiAttachLogStream
 *  @see aiDetachLogStream
 *}
procedure aiDetachAllLogStreams() cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiDetachAllLogStreams' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Releases all resources associated with the given import process.
 *
 * Call this function after you're done with the imported data.
 * @param pScene The imported data to release. NULL is a valid value.
 *}
procedure aiReleaseImport(const pScene: PaiScene) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiReleaseImport' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Returns the error text of the last failed import process. 
 *
 * @return A textual description of the error that occurred at the last
 * import process. NULL if there was no error. There can't be an error if you
 * got a non-NULL #aiScene from #aiImportFile/#aiImportFileEx/#aiApplyPostProcessing.
 *}
function aiGetErrorString(): PChar cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetErrorString' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Returns whether a given file extension is supported by ASSIMP
 *
 * @param szExtension Extension for which the function queries support for.
 * Must include a leading dot '.'. Example: ".3ds", ".md3"
 * @return AI_TRUE if the file extension is supported.
 *}
function aiIsExtensionSupported(const szExtension: PChar): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiIsExtensionSupported' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Get a list of all file extensions supported by ASSIMP.
 *
 * If a file extension is contained in the list this does, of course, not
 * mean that ASSIMP is able to load all files with this extension.
 * @param szOut String to receive the extension list.
 * Format of the list: "*.3ds;*.obj;*.dae". NULL is not a valid parameter.
 *}
procedure aiGetExtensionList(szOut: PaiString) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetExtensionList' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Get the approximated storage required by an imported asset
 * @param pIn Input asset.
 * @param in Data structure to be filled. 
 *}
procedure aiGetMemoryRequirements(const pIn: PaiScene; in_: PaiMemoryInfo) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMemoryRequirements' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Create an empty property store. Property stores are used to collect import
 *  settings.
 * @return New property store. Property stores need to be manually destroyed using
 *   the #aiReleasePropertyStore API function.
 *}
function aiCreatePropertyStore(): PaiPropertyStore cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiCreatePropertyStore' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Delete a property store.
 * @param p Property store to be deleted.
 *}
procedure aiReleasePropertyStore(p: PaiPropertyStore) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiReleasePropertyStore' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Set an integer property. 
 *
 *  This is the C-version of #Assimp::Importer::SetPropertyInteger(). In the C 
 *  interface, properties are always shared by all imports. It is not possible to 
 *  specify them per import.
 *
 * @param szName Name of the configuration property to be set. All supported 
 *   public properties are defined in the config.h header file (#AI_CONFIG_XXX).
 * @param value New value for the property
 *}
procedure aiSetImportPropertyInteger(store: PaiPropertyStore; const szName: PChar; value: Integer) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiImportPropertyStore' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Set a floating-point property. 
 *
 *  This is the C-version of #Assimp::Importer::SetPropertyFloat(). In the C 
 *  interface, properties are always shared by all imports. It is not possible to 
 *  specify them per import.
 *
 * @param szName Name of the configuration property to be set. All supported 
 *   public properties are defined in the config.h header file (#AI_CONFIG_XXX).
 * @param value New value for the property
 *}
procedure aiSetImportPropertyFloat(store: PaiPropertyStore; const szName: PChar; value: Single) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiSetImportPropertyStore' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Set a string property. 
 *
 *  This is the C-version of #Assimp::Importer::SetPropertyString(). In the C 
 *  interface, properties are always shared by all imports. It is not possible to 
 *  specify them per import.
 *
 * @param property store to modify. Use #aiCreatePropertyStore to obtain a store.
 * @param szName Name of the configuration property to be set. All supported 
 *   public properties are defined in the config.h header file (#AI_CONFIG_XXX).
 * @param value New value for the property
 *}
procedure aiSetImportPropertyString(store: PaiPropertyStore; const szName: PChar; const st: PaiString) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiSetImportPropertyString' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Set a matrix property. 
 *
 *  This is the C-version of #Assimp::Importer::SetPropertyMatrix(). In the C 
 *  interface, properties are always shared by all imports. It is not possible to 
 *  specify them per import.
 *
 * @param property store to modify. Use #aiCreatePropertyStore to obtain a store.
 * @param szName Name of the configuration property to be set. All supported 
 *   public properties are defined in the config.h header file (#AI_CONFIG_XXX).
 * @param value New value for the property
 *}
procedure aiSetImportPropertyMatrix(store: PaiPropertyStore; const szName: PChar; const mat: PaiMatrix4x4) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiSetImportPropertyMatrix' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Construct a quaternion from a 3x3 rotation matrix.
 *  @param quat Receives the output quaternion.
 *  @param mat Matrix to 'quaternionize'.
 *  @see aiQuaternion(const aiMatrix3x3& pRotMatrix)
 *}
procedure aiCreateQuaternionFromMatrix(quat: PaiQuaternion; const mat: PaiMatrix3x3) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiCreateQuaternionFromMatrix' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Decompose a transformation matrix into its rotational, translational and
 *  scaling components.
 * 
 * @param mat Matrix to decompose
 * @param scaling Receives the scaling component
 * @param rotation Receives the rotational component
 * @param position Receives the translational component.
 * @see aiMatrix4x4::Decompose (aiVector3D&, aiQuaternion&, aiVector3D&) const;
 *}
procedure aiDecomposeMatrix(const mat: PaiMatrix4x4; scaling: PaiVector3D; rotation: PaiQuaternion; position: PaiVector3D) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiDecomposeMatrix' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Transpose a 4x4 matrix.
 *  @param mat Pointer to the matrix to be transposed
 *}
procedure aiTransposeMatrix4(mat: PaiMatrix4x4) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiTransposeMatrix4' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Transpose a 3x3 matrix.
 *  @param mat Pointer to the matrix to be transposed
 *}
procedure aiTransposeMatrix3(mat: PaiMatrix3x3) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiTransposeMatrix3' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Transform a vector by a 3x3 matrix
 *  @param vec Vector to be transformed.
 *  @param mat Matrix to transform the vector with.
 *}
procedure aiTransformVecByMatrix3(vec: PaiVector3D; const mat: PaiMatrix3x3) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiTransformVecByMatrix3' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Transform a vector by a 4x4 matrix
 *  @param vec Vector to be transformed.
 *  @param mat Matrix to transform the vector with.
 *}
procedure aiTransformVecByMatrix4(vec: PaiVector3D; const mat: PaiMatrix4x4) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiTransformVecByMatrix4' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Multiply two 4x4 matrices.
 *  @param dst First factor, receives result.
 *  @param src Matrix to be multiplied with 'dst'.
 *}
procedure aiMultiplyMatrix4(dst: PaiMatrix4x4; const src: PaiMatrix4x4) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiMultiplyMatrix4' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Multiply two 3x3 matrices.
 *  @param dst First factor, receives result.
 *  @param src Matrix to be multiplied with 'dst'.
 *}
procedure aiMultiplyMatrix3(dst: PaiMatrix3x3; const src: PaiMatrix3x3) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiMultiplyMatrix3' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Get a 3x3 identity matrix.
 *  @param mat Matrix to receive its personal identity
 *}
procedure aiIdentityMatrix3(mat: PaiMatrix3x3) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiIdentityMatrix3' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Get a 4x4 identity matrix.
 *  @param mat Matrix to receive its personal identity
 *}
procedure aiIdentityMatrix4(mat: PaiMatrix4x4) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiIdentityMatrix4' {$ENDIF} {$ENDIF};
