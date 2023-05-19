#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int IsPalindrome(char* for_char, int len); // 회문 판별해서 0, 1 반환
int Can_Palindrome(char* for_char, int* Count_Alphabet, int len);       // 알파벳 개수 확인, 회문으로 바꿀 수 있는지 판별해서 0, 1 반환
void Swap(char* a, char* b);
void Generator(char* for_char, int* Count_Alphabet, int len);
void Count_ABC(char* str, int len);
void Print_Mode(char* str, int len);
void ReverseStr(char* str, int len);
void SortStr(char* str, int len);


int main()
{
    char forward_char[100] = {0, };
    int Alphabet[26] = {0, };

    scanf("%s", forward_char);
    Count_ABC(forward_char, strlen(forward_char));
    Print_Mode(forward_char, strlen(forward_char));
    ReverseStr(forward_char, strlen(forward_char));
    SortStr(forward_char, strlen(forward_char));
    Generator(forward_char, Alphabet, strlen(forward_char));

    return 0;
}

int IsPalindrome(char* for_char, int len)
{
    int res = 1;
    for (int i = 0; i < len / 2; i++)
    {
        if (for_char[i] != for_char[len - 1 - i])
            res = 0;
    }
    if (res == 0)
        return 0;
    else
        return 1;
}
int Can_Palindrome(char* for_char, int* Count_Alphabet, int len)
{
    int count = 0;

    for (int i = 0; i < len; i++)        // A~Z(0~25)까지 각각의 개수가 들어감
    {
        Count_Alphabet[for_char[i] - 65]++;
    }

    for (int i = 0; i < 26; i++)       // 알파벳의 개수가 홀수일 때마다 count에 1 더함
    {
        if (Count_Alphabet[i] % 2 == 1)
            count += 1;
    }
    if (count > 1)                 // count가 홀수면 회문생성 불가, 짝수면 가능
        return 0;
    else
        return 1;
}
void Swap(char* a, char* b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void Generator(char* for_char, int* Count_Alphabet, int len)
{
    char odd_char = 0;
    int Swap_Count = 0;

    if (!IsPalindrome(for_char, len))                           // 회문이 아닐때
    {                           
        if (!Can_Palindrome(for_char, Count_Alphabet, len))     // 회문으로 만들 수 없을 때
        {
            printf("Impossible\n");
        }
        else if ((len % 2) == 1)                               // 문자열 길이가 홀수일 때
        {
            for (int i = 0; i < 26; i++)                      // 갯수가 홀수인 알파벳 찾아주기 
            {
                if (Count_Alphabet[i] == 1)
                    odd_char = i + 65;
            }                                                  // ~까지
            if (for_char[len / 2] == odd_char)                 // 가운데 값이 홀수갯수 알파벳이면
                for_char[len / 2] = odd_char;
            else
            {
                for (int i = 0; i < len; i++)                  // 가운데 값이 홀수갯수 알파벳이 아니면
                {
                    if (for_char[i] == odd_char)
                    {
                        Swap(&for_char[len / 2], &for_char[i]);
                        Swap_Count += 1;
                        printf("%s\n", for_char);
                        break;
                    }
                }                    
            }
            for (int i = 1; i <= (len / 2); i++)                  // 가운데 +- 인덱스 값 검사 및 스왑
            {
                if (for_char[(len / 2) - i] == for_char[(len / 2) + i]) // 가운데 +- 인덱스 값이 같을 때
                    for_char[(len / 2) - i] = for_char[(len / 2) + i];
                else                                                    // 가운데 +- 인덱스 값이 다를 때
                {
                    for (int j = 0; j < len; j++)                       // 같은 값을 찾는다
                    {
                        if (j != (len / 2) - i && for_char[j] == for_char[(len / 2) - i]) // 인덱스가 다르고 값은 같은 경우 swap
                        {
                            Swap(&for_char[(len / 2) + i], &for_char[j]);
                            Swap_Count += 1;
                            printf("%s\n", for_char);
                            break;
                        }   
                    }
                }        
            }
            printf("%d\n", Swap_Count);
        }
        else if ((len % 2) == 0)   // 문자열 길이가 짝수일 때
        {
            for (int i = 0; i < (len / 2); i++)
            {
                if (for_char[(len / 2) - 1 - i] == for_char[(len / 2) + i])
                    for_char[(len / 2) - 1 - i] = for_char[(len / 2) + i];
                else
                {
                    for (int j = 0; j < len; j++)
                    {
                        if (j != (len / 2) - 1 - i && for_char[j] == for_char[(len / 2) - 1 - i])
                        {
                            Swap(&for_char[(len / 2) + i], &for_char[j]);
                            Swap_Count += 1;
                            printf("%s\n", for_char);
                            break;
                        }
                    }
                }        
            }
            printf("%d\n", Swap_Count);
        }
    }                           
}

void Count_ABC(char* str, int len)
{
    int Count_ABC[26] = {0, };

    for (int i = 0; i < len; i++)
    {
        Count_ABC[str[i] - 65]++;
    }
    
    printf("A : %d\n", Count_ABC[0]);
    printf("B : %d\n", Count_ABC[1]);
    printf("C : %d\n", Count_ABC[2]);
    printf("D : %d\n", Count_ABC[3]);
    printf("E : %d\n", Count_ABC[4]);
    printf("F : %d\n", Count_ABC[5]);
    printf("G : %d\n", Count_ABC[6]);
    printf("H : %d\n", Count_ABC[7]);
    printf("I : %d\n", Count_ABC[8]);
    printf("J : %d\n", Count_ABC[9]);
    printf("K : %d\n", Count_ABC[10]);
    printf("L : %d\n", Count_ABC[11]);
    printf("M : %d\n", Count_ABC[12]);
    printf("N : %d\n", Count_ABC[13]);
    printf("O : %d\n", Count_ABC[14]);
    printf("P : %d\n", Count_ABC[15]);
    printf("Q : %d\n", Count_ABC[16]);
    printf("R : %d\n", Count_ABC[17]);
    printf("S : %d\n", Count_ABC[18]);
    printf("T : %d\n", Count_ABC[19]);
    printf("U : %d\n", Count_ABC[20]);
    printf("V : %d\n", Count_ABC[21]);
    printf("W : %d\n", Count_ABC[22]);
    printf("X : %d\n", Count_ABC[23]);
    printf("Y : %d\n", Count_ABC[24]);
    printf("Z : %d\n", Count_ABC[25]);
}

void Print_Mode(char* str, int len)
{
    char Mode_Alpha = 0;
    int Count_ABC[26] = {0, };

    for (int i = 0; i < len; i++)
    {
        Count_ABC[str[i] - 65]++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (Count_ABC[i] > Count_ABC[i + 1])
            Mode_Alpha = Count_ABC[i] + 65;
    }
    printf("Mode Alphabet : %c\n", Mode_Alpha);
}

void ReverseStr(char* str, int len)
{
    printf("ReverseStr :");
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

void SortStr(char* str, int len)
{
    char temp_str[100000] = {0, };
    strcpy(temp_str, str);

    int temp;

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < (len - i) - 1; j++)
        {
            if (temp_str[j] > temp_str[j + 1])
            {
                temp = temp_str[j];
                temp_str[j] = temp_str[j + 1];
                temp_str[j + 1] = temp;
            }
        }
    }
    
    printf("SortStr : ");
    for (int i = 0; i < len; i++)
    {
        printf("%c", temp_str[i]);
    }
    
    printf("\n");
}