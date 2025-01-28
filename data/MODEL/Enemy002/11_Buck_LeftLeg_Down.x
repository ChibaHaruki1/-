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
 -11.12622;-1.07837;21.95125;,
 13.19098;-1.07837;18.84333;,
 10.93346;1.12999;-22.65846;,
 -13.17910;1.12999;-19.55043;,
 -15.35714;-53.63613;-28.75995;,
 8.96002;-53.63613;-31.86799;,
 11.70370;-53.86756;9.63365;,
 -12.61346;-53.86756;12.74168;,
 10.44730;-6.15701;-22.65846;,
 8.96002;-53.63613;-31.86799;,
 -15.35714;-53.63613;-28.75995;,
 -13.86990;-6.76265;-19.55043;,
 -13.17910;1.12999;-19.55043;,
 10.93346;1.12999;-22.65846;,
 13.19098;-6.37353;18.84333;,
 8.96002;-53.63613;-31.86799;,
 10.44730;-6.15701;-22.65846;,
 10.93346;1.12999;-22.65846;,
 -11.12622;-6.97917;21.95125;,
 -12.61346;-53.86756;12.74168;,
 11.70370;-53.86756;9.63365;,
 13.19098;-6.37353;18.84333;,
 13.19098;-1.07837;18.84333;,
 -11.12622;-1.07837;21.95125;,
 -13.86990;-6.76265;-19.55043;,
 -15.35714;-53.63613;-28.75995;,
 -11.12622;-6.97917;21.95125;,
 -13.17910;1.12999;-19.55043;;
 
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
  14;
  0.006775;0.998583;0.052784;,
  -0.000707;-0.999984;-0.005530;,
  -0.127635;0.102305;-0.986531;,
  0.997617;-0.025842;-0.063968;,
  0.127360;-0.097389;0.987064;,
  -0.126736;0.193908;-0.972799;,
  -0.127440;0.009824;-0.991798;,
  0.997646;-0.018436;-0.066054;,
  0.997530;-0.033247;-0.061878;,
  0.126734;-0.193851;0.972811;,
  0.126776;0.000000;0.991931;,
  -0.997527;0.031126;0.063013;,
  -0.997641;0.018673;0.066055;,
  -0.997249;0.043575;0.059960;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,5,5,2;,
  4;2,2,6,6;,
  4;3,7,7,3;,
  4;3,3,8,8;,
  4;4,9,9,4;,
  4;4,4,10,10;,
  4;11,12,12,11;,
  4;11,11,13,13;;
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
