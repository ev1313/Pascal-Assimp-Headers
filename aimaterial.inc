//from material.h

// Name for default materials (2nd is used if meshes have UV coords)
const
  AI_DEFAULT_MATERIAL_NAME = 'DefaultMaterial';

// ---------------------------------------------------------------------------
  {** @brief Defines how the Nth texture of a specific type is combined with
   *  the result of all previous layers.
   *
   *  Example (left: key, right: value): <br>
   *  @code
   *  DiffColor0     - gray
   *  DiffTextureOp0 - aiTextureOpMultiply
   *  DiffTexture0   - tex1.png
   *  DiffTextureOp0 - aiTextureOpAdd
   *  DiffTexture1   - tex2.png
   *  @endcode
   *  Written as equation, the final diffuse term for a specific pixel would be:
   *  @code
   *  diffFinal = DiffColor0 * sampleTex(DiffTexture0,UV0) +
   *     sampleTex(DiffTexture1,UV0) * diffContrib;
   *  @endcode
   *  where 'diffContrib' is the intensity of the incoming light for that pixel.
   *}
const
  {** T = T1 * T2 *}
  aiTextureOp_Multiply = $0;

  {** T = T1 + T2 *}
  aiTextureOp_Add = $1;

  {** T = T1 - T2 *}
  aiTextureOp_Subtract = $2;

  {** T = T1 / T2 *}
  aiTextureOp_Divide = $3;

  {** T = (T1 + T2) - (T1 * T2) *}
  aiTextureOp_SmoothAdd = $4;

  {** T = T1 + (T2-0.5) *}
  aiTextureOp_SignedAdd = $5;

type
  TaiTextureOp = Integer;
  PaiTextureOP = ^TaiTextureOP;

// ---------------------------------------------------------------------------
  {** @brief Defines how UV coordinates outside the [0...1] range are handled.
   *
   *  Commonly refered to as 'wrapping mode'.
   *}
const
    {** A texture coordinate u|v is translated to u%1|v%1 *}
    aiTextureMapMode_Wrap = $0;
    {** Texture coordinates outside [0...1]
     *  are clamped to the nearest valid value.
     *}
    aiTextureMapMode_Clamp = $1;
    {** A texture coordinate u|v becomes u%1|v%1 if (u-(u%1))%2 is zero and
     *  1-(u%1)|1-(v%1) otherwise
     *}
    aiTextureMapMode_Mirror = $2;
    {** If the texture coordinates for a pixel are outside [0...1]
     *  the texture is not applied to that pixel
     *}
    aiTextureMapMode_Decal = $3;

type
  TaiTextureMapMode = Integer;
  PaiTextureMapMode = ^TaiTextureMapMode;

// ---------------------------------------------------------------------------
  {** @brief Defines how the mapping coords for a texture are generated.
   *
   *  Real-time applications typically require full UV coordinates, so the use of
   *  the aiProcess_GenUVCoords step is highly recommended. It generates proper
   *  UV channels for non-UV mapped objects, as long as an accurate description
   *  how the mapping should look like (e.g spherical) is given.
   *  See the #AI_MATKEY_MAPPING property for more details.
   *}
const
    {** The mapping coordinates are taken from an UV channel.
     *
     *  The #AI_MATKEY_UVWSRC key specifies from which UV channel
     *  the texture coordinates are to be taken from (remember,
     *  meshes can have more than one UV channel).
     *}
    aiTextureMapping_UV = $0;
    {** Spherical mapping *}
    aiTextureMapping_SPHERE = $1;
    {** Cylindrical mapping *}
    aiTextureMapping_CYLINDER = $2;
    {** Cubic mapping *}
    aiTextureMapping_BOX = $3;
    {** Planar mapping *}
    aiTextureMapping_PLANE = $4;
    {** Undefined mapping. Have fun. *}
    aiTextureMapping_OTHER = $5;

type
  TaiTextureMapping = Integer;
  PaiTextureMapping = ^TaiTextureMapping;

// ---------------------------------------------------------------------------
  {** @brief Defines the purpose of a texture
   *
   *  This is a very difficult topic. Different 3D packages support different
   *  kinds of textures. For very common texture types, such as bumpmaps, the
   *  rendering results depend on implementation details in the rendering
   *  pipelines of these applications. Assimp loads all texture references from
   *  the model file and tries to determine which of the predefined texture
   *  types below is the best choice to match the original use of the texture
   *  as closely as possible.<br>
   *
   *  In content pipelines you'll usually define how textures have to be handled,
   *  and the artists working on models have to conform to this specification,
   *  regardless which 3D tool they're using.
   *}
const
  {** Dummy value.
   *
   *  No texture, but the value to be used as 'texture semantic'
   *  (#aiMaterialProperty::mSemantic) for all material properties
   *  *not* related to textures.
   *}
  aiTextureType_NONE = $0;
  {** The texture is combined with the result of the diffuse
   *  lighting equation.
   *}
  aiTextureType_DIFFUSE = $1;
  {** The texture is combined with the result of the specular
   *  lighting equation.
   *}
  aiTextureType_SPECULAR = $2;
  {** The texture is combined with the result of the ambient
   *  lighting equation.
   *}
  aiTextureType_AMBIENT = $3;
  {** The texture is added to the result of the lighting
   *  calculation. It isn't influenced by incoming light.
   *}
  aiTextureType_EMISSIVE = $4;
  {** The texture is a height map.
   *
   *  By convention, higher gray-scale values stand for
   *  higher elevations from the base height.
   *}
  aiTextureType_HEIGHT = $5;
  {** The texture is a (tangent space) normal-map.
   *
   *  Again, there are several conventions for tangent-space
   *  normal maps. Assimp does (intentionally) not
   *  distinguish here.
   *}
  aiTextureType_NORMALS = $6;
  {** The texture defines the glossiness of the material.
   *
   *  The glossiness is in fact the exponent of the specular
   *  (phong) lighting equation. Usually there is a conversion
   *  function defined to map the linear color values in the
   *  texture to a suitable exponent. Have fun.
   *}
  aiTextureType_SHININESS = $7;
  {** The texture defines per-pixel opacity.
   *
   *  Usually 'white' means opaque and 'black' means
   *  'transparency'. Or quite the opposite. Have fun.
   *}
  aiTextureType_OPACITY = $8;
  {** Displacement texture
   *
   *  The exact purpose and format is application-dependent.
   *  Higher color values stand for higher vertex displacements.
   *}
  aiTextureType_DISPLACEMENT = $9;
  {** Lightmap texture (aka Ambient Occlusion)
   *
   *  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
   *  covered by this material property. The texture contains a
   *  scaling value for the final color value of a pixel. Its
   *  intensity is not affected by incoming light.
   *}
  aiTextureType_LIGHTMAP = $A;

  {** Reflection texture
   *
   * Contains the color of a perfect mirror reflection.
   * Rarely used, almost never for real-time applications.
   *}
  aiTextureType_REFLECTION = $B;

  {** Unknown texture
   *
   *  A texture reference that does not match any of the definitions
   *  above is considered to be 'unknown'. It is still imported,
   *  but is excluded from any further postprocessing.
   *}
  aiTextureType_UNKNOWN = $C;
  AI_TEXTURE_TYPE_MAX = aiTextureType_UNKNOWN;

type
  TaiTextureType = Integer;
  PaiTextureType = ^TaiTextureType;

// ---------------------------------------------------------------------------
  {** @brief Defines all shading models supported by the library
   *
   *  The list of shading modes has been taken from Blender.
   *  See Blender documentation for more information. The API does
   *  not distinguish between "specular" and "diffuse" shaders (thus the
   *  specular term for diffuse shading models like Oren-Nayar remains
   *  undefined). <br>
   *  Again, this value is just a hint. Assimp tries to select the shader whose
   *  most common implementation matches the original rendering results of the
   *  3D modeller which wrote a particular model as closely as possible.
   *}
const
  {** Flat shading. Shading is done on per-face base,
   *  diffuse only. Also known as 'faceted shading'.
   *}
  aiShadingMode_Flat = $1;

  {** Simple Gouraud shading. *}
  aiShadingMode_Gouraud = $2;

  {** Phong-Shading - *}
  aiShadingMode_Phong = $3;

  {** Phong-Blinn-Shading *}
  aiShadingMode_Blinn	= $4;

  {** Toon-Shading per pixel
   *
   *  Also known as 'comic' shader.
   *}
  aiShadingMode_Toon = $5;

  {** OrenNayar-Shading per pixel
   *
   *  Extension to standard Lambertian shading, taking the
   *  roughness of the material into account
   *}
  aiShadingMode_OrenNayar = $6;

  {** Minnaert-Shading per pixel
   *
   *  Extension to standard Lambertian shading, taking the
   *  "darkness" of the material into account
   *}
  aiShadingMode_Minnaert = $7;

  {** CookTorrance-Shading per pixel
   *
   *  Special shader for metallic surfaces.
   *}
  aiShadingMode_CookTorrance = $8;

  {** No shading at all. Constant light influence of 1.0. *}
  aiShadingMode_NoShading = $9;

  {** Fresnel shading *}
  aiShadingMode_Fresnel = $a;

type
  TaiShadingMode = Integer;
  PaiShadingMode = ^TaiShadingMode;

// ---------------------------------------------------------------------------
  {** @brief Defines some mixed flags for a particular texture.
   *
   *  Usually you'll instruct your cg artists how textures have to look like ...
   *  and how they will be processed in your application. However, if you use
   *  Assimp for completely generic loading purposes you might also need to
   *  process these flags in order to display as many 'unknown' 3D models as
   *  possible correctly.
   *
   *  This corresponds to the #AI_MATKEY_TEXFLAGS property.
   *}
const
  {** The texture's color values have to be inverted (componentwise 1-n) *}
  aiTextureFlags_Invert = $1;

  {** Explicit request to the application to process the alpha channel
   *  of the texture.
   *
   *  Mutually exclusive with #aiTextureFlags_IgnoreAlpha. These
   *  flags are set if the library can say for sure that the alpha
   *  channel is used/is not used. If the model format does not
   *  define this, it is left to the application to decide whether
   *  the texture alpha channel - if any - is evaluated or not.
   *}
  aiTextureFlags_UseAlpha = $2;

  {** Explicit request to the application to ignore the alpha channel
   *  of the texture.
   *
   *  Mutually exclusive with #aiTextureFlags_UseAlpha.
   *}
  aiTextureFlags_IgnoreAlpha = $4;

type
  TaiTextureFlags = Integer;
  PaiTextureFlags = ^TaiTextureFlags;

// ---------------------------------------------------------------------------
  {** @brief Defines alpha-blend flags.
   *
   *  If you're familiar with OpenGL or D3D, these flags aren't new to you.
   *  They define *how* the final color value of a pixel is computed, basing
   *  on the previous color at that pixel and the new color value from the
   *  material.
   *  The blend formula is:
   *  @code
   *    SourceColor * SourceBlend + DestColor * DestBlend
   *  @endcode
   *  where <DestColor> is the previous color in the framebuffer at this
   *  position and <SourceColor> is the material colro before the transparency
   *  calculation.<br>
   *  This corresponds to the #AI_MATKEY_BLEND_FUNC property.
   *}
const
  {**
   *  Formula:
   *  @code
   *  SourceColor*SourceAlpha + DestColor*(1-SourceAlpha)
   *  @endcode
   *}
  aiBlendMode_Default = $0;

  {** Additive blending
   *
   *  Formula:
   *  @code
   *  SourceColor*1 + DestColor*1
   *  @endcode
   *}
  aiBlendMode_Additive = $1;

  // we don't need more for the moment, but we might need them
  // in future versions ...
type
  TaiBlendMode = Integer;
  PaiBlendMode = ^TaiBlendMode;

// ---------------------------------------------------------------------------
  {** @brief Defines how an UV channel is transformed.
   *
   *  This is just a helper structure for the #AI_MATKEY_UVTRANSFORM key.
   *  See its documentation for more details.
   *
   *  Typically you'll want to build a matrix of this information. However,
   *  we keep separate scaling/translation/rotation values to make it
   *  easier to process and optimize UV transformations internally.
   *}
  TaiUVTransform = packed record
    {** Translation on the u and v axes.
     *
     *  The default value is (0|0).
     *}
    mTranslation: TaiVector2D;

    {** Scaling on the u and v axes.
     *
     *  The default value is (1|1).
     *}
    mScaling: TaiVector2D;

    {** Rotation - in counter-clockwise direction.
     *
     *  The rotation angle is specified in radians. The
     *  rotation center is 0.5f|0.5f. The default value
     *  0.f.
     *}
    mRotation: Single;
  end;
  PaiUVTransform = ^TaiUVTransform;

//! @cond AI_DOX_INCLUDE_INTERNAL
// ---------------------------------------------------------------------------
  {** @brief A very primitive RTTI system for the contents of material
   *  properties.
   *}
const
  {** Array of single-precision (32 Bit) floats
   *
   *  It is possible to use aiGetMaterialInteger[Array]() (or the C++-API
   *  aiMaterial::Get()) to query properties stored in floating-point format.
   *  The material system performs the type conversion automatically.
   *}
  aiPTI_Float   = $1;
  {** The material property is an aiString.
   *
   *  Arrays of strings aren't possible, aiGetMaterialString() (or the
   *  C++-API aiMaterial::Get()) *must* be used to query a string property.
   *}
  aiPTI_String  = $3;
  {** Array of (32 Bit) integers
   *
   *  It is possible to use aiGetMaterialFloat[Array]() (or the C++-API
   *  aiMaterial::Get()) to query properties stored in integer format.
   *  The material system performs the type conversion automatically.
   *}
  aiPTI_Integer = $4;
  {** Simple binary buffer, content undefined. Not convertible to anything. *}
  aiPTI_Buffer  = $5;
type
  TaiPropertyTypeInfo = Integer;
  PaiPropertyTypeInfo = ^TaiPropertyTypeInfo;

// ---------------------------------------------------------------------------
  {** @brief Data structure for a single material property
   *
   *  As an user, you'll probably never need to deal with this data structure.
   *  Just use the provided aiGetMaterialXXX() or aiMaterial::Get() family
   *  of functions to query material properties easily. Processing them
   *  manually is faster, but it is not the recommended way. It isn't worth
   *  the effort. <br>
   *  Material property names follow a simple scheme:
   *  @code
   *    $<name>
   *    ?<name>
   *       A public property, there must be corresponding AI_MATKEY_XXX define
   *       2nd: Public, but ignored by the #aiProcess_RemoveRedundantMaterials
   *       post-processing step.
   *    ~<name>
   *       A temporary property for internal use.
   *  @endcode
   *  @see aiMaterial
   *}
  TaiMaterialProperty = record
    {** Specifies the name of the property (key)
     *  Keys are generally case insensitive.
     *}
    mKey: TaiString;
    {** Textures: Specifies their exact usage semantic.
     * For non-texture properties, this member is always 0
     * (or, better-said, #aiTextureType_NONE).
     *}
    mSemantic: CUInt;
    {** Textures: Specifies the index of the texture.
     *  For non-texture properties, this member is always 0.
     *}
    mIndex: CUInt;
    {**	Size of the buffer mData is pointing to, in bytes.
     *  This value may not be 0.
     *}
    mDataLength: CUInt;
    {** Type information for the property.
     *
     * Defines the data layout inside the data buffer. This is used
     * by the library internally to perform debug checks and to
     * utilize proper type conversions.
     * (It's probably a hacky solution, but it works.)
     *}
    mType: TaiPropertyTypeInfo;
    {**	Binary buffer to hold the property's value.
     * The size of the buffer is always mDataLength.
     *}
    mData: PChar;
  end;
  PaiMaterialProperty = ^TaiMaterialProperty;
  PPaiMaterialProperty = ^PaiMaterialProperty;

// ---------------------------------------------------------------------------
  {** @brief Data structure for a material
   *
   *  Material data is stored using a key-value structure. A single key-value
   *  pair is called a 'material property'. C++ users should use the provided
   *  member functions of aiMaterial to process material properties, C users
   *  have to stick with the aiMaterialGetXXX family of unbound functions.
   *  The library defines a set of standard keys (AI_MATKEY_XXX).
   *}
  TaiMaterial = record
    {** List of all material properties loaded. *}
    mProperties: PPaiMaterialProperty;

    {** Number of properties in the data base *}
    mNumProperties: CUInt;

    {** Storage allocated *}
    mNumAllocated: CUInt;
  end;
  PaiMaterial = ^TaiMaterial;
  PPaiMaterial = ^PaiMaterial;

// ---------------------------------------------------------------------------
{$DEFINE AI_MATKEY_NAME:='?mat.name',0,0}
{$DEFINE AI_MATKEY_TWOSIDED:='$mat.twosided',0,0}
{$DEFINE AI_MATKEY_SHADING_MODEL:='$mat.shadingm',0,0}
{$DEFINE AI_MATKEY_ENABLE_WIREFRAME:='$mat.wireframe',0,0}
{$DEFINE AI_MATKEY_BLEND_FUNC:='$mat.blend',0,0}
{$DEFINE AI_MATKEY_OPACITY:='$mat.opacity',0,0}
{$DEFINE AI_MATKEY_BUMPSCALING:='$mat.bumpscaling',0,0}
{$DEFINE AI_MATKEY_SHININESS:='$mat.shininess',0,0}
{$DEFINE AI_MATKEY_REFLECTIVITY:='$mat.reflectivity',0,0}
{$DEFINE AI_MATKEY_SHININESS_STRENGTH:='$mat.shinpercent',0,0}
{$DEFINE AI_MATKEY_REFRACTI:='$mat.refracti',0,0}
{$DEFINE AI_MATKEY_COLOR_DIFFUSE:='$clr.diffuse',0,0}
{$DEFINE AI_MATKEY_COLOR_AMBIENT:='$clr.ambient',0,0}
{$DEFINE AI_MATKEY_COLOR_SPECULAR:='$clr.specular',0,0}
{$DEFINE AI_MATKEY_COLOR_EMISSIVE:='$clr.emissive',0,0}
{$DEFINE AI_MATKEY_COLOR_TRANSPARENT:='$clr.transparent',0,0}
{$DEFINE AI_MATKEY_COLOR_REFLECTIVE:='$clr.reflective',0,0}
{$DEFINE AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:='?bg.global',0,0}

// ---------------------------------------------------------------------------
// Pure key names for all texture-related properties
//! @cond MATS_DOC_FULL
const
  _AI_MATKEY_TEXTURE_BASE = '$tex.file';
  _AI_MATKEY_UVWSRC_BASE = '$tex.uvwsrc';
  _AI_MATKEY_TEXOP_BASE	= '$tex.op';
  _AI_MATKEY_MAPPING_BASE = '$tex.mapping';
  _AI_MATKEY_TEXBLEND_BASE = '$tex.blend';
  _AI_MATKEY_MAPPINGMODE_U_BASE = '$tex.mapmodeu';
  _AI_MATKEY_MAPPINGMODE_V_BASE = '$tex.mapmodev';
  _AI_MATKEY_TEXMAP_AXIS_BASE = '$tex.mapaxis';
  _AI_MATKEY_UVTRANSFORM_BASE = '$tex.uvtrafo';
  _AI_MATKEY_TEXFLAGS_BASE = '$tex.flags';

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_TEXTURE_DIFFUSE:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_TEXTURE_SPECULAR:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_TEXTURE_AMBIENT:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_TEXTURE_EMISSIVE:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_TEXTURE_NORMALS:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_TEXTURE_HEIGHT:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_TEXTURE_SHININESS:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_TEXTURE_OPACITY:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_TEXTURE_DISPLACEMENT:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_TEXTURE_LIGHTMAP:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_TEXTURE_REFLECTION:=_AI_MATKEY_TEXTURE_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_UVWSRC_DIFFUSE:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_UVWSRC_SPECULAR:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_UVWSRC_AMBIENT:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_UVWSRC_EMISSIVE:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_UVWSRC_NORMALS:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_UVWSRC_HEIGHT:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_UVWSRC_SHININESS:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_UVWSRC_OPACITY:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_UVWSRC_DISPLACEMENT:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_UVWSRC_LIGHTMAP:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_UVWSRC_REFLECTION:=_AI_MATKEY_UVWSRC_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_TEXOP_DIFFUSE:=_AI_MATKEY_TEXOP_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_TEXOP_SPECULAR:=_AI_MATKEY_TEXOP_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_TEXOP_AMBIENT:=_AI_MATKEY_TEXOP_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_TEXOP_EMISSIVE:=_AI_MATKEY_TEXOP_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_TEXOP_NORMALS:=_AI_MATKEY_TEXOP_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_TEXOP_HEIGHT:=_AI_MATKEY_TEXOP_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_TEXOP_SHININESS:=_AI_MATKEY_TEXOP_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_TEXOP_OPACITY:=_AI_MATKEY_TEXOP_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_TEXOP_DISPLACEMENT:=_AI_MATKEY_TEXOP_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_TEXOP_LIGHTMAP:=_AI_MATKEY_TEXOP_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_TEXOP_REFLECTION:=_AI_MATKEY_TEXOP_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_MAPPING_DIFFUSE:=_AI_MATKEY_MAPPING_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_MAPPING_SPECULAR:=_AI_MATKEY_MAPPING_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_MAPPING_AMBIENT:=_AI_MATKEY_MAPPING_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_MAPPING_EMISSIVE:=_AI_MATKEY_MAPPING_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_MAPPING_NORMALS:=_AI_MATKEY_MAPPING_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_MAPPING_HEIGHT:=_AI_MATKEY_MAPPING_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_MAPPING_SHININESS:=_AI_MATKEY_MAPPING_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_MAPPING_OPACITY:=_AI_MATKEY_MAPPING_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_MAPPING_DISPLACEMENT:=_AI_MATKEY_MAPPING_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_MAPPING_LIGHTMAP:=_AI_MATKEY_MAPPING_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_MAPPING_REFLECTION:=_AI_MATKEY_MAPPING_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_TEXBLEND_DIFFUSE:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_TEXBLEND_SPECULAR:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_TEXBLEND_AMBIENT:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_TEXBLEND_EMISSIVE:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_TEXBLEND_NORMALS:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_TEXBLEND_HEIGHT:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_TEXBLEND_SHININESS:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_TEXBLEND_OPACITY:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_TEXBLEND_DISPLACEMENT:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_TEXBLEND_LIGHTMAP:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_TEXBLEND_REFLECTION:=_AI_MATKEY_TEXBLEND_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_MAPPINGMODE_U_DIFFUSE:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_SPECULAR:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_AMBIENT:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_EMISSIVE:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_NORMALS:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_HEIGHT:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_SHININESS:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_OPACITY:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_DISPLACEMENT:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_LIGHTMAP:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_MAPPINGMODE_U_REFLECTION:=_AI_MATKEY_MAPPINGMODE_U_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_MAPPINGMODE_V_DIFFUSE:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_SPECULAR:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_AMBIENT:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_EMISSIVE:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_NORMALS:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_HEIGHT:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_SHININESS:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_OPACITY:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_DISPLACEMENT:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_LIGHTMAP:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_MAPPINGMODE_V_REFLECTION:=_AI_MATKEY_MAPPINGMODE_V_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_TEXMAP_AXIS_DIFFUSE:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_SPECULAR:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_AMBIENT:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_EMISSIVE:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_NORMALS:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_HEIGHT:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_SHININESS:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_OPACITY:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_DISPLACEMENT:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_LIGHTMAP:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_TEXMAP_AXIS_REFLECTION:=_AI_MATKEY_TEXMAP_AXIS_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_UVTRANSFORM_DIFFUSE:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_UVTRANSFORM_SPECULAR:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_UVTRANSFORM_AMBIENT:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_UVTRANSFORM_EMISSIVE:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_UVTRANSFORM_NORMALS:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_UVTRANSFORM_HEIGHT:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_UVTRANSFORM_SHININESS:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_UVTRANSFORM_OPACITY:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_UVTRANSFORM_DISPLACEMENT:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_UVTRANSFORM_LIGHTMAP:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_UVTRANSFORM_REFLECTION:=_AI_MATKEY_UVTRANSFORM_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------

// For backward compatibility and simplicity
//! @cond MATS_DOC_FULL
{$DEFINE AI_MATKEY_TEXFLAGS_DIFFUSE:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_DIFFUSE}
{$DEFINE AI_MATKEY_TEXFLAGS_SPECULAR:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_SPECULAR}
{$DEFINE AI_MATKEY_TEXFLAGS_AMBIENT:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_AMBIENT}
{$DEFINE AI_MATKEY_TEXFLAGS_EMISSIVE:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_EMISSIVE}
{$DEFINE AI_MATKEY_TEXFLAGS_NORMALS:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_NORMALS}
{$DEFINE AI_MATKEY_TEXFLAGS_HEIGHT:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_HEIGHT}
{$DEFINE AI_MATKEY_TEXFLAGS_SHININESS:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_SHININESS}
{$DEFINE AI_MATKEY_TEXFLAGS_OPACITY:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_OPACITY}
{$DEFINE AI_MATKEY_TEXFLAGS_DISPLACEMENT:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_DISPLACEMENT}
{$DEFINE AI_MATKEY_TEXFLAGS_LIGHTMAP:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_LIGHTMAP}
{$DEFINE AI_MATKEY_TEXFLAGS_REFLECTION:=_AI_MATKEY_TEXFLAGS_BASE,aiTextureType_REFLECTION}

// ---------------------------------------------------------------------------
  {** @brief Retrieve a material property with a specific key from the material
   *
   * @param pMat Pointer to the input material. May not be NULL
   * @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
   * @param type Specifies the type of the texture to be retrieved (
   *    e.g. diffuse, specular, height map ...)
   * @param index Index of the texture to be retrieved.
   * @param pPropOut Pointer to receive a pointer to a valid aiMaterialProperty
   *        structure or NULL if the key has not been found. *}
// ---------------------------------------------------------------------------
function aiGetMaterialProperty(const pMat: PaiMaterial;
                               const pKey: PChar;
                               type_: CUInt;
                               index: CUInt;
                               const pPropOut: PPaiMaterialProperty): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialProperty' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Retrieve an array of float values with a specific key
   *  from the material
   *
   * Pass one of the AI_MATKEY_XXX constants for the last three parameters (the
   * example reads the #AI_MATKEY_UVTRANSFORM property of the first diffuse texture)
   * @code
   * aiUVTransform trafo;
   * unsigned int max = sizeof(aiUVTransform);
   * if (AI_SUCCESS != aiGetMaterialFloatArray(mat, AI_MATKEY_UVTRANSFORM(aiTextureType_DIFFUSE,0),
   *    (float*)&trafo, &max) || sizeof(aiUVTransform) != max)
   *
   *   // error handling
   *
   * @endcode
   *
   * @param pMat Pointer to the input material. May not be NULL
   * @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
   * @param pOut Pointer to a buffer to receive the result.
   * @param pMax Specifies the size of the given buffer, in float's.
   *        Receives the number of values (not bytes!) read.
   * @param type (see the code sample above)
   * @param index (see the code sample above)
   * @return Specifies whether the key has been found. If not, the output
   *   arrays remains unmodified and pMax is set to 0.*}
// ---------------------------------------------------------------------------
function aiGetMaterialFloatArray(const pMat: PaiMaterial;
                                 const pKey: PChar;
                                 type_: CUInt;
                                 index: CUInt;
                                 pOut: PSingle;
                                 pMax: PCUInt): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialFloatArray' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
 {** @brief Retrieve a single float property with a specific key from the material.
  *
  * Pass one of the AI_MATKEY_XXX constants for the last three parameters (the
  * example reads the #AI_MATKEY_SHININESS_STRENGTH property of the first diffuse texture)
  * @code
  * float specStrength = 1.f; // default value, remains unmodified if we fail.
  * aiGetMaterialFloat(mat, AI_MATKEY_SHININESS_STRENGTH,
  *    (float*)&specStrength);
  * @endcode
  *
  * @param pMat Pointer to the input material. May not be NULL
  * @param pKey Key to search for. One of the AI_MATKEY_XXX constants.
  * @param pOut Receives the output float.
  * @param type (see the code sample above)
  * @param index (see the code sample above)
  * @return Specifies whether the key has been found. If not, the output
  *   float remains unmodified.*}
// ---------------------------------------------------------------------------
function aiGetMaterialFloat(const pMat: PaiMaterial;
                            const pKey: PChar;
                            type_: CUInt;
                            index: CUInt;
                            pOut: PSingle): TaiReturn; inline;

// ---------------------------------------------------------------------------
  {** @brief Retrieve an array of integer values with a specific key
   *  from a material
   *
   * See the sample for aiGetMaterialFloatArray for more information.*}
function aiGetMaterialIntegerArray(const pMat: PaiMaterial;
                                   const pKey: PChar;
                                   type_: CUInt;
                                   index: CUInt;
                                   pOut: PInteger;
                                   pMax: PCUInt): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialIntegerArray' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Retrieve an integer property with a specific key from a material
   *
   * See the sample for aiGetMaterialFloat for more information.*}
function aiGetMaterialInteger(const pMat: PaiMaterial;
                              const pKey: PChar;
                              type_: CUInt;
                              index: CUInt;
                              pOut: PInteger
                              ): TaiReturn; inline;

// ---------------------------------------------------------------------------
  {** @brief Retrieve a color value from the material property table
  *
  * See the sample for aiGetMaterialFloat for more information*}
function aiGetMaterialColor(const pMat: PaiMaterial;
                            const pKey: PChar;
                            type_: CUInt;
                            index: CUInt;
                            pOut: PaiColor4D): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialColor' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Retrieve a aiUVTransform value from the material property table
  *
  * See the sample for aiGetMaterialFloat for more information*}
function aiGetMaterialUVTransform(const pMat: PaiMaterial;
                                  const pKey: PChar;
                                  type_: CUInt;
                                  index: CUInt;
                                  pOut: PaiUVTransform): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialUVTransform' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Retrieve a string from the material property table
  *
  * See the sample for aiGetMaterialFloat for more information.*}
// ---------------------------------------------------------------------------
function aiGetMaterialString(const pMat: PaiMaterial;
                             const pKey: PChar;
                             type_: CUInt;
                             index: CUInt;
                             pOut: PaiString): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialString' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** Get the number of textures for a particular texture type.
   *  @param[in] pMat Pointer to the input material. May not be NULL
   *  @param type Texture type to check for
   *  @return Number of textures for this type.
   *  @note A texture can be easily queried using #aiGetMaterialTexture() *}
function aiGetMaterialTextureCount(const pMat: PaiMaterial;
                                   type_: TaiTextureType): CUInt cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialTextureCount' {$ENDIF} {$ENDIF};

// ---------------------------------------------------------------------------
  {** @brief Helper function to get all values pertaining to a particular
   *  texture slot from a material structure.
   *
   *  This function is provided just for convenience. You could also read the
   *  texture by parsing all of its properties manually. This function bundles
   *  all of them in a huge function monster.
   *
   *  @param[in] mat Pointer to the input material. May not be NULL
   *  @param[in] type Specifies the texture stack to read from (e.g. diffuse,
   *     specular, height map ...).
   *  @param[in] index Index of the texture. The function fails if the
   *     requested index is not available for this texture type.
   *     #aiGetMaterialTextureCount() can be used to determine the number of
   *     textures in a particular texture stack.
   *  @param[out] path Receives the output path
   *      This parameter must be non-null.
   *  @param mapping The texture mapping mode to be used.
   *      Pass NULL if you're not interested in this information.
   *  @param[out] uvindex For UV-mapped textures: receives the index of the UV
   *      source channel. Unmodified otherwise.
   *      Pass NULL if you're not interested in this information.
   *  @param[out] blend Receives the blend factor for the texture
   *      Pass NULL if you're not interested in this information.
   *  @param[out] op Receives the texture blend operation to be perform between
   *		this texture and the previous texture.
   *      Pass NULL if you're not interested in this information.
   *  @param[out] mapmode Receives the mapping modes to be used for the texture.
   *      Pass NULL if you're not interested in this information. Otherwise,
   *      pass a pointer to an array of two aiTextureMapMode's (one for each
   *      axis, UV order).
   *  @return AI_SUCCESS on success, otherwise something else. Have fun.*}
function aiGetMaterialTexture(const pMat: PaiMaterial;
                              type_: TaiTextureType;
                              path: PaiString;
                              mapping: PaiTextureMapping = nil;
                              uvindex: PCUInt = nil;
                              blend: PSingle = nil;
                              op: PaiTextureOP = nil;
                              mapmode: PaiTextureMapMode = nil;
                              flags: PCUInt = nil): TaiReturn cdecl; external ASSIMP_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_aiGetMaterialTexture' {$ENDIF} {$ENDIF};
