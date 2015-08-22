/*
hold screen for accepting arrow keys
http://ift.tt/1IXOBrX
for using arrow keys, first it has to be stored for analyzing it. 
* That's why I am using scanf to store it. 
* But when I try to run this code, and when I press up key, 
* then it is showing ^[[A and when I press enter then this ^[[A removes
* and program exit without printing printf statement of printf("%s",c).
* and printf("UP\n").
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    char c[50];
    // scanf ("%s", c);
    // printf ("%s",c);
    char ch;
    if ((ch = getchar ()) == '\033')
    { // if the first value is esc
        printf ("CHAR, ");
        ch = getchar ();// skip the [
        if (ch == '[')
            printf ("[, ");
        
        ch = getchar (); // third char is A or B.
        printf ("%c, \n", ch);
        switch (ch) 
        { // the real value
            case 'A':
                printf("UP\n");
                break;
            case 'B':
                printf("DOWN\n");
                break;
        }
        // getchar () fourth char is \n.
    }
return 0;
}

