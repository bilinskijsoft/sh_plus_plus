#include <stdio.h>
#include <stdlib.h>
 
#include "bmp.h"

bool checkFormat(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi) {
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0) {
        return false;
    }
    return true;
}

bool checkParameters(int argc) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./resize scale infile outfile\n");
        return false;
    }   
    return true;
}

 
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (checkParameters(argc))
    {
        return 1;
    }
    
    
    // remember filenames and scale
    float scale = atof(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
 
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
 
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
 
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
 
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
 
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (!checkFormat(bf, bi)) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
 
    // determine padding for scanlines (for the image we are reading from)
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // temporary image
    RGBTRIPLE image[bi.biWidth][abs(bi.biHeight)];
    
  
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            image[j][i] = triple;
        }
        // poisk v file
        fseek(inptr, padding, SEEK_CUR);
    }
    
    //Change size of image in header
    bi.biWidth = bi.biWidth * mashtab;
    bi.biHeight =bi.biHeight* mashtab;
    // recalculate the padding (for the sclaed image we are writing)
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = bi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
 
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // writing to the scaled image's out file
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            triple = image[(int) (j / mashtab)][(int) (i / mashtab)];
            // write the pixel to the file
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
        }
        
        // write яzero bytes
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    // close infile
    fclose(inptr);
 
    // close outfile
    fclose(outptr);

    return 0;
}