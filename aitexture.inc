//from texture.h

// --------------------------------------------------------------------------------
{** @def AI_MAKE_EMBEDDED_TEXNAME
 *  Used to build the reserved path name used by the material system to
 *  reference textures that are embedded into their corresponding
 *  model files. The parameter specifies the index of the texture
 *  (zero-based, in the aiScene::mTextures array)
 *}     {
#if (!defined AI_MAKE_EMBEDDED_TEXNAME)
#	define AI_MAKE_EMBEDDED_TEXNAME(_n_) "*" # _n_
#endif }

// --------------------------------------------------------------------------------
  {** @brief Helper structure to represent a texel in a ARGB8888 format
  *
  *  Used by aiTexture.
  *}
  TaiTexel = packed record
    b,g,r,a: Byte;
  end;
  PaiTexel = ^TaiTexel;

// --------------------------------------------------------------------------------
  {** Helper structure to describe an embedded texture
   *
   * Normally textures are contained in external files but some file formats embed
   * them directly in the model file. There are two types of embedded textures:
   * 1. Uncompressed textures. The color data is given in an uncompressed format.
   * 2. Compressed textures stored in a file format like png or jpg. The raw file
   * bytes are given so the application must utilize an image decoder (e.g. DevIL) to
   * get access to the actual color data.
   *}
  TaiTexture = packed record
    {** Width of the texture, in pixels
     *
     * If mHeight is zero the texture is compressed in a format
     * like JPEG. In this case mWidth specifies the size of the
     * memory area pcData is pointing to, in bytes.
     *}
    mWidth: CUInt;

    {** Height of the texture, in pixels
     *
     * If this value is zero, pcData points to an compressed texture
     * in any format (e.g. JPEG).
     *}
    mHeight: CUInt;

    {** A hint from the loader to make it easier for applications
     *  to determine the type of embedded compressed textures.
     *
     * If mHeight != 0 this member is undefined. Otherwise it
     * is set set to '\\0\\0\\0\\0' if the loader has no additional
     * information about the texture file format used OR the
     * file extension of the format without a trailing dot. If there
     * are multiple file extensions for a format, the shortest
     * extension is chosen (JPEG maps to 'jpg', not to 'jpeg').
     * E.g. 'dds\\0', 'pcx\\0', 'jpg\\0'.  All characters are lower-case.
     * The fourth character will always be '\\0'.
     *}
    achFormatHint: array[0..3] of Char;

    {** Data of the texture.
      *
      * Points to an array of mWidth * mHeight aiTexel's.
      * The format of the texture data is always ARGB8888 to
      * make the implementation for user of the library as easy
      * as possible. If mHeight = 0 this is a pointer to a memory
      * buffer of size mWidth containing the compressed texture
      * data. Good luck, have fun!
      *}
    pcData: PaiTexel;
  end;
  PaiTexture = ^TaiTexture;
  PPaiTexture = ^PaiTexture;
