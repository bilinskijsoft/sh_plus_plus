#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

bool checkInput(int argc) {
    if (argc != 2)
    {
        fprintf(stderr,"Usage: ./recover image");
        return false;
    }
    return true;
}

bool checkJpgHeader(unsigned char *block) {
    return (block[0] == 255 && 
            block[1] == 216 && 
            block[2] == 255 && 
            (block[3] == 224 || block[3] == 225));
}

int main(int argc, char* argv[])
{
    unsigned char block[512];
    int name = 0; 
    bool Start = false;
    
    // Check for valid input
    if (!checkInput(argc)) {
        return 1;
    }
    
    // Open input file
    char* infile =argv[1];
    FILE* inptr = fopen(infile, "r");
   

    // Open file for output 
    FILE* outptr;
    
    //Read file till the end
    while(fread(block, 512, 1, inptr) != 0){
        // If found Jpg Header write it into new file
        if (checkJpgHeader(block)) {
            // If we are at start of a new file ,close old file and open new
            if (Start) {
                fclose(outptr); 
            }
            else {
                Start  = true;
            }
                
            // Generate fileName  
            char fileName[4];
            
            if (name < 10) {
                sprintf(fileName, "00%i.jpg", name);
            }
            else {
                sprintf(fileName, "0%i.jpg", name);
            }
            
            // Check for write error
            outptr = fopen(fileName, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", fileName);
                return 3;
            }
      
            name++; //Next name for file
        }
        
        if (Start) {
            fwrite(&block, 512, 1, outptr);
        }

    }
    
    // Close all files
    fclose(outptr);
    fclose(inptr);  
    return 0;
}