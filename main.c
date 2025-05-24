#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	test_file(const char *path)
{
	int		fd;
	char	*line;
	size_t	ln;

	ln = 1;
	printf("=== Testing %s ===\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE %zu: %s\n", ln++, line);
		free(line);
	}
	close(fd);
	printf("=== End of %s ===\n\n", path);
}

static void	test_gnl_on_fd(const char *label, int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf("%s: %s\n", label, line ? line : "NULL");
	free(line);
}

int	main(void)
{
	const char	*tests[] = {"tests/empty.txt", "tests/single_with_nl.txt",
			"tests/single_without_nl.txt", "tests/multiple_lines.txt",
			"tests/multiple_no_final_nl.txt", "tests/consecutive_newlines.txt",
			"tests/long_line.txt"};
	int			fd;
	size_t		i;

	printf("=== Testing invalid FD ===\n");
	test_gnl_on_fd("Invalid FD returned", -1);
	printf("\n");
	for (i = 0; i < sizeof tests / sizeof tests[0]; ++i)
		test_file(tests[i]);
	printf("=== Testing write-only FD ===\n");
	fd = open(tests[1], O_WRONLY);
	if (fd < 0)
		perror("open write-only");
	else
	{
		test_gnl_on_fd("Write-only FD returned", fd);
		close(fd);
	}
	printf("\n");
	printf("=== Testing closed FD ===\n");
	fd = open(tests[1], O_RDONLY);
	if (fd < 0)
		perror("open for closed");
	else
	{
		close(fd);
		test_gnl_on_fd("Closed FD returned", fd);
	}
	printf("\n");
	printf("=== Testing directory FD ===\n");
	fd = open(".", O_RDONLY);
	if (fd < 0)
		perror("open directory");
	else
	{
		test_gnl_on_fd("Directory FD returned", fd);
		close(fd);
	}
	return (0);
}
