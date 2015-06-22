/* Функция загрузки текстуры.
 * АРГУМЕНТЫ:
 *   - имя файла:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT ) идентификатор OpenGL для текстуры.
 */
INT LA1_TextureLoad( CHAR *FileName )
{
  INT TexId = 0, i;
  HDC hMemDC, hMemDCDIB;
  BITMAP bm;
  HBITMAP hBm, hBmDIB;
  DWORD *Bits;
  BITMAPINFOHEADER bih = {0};

  /* загружаем изображение из файла */
  hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  if (hBm == NULL)
    return 0;

  /* Create compatible context and select image into one */
  hMemDC = CreateCompatibleDC(LA1_Anim.hDC);
  hMemDCDIB = CreateCompatibleDC(LA1_Anim.hDC);
  SelectObject(hMemDC, hBm);

  /* Obtain image size */
  GetObject(hBm, sizeof(BITMAP), &bm);

  /* строим DIB - device-independed-bitmap секция */
  bih.biSize = sizeof(BITMAPINFOHEADER);
  bih.biWidth = bm.bmWidth;
  bih.biHeight = -bm.bmHeight;
  bih.biBitCount = 32;
  bih.biCompression = BI_RGB;
  bih.biPlanes = 1;
  bih.biSizeImage = bm.bmWidth * bm.bmHeight * 4;

  hBmDIB = CreateDIBSection(NULL, (BITMAPINFO *)&bih, DIB_RGB_COLORS, &Bits, NULL, 0);
  SelectObject(hMemDCDIB, hBmDIB);

  /* отображаем в DIB картинку */
  BitBlt(hMemDCDIB, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

  /* установка альфа канала */
  for (i = bm.bmWidth * bm.bmHeight - 1; i >= 0; i--)
    Bits[i] |= 0xFF000000;

  /* переносим в память OpenGL */
  glGenTextures(1, &TexId);
  glBindTexture(GL_TEXTURE_2D, TexId);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bm.bmWidth, bm.bmHeight,
    GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
  glBindTexture(GL_TEXTURE_2D, 0);

  /*
  if ((Bits = malloc(sizeof(DWORD) * bm.bmWidth * bm.bmHeight)) != NULL)
  {
    INT x, y, r, g, b;
    COLORREF c;

    for (y = 0; y < bm.bmHeight; y++)
      for (x = 0; x < bm.bmWidth; x++)
      {
        c = GetPixel(hMemDC, x, y);
        r = GetRValue(c);
        g = GetGValue(c);
        b = GetBValue(c);
        Bits[(bm.bmHeight - 1 - y) * bm.bmWidth + x] = 0xFF000000 | (r << 16) | (g << 8) | b;
      }
    glGenTextures(1, &TexId);
    glBindTexture(GL_TEXTURE_2D, TexId);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bm.bmWidth, bm.bmHeight,
      GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(Bits);
  }
  */

  DeleteDC(hMemDC);
  DeleteDC(hMemDCDIB);
  DeleteObject(hBm);
  DeleteObject(hBmDIB);
  return TexId;
} /* End of 'LA1_TextureLoadfunction */
