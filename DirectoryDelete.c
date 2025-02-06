/*
accept directory name from user and delete all such files whose size is greater than 100 bytes.
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
	DIR *dir;
	struct dirent *entry;
	struct stat fileStat;	// Structure which stores all information of file.
	int max = 0;
	char name[100] = {'\0'};	

	if(argc != 2)
	{
		printf("Error: Not sufficeient arguments\n");
		fprintf(stderr, "Usage: %s: DirectoryName\n", argv[1]);
		
		return -1;
	}

	// Open the specified directory
	if ((dir = opendir(argv[1])) == NULL)
	{
		printf("Unable to open specified directory\n");
		return -1;
	}

	// Traverse directory
	while ((entry = readdir(dir)) != NULL)
	{
		// Use to create absolute path of file
		sprintf(name,"%s/%s",argv[1],entry->d_name);		
		stat(name,&fileStat);				
		
		// Check file size only if it is regular file
		if(S_ISREG(fileStat.st_mode))
		{		
			// Compaire file size
			if((int)fileStat.st_size > 100) // 100 is filesize in bytes
			{
				// Delete the specified file
				remove(name);
				printf("file is deleted whose size is more than 100 bytes");
			}
		}
		memset(&fileStat,0,sizeof(fileStat));
	}
	
	// close that opened directory
	closedir(dir);
return 0;
}

