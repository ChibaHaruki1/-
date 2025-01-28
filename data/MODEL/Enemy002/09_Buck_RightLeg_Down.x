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
 -13.23109;-1.01511;20.78582;,
 11.04519;-1.01511;24.51331;,
 14.78091;0.77617;-20.58186;,
 -9.11965;0.77617;-24.63907;,
 -10.02233;-53.57288;-32.63375;,
 14.25399;-53.57288;-28.90624;,
 9.98743;-53.80432;16.51859;,
 -14.28889;-53.80432;12.79098;,
 15.31179;-6.09371;-20.91145;,
 14.25399;-53.57288;-28.90624;,
 -10.02233;-53.57288;-32.63375;,
 -8.96453;-6.69935;-24.63907;,
 -9.11965;0.77617;-24.63907;,
 14.78091;0.77617;-20.58186;,
 11.04519;-6.31023;24.51331;,
 14.25399;-53.57288;-28.90624;,
 15.31179;-6.09371;-20.91145;,
 14.78091;0.77617;-20.58186;,
 -13.23109;-6.91591;20.78582;,
 -14.28889;-53.80432;12.79098;,
 9.98743;-53.80432;16.51859;,
 11.04519;-6.31023;24.51331;,
 11.04519;-1.01511;24.51331;,
 -13.23109;-1.01511;20.78582;,
 -8.96453;-6.69935;-24.63907;,
 -10.02233;-53.57288;-32.63375;,
 -13.23109;-6.91591;20.78582;,
 -9.11965;0.77617;-24.63907;;
 
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
  -0.006303;0.999219;0.039000;,
  0.000771;-0.999987;-0.005023;,
  0.153624;0.096837;-0.983373;,
  0.995872;-0.000860;0.090766;,
  -0.150280;-0.081260;0.985298;,
  0.147799;0.162031;-0.975654;,
  0.158781;0.031222;-0.986820;,
  0.994921;-0.037864;0.093262;,
  0.995452;0.036146;0.088144;,
  -0.147801;-0.161982;0.975662;,
  -0.151766;0.000000;0.988417;,
  -0.995589;0.014015;-0.092770;,
  -0.994903;0.038352;-0.093258;,
  -0.995684;-0.010331;-0.092228;;
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
