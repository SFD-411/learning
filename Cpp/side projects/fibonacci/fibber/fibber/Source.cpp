#include <iostream>

int F(int n) {
	if (n == 0) { return 0; }
	if (n == 1) { return 1; }
	else { return F(n - 1) + F(n - 2); }
}

int main()
{
int i = 1;
int j = i;
for (int longtime = 1; longtime < 39; longtime++)
{
	int k = i;
	i = j;
	std::cout << j << "\t";
	j = i + k;

	if (longtime % 10 == 0)
		std::cout << std::endl;
}
std::cout << "\n\n newline" << std::endl;
while (j > 0)
{
	i = F(j);
	std::cout << i << " ";
	j = i;

}

return 0;
}
