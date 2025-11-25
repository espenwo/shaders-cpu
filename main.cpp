#include <stdio.h>

int main()
{
    const char* output_path = "output.ppm";
    FILE *f = fopen(output_path, "wb");
    
    int width = 16 * 60;
    int height = 9 * 60;
    
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", width, height);
    fprintf(f, "255\n"); // max bit depth

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            fputc(0xFF, f); // full red
            fputc(0x00, f); // no green for now
            fputc(0x00, f); // no blue for now
        }
    }

    fclose(f); // close file
    printf("Generated %s\n", output_path);

    return 0;
}
