#include <iostream>
#include <algorithm>
#include <xtgmath.h>

struct vec2
{
	double x;
	double y;
};

int main() {
	vec2 v;
	double pi = 3.14159;
	double r;
	double t;
	double circ;
	for (r = 15; r < 22;) 
	{  
		circ = (2*pi)*r;
		for (t = 0; t <= 360;) 
		{
			double rad = t * (pi / 180);
			v.x = (r * cos(rad));
			v.y = (r * sin(rad));
			
			std::cout << "circ " << circ << " - degree: " << t ;
			std::cout << " :: x,y: " << v.x << " " << v.y << std::endl;
			
			t += 30;
		}
		std::cout << std::endl;
		r += 3; // increase radius
	}
	return 0;
}