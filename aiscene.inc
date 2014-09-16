//from scene.h

// -------------------------------------------------------------------------------
type
  {** A node in the imported hierarchy.
   *
   * Each node has name, a parent node (except for the root node), 
   * a transformation relative to its parent and possibly several child nodes.
   * Simple file formats don't support hierarchical structures - for these formats 
   * the imported scene does consist of only a single root node without children.
   *}
// -------------------------------------------------------------------------------
  PaiNode = ^TaiNode;
  PPaiNode = ^PaiNode;
  TaiNode = record
    {** The name of the node. 
     *
     * The name might be empty (length of zero) but all nodes which 
     * need to be referenced by either bones or animations are named.
     * Multiple nodes may have the same name, except for nodes which are referenced
     * by bones (see #aiBone and #aiMesh::mBones). Their names *must* be unique.
     * 
     * Cameras and lights reference a specific node by name - if there
     * are multiple nodes with this name, they are assigned to each of them.
     * <br>
     * There are no limitations with regard to the characters contained in
     * the name string as it is usually taken directly from the source file. 
     * 
     * Implementations should be able to handle tokens such as whitespace, tabs,
     * line feeds, quotation marks, ampersands etc.
     *
     * Sometimes assimp introduces new nodes not present in the source file
     * into the hierarchy (usually out of necessity because sometimes the
     * source hierarchy format is simply not compatible). Their names are
     * surrounded by @verbatim <> @endverbatim e.g.
     *  @verbatim<DummyRootNode> @endverbatim.
     *}
    mName: TaiString;

    {** The transformation relative to the node's parent. *}
    mTransformation: TaiMatrix4x4;

    {** Parent node. NULL if this node is the root node. *}
    mParent: PaiNode;

    {** The number of child nodes of this node. *}
    mNumChildren: CUInt;

    {** The child nodes of this node. NULL if mNumChildren is 0. *}
    mChildren: PPaiNode;

    {** The number of meshes of this node. *}
    mNumMeshes: CUInt;

    {** The meshes of this node. Each entry is an index into the mesh *}
    mMeshes: PCUInt;

    {** Metadata associated with this node or NULL if there is no metadata.
      *  Whether any metadata is generated depends on the source file format. See the
      * @link importer_notes @endlink page for more information on every source file
      * format. Importers that don't document any metadata don't write any. 
      *}
    mMetaData: PaiMetadata;
  end;

// -------------------------------------------------------------------------------
const
  {** @def AI_SCENE_FLAGS_INCOMPLETE
   * Specifies that the scene data structure that was imported is not complete.
   * This flag bypasses some internal validations and allows the import 
   * of animation skeletons, material libraries or camera animation paths 
   * using Assimp. Most applications won't support such data. 
   *}
  AI_SCENE_FLAGS_INCOMPLETE =	$1;
  {** @def AI_SCENE_FLAGS_VALIDATED
   * This flag is set by the validation postprocess-step (aiPostProcess_ValidateDS)
   * if the validation is successful. In a validated scene you can be sure that
   * any cross references in the data structure (e.g. vertex indices) are valid.
   *}
  AI_SCENE_FLAGS_VALIDATED = $2;
  {** @def AI_SCENE_FLAGS_VALIDATION_WARNING
   * This flag is set by the validation postprocess-step (aiPostProcess_ValidateDS)
   * if the validation is successful but some issues have been found.
   * This can for example mean that a texture that does not exist is referenced 
   * by a material or that the bone weights for a vertex don't sum to 1.0 ... .
   * In most cases you should still be able to use the import. This flag could
   * be useful for applications which don't capture Assimp's log output.
   *}
  AI_SCENE_FLAGS_VALIDATION_WARNING = $4;
  {** @def AI_SCENE_FLAGS_NON_VERBOSE_FORMAT
   * This flag is currently only set by the aiProcess_JoinIdenticalVertices step.
   * It indicates that the vertices of the output meshes aren't in the internal
   * verbose format anymore. In the verbose format all vertices are unique,
   * no vertex is ever referenced by more than one face.
   *}
  AI_SCENE_FLAGS_NON_VERBOSE_FORMAT = $8;
   {** @def AI_SCENE_FLAGS_TERRAIN
   * Denotes pure height-map terrain data. Pure terrains usually consist of quads, 
   * sometimes triangles, in a regular grid. The x,y coordinates of all vertex 
   * positions refer to the x,y coordinates on the terrain height map, the z-axis
   * stores the elevation at a specific point.
   *
   * TER (Terragen) and HMP (3D Game Studio) are height map formats.
   * @note Assimp is probably not the best choice for loading *huge* terrains -
   * fully triangulated data takes extremely much free store and should be avoided
   * as long as possible (typically you'll do the triangulation when you actually
   * need to render it).
   *}
  AI_SCENE_FLAGS_TERRAIN = $10;

// -------------------------------------------------------------------------------
type
  {** The root structure of the imported data. 
   * 
   *  Everything that was imported from the given file can be accessed from here.
   *  Objects of this class are generally maintained and owned by Assimp, not
   *  by the caller. You shouldn't want to instance it, nor should you ever try to
   *  delete a given scene on your own.
   *}
// -------------------------------------------------------------------------------
  TaiScene = record
    {** Any combination of the AI_SCENE_FLAGS_XXX flags. By default 
      * this value is 0, no flags are set. Most applications will
      * want to reject all scenes with the AI_SCENE_FLAGS_INCOMPLETE 
      * bit set.
      *}
    mFlags: CUInt;
    {** The root node of the hierarchy. 
      * 
      * There will always be at least the root node if the import
      * was successful (and no special flags have been set). 
      * Presence of further nodes depends on the format and content 
      * of the imported file.
      *}
    mRootNode: PaiNode;
    {** The number of meshes in the scene. *}
    mNumMeshes: CUInt;
    {** The array of meshes. 
      *
      * Use the indices given in the aiNode structure to access 
      * this array. The array is mNumMeshes in size. If the
      * AI_SCENE_FLAGS_INCOMPLETE flag is not set there will always 
      * be at least ONE material.
      *}
    mMeshes: PPaiMesh;  
    {** The number of materials in the scene. *}
    mNumMaterials: CUInt;  
    {** The array of materials. 
      * 
      * Use the index given in each aiMesh structure to access this
      * array. The array is mNumMaterials in size. If the
      * AI_SCENE_FLAGS_INCOMPLETE flag is not set there will always 
      * be at least ONE material.
      *}
    mMaterials: PPaiMaterial;  
    {** The number of animations in the scene. *}
    mNumAnimations: CUInt;   
    {** The array of animations. 
      *
      * All animations imported from the given file are listed here.
      * The array is mNumAnimations in size.
      *}
    mAnimations: PPaiAnimation;  
    {** The number of textures embedded into the file *}
    mNumTextures: CUInt;
    {** The array of embedded textures.
      * 
      * Not many file formats embed their textures into the file.
      * An example is Quake's MDL format (which is also used by
      * some GameStudio versions)
      *}
    mTextures: PPaiTexture;  
    {** The number of light sources in the scene. Light sources
      * are fully optional, in most cases this attribute will be 0 
      *}
    mNumLights: CUInt;  
    {** The array of light sources.
      * 
      * All light sources imported from the given file are
      * listed here. The array is mNumLights in size.
      *}
    mLights: PPaiLight; 
    {** The number of cameras in the scene. Cameras
     * are fully optional, in most cases this attribute will be 0 
     *}
    mNumCameras: CUInt;
    {** The array of cameras.
    * 
    * All cameras imported from the given file are listed here.
    * The array is mNumCameras in size. The first camera in the
    * array (if existing) is the default camera view into
    * the scene.
    *}
    mCameras: PPaiCamera;
    
    mPrivate: PChar;
  end;
  PaiScene = ^TaiScene;
  PPaiScene = ^PaiScene;

