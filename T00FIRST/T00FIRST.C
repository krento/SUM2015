#include<stdio.h>
#include<windows.h>

void main( void )
{
  int i;

  if (MessageBox(NULL, "?", "question", MB_YESNO | MB_ICONQUESTION) == IDNO)
    if (MessageBox(NULL, "Вы уверены что хотите нажать NO?", "question", MB_YESNO | MB_ICONQUESTION) == IDNO)
      MessageBox(NULL, "U PRESSED NO", "info", MB_OK | MB_ICONERROR);
    else
      for(i = 0; i < 5; i++)
        MessageBox(NULL, "ERROR", "info", MB_OK | MB_ICONERROR);

  else
    if (MessageBox(NULL, "Вы уверены что хотите нажать YES?", "question", MB_YESNO | MB_ICONQUESTION) == IDYES)
      MessageBox(NULL, "U PRESSED YES", "info", MB_OK | MB_ICONINFORMATION);
    else
       for(i = 0; i < 5; i++)
         MessageBox(NULL, "ERROR", "info", MB_OK | MB_ICONERROR);
}
