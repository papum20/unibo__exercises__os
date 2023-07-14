#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define PATH_LEN 400


void tree_rec(char *path, int indent) {
	DIR *dir = opendir(path);
	struct dirent *file;
	int i;

	if(dir != NULL) {
		for(i = 0; i < indent - 1; i++) printf("\t");
		printf("%s\n", path);

		while((file = readdir(dir)) != NULL) {
			switch(file->d_type) {

				case DT_DIR:
					if(strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
						char new_path[PATH_LEN];
						strcpy(new_path, path);
						strcat(new_path, "/");
						strcat(new_path, file->d_name);
						tree_rec(new_path, indent+1);
					}
					break;
				case DT_REG:
					for(i = 0; i < indent; i++) printf("\t");
					printf("%s\n", file->d_name);
			}
		}

		closedir(dir);
	}
}



int main(int argc, char *argv[]) {

	if(argc < 2)
		printf("missing argument");

	char *root = argv[1];


	tree_rec(root, 1);


}
