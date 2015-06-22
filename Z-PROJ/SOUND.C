/* полключание звука */
#include <al.h>
#include <alc.h>
#include <alut.h>


#pragma comment(lib, "alut")
#pragma comment(lib, "openal32")


  /* »нициализаци€ аудио системы */
  alutInit(NULL, 0);
  alGetError();
 
  
  
  INT format;
  UINT size, freq;
  VOID *mem;
  CHAR loop;

  /* создаем буфера */
  alGenBuffers(2, Uni->ABuf);

  /* загружаем звук в буфер */
  alutLoadWAVFile("a.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[0], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  alutLoadWAVFile("a1.wav", &format, &mem, &size, &freq, &loop);
  alBufferData(Uni->ABuf[1], format, mem, size, freq);
  alutUnloadWAV(format, mem, size, freq);

  /* создаем источники звука и параметризируем их */
  alGenSources(2, Uni->ASrc);

  alSourcei(Uni->ASrc[0], AL_BUFFER, Uni->ABuf[0]); /* закрепл€ем буфер за источником */
  alSourcef(Uni->ASrc[0], AL_PITCH, 1);             /* скорость воспроизведени€: 1.0 - обычна€*/
  alSourcef(Uni->ASrc[0], AL_GAIN, 0.3);              /* громкость: 1.0 Ц обычна€ */
  alSourcei(Uni->ASrc[0], AL_LOOPING, 1);           /* флаг повтора: 0 Ц нет, 1 Ц бесконечно */

  alSourcePlay(Uni->ASrc[0]); /* запуск проигрывани€ */

  alSourcei(Uni->ASrc[1], AL_BUFFER, Uni->ABuf[1]); /* закрепл€ем буфер за источником */
  alSourcef(Uni->ASrc[1], AL_PITCH, 1);             /* скорость воспроизведени€: 1.0 - обычна€*/
  alSourcef(Uni->ASrc[1], AL_GAIN, 1);              /* громкость: 1.0 Ц обычна€ */
  alSourcei(Uni->ASrc[1], AL_LOOPING, 0);           /* флаг повтора: 0 Ц нет, 1 Ц бесконечно */



  if (Ani->JButsClick[0])
    alSourcePlay(Uni->ASrc[1]);
  if (Ani->KeysClick['S'])
    alSourceStopv(2, Uni->ASrc);




