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
 -11.98729;-0.95672;18.13383;,
 12.42274;-0.95672;18.13383;,
 12.42274;0.83456;-15.85545;,
 -11.98729;0.83456;-15.85545;,
 -12.87645;-56.36868;-31.18078;,
 11.53358;-56.36868;-31.18078;,
 11.53358;-56.60013;2.80843;,
 -12.87645;-56.60013;2.80843;,
 12.42274;-6.03532;-15.85545;,
 11.53358;-56.36868;-31.18078;,
 -12.87645;-56.36868;-31.18078;,
 -11.98729;-6.64096;-15.85545;,
 -11.98729;0.83456;-15.85545;,
 12.42274;0.83456;-15.85545;,
 12.42274;-6.25184;18.13383;,
 11.53358;-56.36868;-31.18078;,
 12.42274;-6.03532;-15.85545;,
 12.42274;0.83456;-15.85545;,
 -11.98729;-6.85752;18.13383;,
 -12.87645;-56.60013;2.80843;,
 11.53358;-56.60013;2.80843;,
 12.42274;-6.25184;18.13383;,
 12.42274;-0.95672;18.13383;,
 -11.98729;-0.95672;18.13383;,
 -11.98729;-6.64096;-15.85545;,
 -12.87645;-56.36868;-31.18078;,
 -11.98729;-6.85752;18.13383;,
 -11.98729;0.83456;-15.85545;;
 
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
  0.000000;0.998614;0.052628;,
  0.000000;-0.999977;-0.006809;,
  -0.001828;0.148110;-0.988969;,
  0.999961;-0.008813;-0.000058;,
  0.001827;-0.148069;0.988975;,
  -0.003615;0.292952;-0.956120;,
  0.000000;0.000000;-1.000000;,
  0.999845;-0.017625;-0.000116;,
  1.000000;0.000000;0.000000;,
  0.003614;-0.292873;0.956144;,
  0.000000;0.000000;1.000000;,
  -0.999960;0.008920;0.000059;,
  -0.999841;0.017839;0.000118;,
  -1.000000;0.000000;0.000000;;
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
