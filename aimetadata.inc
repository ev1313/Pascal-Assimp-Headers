//from metadata.h

// -------------------------------------------------------------------------------
  {**
    * Enum used to distinguish data types
    *}
 // -------------------------------------------------------------------------------
const
	AI_BOOL = 0; 
	AI_INT = 1;
	AI_UINT64 = 2; 
	AI_FLOAT = 3; 
	AI_AISTRING = 4;
	AI_AIVECTOR3D = 5;

type
  TaiMetadataType = Integer;

// -------------------------------------------------------------------------------
type
  {**
    * Metadata entry
    *
    * The type field uniquely identifies the underlying type of the data field
    *}
// -------------------------------------------------------------------------------
  TaiMetadataEntry = record
    mType: TaiMetadataType;
    mData: Pointer;
  end;
  PaiMetadataEntry = ^TaiMetadataEntry;

// -------------------------------------------------------------------------------
  {**
    * Container for holding metadata.
    *
    * Metadata is a key-value store using string keys and values.
    *}
// -------------------------------------------------------------------------------
  TaiMetadata = record
    {** Length of the mKeys and mValues arrays, respectively *}
    mNumProperties: CUInt;
  
    {** Arrays of keys, may not be NULL. Entries in this array may not be NULL as well. *}
    mKeys: PaiString;
  
    {** Arrays of values, may not be NULL. Entries in this array may be NULL if the
      * corresponding property key has no assigned value. *}
    mValues: PaiMetadataEntry;
  end;
  PaiMetadata = ^TaiMetadata;
