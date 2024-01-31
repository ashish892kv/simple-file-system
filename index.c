#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for file and directory
typedef struct {
    char name[50];
    char content[1000];
} File;

typedef struct {
    char name[50];
    File* files;
    int fileCount;
} Directory;

// Function to create a file
File createFile(const char* name, const char* content) {
    File newFile;
    strcpy(newFile.name, name);
    strcpy(newFile.content, content);
    return newFile;
}

// Function to create a directory
Directory createDirectory(const char* name) {
    Directory newDir;
    strcpy(newDir.name, name);
    newDir.files = NULL;
    newDir.fileCount = 0;
    return newDir;
}

// Function to add a file to a directory
void addFileToDirectory(Directory* dir, File file) {
    dir->files = realloc(dir->files, (dir->fileCount + 1) * sizeof(File));
    dir->files[dir->fileCount] = file;
    dir->fileCount++;
}

// Function to list files in a directory
void listFilesInDirectory(Directory dir) {
    printf("Files in directory '%s':\n", dir.name);
    for (int i = 0; i < dir.fileCount; i++) {
        printf("- %s\n", dir.files[i].name);
    }
}

int main() {
    // Create a root directory
    Directory root = createDirectory("Root");

    // Create and add files to the root directory
    File file1 = createFile("file1.txt", "This is the content of file1.");
    File file2 = createFile("file2.txt", "Content of file2 is here.");
    addFileToDirectory(&root, file1);
    addFileToDirectory(&root, file2);

    // List files in the root directory
    listFilesInDirectory(root);

    // Create a subdirectory
    Directory subDir = createDirectory("Subdirectory");

    // Create and add files to the subdirectory
    File file3 = createFile("file3.txt", "Hello from file3!");
    addFileToDirectory(&subDir, file3);

    // Add the subdirectory to the root directory
    addFileToDirectory(&root, createFile(subDir.name, ""));

    // List files in the root directory (including subdirectories)
    listFilesInDirectory(root);

    // Clean up allocated memory
    free(root.files);
    free(subDir.files);

    return 0;
}