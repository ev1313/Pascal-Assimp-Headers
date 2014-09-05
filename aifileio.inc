//from fileio.inc

type
  PaiFileIO = ^TaiFileIO;
  PaiFile = ^TaiFile;

  // aiFile callbacks
  TaiFileWriteProc = function(a: PaiFile; const b: PChar; c, d: size_t): size_t;
  TaiFileReadProc = function(a: PaiFile; b: PChar; c, d: size_t): size_t;
  TaiFileTellProc = function(a: PaiFile): size_t;
  TaiFileFlushProc = procedure(a: PaiFile);
  TaiFileSeek = function(a: PaiFile; b: size_t; c: TaiOrigin): TaiReturn;

  // aiFileIO callbacks
  TaiFileOpenProc = function(a: PaiFileIO; b, c: PChar): PaiFile;
  TaiFileCloseProc = procedure(a: PaiFileIO; b: PaiFile);

  // Represents user-defined data
  TaiUserData = PChar;

// ----------------------------------------------------------------------------------
  {** @brief C-API: File system callbacks
   *
   *  Provided are functions to open and close files. Supply a custom structure to
   *  the import function. If you don't, a default implementation is used. Use custom
   *  file systems to enable reading from other sources, such as ZIPs
   *  or memory locations. *}
  TaiFileIO = record
    {** Function used to open a new file *}
    OpenProc: TaiFileOpenProc;
    {** Function used to close an existing file *}
    CloseProc: TaiFileCloseProc;
    {** User-defined, opaque data *}
    UserData: TaiUserData;
  end;

// ----------------------------------------------------------------------------------
  {** @brief C-API: File callbacks
   *
   *  Actually, it's a data structure to wrap a set of fXXXX (e.g fopen)
   *  replacement functions.
   *
   *  The default implementation of the functions utilizes the fXXX functions from
   *  the CRT. However, you can supply a custom implementation to Assimp by
   *  delivering a custom aiFileIO. Use this to enable reading from other sources,
   *  such as ZIP archives or memory locations. *}
  TaiFile = record
    {** Callback to read from a file *}
    ReadProc: TaiFileReadProc;

    {** Callback to write to a file *}
    WriteProc: TaiFileWriteProc;

    {** Callback to retrieve the current position of
     *  the file cursor (ftell())
     *}
    TellProc: TaiFileTellProc;

    {** Callback to retrieve the size of the file,
     *  in bytes
     *}
    FileSizeProc: TaiFileTellProc;

    {** Callback to set the current position
     * of the file cursor (fseek())
     *}
    SeekProc: TaiFileSeek;

    {** Callback to flush the file contents
     *}
    FlushProc: TaiFileFlushProc;

    {** User-defined, opaque data
     *}
    UserData: TaiUserData;
  end;
