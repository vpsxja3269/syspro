#include <stdio.h>
#include "db.h"

int main(int argc, char* argv[]){
	
	struct db rec;
	FILE *fp;

	if (argc != 2){
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "w");
	printf("%-2s %-12s %-8s %-12s %-5s \n", "id", "name", "category", "expired date", "stock");
	printf("---------------------------------------------");	
	while(scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, &rec.expired_date, &rec.stock) == 5)
		fprintf(fp, "\n %d %s %s %d %d ", rec.id, rec.name, rec.category, rec.expired_date, rec.stock);
	fclose(fp);
	return 0;
}
