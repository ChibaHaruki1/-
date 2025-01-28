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
 -37.69215;27.50858;-0.32285;,
 38.89449;27.50858;-0.32285;,
 38.89449;-28.98358;-0.32285;,
 -37.69215;-28.98358;-0.32285;,
 28.56917;19.08542;217.26314;,
 -27.36679;19.08542;217.26314;,
 -27.36679;-20.56042;217.26314;,
 28.56917;-20.56042;217.26314;,
 39.34113;53.05592;81.13460;,
 28.56917;19.08542;217.26314;,
 28.56917;-20.56042;217.26314;,
 39.35501;-24.97202;83.67299;,
 38.89449;-28.98358;-0.32285;,
 38.89449;27.50858;-0.32285;,
 -38.13799;53.06261;80.99400;,
 -37.69215;27.50858;-0.32285;,
 -37.69215;-28.98358;-0.32285;,
 -38.15191;-24.97870;83.53287;,
 -27.36679;-20.56042;217.26314;,
 -27.36679;19.08542;217.26314;,
 39.34113;53.05592;81.13460;,
 38.89449;27.50858;-0.32285;,
 -37.69215;27.50858;-0.32285;,
 -38.13799;53.06261;80.99400;,
 39.35501;-24.97202;83.67299;,
 -38.15191;-24.97870;83.53287;,
 -37.69215;-28.98358;-0.32285;,
 38.89449;-28.98358;-0.32285;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,16,17;,
 4;14,17,18,19;,
 4;20,21,22,23;,
 4;20,23,19,9;,
 4;24,10,18,25;,
 4;24,25,26,27;;
 
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
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.999305;0.000692;0.037260;,
  0.999304;0.000692;0.037304;,
  0.996792;0.001383;0.080023;,
  0.999985;-0.000000;-0.005483;,
  -0.999985;-0.000000;-0.005483;,
  -0.996799;0.001382;0.079935;,
  0.000070;0.999554;-0.029874;,
  0.000313;0.954087;-0.299528;,
  -0.000178;0.970273;0.242014;,
  0.000007;-0.999185;0.040359;,
  0.000013;-0.999455;0.033012;,
  -0.000000;-0.998861;0.047705;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;3,4,4,3;,
  4;3,3,5,5;,
  4;2,6,6,2;,
  4;2,2,7,7;,
  4;8,9,9,8;,
  4;8,8,10,10;,
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
  0.461860;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.476250;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.538940;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.524540;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.538140;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.538940;,
  1.000000;0.476250;,
  0.000000;0.475460;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
