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
 36;
 -19.47148;12.93754;8.79210;,
 0.03578;4.27244;8.79210;,
 0.03578;4.27244;-7.10576;,
 -19.47148;12.93754;-7.10576;,
 -19.47148;-9.66792;-7.10576;,
 0.03578;-4.07680;-7.10576;,
 0.03578;-4.07680;8.79210;,
 -19.47148;-9.66792;8.79210;,
 0.01694;1.35982;-7.10576;,
 -25.98228;5.32644;-7.10576;,
 -19.47148;12.93754;-7.10576;,
 0.03578;4.27244;-7.10576;,
 0.01694;1.35982;8.79210;,
 0.01694;1.35982;-7.10576;,
 0.03578;4.27244;-7.10576;,
 -25.98228;5.32664;8.79210;,
 0.01694;1.35982;8.79210;,
 0.03578;4.27244;8.79210;,
 -19.47148;12.93754;8.79210;,
 -25.98228;5.32644;-7.10576;,
 -25.98228;5.32664;8.79210;,
 -19.47148;12.93754;-7.10576;,
 0.01694;-1.42568;-7.10576;,
 0.03578;-4.07680;-7.10576;,
 -19.47148;-9.66792;-7.10576;,
 -25.98228;-6.31952;-7.10576;,
 0.01694;-1.42652;8.79210;,
 0.03578;-4.07680;-7.10576;,
 0.01694;-1.42568;-7.10576;,
 -25.98228;-6.32334;8.79210;,
 -19.47148;-9.66792;8.79210;,
 0.03578;-4.07680;8.79210;,
 0.01694;-1.42652;8.79210;,
 -25.98228;-6.31952;-7.10576;,
 -19.47148;-9.66792;-7.10576;,
 -25.98228;-6.32334;8.79210;;
 
 14;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,1;,
 4;15,16,17,18;,
 4;19,20,0,21;,
 4;22,23,24,25;,
 4;22,25,9,8;,
 4;26,6,27,28;,
 4;26,28,13,12;,
 4;29,30,31,32;,
 4;29,32,16,15;,
 4;33,34,7,35;,
 4;33,35,20,19;;
 
 MeshMaterialList {
  2;
  14;
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
  13;
  0.405951;0.913895;0.000000;,
  -0.097665;-0.995219;-0.000057;,
  0.275524;-0.961294;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999995;-0.003234;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.999994;0.003554;0.000000;,
  0.999979;-0.006468;-0.000000;,
  -0.938055;0.346487;-0.000002;,
  -0.759893;0.650048;-0.000004;,
  0.999975;0.007107;0.000000;,
  -0.457140;-0.889395;-0.000107;,
  -1.000000;0.000000;0.000000;;
  14;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;4,4,7,7;,
  4;5,5,5,5;,
  4;8,8,9,9;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;6,10,10,6;,
  4;6,6,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;11,1,1,11;,
  4;12,12,8,8;;
 }
 MeshTextureCoords {
  36;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.277360;,
  0.000000;0.279100;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.277350;,
  0.000000;0.277360;,
  0.000000;0.000000;,
  1.000000;0.279090;,
  0.000000;0.277350;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.279100;,
  0.000000;0.279090;,
  1.000000;0.000000;,
  1.000000;0.738440;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.706560;,
  1.000000;0.738580;,
  0.000000;1.000000;,
  0.000000;0.738440;,
  1.000000;0.706700;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.738580;,
  1.000000;0.706560;,
  1.000000;1.000000;,
  0.000000;0.706700;;
 }
}
