/**
 * Pset 4
 *
 *
 * resize a bmp file
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // check multiplier
    if (n <= 0 || n >= 100)
    {
        printf("Invalid multiplier n\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // read outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfout = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER biout = bi;
    // update bitmap info
    biout.biHeight = bi.biHeight * n; 
    biout.biWidth = bi.biWidth * n;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingout =  (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update the file size info
    biout.biSizeImage = abs(biout.biHeight) * (sizeof(RGBTRIPLE) * biout.biWidth + paddingout);
    bfout.bfSize = bf.bfOffBits + biout.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfout, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate an array to store each scanline
    RGBTRIPLE scanline[bi.biWidth];
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store RGB triple to the array
            scanline[j] = triple;      
        }
        
        // iterate n times
        for (int iter = 0; iter < n; iter++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // write RGB triple to outfile
                // has to repeat n times, otherwise the data pointer moves beyond the data storage scope 
                for (int l = 0; l < n; l++)
                {
                    fwrite(&scanline[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }    
            // add new padding
            for (int k = 0; k < paddingout; k++)
            {
                fputc(0x00, outptr);
            }    
        }
        // skip over old padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
