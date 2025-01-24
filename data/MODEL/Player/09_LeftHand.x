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
 52;
 -0.01700;4.94060;-4.87568;,
 -0.01700;-5.20768;-4.87568;,
 -0.01700;-5.20768;4.87568;,
 -0.01700;4.94060;4.87566;,
 9.73432;4.94060;4.87566;,
 10.81044;-4.60478;4.87568;,
 10.81044;-4.60478;-4.87568;,
 9.73432;4.94060;-4.87568;,
 3.63594;4.94060;4.87566;,
 -0.01700;4.94060;4.87566;,
 -0.01700;-5.20768;4.87568;,
 2.84036;-5.20768;4.87568;,
 3.92514;-9.04840;4.87568;,
 4.68442;4.94060;4.87566;,
 2.84036;-5.20768;4.87568;,
 -0.01700;-5.20768;4.87568;,
 2.92486;-5.20768;-4.87568;,
 3.87420;-9.04840;-4.87566;,
 3.92514;-9.04840;4.87568;,
 2.92486;-5.20768;-4.87568;,
 -0.01700;-5.20768;-4.87568;,
 -0.01700;4.94060;-4.87568;,
 3.72042;4.94060;-4.87568;,
 4.63344;4.94060;-4.87568;,
 3.87420;-9.04840;-4.87566;,
 3.72042;4.94060;-4.87568;,
 -0.01700;4.94060;4.87566;,
 3.63594;4.94060;4.87566;,
 4.68442;4.94060;4.87566;,
 4.63344;4.94060;-4.87568;,
 6.52486;-9.38108;4.87568;,
 6.49986;4.94060;4.87566;,
 6.53558;-9.38108;-4.87566;,
 6.52486;-9.38108;4.87568;,
 6.51054;4.94060;-4.87568;,
 6.53558;-9.38108;-4.87566;,
 6.49986;4.94060;4.87566;,
 6.51054;4.94060;-4.87568;,
 8.13742;-8.95518;4.87568;,
 10.81044;-4.60478;4.87568;,
 9.73432;4.94060;4.87566;,
 8.10892;4.94060;4.87566;,
 8.20152;-8.95518;-4.87568;,
 10.81044;-4.60478;4.87568;,
 8.13742;-8.95518;4.87568;,
 8.17298;4.94060;-4.87568;,
 9.73432;4.94060;-4.87568;,
 10.81044;-4.60478;-4.87568;,
 8.20152;-8.95518;-4.87568;,
 8.10892;4.94060;4.87566;,
 9.73432;4.94060;4.87566;,
 8.17298;4.94060;-4.87568;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,1,16;,
 4;14,16,17,18;,
 4;19,20,21,22;,
 4;19,22,23,24;,
 4;25,0,26,27;,
 4;25,27,28,29;,
 4;30,31,13,12;,
 4;32,33,18,17;,
 4;34,35,24,23;,
 4;36,37,29,28;,
 4;38,39,40,41;,
 4;38,41,31,30;,
 4;42,6,43,44;,
 4;42,44,33,32;,
 4;45,46,47,48;,
 4;45,48,35,34;,
 4;49,50,7,51;,
 4;49,51,37,36;;
 
 MeshMaterialList {
  2;
  22;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
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
  20;
  -1.000000;0.000000;0.000000;,
  0.993705;0.112028;0.000000;,
  0.976620;-0.214966;0.001479;,
  0.000001;0.000002;1.000000;,
  -0.966698;-0.255916;-0.001634;,
  0.000003;-0.000001;-1.000000;,
  0.000001;0.000002;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000003;-0.000001;-1.000000;,
  -0.000000;0.000001;1.000000;,
  0.064174;-0.997939;0.000615;,
  -0.000003;-0.000001;-1.000000;,
  -0.000001;0.000002;1.000000;,
  0.596981;-0.802253;0.002026;,
  -0.000003;-0.000000;-1.000000;,
  0.000000;0.000002;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.125485;-0.992096;0.000254;,
  -0.000001;0.000002;1.000000;;
  22;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;6,15,15,6;,
  4;6,6,3,3;,
  4;7,7,7,7;,
  4;4,4,4,4;,
  4;8,16,16,8;,
  4;8,8,5,5;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;9,9,3,3;,
  4;10,10,18,18;,
  4;11,11,5,5;,
  4;17,17,17,17;,
  4;12,19,19,12;,
  4;12,12,9,9;,
  4;13,2,2,13;,
  4;13,13,10,10;,
  4;14,16,16,14;,
  4;14,14,11,11;,
  4;17,17,17,17;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.290460;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.291540;,
  1.000000;0.486930;,
  0.000000;0.482130;,
  0.000000;0.291540;,
  0.000000;0.000000;,
  1.000000;0.308060;,
  1.000000;0.489560;,
  0.000000;0.486930;,
  0.000000;0.308060;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.306980;,
  1.000000;0.484760;,
  0.000000;0.489560;,
  0.000000;0.306980;,
  1.000000;0.000000;,
  1.000000;0.290460;,
  1.000000;0.482130;,
  0.000000;0.484760;,
  1.000000;0.670870;,
  0.000000;0.668310;,
  1.000000;0.710140;,
  0.000000;0.670870;,
  1.000000;0.707580;,
  0.000000;0.710140;,
  1.000000;0.668310;,
  0.000000;0.707580;,
  1.000000;0.836240;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.833310;,
  1.000000;0.880990;,
  0.000000;1.000000;,
  0.000000;0.836240;,
  1.000000;0.878060;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.880990;,
  1.000000;0.833310;,
  1.000000;1.000000;,
  0.000000;0.878060;;
 }
}
