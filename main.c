#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Helper to test one file
static void	test_file(const char *path)
{
	int		fd;
	char	*line;

	printf("=== Testing %s ===\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	int ln = 1; // 行番号カウンタを初期化
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE %d: %s\n", ln, line);
		free(line);
		ln++; // 次の行へ
	}
	close(fd);
	printf("=== End of %s ===\n\n", path);
}

int	main(void)
{
	char		*bad;
	const char	*tests[] = {"tests/empty.txt", "tests/single_with_nl.txt",
			"tests/single_without_nl.txt", "tests/multiple_lines.txt",
			"tests/multiple_no_final_nl.txt", "tests/consecutive_newlines.txt",
			"tests/long_line.txt"};
	int			wfd;
	char		*w;
	int			cfd;
	char		*c;
	int			dfd;
	char		*d;

	// 1) 無効な FD
	printf("=== Testing invalid FD ===\n");
	bad = get_next_line(-1);
	printf("Invalid FD returned: %s\n\n", bad ? bad : "NULL");
	// 2) 標準テストファイル
	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test_file(tests[i]);
	// 3) 書き込み専用 FD
	printf("=== Testing write-only FD ===\n");
	wfd = open("tests/single_with_nl.txt", O_WRONLY);
	if (wfd < 0)
	{
		perror("open write-only");
	}
	else
	{
		w = get_next_line(wfd);
		printf("Write-only FD returned: %s\n", w ? w : "NULL");
		close(wfd);
	}
	printf("\n");
	// 4) クローズ済み FD
	printf("=== Testing closed FD ===\n");
	cfd = open("tests/single_with_nl.txt", O_RDONLY);
	if (cfd < 0)
	{
		perror("open for closed");
	}
	else
	{
		close(cfd);
		c = get_next_line(cfd);
		printf("Closed FD returned: %s\n", c ? c : "NULL");
	}
	printf("\n");
	// 5) ディレクトリ FD
	printf("=== Testing directory FD ===\n");
	dfd = open(".", O_RDONLY);
	if (dfd < 0)
	{
		perror("open directory");
	}
	else
	{
		d = get_next_line(dfd);
		printf("Directory FD returned: %s\n", d ? d : "NULL");
		close(dfd);
	}
	printf("\n");
	return (0);
}
