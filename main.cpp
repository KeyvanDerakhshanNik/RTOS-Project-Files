/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kdn807
 * Title of Program I/O
 * Created on February 26, 2016, 10:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

/*
 * 
 */
struct timeval GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}

char* ReadFile(char *filename) {
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");
    if (handler) {
        //seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        //offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        //go back to the start of the file
        rewind(handler);

        //allocate a string that can hold it all
        buffer = (char*) malloc(sizeof (char) * (string_size + 1));
        //read it all in one operation
        read_size = fread(buffer, sizeof (char), string_size, handler);
        //fread doesnt set it so put a \0 in the last position
        //and buffer is now officialy a string
        buffer[string_size] = '\0';
        if (string_size != read_size) {
            //something went wrong, throw away the memory and set
            //the buffer to NULL
            free(buffer);
            buffer = NULL;
        }
    }

    return buffer;
}

void WriteFile(char *string) {
    FILE *fp;
    fp = fopen("test.txt", "wb");
    if (fp == NULL)
        return;
    fprintf(fp,"%s",string);
    fclose(fp);
}

int main(int argc, char** argv) {
    int i;
    int count;
    struct timeval t1, t2;
    t1 = GetTimeStamp();
    printf("I/O \n");
    printf("%ld \n", t1.tv_usec);
    char *string = ReadFile("/media/disk/read.txt");
    if (string) {
        WriteFile(string);

    }
    free(string);
    t2 = GetTimeStamp();
    printf("%ld \n", t2.tv_usec);
    printf("Total execution time in micro-second is : %ld \n", t2.tv_usec - t1.tv_usec);
    return 0;
}

