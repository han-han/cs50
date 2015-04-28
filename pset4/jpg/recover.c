/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

typedef uint8_t  BYTE;

#define jpgB 512

int main(void)
{
    // open card file
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    int counter = 0;
    char filename[8];
    FILE* jpgptr = NULL;  
    BYTE buff[jpgB];
    
    // repeat until end of card
    while(!feof(inptr))
    {
        // read 512 bytes into a buffer
        fread(&buff, sizeof(BYTE), jpgB, inptr);
        // start of a new jpeg? 
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] == 0xe0 || buff[3] == 0xe1))
        {
            // found a new jepg, close previous file
            if (jpgptr != NULL)
            {
                fclose(jpgptr);
            }
            sprintf(filename, "%.03d.jpg", counter);
            jpgptr = fopen(filename, "w");
            counter++;
            if (jpgptr == NULL)
            {
                printf("Could not open %s\n", filename);
                return 2;
            }
            fwrite(&buff, sizeof(BYTE), jpgB, jpgptr);
        }
        // skip initial blocks, or continue the current jpeg
        else if (counter > 0)
        {
            if (jpgptr == NULL)
            {
                jpgptr = fopen(filename, "w");
            }
            fwrite(&buff, sizeof(BYTE), jpgB, jpgptr);
        }   
    }

    // close outfile
    fclose(jpgptr);
        
    // close infile
    fclose(inptr);

    return 0;
}
