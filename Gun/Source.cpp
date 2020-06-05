#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct gun_pos
{
	double x, angle;
};

struct gun_command
{
	virtual ~gun_command() {};
	virtual void exec(double& x_gun, double& angle_gun) =0;
};

struct  move : public gun_command
{
	double x;
	move(double x) : x(x) {};
	virtual void exec(double& x_gun, double& angle_gun)
	{
		std::cout << "Move " << x << std::endl;
		x_gun += x;
	}
};

struct look_at : public gun_command
{
	double a;
	look_at(double a) : a(a) {};
	virtual void exec(double& x_gun, double& angle_gun)
	{
		std::cout << "Look at " << a<< std::endl;
		angle_gun += a;
	}
};

int main()
{
	std::cout << "Start!" << std::endl;

	std::ifstream file("E:\\1.Юля_учеба\\c++\\2sem\\Gun\\pushka.txt");
	std::vector<gun_command*> vec;
	std::string comand;
	double value;

	while (file >> comand >> value)
	{
		if (comand == "Move")
		{
			vec.push_back(new move(value));
		}
		if (comand == "Look_at")
		{
			vec.push_back(new look_at(value));
		}
	}

	double x0,angle0;

	std::cout << "Input start value of Position and Angle: ";

	std::cin >> x0 >> angle0;
	std::cout << std::endl;

	gun_pos pushka;

	pushka.x = x0; 
	pushka.angle = angle0;

	std::cout << "Position = " << pushka.x << " Angle = " << pushka.angle << std::endl;

	for (auto it : vec)
	{
		it->exec(pushka.x, pushka.angle);
		std::cout << "x = " << pushka.x << " angle = " << pushka.angle << std::endl;
	}
}