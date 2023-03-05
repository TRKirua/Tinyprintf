#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../src/tinyprintf.c"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(tinyprintf, simple, .init = redirect_all_stdout)
{
    tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello [42] world!");
}

Test(tinyprintf, hexadecimal, .init = redirect_all_stdout)
{
    tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello [2a] world!");
}

Test(tinyprintf, percent, .init = redirect_all_stdout)
{
    tinyprintf("%%s", "in your head");
    fflush(stdout);
    cr_assert_stdout_eq_str("%s");
}

Test(tinyprintf, unknown, .init = redirect_all_stdout)
{
    tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    fflush(stdout);
    cr_assert_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
}

Test(tinyprintf, tricky, .init = redirect_all_stdout)
{
    tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", '*');
    fflush(stdout);
    cr_assert_stdout_eq_str("42 is the answer... 42 too.");
}

Test(tinyprintf, t1, .init = redirect_all_stdout)
{
    tinyprintf(" %x ::", -506);
    fflush(stdout);
    cr_assert_stdout_eq_str(" -1fa ::");
}

Test(tinyprintf, t2, .init = redirect_all_stdout)
{
    tinyprintf(" %o", 154);
    fflush(stdout);
    cr_assert_stdout_eq_str(" 232");
}

Test(tinyprintf, t3, .init = redirect_all_stdout)
{
    tinyprintf("abc012  ! %s %c %d %x", "Moi", 'e', 100, 15);
    fflush(stdout);
    cr_assert_stdout_eq_str("abc012  ! Moi e 100 f");
}
