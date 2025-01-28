xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 28;
 12.51458;-4.71343;-16.83616;,
 -11.89537;-4.71343;-16.83616;,
 -11.89537;5.56518;17.15316;,
 12.51458;5.56518;17.15316;,
 8.46079;-63.87763;17.15316;,
 -15.94921;-63.87763;17.15316;,
 -15.94921;-61.70626;-16.83616;,
 8.46079;-61.70626;-16.83616;,
 -11.89537;-11.63323;17.15316;,
 -15.94921;-63.87763;17.15316;,
 8.46079;-63.87763;17.15316;,
 12.51458;-12.23887;17.15316;,
 12.51458;5.56518;17.15316;,
 -11.89537;5.56518;17.15316;,
 -11.89537;-11.84975;-16.83616;,
 -15.94921;-63.87763;17.15316;,
 -11.89537;-11.63323;17.15316;,
 -11.89537;5.56518;17.15316;,
 12.51458;-12.45543;-16.83616;,
 8.46079;-61.70626;-16.83616;,
 -15.94921;-61.70626;-16.83616;,
 -11.89537;-11.84975;-16.83616;,
 -11.89537;-4.71343;-16.83616;,
 12.51458;-4.71343;-16.83616;,
 12.51458;-12.23887;17.15316;,
 8.46079;-63.87763;17.15316;,
 12.51458;-12.45543;-16.83616;,
 12.51458;5.56518;17.15316;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,6,15,16;,
 4;14,16,17,1;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,25,7,26;,
 4;24,26,0,27;;
 
 MeshMaterialList {
  2;
  10;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.385600;0.385600;0.385600;1.000000;;
   5.000000;
   0.360000;0.360000;0.360000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.620800;0.620800;0.620800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.000000;0.957190;-0.289461;,
  0.000000;-0.997966;-0.063754;,
  0.000000;0.000000;1.000000;,
  -0.999214;0.039632;0.001107;,
  0.000000;0.000000;-1.000000;,
  -0.996856;0.079202;0.002213;,
  -1.000000;0.000000;0.000000;,
  0.999195;-0.040106;-0.001120;,
  0.996781;-0.080147;-0.002238;,
  1.000000;0.000000;0.000000;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,5,5,3;,
  4;3,3,6,6;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;7,8,8,7;,
  4;7,7,9,9;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.121770;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.132500;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.100310;,
  0.000000;1.000000;,
  0.000000;0.121770;,
  0.000000;0.000000;,
  1.000000;0.111780;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.100310;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.132500;,
  1.000000;1.000000;,
  0.000000;0.111780;,
  1.000000;0.000000;;
 }
}
