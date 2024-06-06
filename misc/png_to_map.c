#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void convertXPMToCUB(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("🚨 Error: Could not open the input file '%s'!\n", inputFileName);
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("🚨 Error: Could not open the output file '%s'!\n", outputFileName);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int readImage = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        if (strstr(line, "/* pixels */")) {
            readImage = 1;
            continue;
        }

        if (readImage) {
            if (line[0] == '"') {
                for (int i = 1; i < strlen(line) - 2; i++) {
                    char pixel = line[i];
                    switch (pixel) {
                        case ' ':
                            fputc('1', outputFile); // Space represents black
                            break;
                        case '.':
                            fputc('0', outputFile); // Dot represents white
                            break;
                        default:
                            fputc(' ', outputFile); // Any other character
                            break;
                    }
                }
                fputc('\n', outputFile);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("✅ Conversion complete! Check your output file: '%s'\n", outputFileName);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("🤔 Usage: %s <input xpm file> <output cub file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    printf("🔄 Converting XPM file '%s' to CUB file '%s'...\n", inputFileName, outputFileName);
    convertXPMToCUB(inputFileName, outputFileName);

    return 0;
}
