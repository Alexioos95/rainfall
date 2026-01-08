#include <cstring>
#include <cstdlib>
#include <cstdio>

class	N
{
	public:
		char	annotation[100];
		int		value;

		N(int val) : value(val)
			{ }
		void setAnnotation(char *str)
			{ memcpy(annotation, str, strlen(str)); }
		int operator+(N &rhs)
			{ return this->value + rhs.value; }
		int operator-(N &rhs)
			{ return this->value - rhs.value; }
};

int	main(int argc, char **argv)
{
	if (argc < 2)
		exit(1);
	N	*a = new N(5);
	N	*b = new N(6);
	a->setAnnotation(argv[1]);
	(void)(*b + *a);
	return (0);
}
