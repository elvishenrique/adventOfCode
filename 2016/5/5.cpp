#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

unsigned char* md5(char* input, int len)
{
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_md5();
    unsigned char* md_value = (unsigned char*) malloc(EVP_MAX_MD_SIZE * sizeof(unsigned char));
    unsigned int md_len;

    EVP_DigestInit_ex(context, md, NULL);
    EVP_DigestUpdate(context, input, len);
    EVP_DigestFinal_ex(context, md_value, &md_len);
    EVP_MD_CTX_free(context);

    return md_value;
}

int main()
{
    char doorId[11];
    scanf("%s", doorId);
    char part1[9] = "________", part2[9] = "________";
    int c = 0, d = 0, index = 0;
    system("clear");
    printf("part1: %s\npart2: %s\n", part1, part2);

    while (d < 8)
    {
        string number = to_string(index);
        int n = strlen(doorId) + number.size();
        char* input = (char*) malloc(n * sizeof(char));
        input[0] = 0;
        strcat(input, doorId);
        strcat(input, number.c_str());

        unsigned char* hash = md5(input, n);
        if (hash[0] == 0 && hash[1] == 0 && hash[2] < 16)
        {
            char hex[3] = "";
            unsigned int value = hash[2];
            if (c < 8)
            {
                sprintf(hex, "%x", value);
                part1[c] = hex[0];
                c++;
            }

            if (value < 8 && part2[value] == '_')
            {
                unsigned int value2 = hash[3] / 16;
                sprintf(hex, "%x", value2);
                system("clear");
                printf("part1: %s\npart2: %s\n", part1, part2);
                part2[value] = hex[0];
                d++;
            }
            else if (c < 8)
            {
                system("clear");
                printf("part1: %s\npart2: %s\n", part1, part2);
            }
        }

        index++;
    }

    system("clear");
    printf("part1: %s\npart2: %s\n", part1, part2);
}