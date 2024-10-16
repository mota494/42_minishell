#include <stdio.h>

typedef struct s_truct
{
	char	*val;
}		t_truct;

t_truct	*ret_struct(t_truct *tstruct)
{
	static t_truct *test;

	if (tstruct)
		test = tstruct;
	return (test);

}

void	print_test(void)
{
	t_truct *tstruct;

	tstruct = ret_struct(NULL);
	printf("%s", tstruct->val);
}

int	main()
{
	t_truct test;

	test.val = "test";
	ret_struct(&test);
	print_test();
}
