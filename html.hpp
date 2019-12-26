#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

struct Queries
{
	string	key;
	string	value;
	string	toString(){	return key + "=" + value;}
};

class WebPage{
	private:
		string	title;
		string	stylesheet;
		int		qn;
		string	qs;
		Queries* list;
	public: 
		WebPage();	//done
		WebPage(string title, string stylesheet);	//done
		void	set_qs(string qs);	//done
		string	get_qs();	//done
		void	set_qn(int qn);	//done
		int		get_qn();	//done
		void	parse();	//done
		string	get_value(string key);	//done
		int		count_qn();	//done
		void	print_header();	//done
		void	print_footer();	//done
};

#endif
