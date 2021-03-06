/* FILENAME: ANIM.C
 * PROGRAMMER: LA1
 * PURPOSE: Animation system module.
 * LAST UPDATE: 15.06.2015
 */

#include "anim.h"


#include <mmsystem.h>
#pragma comment(lib, "winmm")


#define LA1_GET_AXIS_VALUE(Axis) \
  (2.0 * (ji.dw ## Axis ## pos - jc.w ## Axis ## min) / (jc.w ## Axis ## max - jc.w ## Axis ## min) - 1.0)


la1ANIM LA1_Anim;

static INT64
  TimeFreq,  
  TimeStart, 
  TimeOld,   
  TimePause, 
  TimeFPS;   
static INT
  FrameCounter; 


static INT
  LA1_MouseOldX, LA1_MouseOldY;

/* 
 * 
 * 
 * 
 */
BOOL LA1_AnimInit( HWND hWnd )
{
  INT i;
  LARGE_INTEGER li;
  POINT pt;
  PIXELFORMATDESCRIPTOR pfd = {0};

  memset(&LA1_Anim, 0, sizeof(la1ANIM));
  LA1_Anim.hWnd = hWnd;
  LA1_Anim.hDC = GetDC(hWnd);


  LA1_Anim.W = 30;
  LA1_Anim.H = 30;
  LA1_Anim.NumOfUnits = 0;




  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(LA1_Anim.hDC, &pfd);
  DescribePixelFormat(LA1_Anim.hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(LA1_Anim.hDC, i, &pfd);


  LA1_Anim.hGLRC = wglCreateContext(LA1_Anim.hDC);

  wglMakeCurrent(LA1_Anim.hDC, LA1_Anim.hGLRC);


  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(LA1_Anim.hGLRC);
    ReleaseDC(LA1_Anim.hWnd, LA1_Anim.hDC);
    memset(&LA1_Anim, 0, sizeof(la1ANIM));
    return FALSE;
  }

  LA1_RndProg = LA1_ShaderLoad("TEST");

  glActiveTexture(GL_TEXTURE0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glActiveTexture(GL_TEXTURE1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glActiveTexture(GL_TEXTURE0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////

  
  ////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////
  

  QueryPerformanceFrequency(&li);
  TimeFreq = li.QuadPart;
  QueryPerformanceCounter(&li);
  TimeStart = TimeOld = TimeFPS = li.QuadPart;
  LA1_Anim.IsPause = FALSE;
  FrameCounter = 0;

  GetCursorPos(&pt);
  ScreenToClient(LA1_Anim.hWnd, &pt);
  LA1_MouseOldX = pt.x;
  LA1_MouseOldY = pt.y;
  GetKeyboardState(LA1_Anim.KeysOld);
  return TRUE;
} /* End of 'LA1_AnimInit' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimClose( VOID )
{
  INT i;


  for (i = 0; i < LA1_Anim.NumOfUnits; i++)
  {
    LA1_Anim.Units[i]->Close(LA1_Anim.Units[i], &LA1_Anim);
    free(LA1_Anim.Units[i]);
    LA1_Anim.Units[i] = NULL;
  }

  LA1_ShaderFree(LA1_RndProg);
  LA1_RndProg = 0;

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(LA1_Anim.hGLRC);

  ReleaseDC(LA1_Anim.hWnd, LA1_Anim.hDC);
} /* End of 'LA1_AnimClose' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimResize( INT W, INT H )
{

  LA1_Anim.W = W;
  LA1_Anim.H = H;

  glViewport(0, 0, W, H);


  if (W > H)
    LA1_RndWp = (DBL)W / H * 3, LA1_RndHp = 3;
  else
    LA1_RndHp = (DBL)H / W * 3, LA1_RndWp = 3;

  LA1_RndMatrProj = MatrFrustum(-LA1_RndWp / 2, LA1_RndWp / 2,
                                -LA1_RndHp / 2, LA1_RndHp / 2,
                                LA1_RndProjDist, 800);

} /* End of 'LA1_AnimResize' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimRender( VOID )
{
  INT i;
  LARGE_INTEGER li;
  POINT pt;


  QueryPerformanceCounter(&li);
  LA1_Anim.GlobalTime = (DBL)(li.QuadPart - TimeStart) / TimeFreq;
  LA1_Anim.GlobalDeltaTime = (DBL)(li.QuadPart - TimeOld) / TimeFreq;

  if (!LA1_Anim.IsPause)
    LA1_Anim.DeltaTime = LA1_Anim.GlobalDeltaTime;
  else
  {
    TimePause += li.QuadPart - TimeOld;
    LA1_Anim.DeltaTime = 0;
  }

  LA1_Anim.Time = (DBL)(li.QuadPart - TimePause - TimeStart) / TimeFreq;

  if (li.QuadPart - TimeFPS > TimeFreq)
  {
    LA1_Anim.FPS = FrameCounter / ((DBL)(li.QuadPart - TimeFPS) / TimeFreq);
    TimeFPS = li.QuadPart;
    FrameCounter = 0;
  }


  TimeOld = li.QuadPart;




  GetKeyboardState(LA1_Anim.Keys);
  for (i = 0; i < 256; i++)
    LA1_Anim.Keys[i] >>= 7;
  for (i = 0; i < 256; i++)
    LA1_Anim.KeysClick[i] = LA1_Anim.Keys[i] && !LA1_Anim.KeysOld[i];
  memcpy(LA1_Anim.KeysOld, LA1_Anim.Keys, sizeof(LA1_Anim.KeysOld));

  LA1_Anim.MsWheel = LA1_MouseWheel;
  LA1_MouseWheel = 0;

  GetCursorPos(&pt);
  ScreenToClient(LA1_Anim.hWnd, &pt);
  LA1_Anim.MsX = pt.x;
  LA1_Anim.MsY = pt.y;

  LA1_Anim.MsDeltaX = pt.x - LA1_MouseOldX;
  LA1_Anim.MsDeltaY = pt.y - LA1_MouseOldY;
  LA1_MouseOldX = pt.x;
  LA1_MouseOldY = pt.y;

  if ((i = joyGetNumDevs()) > 0)
  {
    JOYCAPS jc;

    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYCAPS);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {

        memcpy(LA1_Anim.JButsOld, LA1_Anim.JButs, sizeof(LA1_Anim.JButs));
        for (i = 0; i < 32; i++)
          LA1_Anim.JButs[i] = (ji.dwButtons >> i) & 1;
        for (i = 0; i < 32; i++)
          LA1_Anim.JButsClick[i] = LA1_Anim.JButs[i] && !LA1_Anim.JButsOld[i];


        LA1_Anim.JX = LA1_GET_AXIS_VALUE(X);
        LA1_Anim.JY = LA1_GET_AXIS_VALUE(Y);
        if (jc.wCaps & JOYCAPS_HASZ)
          LA1_Anim.JZ = LA1_GET_AXIS_VALUE(Z);
        if (jc.wCaps & JOYCAPS_HASU)
          LA1_Anim.JU = LA1_GET_AXIS_VALUE(U);
        if (jc.wCaps & JOYCAPS_HASV)
          LA1_Anim.JV = LA1_GET_AXIS_VALUE(V);
        if (jc.wCaps & JOYCAPS_HASR)
          LA1_Anim.JR = LA1_GET_AXIS_VALUE(R);

        if (jc.wCaps & JOYCAPS_HASPOV)
        {
          if (ji.dwPOV == 0xFFFF)
            LA1_Anim.JPOV = 0;
          else
            LA1_Anim.JPOV = ji.dwPOV / 4500 + 1;
        }
      }
    }
  }

  for (i = 0; i < LA1_Anim.NumOfUnits; i++)
    LA1_Anim.Units[i]->Response(LA1_Anim.Units[i], &LA1_Anim);


  glClearColor(0.3, 0.5, 0.7, 1);
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColorMask(TRUE, TRUE, TRUE, TRUE);

  for (i = 0; i < LA1_Anim.NumOfUnits; i++)
  {
    static DBL time = 5;

    time += LA1_Anim.GlobalDeltaTime;
    if (time > 5)
    {
      time = 0;
      LA1_ShaderFree(LA1_RndProg);
      LA1_RndProg = LA1_ShaderLoad("TEST");
    }

    LA1_RndMatrWorld = MatrIdentity();

    LA1_Anim.Units[i]->Render(LA1_Anim.Units[i], &LA1_Anim);
  }
  glFinish();
  FrameCounter++;
} /* End of 'LA1_AnimRender' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimCopyFrame( VOID )
{

  SwapBuffers(LA1_Anim.hDC);
} /* End of 'LA1_AnimCopyFrame' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimAddUnit( la1UNIT *Unit )
{
  if (LA1_Anim.NumOfUnits < LA1_MAX_UNITS)
  {
    LA1_Anim.Units[LA1_Anim.NumOfUnits++] = Unit;
    Unit->Init(Unit, &LA1_Anim);
  }
} /* End of 'LA1_AnimAddUnit' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;               

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;


    GetWindowRect(LA1_Anim.hWnd, &SaveRC);


    hmon = MonitorFromWindow(LA1_Anim.hWnd, MONITOR_DEFAULTTONEAREST);


    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);


    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(LA1_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(LA1_Anim.hWnd, HWND_TOPMOST,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
 
    SetWindowPos(LA1_Anim.hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'LA1_AnimFlipFullScreen' function */

/* 
 * 
 * 
 * 
 */
VOID LA1_AnimDoExit( VOID )
{
  PostMessage(LA1_Anim.hWnd, WM_CLOSE, 0, 0);
} /* End of 'LA1_AnimDoExit' function */
/* 
 * 
 * 
 * 
 */
VOID LA1_AnimSetPause( BOOL NewPauseFlag )
{
  LA1_Anim.IsPause = NewPauseFlag;
} /* End of 'LA1_AnimSetPause' function */

/* END OF 'ANIM.C' FILE */
