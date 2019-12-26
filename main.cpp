#include <iostream>
#include <fstream>
#include "rover.hpp"
#include "html.hpp"
using namespace std;

void	print_form(Rover* r, string filename = "map.txt");
void	print_stats(Rover *r);
int main()
{
	WebPage wp("Rover", "http://localhost:8080/home/Tutoring/Rover/style.css");
	/**
	 ** parse environment string
	 ** get file name from environment
	 **	make rover object and 
	 ** set its variables using query string
	 **/
	Rover	rover(	std::stoi(wp.get_value("x"))	, 
					std::stoi(wp.get_value("y"))	, 
					std::stoi(wp.get_value("s"))	, 
					std::stoi(wp.get_value("f"))	);
	string filename =  "map.txt";
	Grid map(filename);
	map.drawGrid(&rover);
	if(rover.x == 0 and rover.y == 0)
		rover.move(map.get_block_pointer(0,0));
	if(rover.x != map.get_size()-1 and rover.y != map.get_size()-1)
		rover.move(map.find_route(rover.x, rover.y, rover.fuel, rover.sample));
	print_form(&rover);
	print_stats(&rover);
	wp.print_footer();
	map.updateMap(filename);
}

void	print_form(Rover *r, string filename)
{
	cout << "<form action=\"http://localhost:8080/cgi-bin/rover.cgi\" method=\"GET\">"
	<<	"<input type=\"hidden\" name=\"x\" value="<<r->x<<">"
	<<	"<input type=\"hidden\" name=\"y\" value="<<r->y<<">"
	<<	"<input type=\"hidden\" name=\"s\" value="<<r->sample<<">"
	<<	"<input type=\"hidden\" name=\"f\" value="<<r->fuel<<">"
	<<	"<input type=\"hidden\" name=\"fname\" value="<<filename<<">"
	<<	"<button autofocus class=\"next-button\" type=\"submit\" value=\"next\"></button></form>";
}

void	print_stats(Rover *r)
{
	cout <<	"<div class=\"stats-div\">"
	<<	"<table>"
	<<	"<tbody>"
	<<	"<tr><td>Fuel</td><td>Samples</td></tr>"
	<<	"<tr><td>"<<r->fuel<<"</td><td>"<<r->sample<<"</td></tr>"
	<<	"</table>"
	<<	"</div>";
}
