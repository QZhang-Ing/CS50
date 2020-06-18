#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // if not exactly one argument recevied
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover inputfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    // open file
    FILE *inptr = fopen(infile, "r");
    // if forensic image cant be open, inform users
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // creates array of type char to contain the name of the output file, which
    // has to be 8 bytes to store the name xxx.jpg and 0 at the end.
    char outfile[8];
    FILE *outptr = NULL;
    // creates counter to record how many new jpegs have been created
    int counter = 0;
    // creates buffer array of type BYTE to store 512 bytes at one time of input file
    unsigned char *buffer = malloc(512 * sizeof(char));
    while (fread(buffer, 512, 1, inptr))
    {
        // compares the first four BYTEs with the pattern of beginning of a jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check whether it is the first time finding a jepg
            if (counter != 0)
            {
                fclose(outptr);
            }

            counter++;
            // write correct output file name
            sprintf(outfile, "%03i.jpg", counter);
            // creates and writes new file
            outptr = fopen(outfile, "w");
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
        fseek(inptr, 512, SEEK_CUR);
    }

    // reached the end of the card or some errors occour, close all files
    fclose(inptr);
    //fclose(outptr);
    free(buffer);
    return 0;

}