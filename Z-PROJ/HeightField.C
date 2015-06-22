  pd6MATERIAL Mtl = PD6_MtlLib[0];

  . . .

  PD6_RndPrimMatrConvert = MatrIdentity();
  PD6_PrimCreateHeightField(&Uni->Pr, VecSet(0, 0, 0), VecSet(-1200, 0, 0), VecSet(0, 0, 1200), 180.0, "E:\\SPR09\\Test2.BMP");
  Mtl.TexId = PD6_TextureLoad("HF1TEX.BMP");
  Uni->Pr.MtlNo = Uni->TextId = PD6_MtlAdd(&Mtl);
