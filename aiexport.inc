//from cexport.inc

// --------------------------------------------------------------------------------
type
  {** Describes an file format which Assimp can export to. Use #aiGetExportFormatCount() to
    * learn how many export formats the current Assimp build supports and #aiGetExportFormatDescription()
    * to retrieve a description of an export format option.
    *}
  TaiExportFormatDesc = record
    /// a short string ID to uniquely identify the export format. Use this ID string to
    /// specify which file format you want to export to when calling #aiExportScene().
    /// Example: "dae" or "obj"
    id: PChar;

    /// A short description of the file format to present to users. Useful if you want
    /// to allow the user to select an export format.
    description: PChar;

    /// Recommended file extension for the exported file in lower case.
    fileExtension: PChar;
  end;
  PaiExportFormatDesc = ^TaiExportFormatDesc;

// --------------------------------------------------------------------------------
{** Returns the number of export file formats available in the current Assimp build.
 * Use aiGetExportFormatDescription() to retrieve infos of a specific export format.
 *}
function aiGetExportFormatCount(): size_t cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetExportFormatCount' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Returns a description of the nth export file format. Use #aiGetExportFormatCount()
 * to learn how many export formats are supported. 
 * @param pIndex Index of the export format to retrieve information for. Valid range is
 *    0 to #aiGetExportFormatCount()
 * @return A description of that specific export format. NULL if pIndex is out of range.
 *}
function aiGetExportFormatDescription(pIndex: size_t): PaiExportFormatDesc cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetExportFormatDescription' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Create a modifiable copy of a scene.
 *  This is useful to import files via Assimp, change their topology and 
 *  export them again. Since the scene returned by the various importer functions
 *  is const, a modifiable copy is needed.
 *  @param pIn Valid scene to be copied
 *  @param pOut Receives a modifyable copy of the scene. Use aiFreeScene() to
 *    delete it again.
 *}
procedure aiCopyScene(const pIn: PaiScene; pOut: PPaiScene) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiCopyScene' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Frees a scene copy created using aiCopyScene() *}
procedure aiFreeScene(const pIn: PaiScene) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiFreeScene' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Exports the given scene to a chosen file format and writes the result file(s) to disk.
* @param pScene The scene to export. Stays in possession of the caller, is not changed by the function.
*   The scene is expected to conform to Assimp's Importer output format as specified
*   in the @link data Data Structures Page @endlink. In short, this means the model data
*   should use a right-handed coordinate systems, face winding should be counter-clockwise
*   and the UV coordinate origin is assumed to be in the upper left. If your input data
*   uses different conventions, have a look at the last parameter.
* @param pFormatId ID string to specify to which format you want to export to. Use 
* aiGetExportFormatCount() / aiGetExportFormatDescription() to learn which export formats are available.
* @param pFileName Output file to write
* @param pIO custom IO implementation to be used. Use this if you use your own storage methods.
*   If none is supplied, a default implementation using standard file IO is used. Note that
*   #aiExportSceneToBlob is provided as convenience function to export to memory buffers.
* @param pPreprocessing Accepts any choice of the #aiPostProcessing enumerated
*   flags, but in reality only a subset of them makes sense here. Specifying
*   'preprocessing' flags is useful if the input scene does not conform to 
*   Assimp's default conventions as specified in the @link data Data Structures Page @endlink. 
*   In short, this means the geometry data should use a right-handed coordinate systems, face 
*   winding should be counter-clockwise and the UV coordinate origin is assumed to be in
*   the upper left. The #aiProcess_MakeLeftHanded, #aiProcess_FlipUVs and 
*   #aiProcess_FlipWindingOrder flags are used in the import side to allow users
*   to have those defaults automatically adapted to their conventions. Specifying those flags
*   for exporting has the opposite effect, respectively. Some other of the
*   #aiPostProcessSteps enumerated values may be useful as well, but you'll need
*   to try out what their effect on the exported file is. Many formats impose
*   their own restrictions on the structure of the geometry stored therein,
*   so some preprocessing may have little or no effect at all, or may be
*   redundant as exporters would apply them anyhow. A good example 
*   is triangulation - whilst you can enforce it by specifying
*   the #aiProcess_Triangulate flag, most export formats support only
*   triangulate data so they would run the step anyway.
*
*   If assimp detects that the input scene was directly taken from the importer side of 
*   the library (i.e. not copied using aiCopyScene and potetially modified afterwards), 
*   any postprocessing steps already applied to the scene will not be applied again, unless
*   they show non-idempotent behaviour (#aiProcess_MakeLeftHanded, #aiProcess_FlipUVs and 
*   #aiProcess_FlipWindingOrder).
* @return a status code indicating the result of the export
* @note Use aiCopyScene() to get a modifiable copy of a previously
*   imported scene.
*}
function aiExportScene(const pScene: PaiScene; const pFormatId: PChar; const pFileName: PChar; pPreprocessing: CUInt): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiExportScene' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Exports the given scene to a chosen file format using custom IO logic supplied by you.
* @param pScene The scene to export. Stays in possession of the caller, is not changed by the function.
* @param pFormatId ID string to specify to which format you want to export to. Use 
* aiGetExportFormatCount() / aiGetExportFormatDescription() to learn which export formats are available.
* @param pFileName Output file to write
* @param pIO custom IO implementation to be used. Use this if you use your own storage methods.
*   If none is supplied, a default implementation using standard file IO is used. Note that
*   #aiExportSceneToBlob is provided as convenience function to export to memory buffers.
* @param pPreprocessing Please see the documentation for #aiExportScene
* @return a status code indicating the result of the export
* @note Include <aiFileIO.h> for the definition of #aiFileIO.
* @note Use aiCopyScene() to get a modifiable copy of a previously
*   imported scene.
*}
function aiExportSceneEx(const pScene: PaiScene; const pFormatId: PChar; const pFileName: PChar; pIO: PaiFileIO; pPreprocessing: CUInt): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiExportSceneEx' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
type
  {** Describes a blob of exported scene data. Use #aiExportSceneToBlob() to create a blob containing an
  * exported scene. The memory referred by this structure is owned by Assimp. Use #aiReleaseExportedFile()
  * to free its resources. Don't try to free the memory on your side - it will crash for most build configurations
  * due to conflicting heaps.
  *
  * Blobs can be nested - each blob may reference another blob, which may in turn reference another blob and so on.
  * This is used when exporters write more than one output file for a given #aiScene. See the remarks for
  * #aiExportDataBlob::name for more information.
  *}
  PaiExportDataBlob = ^TaiExportDataBlob;
  TaiExportDataBlob = record
    /// Size of the data in bytes
    size: size_t;

    /// The data.
    data: Pointer;

    {** Name of the blob. An empty string always
	indicates the first (and primary) blob,
	which contains the actual file data.
        Any other blobs are auxiliary files produced
	by exporters (i.e. material files). Existence
	of such files depends on the file format. Most
	formats don't split assets across multiple files.

	If used, blob names usually contain the file
	extension that should be used when writing
	the data to disc.
     *}
    name: TaiString;

    {** Pointer to the next blob in the chain or NULL if there is none. *}
    next: PaiExportDataBlob;
  end;

// --------------------------------------------------------------------------------
{** Exports the given scene to a chosen file format. Returns the exported data as a binary blob which
* you can write into a file or something. When you're done with the data, use #aiReleaseExportBlob()
* to free the resources associated with the export. 
* @param pScene The scene to export. Stays in possession of the caller, is not changed by the function.
* @param pFormatId ID string to specify to which format you want to export to. Use 
* #aiGetExportFormatCount() / #aiGetExportFormatDescription() to learn which export formats are available.
* @param pPreprocessing Please see the documentation for #aiExportScene
* @return the exported data or NULL in case of error
*}
function aiExportSceneToBlob(const pScene: PaiScene; const pFormatId: PChar; pPreprocessing: CUInt): PaiExportDataBlob cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiExportSceneToBlob' {$ENDIF} {$ENDIF};

// --------------------------------------------------------------------------------
{** Releases the memory associated with the given exported data. Use this function to free a data blob
* returned by aiExportScene(). 
* @param pData the data blob returned by #aiExportSceneToBlob
*}
procedure aiReleaseExportBlob(const pData: PaiExportDataBlob) cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiReleaseExportBlob' {$ENDIF} {$ENDIF};
