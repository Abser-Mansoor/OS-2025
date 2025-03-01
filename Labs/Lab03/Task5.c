#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void copyFile(const char *src, const char *dest) {
    FILE *sourceFile = fopen(src, "rb");
    if (!sourceFile) return;

    FILE *destFile = fopen(dest, "wb");
    if (!destFile) {
        fclose(sourceFile);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);
}

void backupDirectory(const char *srcDir, const char *destDir) {
    struct stat st;
    if (stat(destDir, &st) == -1) {
        mkdir(destDir, 0755);
    }

    DIR *dir = opendir(srcDir);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        char srcPath[512], destPath[512];
        snprintf(srcPath, sizeof(srcPath), "%s/%s", srcDir, entry->d_name);
        snprintf(destPath, sizeof(destPath), "%s/%s", destDir, entry->d_name);

        if (entry->d_type == DT_DIR) {
            backupDirectory(srcPath, destPath);
        } else {
            copyFile(srcPath, destPath);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s D:/abseruni\n", argv[0]);
        return 1;
    }

    char backupDir[512];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(backupDir, sizeof(backupDir), "backup_%04d%02d%02d_%02d%02d%02d",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);

    printf("Backing up %s to %s\n", argv[1], backupDir);
    backupDirectory(argv[1], backupDir);
    printf("Backup completed!\n");

    return 0;
}
