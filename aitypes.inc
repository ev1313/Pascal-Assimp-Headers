//from types.h

{** Maximum dimension for strings, ASSIMP strings are zero terminated. *}
const
  MAXLEN = 1024;

type
// ----------------------------------------------------------------------------------
  {** Represents a plane in a three-dimensional, euclidean space *}
  TaiPlane = packed record
    //! Plane equation
    a,b,c,d: Single;
  end;
  PaiPlane = ^TaiPlane;

// ----------------------------------------------------------------------------------
  {** Represents a ray *}
  TaiRay = packed record
    //! Position and direction of the ray
    pos, dir: TaiVector3D;
  end;
  PaiRay = ^TaiRay;

// ----------------------------------------------------------------------------------
  {** Represents a color in Red-Green-Blue space. *}
  TaiColor3D = packed record
    //! Red, green and blue color values
    r, g, b: Single;
  end;
  PaiColor3D = ^TaiColor3D;

// ----------------------------------------------------------------------------------
  {** Represents an UTF-8 string, zero byte terminated.
   *
   *  The character set of an aiString is explicitly defined to be UTF-8. This Unicode
   *  transformation was chosen in the belief that most strings in 3d files are limited
   *  to ASCII, thus the character set needed to be strictly ASCII compatible.
   *
   *  Most text file loaders provide proper Unicode input file handling, special unicode
   *  characters are correctly transcoded to UTF8 and are kept throughout the libraries'
   *  import pipeline.
   *
   *  For most applications, it will be absolutely sufficient to interpret the
   *  aiString as ASCII data and work with it as one would work with a plain char*.
   *  Windows users in need of proper support for i.e asian characters can use the
   *  #MultiByteToWideChar(), #WideCharToMultiByte() WinAPI functionality to convert the
   *  UTF-8 strings to their working character set (i.e. MBCS, WideChar).
   *
   *  We use this representation instead of std::string to be C-compatible. The
   *  (binary) length of such a string is limited to MAXLEN characters (including the
   *  the terminating zero).
   *}
  TaiString = packed record
    {** Binary length of the string excluding the terminal 0. This is NOT the
      *  logical length of strings containing UTF-8 multibyte sequences! It's
      *  the number of bytes from the beginning of the string to its end.*}
    length: size_t;

    {** String buffer. Size limit is MAXLEN *}
    data: array[0..MAXLEN - 1] of Char;
  end;
  PaiString = ^TaiString;

// ----------------------------------------------------------------------------------
  {**	Standard return type for some library functions.
   * Rarely used, and if, mostly in the C API.
   *}
const
  {** Indicates that a function was successful *}
  aiReturn_SUCCESS = $0;
  {** Indicates that a function failed *}
  aiReturn_FAILURE = -$1;
  {** Indicates that not enough memory was available
    * to perform the requested operation
    *}
  aiReturn_OUTOFMEMORY = -$3;
  // just for backwards compatibility, don't use these constants anymore
  AI_SUCCESS = aiReturn_SUCCESS;
  AI_FAILURE = aiReturn_FAILURE;
  AI_OUTOFMEMORY = aiReturn_OUTOFMEMORY;
type
  TaiReturn = Integer;

// ----------------------------------------------------------------------------------
  {** Seek origins (for the virtual file system API).
   *  Much cooler than using SEEK_SET, SEEK_CUR or SEEK_END.
   *}
const
  {** Beginning of the file *}
  aiOrigin_SET = $0;
  {** Current position of the file pointer *}
  aiOrigin_CUR = $1;
  {** End of the file, offsets must be negative *}
  aiOrigin_END = $2;
type
  TaiOrigin = Integer;

// ----------------------------------------------------------------------------------
  {** @brief Enumerates predefined log streaming destinations.
   *  Logging to these streams can be enabled with a single call to
   *   #LogStream::createDefaultStream or #aiAttachPredefinedLogStream(),
   *   respectively.
   *}
const
  {** Stream the log to a file *}
  aiDefaultLogStream_FILE = $1;
  {** Stream the log to std::cout *}
  aiDefaultLogStream_STDOUT = $2;
  {** Stream the log to std::cerr *}
  aiDefaultLogStream_STDERR = $4;
  {** MSVC only: Stream the log the the debugger
    * (this relies on OutputDebugString from the Win32 SDK)
    *}
  aiDefaultLogStream_DEBUGGER = $8;
  // just for backwards compatibility, don't use these constants anymore
  DLS_FILE     = aiDefaultLogStream_FILE;
  DLS_STDOUT   = aiDefaultLogStream_STDOUT;
  DLS_STDERR   = aiDefaultLogStream_STDERR;
  DLS_DEBUGGER = aiDefaultLogStream_DEBUGGER;

type
  TaiDefaultLogStream = Integer;

// ----------------------------------------------------------------------------------
  {** Stores the memory requirements for different components (e.g. meshes, materials,
   *  animations) of an import. All sizes are in bytes.
   *  @see Importer::GetMemoryRequirements()
   *}
  TaiMemoryInfo = packed record
    {** Storage allocated for texture data *}
    textures: CUInt;

    {** Storage allocated for material data  *}
    materials: CUInt;

    {** Storage allocated for mesh data *}
    meshes: CUInt;

    {** Storage allocated for node data *}
    nodes: CUInt;

    {** Storage allocated for animation data *}
    animations: CUInt;

    {** Storage allocated for camera data *}
    cameras: CUInt;

    {** Storage allocated for light data *}
    lights: CUInt;

    {** Total storage allocated for the full import. *}
    total: CUInt;
  end;
  PaiMemoryInfo = ^TaiMemoryInfo;
