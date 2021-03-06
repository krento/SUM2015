/* ����������� ����� */
#include <al.h>
#include <alc.h>
#include <alut.h>


#pragma comment(lib, "alut")
#pragma comment(lib, "openal32")


  /* ������������� ����� ������� */
  alutInit(NULL, 0);
  alGetError();
 
  
  
  INT format;
  UINT size, freq;
  VOID *mem;
  CHAR loop;

  /* ������� ������ */
  alGenBuffers(2, Uni->ABuf);

  /* ��������� ���� � ����� */
  alutLoadWAVFile("a.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[0], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  alutLoadWAVFile("a1.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[1], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  /* ������� ��������� ����� � ��������������� �� */
  alGenSources(2, Uni->ASrc);

  alSourcei(Uni->ASrc[0], AL_BUFFER, Uni->ABuf[0]); /* ���������� ����� �� ���������� */
  alSourcef(Uni->ASrc[0], AL_PITCH, 1);             /* �������� ���������������: 1.0 - �������*/
  alSourcef(Uni->ASrc[0], AL_GAIN, 0.3);              /* ���������: 1.0 � ������� */
  alSourcei(Uni->ASrc[0], AL_LOOPING, 1);           /* ���� �������: 0 � ���, 1 � ���������� */

  alSourcePlay(Uni->ASrc[0]); /* ������ ������������ */

  alSourcei(Uni->ASrc[1], AL_BUFFER, Uni->ABuf[1]); /* ���������� ����� �� ���������� */
  alSourcef(Uni->ASrc[1], AL_PITCH, 1);             /* �������� ���������������: 1.0 - �������*/
  alSourcef(Uni->ASrc[1], AL_GAIN, 1);              /* ���������: 1.0 � ������� */
  alSourcei(Uni->ASrc[1], AL_LOOPING, 0);           /* ���� �������: 0 � ���, 1 � ���������� */



  if (Ani->JButsClick[0])
    alSourcePlay(Uni->ASrc[1]);
  if (Ani->KeysClick['S'])
    alSourceStopv(2, Uni->ASrc);




