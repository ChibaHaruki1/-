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
 15.11456;4.94355;-22.57618;,
 -15.11544;4.94355;-19.46810;,
 -14.74140;-4.95933;22.03366;,
 17.32236;-4.95933;18.92560;,
 9.15472;-62.34982;19.44186;,
 -15.08311;-62.34982;22.54989;,
 -17.14084;-60.17842;-18.95194;,
 7.09696;-60.17842;-22.06002;,
 -14.74140;-10.10540;22.03366;,
 -15.08311;-62.34982;22.54989;,
 9.15472;-62.34982;19.44186;,
 17.32236;-10.71104;18.92560;,
 17.32236;-4.95933;18.92560;,
 -14.74140;-4.95933;22.03366;,
 -17.48507;-10.32193;-19.46810;,
 -15.08311;-62.34982;22.54989;,
 -14.74140;-10.10540;22.03366;,
 -14.74140;-4.95933;22.03366;,
 12.74492;-10.92761;-22.57618;,
 7.09696;-60.17842;-22.06002;,
 -17.14084;-60.17842;-18.95194;,
 -17.48507;-10.32193;-19.46810;,
 -15.11544;4.94355;-19.46810;,
 15.11456;4.94355;-22.57618;,
 17.32236;-10.71104;18.92560;,
 9.15472;-62.34982;19.44186;,
 12.74492;-10.92761;-22.57618;,
 17.32236;-4.95933;18.92560;;
 
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
  0.023104;0.972598;0.231342;,
  -0.006658;-0.998629;-0.051919;,
  0.104143;0.000919;0.994562;,
  -0.997628;0.038657;0.056955;,
  -0.108425;0.005312;-0.994090;,
  0.111799;0.001838;0.993729;,
  0.096481;0.000000;0.995335;,
  -0.998320;0.000410;0.057945;,
  -0.995476;0.076847;0.055881;,
  -0.114728;-0.004923;-0.993385;,
  -0.102106;0.015547;-0.994652;,
  0.990347;-0.104696;-0.090843;,
  0.987312;-0.135529;-0.082746;,
  0.992366;-0.073756;-0.098846;;
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
