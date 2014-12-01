unit assimp;

{*
  ---------------------------------------------------------------------------
  Pascal Assimp Headers
  ---------------------------------------------------------------------------

  2014 by Tim Blume

  The Pascal-Header-Conversion is based on git commit
  "dbf001b81cf5b69a2e78b87690d5abeb31450025"
  and following files:

  "version.h",
  "vector2.h",
  "vector3.h",
  "color4.h",
  "matrix3x3.h",
  "matrix4x4.h",
  "quaternion.h",
  "types.h",
  "texture.h",
  "mesh.h",
  "light.h",
  "camera.h",
  "material.h",
  "scene.h",
  "postprocess.h",
  "fileio.h",
  "cimport.h",
  "cexport.h"

  Original License:

  ---------------------------------------------------------------------------
  Open Asset Import Library (assimp)
  ---------------------------------------------------------------------------

  Copyright (c) 2006-2012, assimp team

  All rights reserved.

  Redistribution and use of this software in source and binary forms,
  with or without modification, are permitted provided that the following
  conditions are met:

  * Redistributions of source code must retain the above
    copyright notice, this list of conditions and the
    following disclaimer.

  * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the
    following disclaimer in the documentation and/or other
    materials provided with the distribution.

  * Neither the name of the assimp team, nor the names of its
    contributors may be used to endorse or promote products
    derived from this software without specific prior
    written permission of the assimp team.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  ---------------------------------------------------------------------------
*}

{$mode objfpc}{$H+}

interface

uses
  {$IFDEF UNIX} unixtype,
  {$ELSE} ctypes, {$ENDIF}
  Classes, SysUtils;
const
  {$IFDEF WINDOWS}
    ASSIMP_LibName = 'assimp.dll';
  {$ENDIF}
  {$IFDEF UNIX}
    {$IFDEF DARWIN}
      ASSIMP_LibName = 'libassimp.dylib';
    {$ELSE}
      {$IFDEF FPC}
        ASSIMP_LibName = 'libassimp.so';
      {$ELSE}
        ASSIMP_LibName = 'libassimp.so.0';
      {$ENDIF}
    {$ENDIF}
  {$ENDIF}
  {$IFDEF MACOS}
    ASSIMP_LibName = 'assimp';
    {$IFDEF FPC}
      {$linklib libAssimp}
    {$ENDIF}
  {$ENDIF}

  {$MACRO ON}

  {$I aiversion.inc}
  {$I aivector2.inc}
  {$I aivector3.inc}
  {$I aicolor4.inc}
  {$I aimatrix3x3.inc}
  {$I aimatrix4x4.inc}
  {$I aiquaternion.inc}
  {$I aitypes.inc}
  {$I aitexture.inc}
  {$I aimesh.inc}
  {$I ailight.inc}
  {$I aicamera.inc}
  {$I aimaterialmacros.inc}
  {$I aimaterial.inc}
  {$I aimetadata.inc}
  {$I aianim.inc}
  {$I aiscene.inc}
  {$I aipostprocess.inc}
  {$I aifileio.inc}
  {$I aiimport.inc}
  {$I aiexport.inc}
  {$I aiimporterdesc.inc}

implementation

function aiGetMaterialProperty(const pMat: PaiMaterial;
                               const matkey: TaiMatKey;
                               const pPropOut: PPaiMaterialProperty): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialProperty(pMat, '?mat.name', 0, 0, pPropOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialProperty(pMat, '$mat.twosided', 0, 0, pPropOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialProperty(pMat, '$mat.shadingm', 0, 0, pPropOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialProperty(pMat, '$mat.wireframe', 0, 0, pPropOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialProperty(pMat, '$mat.blend', 0, 0, pPropOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialProperty(pMat, '$mat.opacity', 0, 0, pPropOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialProperty(pMat, '$mat.bumpscaling', 0, 0, pPropOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialProperty(pMat, '$mat.shininess', 0, 0, pPropOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialProperty(pMat, '$mat.reflectivity', 0, 0, pPropOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialProperty(pMat, '$mat.shinpercent', 0, 0, pPropOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialProperty(pMat, '$mat.refracti', 0, 0, pPropOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialProperty(pMat, '$clr.diffuse', 0, 0, pPropOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialProperty(pMat, '$clr.ambient', 0, 0, pPropOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialProperty(pMat, '$clr.specular', 0, 0, pPropOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialProperty(pMat, '$clr.emissive', 0, 0, pPropOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialProperty(pMat, '$clr.transparent', 0, 0, pPropOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialProperty(pMat, '$clr.reflective', 0, 0, pPropOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialProperty(pMat, '?bg.global', 0, 0, pPropOut);
  end;
end;

function aiGetMaterialFloatArray(const pMat: PaiMaterial;
                                 const matkey: TaiMatKey;
                                 pOut: PSingle;
                                 pMax: PCUInt): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialFloatArray(pMat, '?mat.name', 0, 0, pOut, pMax);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialFloatArray(pMat, '$mat.twosided', 0, 0, pOut, pMax);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialFloatArray(pMat, '$mat.shadingm', 0, 0, pOut, pMax);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialFloatArray(pMat, '$mat.wireframe', 0, 0, pOut, pMax);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialFloatArray(pMat, '$mat.blend', 0, 0, pOut, pMax);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialFloatArray(pMat, '$mat.opacity', 0, 0, pOut, pMax);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialFloatArray(pMat, '$mat.bumpscaling', 0, 0, pOut, pMax);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialFloatArray(pMat, '$mat.shininess', 0, 0, pOut, pMax);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialFloatArray(pMat, '$mat.reflectivity', 0, 0, pOut, pMax);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialFloatArray(pMat, '$mat.shinpercent', 0, 0, pOut, pMax);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialFloatArray(pMat, '$mat.refracti', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialFloatArray(pMat, '$clr.diffuse', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialFloatArray(pMat, '$clr.ambient', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialFloatArray(pMat, '$clr.specular', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialFloatArray(pMat, '$clr.emissive', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialFloatArray(pMat, '$clr.transparent', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialFloatArray(pMat, '$clr.reflective', 0, 0, pOut, pMax);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialFloatArray(pMat, '?bg.global', 0, 0, pOut, pMax);
  end;
end;

function aiGetMaterialFloat(const pMat: PaiMaterial;
                            const pKey: PChar;
                            type_: CUInt;
                            index: CUInt;
                            pOut: PSingle): TaiReturn;
begin
  Result := aiGetMaterialFloatArray(pMat, pKey, type_, index, pOut, nil);
end;

function aiGetMaterialFloat(const pMat: PaiMaterial;
                            const matkey: TaiMatKey;
                            pOut: PSingle): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialFloat(pMat, '?mat.name', 0, 0, pOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialFloat(pMat, '$mat.twosided', 0, 0, pOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialFloat(pMat, '$mat.shadingm', 0, 0, pOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialFloat(pMat, '$mat.wireframe', 0, 0, pOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialFloat(pMat, '$mat.blend', 0, 0, pOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialFloat(pMat, '$mat.opacity', 0, 0, pOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialFloat(pMat, '$mat.bumpscaling', 0, 0, pOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialFloat(pMat, '$mat.shininess', 0, 0, pOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialFloat(pMat, '$mat.reflectivity', 0, 0, pOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialFloat(pMat, '$mat.shinpercent', 0, 0, pOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialFloat(pMat, '$mat.refracti', 0, 0, pOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialFloat(pMat, '$clr.diffuse', 0, 0, pOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialFloat(pMat, '$clr.ambient', 0, 0, pOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialFloat(pMat, '$clr.specular', 0, 0, pOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialFloat(pMat, '$clr.emissive', 0, 0, pOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialFloat(pMat, '$clr.transparent', 0, 0, pOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialFloat(pMat, '$clr.reflective', 0, 0, pOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialFloat(pMat, '?bg.global', 0, 0, pOut);
  end;
end;

function aiGetMaterialIntegerArray(const pMat: PaiMaterial;
                                   const matkey: TaiMatKey;
                                   pOut: PInteger;
                                   pMax: PCUInt): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialIntegerArray(pMat, '?mat.name', 0, 0, pOut, pMax);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.twosided', 0, 0, pOut, pMax);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.shadingm', 0, 0, pOut, pMax);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.wireframe', 0, 0, pOut, pMax);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.blend', 0, 0, pOut, pMax);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.opacity', 0, 0, pOut, pMax);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.bumpscaling', 0, 0, pOut, pMax);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.shininess', 0, 0, pOut, pMax);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.reflectivity', 0, 0, pOut, pMax);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.shinpercent', 0, 0, pOut, pMax);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialIntegerArray(pMat, '$mat.refracti', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.diffuse', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.ambient', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.specular', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.emissive', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.transparent', 0, 0, pOut, pMax);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialIntegerArray(pMat, '$clr.reflective', 0, 0, pOut, pMax);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialIntegerArray(pMat, '?bg.global', 0, 0, pOut, pMax);
  end;
end;

function aiGetMaterialInteger(const pMat: PaiMaterial;
                              const pKey: PChar;
                              type_: CUInt;
                              index: CUInt;
                              pOut: PInteger): TaiReturn;
begin
  Result := aiGetMaterialIntegerArray(pMat, pKey, type_, index, pOut, nil);
end;

function aiGetMaterialInteger(const pMat: PaiMaterial;
                              const matkey: TaiMatKey;
                              pOut: PInteger): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialInteger(pMat, '?mat.name', 0, 0, pOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialInteger(pMat, '$mat.twosided', 0, 0, pOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialInteger(pMat, '$mat.shadingm', 0, 0, pOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialInteger(pMat, '$mat.wireframe', 0, 0, pOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialInteger(pMat, '$mat.blend', 0, 0, pOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialInteger(pMat, '$mat.opacity', 0, 0, pOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialInteger(pMat, '$mat.bumpscaling', 0, 0, pOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialInteger(pMat, '$mat.shininess', 0, 0, pOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialInteger(pMat, '$mat.reflectivity', 0, 0, pOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialInteger(pMat, '$mat.shinpercent', 0, 0, pOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialInteger(pMat, '$mat.refracti', 0, 0, pOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialInteger(pMat, '$clr.diffuse', 0, 0, pOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialInteger(pMat, '$clr.ambient', 0, 0, pOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialInteger(pMat, '$clr.specular', 0, 0, pOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialInteger(pMat, '$clr.emissive', 0, 0, pOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialInteger(pMat, '$clr.transparent', 0, 0, pOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialInteger(pMat, '$clr.reflective', 0, 0, pOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialInteger(pMat, '?bg.global', 0, 0, pOut);
  end;
end;

function aiGetMaterialColor(const pMat: PaiMaterial;
                            const matkey: TaiMatKey;
                            pOut: PaiColor4D): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialColor(pMat, '?mat.name', 0, 0, pOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialColor(pMat, '$mat.twosided', 0, 0, pOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialColor(pMat, '$mat.shadingm', 0, 0, pOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialColor(pMat, '$mat.wireframe', 0, 0, pOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialColor(pMat, '$mat.blend', 0, 0, pOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialColor(pMat, '$mat.opacity', 0, 0, pOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialColor(pMat, '$mat.bumpscaling', 0, 0, pOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialColor(pMat, '$mat.shininess', 0, 0, pOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialColor(pMat, '$mat.reflectivity', 0, 0, pOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialColor(pMat, '$mat.shinpercent', 0, 0, pOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialColor(pMat, '$mat.refracti', 0, 0, pOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialColor(pMat, '$clr.diffuse', 0, 0, pOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialColor(pMat, '$clr.ambient', 0, 0, pOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialColor(pMat, '$clr.specular', 0, 0, pOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialColor(pMat, '$clr.emissive', 0, 0, pOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialColor(pMat, '$clr.transparent', 0, 0, pOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialColor(pMat, '$clr.reflective', 0, 0, pOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialColor(pMat, '?bg.global', 0, 0, pOut);
  end;
end;
           {
function aiGetMaterialUVTransform(const pMat: PaiMaterial;
                                  const matkey: TaiMatKey;
                                  pOut: PaiUVTransform): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialUVTransform(pMat, '?mat.name', 0, 0, pOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialUVTransform(pMat, '$mat.twosided', 0, 0, pOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialUVTransform(pMat, '$mat.shadingm', 0, 0, pOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialUVTransform(pMat, '$mat.wireframe', 0, 0, pOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialUVTransform(pMat, '$mat.blend', 0, 0, pOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialUVTransform(pMat, '$mat.opacity', 0, 0, pOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialUVTransform(pMat, '$mat.bumpscaling', 0, 0, pOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialUVTransform(pMat, '$mat.shininess', 0, 0, pOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialUVTransform(pMat, '$mat.reflectivity', 0, 0, pOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialUVTransform(pMat, '$mat.shinpercent', 0, 0, pOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialUVTransform(pMat, '$mat.refracti', 0, 0, pOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialUVTransform(pMat, '$clr.diffuse', 0, 0, pOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialUVTransform(pMat, '$clr.ambient', 0, 0, pOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialUVTransform(pMat, '$clr.specular', 0, 0, pOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialUVTransform(pMat, '$clr.emissive', 0, 0, pOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialUVTransform(pMat, '$clr.transparent', 0, 0, pOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialUVTransform(pMat, '$clr.reflective', 0, 0, pOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialUVTransform(pMat, '?bg.global', 0, 0, pOut);
  end;
end;            }

function aiGetMaterialString(const pMat: PaiMaterial;
                             const matkey: TaiMatKey;
                             pOut: PaiString): TaiReturn;
begin
  case matkey of
    AI_MATKEY_NAME:
      Result := aiGetMaterialString(pMat, '?mat.name', 0, 0, pOut);
    AI_MATKEY_TWOSIDED:
      Result := aiGetMaterialString(pMat, '$mat.twosided', 0, 0, pOut);
    AI_MATKEY_SHADING_MODEL:
      Result := aiGetMaterialString(pMat, '$mat.shadingm', 0, 0, pOut);
    AI_MATKEY_ENABLE_WIREFRAME:
      Result := aiGetMaterialString(pMat, '$mat.wireframe', 0, 0, pOut);
    AI_MATKEY_BLEND_FUNC:
      Result := aiGetMaterialString(pMat, '$mat.blend', 0, 0, pOut);
    AI_MATKEY_OPACITY:
      Result := aiGetMaterialString(pMat, '$mat.opacity', 0, 0, pOut);
    AI_MATKEY_BUMPSCALING:
      Result := aiGetMaterialString(pMat, '$mat.bumpscaling', 0, 0, pOut);
    AI_MATKEY_SHININESS:
      Result := aiGetMaterialString(pMat, '$mat.shininess', 0, 0, pOut);
    AI_MATKEY_REFLECTIVITY:
      Result := aiGetMaterialString(pMat, '$mat.reflectivity', 0, 0, pOut);
    AI_MATKEY_SHININESS_STRENGTH:
      Result := aiGetMaterialString(pMat, '$mat.shinpercent', 0, 0, pOut);
    AI_MATKEY_REFRACTI:
      Result := aiGetMaterialString(pMat, '$mat.refracti', 0, 0, pOut);
    AI_MATKEY_COLOR_DIFFUSE:
      Result := aiGetMaterialString(pMat, '$clr.diffuse', 0, 0, pOut);
    AI_MATKEY_COLOR_AMBIENT:
      Result := aiGetMaterialString(pMat, '$clr.ambient', 0, 0, pOut);
    AI_MATKEY_COLOR_SPECULAR:
      Result := aiGetMaterialString(pMat, '$clr.specular', 0, 0, pOut);
    AI_MATKEY_COLOR_EMISSIVE:
      Result := aiGetMaterialString(pMat, '$clr.emissive', 0, 0, pOut);
    AI_MATKEY_COLOR_TRANSPARENT:
      Result := aiGetMaterialString(pMat, '$clr.transparent', 0, 0, pOut);
    AI_MATKEY_COLOR_REFLECTIVE:
      Result := aiGetMaterialString(pMat, '$clr.reflective', 0, 0, pOut);
    AI_MATKEY_GLOBAL_BACKGROUND_IMAGE:
      Result := aiGetMaterialString(pMat, '?bg.global', 0, 0, pOut);
  end;
end;

end.

