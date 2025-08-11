#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];
    printf("Enter a string: ");
    fgets(str,sizeof(str),stdin);
    size_t len=strlen(str);
    if(len>0&&str[len-1]=='\n') 
    {
        str[len-1]='\0';
        len--;
    }
    for(int i=0;i<len/2;i++) 
    {
        char temp=str[i];
        str[i]=str[len-1-i];
        str[len-1-i]=temp;
    }
    printf("Reversed string: %s\n",str);
    return 0;
}
