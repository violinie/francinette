
#include "utils.h"

int single_test_putnbr(int n, int fd)
{
	set_sign("ft_putnbr_fd(%i, fd: %i)", n, fd);

	ft_putnbr_fd(n, fd);
	ft_putendl_fd("", fd);
	return check_leaks(NULL);
}

int test_putnbr_fd()
{
	int fd = open("fsoares", O_RDWR | O_CREAT);

	int res = single_test_putnbr(0, fd);
	res = single_test_putnbr(10000043, fd) && res;
	res = single_test_putnbr(-10000043, fd) && res;
	res = single_test_putnbr(INT_MAX, fd) && res;
	res = single_test_putnbr(INT_MIN, fd) && res;

	lseek(fd, SEEK_SET, 0);
	char content[100] = {0};
	read(fd, content, 100);

	char expected[1000];
	sprintf(expected, "0\n10000043\n-10000043\n%i\n%i\n", INT_MAX, INT_MIN);
	if(strcmp(content, expected) != 0)
		res = error("expected: %s, content of the file: %s\n", escape_str(expected), escape_str(content)) && res;

	set_sign("ft_putnbr_fd(%i, fd: %i)", 10000, fd);
	null_null_check(ft_putnbr_fd(10000, fd), res);

	remove("./fsoares");
	return res;
}

int	main()
{
	handle_signals();
	test(putnbr_fd);
}
