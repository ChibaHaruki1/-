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
 22;
 10.85784;3.85200;-12.93802;,
 10.85784;-23.72634;-7.80190;,
 0.02972;-23.72634;-7.80190;,
 0.02972;3.85200;-12.93802;,
 10.85784;-23.45102;7.97158;,
 0.02972;-23.45102;7.97158;,
 10.85784;4.29748;12.58400;,
 0.02972;4.29748;12.58400;,
 10.85784;13.34618;-0.33884;,
 0.02972;13.34618;-0.33884;,
 10.85784;3.85200;-12.93802;,
 0.02972;3.85200;-12.93802;,
 10.85784;-0.07156;-0.10464;,
 10.85784;-0.07156;-0.10464;,
 10.85784;-0.07156;-0.10464;,
 10.85784;-0.07156;-0.10464;,
 10.85784;-0.07156;-0.10464;,
 0.02972;-0.07156;-0.10464;,
 0.02972;-0.07156;-0.10464;,
 0.02972;-0.07156;-0.10464;,
 0.02972;-0.07156;-0.10464;,
 0.02972;-0.07156;-0.10464;;
 
 15;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 3;12,1,0;,
 3;13,4,1;,
 3;14,6,4;,
 3;15,8,6;,
 3;16,10,8;,
 3;17,3,2;,
 3;18,2,5;,
 3;19,5,7;,
 3;20,7,9;,
 3;21,9,11;;
 
 MeshMaterialList {
  2;
  15;
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.659200;0.003200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.329600;0.001600;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.400000;0.400000;;
  }
 }
 MeshNormals {
  7;
  1.000000;0.000000;0.000000;,
  0.000000;-0.183089;-0.983096;,
  0.000000;-0.999848;0.017452;,
  0.000000;-0.163972;0.986465;,
  0.000000;0.819151;0.573578;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.798635;-0.601816;;
  15;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;;
 }
 MeshTextureCoords {
  22;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;;
 }
}
