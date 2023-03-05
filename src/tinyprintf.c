#include "tinyprintf.h"

#include <stdio.h>
#include <stdlib.h>

int calculate_len(char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int printao(char *s)
{
    if (s == NULL)
    {
        printao("(null)");
        return 6;
    }

    int i = 0;
    while (s[i] != '\0')
    {
        putchar(s[i]);
        i++;
    }
    return 0;
}

void str_revert(char str[])
{
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++)
        len++;

    for (int j = 0; j < len / 2; j++)
    {
        char c = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = c;
    }
}

char *my_itoa_base(long n, char *s, const char *base)
{
    long p = 1;
    long b = 0;

    while (base[b] != '\0')
        b++;

    if (n == 0)
    {
        s[0] = base[0];
        s[1] = '\0';
        return s;
    }

    else
    {
        long i = 0;

        if (n < 0)
        {
            *s = '-';
            s++;
            p = 0;
            n = -n;
        }

        while (n != 0)
        {
            s[i] = base[n % b];
            i++;
            n /= b;
        }

        s[i] = '\0';
        str_revert(s);
    }

    if (p == 0)
    {
        s--;
        return s;
    }

    return s;
}

int _tiny(int nb, char c, va_list ap)
{
    char *s = malloc(sizeof(char) * 15);
    char *str;
    int x;
    unsigned int u;
    if (c == 'd')
    {
        x = va_arg(ap, long);
        s = my_itoa_base(x, s, "0123456789");
        nb += calculate_len(s);
        printao(s);
    }
    else if (c == 'u')
    {
        u = va_arg(ap, long);
        s = my_itoa_base(u, s, "0123456789");
        nb += calculate_len(s);
        printao(s);
    }
    else if (c == 'o')
    {
        x = va_arg(ap, long);
        s = my_itoa_base(x, s, "01234567");
        nb += calculate_len(s);
        printao(s);
    }
    else if (c == 'x')
    {
        x = va_arg(ap, long);
        s = my_itoa_base(x, s, "0123456789abcdef");
        nb += calculate_len(s);
        printao(s);
    }
    else if (c == 'c')
    {
        putchar(va_arg(ap, int));
        nb++;
    }
    else if (c == 's')
    {
        str = va_arg(ap, char *);
        nb += calculate_len(str);
        printao(str);
    }
    else
    {
        putchar('%');
        putchar(c);
        nb += 2;
    }
    free(s);
    return nb;
}

int tinyprintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int nb_c = 0;
    int percent = 0;

    for (int i = 0; format[i] != '\0'; i++)
    {
        char c = format[i];

        if (c != '%')
        {
            if (percent == 0)
            {
                putchar(c);
                nb_c++;
            }
            else
            {
                nb_c = _tiny(nb_c, c, ap);
                percent = 0;
            }
        }

        else
        {
            if (percent == 0)
                percent = 1;
            else
            {
                putchar('%');
                nb_c++;
                percent = 0;
            }
        }
    }

    va_end(ap);
    return nb_c;
}

int main()
{
    // Declare your variables here
    // After that, you can use the tinyprintf below like a classic printf

    char *str = "world!"; //EXAMPLE
    tinyprintf("Hello %s\n", str);
    
    return 0;
}
