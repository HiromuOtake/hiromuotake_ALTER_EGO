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
 196;
 0.00000;14.49148;0.00089;,
 8.38867;14.49148;-8.38779;,
 0.00000;14.49148;-11.86246;,
 11.86337;14.49148;0.00089;,
 8.38867;14.49148;8.38956;,
 0.00000;14.49148;11.86425;,
 -8.38867;14.49148;8.38956;,
 -11.86337;14.49148;0.00089;,
 -8.38867;14.49148;-8.38779;,
 9.87160;13.62283;-9.87069;,
 0.00000;13.62283;-13.95967;,
 13.96054;13.62283;0.00089;,
 9.87160;13.62283;9.87248;,
 0.00000;13.62283;13.96143;,
 -9.87160;13.62283;9.87248;,
 -13.96054;13.62283;0.00089;,
 -9.87160;13.62283;-9.87069;,
 10.48584;11.52565;-10.48494;,
 0.00000;11.52565;-14.82833;,
 14.82920;11.52565;0.00089;,
 10.48584;11.52565;10.48672;,
 0.00000;11.52565;14.83009;,
 -10.48584;11.52565;10.48671;,
 -14.82920;11.52565;0.00089;,
 -10.48584;11.52565;-10.48494;,
 11.70190;-0.33772;-11.70101;,
 0.00000;-0.33772;-16.54810;,
 16.54898;-0.33772;0.00089;,
 11.70190;-0.33772;11.70280;,
 0.00000;-0.33772;16.54987;,
 -11.70190;-0.33772;11.70280;,
 -16.54898;-0.33772;0.00089;,
 -11.70190;-0.33772;-11.70101;,
 10.48584;-12.20107;-10.48494;,
 0.00000;-12.20107;-14.82833;,
 14.82920;-12.20107;0.00089;,
 10.48584;-12.20107;10.48672;,
 0.00000;-12.20107;14.83009;,
 -10.48584;-12.20107;10.48671;,
 -14.82920;-12.20107;0.00089;,
 -10.48584;-12.20107;-10.48494;,
 9.87160;-14.29827;-9.87069;,
 0.00000;-14.29827;-13.95967;,
 13.96054;-14.29827;0.00089;,
 9.87160;-14.29827;9.87248;,
 0.00000;-14.29827;13.96143;,
 -9.87160;-14.29827;9.87248;,
 -13.96054;-14.29827;0.00089;,
 -9.87160;-14.29827;-9.87069;,
 8.38867;-15.16694;-8.38779;,
 0.00000;-15.16694;-11.86246;,
 11.86337;-15.16694;0.00089;,
 8.38867;-15.16694;8.38956;,
 0.00000;-15.16694;11.86425;,
 -8.38867;-15.16694;8.38956;,
 -11.86337;-15.16694;0.00089;,
 -8.38867;-15.16694;-8.38779;,
 0.00000;-15.16694;0.00089;,
 -13.43878;17.51130;21.24597;,
 13.43878;17.51130;21.24597;,
 13.43878;17.51130;11.92899;,
 -13.43878;17.51130;11.92899;,
 -13.43878;14.15161;8.56931;,
 13.43878;14.15161;8.56931;,
 13.43878;-12.72596;8.56931;,
 -13.43878;-12.72596;8.56931;,
 -13.43878;-16.08566;11.92899;,
 13.43878;-16.08566;11.92899;,
 13.43878;-16.08566;21.24597;,
 -13.43878;-16.08566;21.24597;,
 -13.43878;-12.72596;24.60568;,
 13.43878;-12.72596;24.60568;,
 13.43878;14.15161;24.60568;,
 -13.43878;14.15161;24.60568;,
 16.79847;14.15161;21.24597;,
 16.79847;-12.72596;21.24597;,
 16.79847;-12.72596;11.92899;,
 16.79847;14.15161;11.92899;,
 -16.79847;-12.72596;21.24597;,
 -16.79847;14.15161;21.24597;,
 -16.79847;14.15161;11.92899;,
 -16.79847;-12.72596;11.92899;,
 -13.43878;17.51130;11.92899;,
 13.43878;17.51130;11.92899;,
 13.43878;17.25556;10.64329;,
 -13.43878;17.25556;10.64329;,
 13.43878;16.52725;9.55334;,
 -13.43878;16.52725;9.55334;,
 13.43878;15.43731;8.82504;,
 -13.43878;15.43731;8.82504;,
 13.43878;14.15161;8.56931;,
 -13.43878;-15.82991;10.64329;,
 13.43878;-15.82991;10.64329;,
 13.43878;-16.08566;11.92899;,
 -13.43878;-15.10159;9.55334;,
 13.43878;-15.10159;9.55334;,
 -13.43878;-14.01165;8.82504;,
 13.43878;-14.01165;8.82504;,
 -13.43878;-12.72596;8.56931;,
 13.43878;-12.72596;8.56931;,
 -13.43878;17.25556;22.53169;,
 13.43878;17.25556;22.53169;,
 13.43878;17.51130;21.24597;,
 -13.43878;16.52725;23.62163;,
 13.43878;16.52725;23.62163;,
 -13.43878;15.43731;24.34994;,
 13.43878;15.43731;24.34994;,
 -13.43878;14.15161;24.60568;,
 13.43878;14.15161;24.60568;,
 -13.43878;-16.08566;21.24597;,
 13.43878;-16.08566;21.24597;,
 13.43878;-15.82991;22.53169;,
 -13.43878;-15.82991;22.53169;,
 13.43878;-15.10159;23.62163;,
 -13.43878;-15.10159;23.62163;,
 13.43878;-14.01165;24.34994;,
 -13.43878;-14.01165;24.34994;,
 13.43878;-12.72596;24.60568;,
 14.72448;17.25556;21.24597;,
 14.72448;17.25556;11.92899;,
 15.81444;16.52725;21.24597;,
 15.81444;16.52725;11.92899;,
 16.54272;15.43731;21.24597;,
 16.54272;15.43731;11.92899;,
 16.79847;14.15161;11.92899;,
 14.72448;-15.82991;11.92899;,
 14.72448;-15.82991;21.24597;,
 15.81444;-15.10159;11.92899;,
 15.81444;-15.10159;21.24597;,
 16.54272;-14.01165;11.92899;,
 16.54272;-14.01165;21.24597;,
 16.79847;-12.72596;11.92899;,
 16.79847;-12.72596;21.24597;,
 -14.72448;17.25556;11.92899;,
 -14.72448;17.25556;21.24597;,
 -15.81444;16.52725;11.92899;,
 -15.81444;16.52725;21.24597;,
 -16.54272;15.43731;11.92899;,
 -16.54272;15.43731;21.24597;,
 -16.79847;14.15161;11.92899;,
 -16.79847;14.15161;21.24597;,
 -14.72448;-15.82991;21.24597;,
 -14.72448;-15.82991;11.92899;,
 -15.81444;-15.10159;21.24597;,
 -15.81444;-15.10159;11.92899;,
 -16.54272;-14.01165;21.24597;,
 -16.54272;-14.01165;11.92899;,
 -16.79847;-12.72596;11.92899;,
 14.72448;14.15161;8.82504;,
 14.72448;-12.72596;8.82504;,
 15.81444;14.15161;9.55334;,
 15.81444;-12.72596;9.55334;,
 16.54272;14.15161;10.64329;,
 16.54272;-12.72596;10.64329;,
 14.72448;-12.72596;24.34994;,
 14.72448;14.15161;24.34994;,
 15.81444;-12.72596;23.62163;,
 15.81444;14.15161;23.62163;,
 16.54272;-12.72596;22.53169;,
 16.54272;14.15161;22.53169;,
 -14.72448;-12.72596;8.82504;,
 -14.72448;14.15161;8.82504;,
 -15.81444;-12.72596;9.55334;,
 -15.81444;14.15161;9.55334;,
 -16.54272;-12.72596;10.64329;,
 -16.54272;14.15161;10.64329;,
 -14.72448;14.15161;24.34994;,
 -14.72448;-12.72596;24.34994;,
 -15.81444;14.15161;23.62163;,
 -15.81444;-12.72596;23.62163;,
 -16.54272;14.15161;22.53169;,
 -16.54272;-12.72596;22.53169;,
 15.11863;16.52725;10.24915;,
 16.12688;15.43731;10.37701;,
 14.99077;15.43731;9.24089;,
 -15.11863;16.52725;10.24915;,
 -16.12688;15.43731;10.37701;,
 -14.99077;15.43731;9.24089;,
 15.11863;-15.10159;10.24915;,
 16.12688;-14.01165;10.37701;,
 14.99077;-14.01165;9.24089;,
 15.11863;16.52725;22.92583;,
 16.12688;15.43731;22.79796;,
 14.99077;15.43731;23.93410;,
 -15.11863;-15.10159;10.24915;,
 -16.12688;-14.01165;10.37701;,
 -14.99077;-14.01165;9.24089;,
 15.11863;-15.10159;22.92583;,
 16.12688;-14.01165;22.79796;,
 14.99077;-14.01165;23.93410;,
 -15.11863;16.52725;22.92583;,
 -16.12688;15.43731;22.79796;,
 -14.99077;15.43731;23.93410;,
 -15.11863;-15.10159;22.92583;,
 -16.12688;-14.01165;22.79796;,
 -14.99077;-14.01165;23.93410;;
 
 246;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 3;50,49,57;,
 3;49,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,56,57;,
 3;56,50,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,90,62;,
 4;91,92,93,66;,
 4;94,95,92,91;,
 4;96,97,95,94;,
 4;98,99,97,96;,
 4;100,101,102,58;,
 4;103,104,101,100;,
 4;105,106,104,103;,
 4;107,108,106,105;,
 4;109,110,111,112;,
 4;112,111,113,114;,
 4;114,113,115,116;,
 4;116,115,117,70;,
 4;83,102,118,119;,
 4;119,118,120,121;,
 4;121,120,122,123;,
 4;123,122,74,124;,
 4;110,93,125,126;,
 4;126,125,127,128;,
 4;128,127,129,130;,
 4;130,129,131,132;,
 4;58,82,133,134;,
 4;134,133,135,136;,
 4;136,135,137,138;,
 4;138,137,139,140;,
 4;66,109,141,142;,
 4;142,141,143,144;,
 4;144,143,145,146;,
 4;146,145,78,147;,
 4;99,90,148,149;,
 4;149,148,150,151;,
 4;151,150,152,153;,
 4;153,152,124,131;,
 4;108,117,154,155;,
 4;155,154,156,157;,
 4;157,156,158,159;,
 4;159,158,132,74;,
 4;62,98,160,161;,
 4;161,160,162,163;,
 4;163,162,164,165;,
 4;165,164,147,139;,
 4;70,107,166,167;,
 4;167,166,168,169;,
 4;169,168,170,171;,
 4;171,170,140,78;,
 3;83,119,84;,
 3;119,121,172;,
 3;172,84,119;,
 3;84,172,86;,
 3;121,123,173;,
 3;173,172,121;,
 3;172,173,174;,
 3;174,86,172;,
 3;86,174,88;,
 3;123,124,152;,
 3;152,173,123;,
 3;173,152,150;,
 3;150,174,173;,
 3;174,150,148;,
 3;148,88,174;,
 3;88,148,90;,
 3;85,133,82;,
 3;175,135,133;,
 3;133,85,175;,
 3;87,175,85;,
 3;176,137,135;,
 3;135,175,176;,
 3;177,176,175;,
 3;175,87,177;,
 3;89,177,87;,
 3;165,139,137;,
 3;137,176,165;,
 3;163,165,176;,
 3;176,177,163;,
 3;161,163,177;,
 3;177,89,161;,
 3;62,161,89;,
 3;92,125,93;,
 3;178,127,125;,
 3;125,92,178;,
 3;95,178,92;,
 3;179,129,127;,
 3;127,178,179;,
 3;180,179,178;,
 3;178,95,180;,
 3;97,180,95;,
 3;153,131,129;,
 3;129,179,153;,
 3;151,153,179;,
 3;179,180,151;,
 3;149,151,180;,
 3;180,97,149;,
 3;99,149,97;,
 3;101,118,102;,
 3;181,120,118;,
 3;118,101,181;,
 3;104,181,101;,
 3;182,122,120;,
 3;120,181,182;,
 3;183,182,181;,
 3;181,104,183;,
 3;106,183,104;,
 3;159,74,122;,
 3;122,182,159;,
 3;157,159,182;,
 3;182,183,157;,
 3;155,157,183;,
 3;183,106,155;,
 3;108,155,106;,
 3;66,142,91;,
 3;142,144,184;,
 3;184,91,142;,
 3;91,184,94;,
 3;144,146,185;,
 3;185,184,144;,
 3;184,185,186;,
 3;186,94,184;,
 3;94,186,96;,
 3;146,147,164;,
 3;164,185,146;,
 3;185,164,162;,
 3;162,186,185;,
 3;186,162,160;,
 3;160,96,186;,
 3;96,160,98;,
 3;110,126,111;,
 3;126,128,187;,
 3;187,111,126;,
 3;111,187,113;,
 3;128,130,188;,
 3;188,187,128;,
 3;187,188,189;,
 3;189,113,187;,
 3;113,189,115;,
 3;130,132,158;,
 3;158,188,130;,
 3;188,158,156;,
 3;156,189,188;,
 3;189,156,154;,
 3;154,115,189;,
 3;115,154,117;,
 3;58,134,100;,
 3;134,136,190;,
 3;190,100,134;,
 3;100,190,103;,
 3;136,138,191;,
 3;191,190,136;,
 3;190,191,192;,
 3;192,103,190;,
 3;103,192,105;,
 3;138,140,170;,
 3;170,191,138;,
 3;191,170,168;,
 3;168,192,191;,
 3;192,168,166;,
 3;166,105,192;,
 3;105,166,107;,
 3;112,141,109;,
 3;193,143,141;,
 3;141,112,193;,
 3;114,193,112;,
 3;194,145,143;,
 3;143,193,194;,
 3;195,194,193;,
 3;193,114,195;,
 3;116,195,114;,
 3;171,78,145;,
 3;145,194,171;,
 3;169,171,194;,
 3;194,195,169;,
 3;167,169,195;,
 3;195,116,167;,
 3;70,167,116;;
 
 MeshMaterialList {
  3;
  246;
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
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.780800;0.787200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.288800;0.339200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357600;0.357600;0.357600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  178;
  0.000000;1.000000;0.000000;,
  0.000000;0.981026;-0.193875;,
  0.137090;0.981026;-0.137090;,
  0.193875;0.981026;-0.000000;,
  0.137090;0.981026;0.137090;,
  0.000000;0.981026;0.193875;,
  -0.137090;0.981026;0.137090;,
  -0.193875;0.981026;-0.000000;,
  -0.137090;0.981026;-0.137090;,
  0.000000;0.715250;-0.698869;,
  0.494176;0.715249;-0.494175;,
  0.698870;0.715248;-0.000000;,
  0.494176;0.715249;0.494176;,
  -0.000000;0.715248;0.698870;,
  -0.494176;0.715248;0.494176;,
  -0.698871;0.715248;-0.000000;,
  -0.494176;0.715249;-0.494175;,
  0.000000;0.265683;-0.964061;,
  0.681694;0.265682;-0.681693;,
  0.964061;0.265682;-0.000000;,
  0.681694;0.265682;0.681694;,
  -0.000000;0.265682;0.964061;,
  -0.681694;0.265681;0.681694;,
  -0.964061;0.265681;0.000000;,
  -0.681694;0.265682;-0.681693;,
  0.000000;-0.000000;-1.000000;,
  0.707107;0.000000;-0.707106;,
  1.000000;0.000000;-0.000000;,
  0.707107;-0.000000;0.707107;,
  -0.000000;-0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707106;,
  0.000000;-0.265682;-0.964061;,
  0.681695;-0.265682;-0.681693;,
  0.964061;-0.265681;-0.000000;,
  0.681694;-0.265681;0.681694;,
  -0.000000;-0.265681;0.964061;,
  -0.681694;-0.265681;0.681694;,
  -0.964061;-0.265681;0.000000;,
  -0.681695;-0.265682;-0.681693;,
  0.000000;-0.715246;-0.698873;,
  0.494179;-0.715245;-0.494178;,
  0.698874;-0.715245;-0.000000;,
  0.494178;-0.715245;0.494178;,
  -0.000000;-0.715245;0.698874;,
  -0.494179;-0.715244;0.494179;,
  -0.698874;-0.715245;0.000000;,
  -0.494179;-0.715245;-0.494178;,
  0.000000;-0.981025;-0.193879;,
  0.137093;-0.981025;-0.137093;,
  0.193880;-0.981025;-0.000000;,
  0.137093;-0.981025;0.137093;,
  0.000000;-0.981025;0.193879;,
  -0.137093;-0.981025;0.137093;,
  -0.193880;-0.981025;-0.000000;,
  -0.137093;-0.981025;-0.137093;,
  0.000000;-1.000000;-0.000000;,
  -0.097567;0.990435;0.097566;,
  0.097567;0.990435;0.097566;,
  -0.097567;0.990435;-0.097568;,
  0.097567;0.990435;-0.097568;,
  -0.097563;0.097564;-0.990436;,
  0.097563;0.097564;-0.990436;,
  -0.097563;-0.097564;-0.990436;,
  0.097563;-0.097564;-0.990436;,
  -0.097568;-0.990435;-0.097569;,
  0.097568;-0.990435;-0.097569;,
  -0.097568;-0.990435;0.097566;,
  0.097568;-0.990435;0.097566;,
  -0.097568;-0.097569;0.990435;,
  0.097568;-0.097569;0.990435;,
  -0.097568;0.097569;0.990435;,
  0.097568;0.097569;0.990435;,
  0.990435;0.097567;0.097565;,
  0.990435;-0.097567;0.097565;,
  0.990435;0.097567;-0.097567;,
  0.990435;-0.097567;-0.097567;,
  -0.990435;-0.097567;0.097565;,
  -0.990435;0.097567;0.097565;,
  -0.990435;-0.097567;-0.097567;,
  -0.990435;0.097567;-0.097567;,
  -0.149550;0.917626;-0.368235;,
  0.149550;0.917626;-0.368235;,
  -0.151333;0.689780;-0.708027;,
  0.151333;0.689780;-0.708027;,
  -0.134927;0.354969;-0.925090;,
  0.134927;0.354969;-0.925090;,
  -0.149552;-0.917624;-0.368241;,
  0.149552;-0.917624;-0.368241;,
  -0.151333;-0.689777;-0.708029;,
  0.151333;-0.689777;-0.708029;,
  -0.134927;-0.354971;-0.925090;,
  0.134927;-0.354971;-0.925090;,
  -0.149551;0.917627;0.368234;,
  0.149551;0.917627;0.368234;,
  -0.151331;0.689780;0.708027;,
  0.151331;0.689780;0.708027;,
  -0.134927;0.354974;0.925088;,
  0.134927;0.354974;0.925088;,
  -0.149553;-0.917624;0.368240;,
  0.149553;-0.917624;0.368240;,
  -0.151331;-0.689778;0.708029;,
  0.151331;-0.689778;0.708029;,
  -0.134926;-0.354975;0.925088;,
  0.134926;-0.354975;0.925088;,
  0.368233;0.917627;0.149549;,
  0.368232;0.917627;-0.149551;,
  0.708030;0.689776;0.151335;,
  0.708030;0.689776;-0.151336;,
  0.925090;0.354969;0.134928;,
  0.925090;0.354968;-0.134930;,
  0.368238;-0.917625;0.149551;,
  0.368238;-0.917624;-0.149554;,
  0.708032;-0.689774;0.151335;,
  0.708032;-0.689774;-0.151337;,
  0.925090;-0.354970;0.134928;,
  0.925090;-0.354969;-0.134930;,
  -0.368233;0.917627;0.149549;,
  -0.368232;0.917627;-0.149551;,
  -0.708030;0.689776;0.151335;,
  -0.708030;0.689776;-0.151336;,
  -0.925090;0.354969;0.134928;,
  -0.925090;0.354968;-0.134930;,
  -0.368238;-0.917625;0.149551;,
  -0.368238;-0.917624;-0.149554;,
  -0.708032;-0.689774;0.151335;,
  -0.708032;-0.689774;-0.151337;,
  -0.925090;-0.354970;0.134928;,
  -0.925090;-0.354969;-0.134930;,
  0.356108;-0.121463;-0.926517;,
  0.356108;0.121463;-0.926517;,
  0.702221;-0.117385;-0.702216;,
  0.702221;0.117385;-0.702216;,
  0.926516;-0.121466;-0.356108;,
  0.926517;0.121466;-0.356108;,
  0.356112;-0.121463;0.926516;,
  0.356112;0.121463;0.926516;,
  0.702222;-0.117384;0.702215;,
  0.702222;0.117384;0.702215;,
  0.926516;-0.121468;0.356108;,
  0.926516;0.121468;0.356108;,
  -0.356108;-0.121463;-0.926517;,
  -0.356108;0.121463;-0.926517;,
  -0.702221;-0.117385;-0.702216;,
  -0.702221;0.117385;-0.702216;,
  -0.926516;-0.121466;-0.356108;,
  -0.926517;0.121466;-0.356108;,
  -0.356112;-0.121463;0.926516;,
  -0.356112;0.121463;0.926516;,
  -0.702222;-0.117384;0.702215;,
  -0.702222;0.117384;0.702215;,
  -0.926516;-0.121468;0.356108;,
  -0.926516;0.121468;0.356108;,
  0.472231;0.744308;-0.472233;,
  0.794182;0.405800;-0.452329;,
  0.452331;0.405802;-0.794180;,
  -0.472231;0.744308;-0.472233;,
  -0.794182;0.405800;-0.452329;,
  -0.452331;0.405802;-0.794180;,
  0.472234;-0.744305;-0.472235;,
  0.794181;-0.405801;-0.452329;,
  0.452331;-0.405804;-0.794179;,
  0.472233;0.744308;0.472230;,
  0.794183;0.405801;0.452326;,
  0.452333;0.405802;0.794179;,
  -0.472234;-0.744305;-0.472235;,
  -0.794181;-0.405801;-0.452329;,
  -0.452331;-0.405804;-0.794179;,
  0.472235;-0.744305;0.472232;,
  0.794183;-0.405802;0.452326;,
  0.452332;-0.405804;0.794178;,
  -0.472233;0.744308;0.472230;,
  -0.794183;0.405801;0.452326;,
  -0.452333;0.405802;0.794179;,
  -0.472235;-0.744305;0.472232;,
  -0.794183;-0.405802;0.452326;,
  -0.452332;-0.405804;0.794178;;
  246;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,59,61,60;,
  4;62,63,65,64;,
  4;66,67,69,68;,
  4;70,71,73,72;,
  4;74,75,77,76;,
  4;78,79,81,80;,
  4;60,61,83,82;,
  4;82,83,85,84;,
  4;84,85,87,86;,
  4;86,87,63,62;,
  4;88,89,67,66;,
  4;90,91,89,88;,
  4;92,93,91,90;,
  4;64,65,93,92;,
  4;94,95,59,58;,
  4;96,97,95,94;,
  4;98,99,97,96;,
  4;72,73,99,98;,
  4;68,69,101,100;,
  4;100,101,103,102;,
  4;102,103,105,104;,
  4;104,105,71,70;,
  4;61,59,106,107;,
  4;107,106,108,109;,
  4;109,108,110,111;,
  4;111,110,74,76;,
  4;69,67,113,112;,
  4;112,113,115,114;,
  4;114,115,117,116;,
  4;116,117,77,75;,
  4;58,60,119,118;,
  4;118,119,121,120;,
  4;120,121,123,122;,
  4;122,123,81,79;,
  4;66,68,124,125;,
  4;125,124,126,127;,
  4;127,126,128,129;,
  4;129,128,78,80;,
  4;65,63,131,130;,
  4;130,131,133,132;,
  4;132,133,135,134;,
  4;134,135,76,77;,
  4;73,71,136,137;,
  4;137,136,138,139;,
  4;139,138,140,141;,
  4;141,140,75,74;,
  4;62,64,142,143;,
  4;143,142,144,145;,
  4;145,144,146,147;,
  4;147,146,80,81;,
  4;70,72,149,148;,
  4;148,149,151,150;,
  4;150,151,153,152;,
  4;152,153,79,78;,
  3;61,107,83;,
  3;107,109,154;,
  3;154,83,107;,
  3;83,154,85;,
  3;109,111,155;,
  3;155,154,109;,
  3;154,155,156;,
  3;156,85,154;,
  3;85,156,87;,
  3;111,76,135;,
  3;135,155,111;,
  3;155,135,133;,
  3;133,156,155;,
  3;156,133,131;,
  3;131,87,156;,
  3;87,131,63;,
  3;82,119,60;,
  3;157,121,119;,
  3;119,82,157;,
  3;84,157,82;,
  3;158,123,121;,
  3;121,157,158;,
  3;159,158,157;,
  3;157,84,159;,
  3;86,159,84;,
  3;147,81,123;,
  3;123,158,147;,
  3;145,147,158;,
  3;158,159,145;,
  3;143,145,159;,
  3;159,86,143;,
  3;62,143,86;,
  3;89,113,67;,
  3;160,115,113;,
  3;113,89,160;,
  3;91,160,89;,
  3;161,117,115;,
  3;115,160,161;,
  3;162,161,160;,
  3;160,91,162;,
  3;93,162,91;,
  3;134,77,117;,
  3;117,161,134;,
  3;132,134,161;,
  3;161,162,132;,
  3;130,132,162;,
  3;162,93,130;,
  3;65,130,93;,
  3;95,106,59;,
  3;163,108,106;,
  3;106,95,163;,
  3;97,163,95;,
  3;164,110,108;,
  3;108,163,164;,
  3;165,164,163;,
  3;163,97,165;,
  3;99,165,97;,
  3;141,74,110;,
  3;110,164,141;,
  3;139,141,164;,
  3;164,165,139;,
  3;137,139,165;,
  3;165,99,137;,
  3;73,137,99;,
  3;66,125,88;,
  3;125,127,166;,
  3;166,88,125;,
  3;88,166,90;,
  3;127,129,167;,
  3;167,166,127;,
  3;166,167,168;,
  3;168,90,166;,
  3;90,168,92;,
  3;129,80,146;,
  3;146,167,129;,
  3;167,146,144;,
  3;144,168,167;,
  3;168,144,142;,
  3;142,92,168;,
  3;92,142,64;,
  3;69,112,101;,
  3;112,114,169;,
  3;169,101,112;,
  3;101,169,103;,
  3;114,116,170;,
  3;170,169,114;,
  3;169,170,171;,
  3;171,103,169;,
  3;103,171,105;,
  3;116,75,140;,
  3;140,170,116;,
  3;170,140,138;,
  3;138,171,170;,
  3;171,138,136;,
  3;136,105,171;,
  3;105,136,71;,
  3;58,118,94;,
  3;118,120,172;,
  3;172,94,118;,
  3;94,172,96;,
  3;120,122,173;,
  3;173,172,120;,
  3;172,173,174;,
  3;174,96,172;,
  3;96,174,98;,
  3;122,79,153;,
  3;153,173,122;,
  3;173,153,151;,
  3;151,174,173;,
  3;174,151,149;,
  3;149,98,174;,
  3;98,149,72;,
  3;100,124,68;,
  3;175,126,124;,
  3;124,100,175;,
  3;102,175,100;,
  3;176,128,126;,
  3;126,175,176;,
  3;177,176,175;,
  3;175,102,177;,
  3;104,177,102;,
  3;152,78,128;,
  3;128,176,152;,
  3;150,152,176;,
  3;176,177,150;,
  3;148,150,177;,
  3;177,104,148;,
  3;70,148,104;;
 }
 MeshTextureCoords {
  196;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}