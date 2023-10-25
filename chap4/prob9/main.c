#include <stdio.h>
int main(int argc, char *argv[])
{
   char c;
   FILE *fp1, *fp2; //파일 구조체로 두개를 연다
   if (argc !=3) {
      fprintf(stderr,  "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }
fp1 = fopen(argv[1], "r"); //argv[1]=a.txt,2는 b.txt
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }

fp2 = fopen(argv[2], "ab");
while ((c = fgetc(fp1)) != EOF)
	fputc(c, fp2);

	fclose(fp1);
	fclose(fp2);
	return 0;
}
