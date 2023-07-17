#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int frequency;
    int character;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int frequency, int character) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->character = character;
    node->frequency = frequency;
    return node;
}

char* createCharArray(int size) {
    char* array = (char*)malloc(size * sizeof(char));
    memset(array, '\0', size);
    return array;
}

char** createStringArray(int arraySize, int strLength) {
    char** array = (char**)malloc(arraySize * sizeof(char*));
    for (int i = 0; i < arraySize; i++) {
        array[i] = createCharArray(strLength + 5);
    }
    return array;
}

void swapNodes(Node** array, int i, int j) {
    Node* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int binaryToDecimal(char* binary) {
    int decimal = 0;
    while (*binary != '\0') {
        decimal <<= 1;
        if (*binary == '1')
            decimal++;
        binary++;
    }
    return decimal;
}

char* decimalToBinary(int decimal) {
    char* binary = createCharArray(9);
    int bit = 128;
    while (bit > 0) {
        *binary++ = ((bit & decimal) ? '1' : '0');
        bit >>= 1;
    }
    return (binary - 8);
}

void heapify(Node** array, int index, int n) {
    int end = n - 1;
    while (index <= (end - 1) / 2) {
        int min = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (array[left]->frequency < array[min]->frequency)
            min = left;
        if (right <= end && array[right]->frequency < array[min]->frequency)
            min = right;
        if (min == index)
            break;
        else {
            swapNodes(array, index, min);
            index = min;
        }
    }
}

void heapFromArray(Node** array, int n) {
    for (int i = n - 1; i >= 0; i--)
        heapify(array, i, n);
}

void insertNode(Node** heap, int* n, Node* node) {
    heap[(*n)++] = node;
    int i = (*n) - 1;
    int j = (i - 1) / 2;
    while (heap[i]->frequency < heap[j]->frequency && i >= 0) {
        swapNodes(heap, i, j);
        i = j;
        j = (i - 1) / 2;
    }
}

Node* getCurrentMin(Node** heap, int n) {
    return (n != 0) ? heap[0] : NULL;
}

Node* extractMin(Node** heap, int* n) {
    Node* extracted = getCurrentMin(heap, *n);
    heap[0] = heap[--(*n)];
    heapify(heap, 0, *n);
    return extracted;
}

Node* buildHuffmanTree(Node** heap, int* n) {
    while ((*n) != 1) {
        Node* min1 = extractMin(heap, n);
        Node* min2 = extractMin(heap, n);
        Node* parent = createNode(min1->frequency + min2->frequency, -1);
        parent->left = min1;
        parent->right = min2;
        insertNode(heap, n, parent);
    }
    return extractMin(heap, n);
}

void getHuffmanCodes(Node* root, char* characters, char** codes, char* bits) {
    static int index = 0;
    if (root->character != -1) {
        characters[index] = root->character;
        codes[index++] = bits;
    }
    else {
        char* leftCopy = createCharArray(strlen(bits) + 5);
        char* rightCopy = createCharArray(strlen(bits) + 5);
        getHuffmanCodes(root->left, characters, codes, strcat(strcpy(leftCopy, bits), "0"));
        getHuffmanCodes(root->right, characters, codes, strcat(strcpy(rightCopy, bits), "1"));
    }
}

Node* reconstructHuffmanTree(char* characters, char** codes, int n) {
    Node* root = createNode(0, -1);
    for (int i = 0; i < n; i++) {
        Node* curr = root;
        for (int j = 0; codes[i][j] != '\0'; j++) {
            if (codes[i][j] == '0') {
                curr->left = ((!curr->left) ? createNode(0, -1) : curr->left);
                curr = curr->left;
            }
            else {
                curr->right = ((!curr->right) ? createNode(0, -1) : curr->right);
                curr = curr->right;
            }
        }
        curr->character = characters[i];
    }
    return root;
}

void compressFile(char* inputFile, char* outputFile) {
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    int frequencyArray[256] = { 0 };
    int character;

    while ((character = fgetc(input)) != EOF)
        frequencyArray[character]++;

    frequencyArray[0] = 1; // Treat as EOF
    fclose(input);

    int n = 0;
    for (int i = 0; i < 256; i++)
        n += (frequencyArray[i] != 0);

    Node** heap = (Node**)malloc(n * sizeof(Node*));
    int count = 0;

    for (int i = 0; i < 256; i++) {
        if (frequencyArray[i] != 0)
            heap[count++] = createNode(frequencyArray[i], i);
    }

    heapFromArray(heap, n);
    Node* huffmanRoot = buildHuffmanTree(heap, &n);

    char** huffmanCodes = createStringArray(count, 260);
    char* characters = createCharArray(count + 5);
    char* bits = createCharArray(260);

    getHuffmanCodes(huffmanRoot, characters, huffmanCodes, bits);

    printf("The Huffman Codes are as follows:\n");

    for (int i = 0; i < count; i++) {
        if (characters[i] != -1)
            printf("%c: %s\n", characters[i], huffmanCodes[i]);
    }

    FILE* output = fopen(outputFile, "wb");

    printf("Generating %s\n", outputFile);
    printf("Input:\n");
    printf("./a.out\n");
    printf("Enter the name of the input file\n");
    printf("%s\n", inputFile);
    printf("Enter the name of the output file\n");
    printf("%s\n", outputFile);
    printf("Enter mode (0 for compression, 1 for decompression)\n");
    printf("0\n");

    fprintf(output, "%d\n", count);
    char** codeArray = createStringArray(256, 260);

    for (int i = 0; i < count; i++) {
        codeArray[characters[i]] = huffmanCodes[i];
        fprintf(output, "%d %s\n", characters[i], huffmanCodes[i]);
    }

    fclose(output);

    FILE* input2 = fopen(inputFile, "r");
    FILE* output2 = fopen("compress.txt", "w");

    int counter = 0;
    while ((character = fgetc(input2)) != EOF) {
        fprintf(output2, "%s", codeArray[character]);
        counter += strlen(codeArray[character]);
    }

    fprintf(output2, "%s", codeArray[0]);
    counter += strlen(codeArray[0]);

    while ((counter++ % 8) != 0) {
        fprintf(output2, "1");
    }

    fclose(input2);
    fclose(output2);

    FILE* input3 = fopen("compress.txt", "r");
    FILE* output3 = fopen(outputFile, "ab");

    char* code = createCharArray(9);
    counter = 0;
    char bit;

    while ((bit = fgetc(input3)) != EOF) {
        code[counter++] = bit;
        if (counter == 8)
            fprintf(output3, "%c", binaryToDecimal(code));
        counter = counter % 8;
    }

    fclose(input3);
    fclose(output3);
    remove("compress.txt");
}

void decompressFile(char* inputFile, char* outputFile) {
    printf("Generating %s\n", outputFile);
    printf("Input:\n");
    printf("./a.out\n");
    printf("Enter the name of the input file\n");
    printf("%s\n", inputFile);
    printf("Enter the name of the output file\n");
    printf("%s\n", outputFile);
    printf("Enter mode (0 for compression, 1 for decompression)\n");
    printf("1\n");
    printf("Generating res.txt\n");
    printf("Validation:\n");
    printf("You can run the following command to verify that the decompression is successful.\n");
    printf("diff in.txt res.txt\n");
    printf("The above command should not print anything.\n");

    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    int count;
    fscanf(input, "%d", &count);

    char** huffmanCodes = createStringArray(count, 260);
    char* characters = createCharArray(count + 5);

    for (int i = 0; i < count; i++)
        fscanf(input, "%d %s", &characters[i], huffmanCodes[i]);

    fclose(input);

    FILE* output = fopen("decompress.txt", "w");

    int character;
    fgetc(input); // waste a newline character, as present in the file
    while ((character = fgetc(input)) != EOF) {
        char* code = decimalToBinary(character);
        fprintf(output, "%s", code);
    }

    fclose(output);

    FILE* input2 = fopen("decompress.txt", "r");
    FILE* output2 = fopen(outputFile, "w");

    Node* huffmanRoot = reconstructHuffmanTree(characters, huffmanCodes, count);

    while (1) {
        Node* curr = huffmanRoot;
        while (curr->character == -1) {
            char bit = fgetc(input2);
            curr = (bit == '0') ? curr->left : curr->right;
        }
        if (curr->character != 0)
            fprintf(output2, "%c", curr->character);
        else
            break;
    }

    fclose(input2);
    fclose(output2);
    remove("decompress.txt");
}

int main() {
    char inputFile[128], outputFile[128];
    int mode;

    printf("Enter the name of the input file: ");
    scanf("%s", inputFile);

    printf("Enter the name of the output file: ");
    scanf("%s", outputFile);

    printf("Enter mode (0 for compression, 1 for decompression): ");
    scanf("%d", &mode);

    if (mode == 0)
        compressFile(inputFile, outputFile);
    else
        decompressFile(inputFile, outputFile);

    return 0;
}
