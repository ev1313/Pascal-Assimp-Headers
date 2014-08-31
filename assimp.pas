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
  Classes, SysUtils, CTypes;
const
  {$IFDEF WINDOWS}
    ASSIMP_LibName = 'Assimp.dll';
  {$ENDIF}
  {$IFDEF UNIX}
    {$IFDEF DARWIN}
      ASSIMP_LibName = 'libAssimp.dylib';
    {$ELSE}
      {$IFDEF FPC}
        ASSIMP_LibName = 'libAssimp.so';
      {$ELSE}
        ASSIMP_LibName = 'libAssimp.so.0';
      {$ENDIF}
    {$ENDIF}
  {$ENDIF}
  {$IFDEF MACOS}
    ASSIMP_LibName = 'SDL2';
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
  {$I aimaterial.inc}
  {$I aiscene.inc}

implementation

function aiGetMaterialFloat(const pMat: PaiMaterial; const pKey: PChar; type_: CUInt; index: CUInt; pOut: PSingle): TaiReturn;
begin
  Result := aiGetMaterialFloatArray(pMat, pKey, type_, index, pOut, nil);
end;

function aiGetMaterialInteger(const pMat: PaiMaterial; const pKey: PChar; type_: CUInt; index: CUInt; pOut: PInteger): TaiReturn;
begin
  Result := aiGetMaterialIntegerArray(pMat, pKey, type_, index, pOut, nil);
end;

end.

