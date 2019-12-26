#include "html.hpp"

WebPage::WebPage(){
	title = "Interesting Title";
	stylesheet = "NULL";
	print_header();
    set_qs(getenv("QUERY_STRING"));
    //~ set_qs("x=0&y=0&s=0&f=0");
    set_qn(count_qn());
    parse();
}

WebPage::WebPage(string title, string stylesheet){
	this->title = title;
	this->stylesheet = stylesheet;
	print_header();
    set_qs(getenv("QUERY_STRING"));
    set_qn(count_qn());
    parse();
}

void	WebPage::print_header()
{
	cout << "Content-type:text/html\n\n"
    << "<html><head><title>"
    <<title
    <<"</title>";
    if (stylesheet != "NULL")
		cout << "<link rel=\"stylesheet\" type=\"text/css\" href=\""<<stylesheet<<"\">";
    cout <<"</head><body>";
}

int		WebPage::count_qn()
{
	int count = 0;
	int pos = qs.find("=", 0);
	while(pos != string::npos)
	{
		count++;
		pos = qs.find("=", pos+1);
	}
	return count;
}

void	WebPage::parse(){
	list = new Queries[qn];
	int start  = 0;
	int end = -1;
	for(int i = 0; i < qn; i++)
	{
		start = end + 1;
		end = qs.find("=", start);
		list[i].key = qs.substr(start, end-start);
		start = end + 1;
		end = qs.find("&", start);
		if (end == string::npos)
			end = qs.length();
		list[i].value = qs.substr(start, end-start);
		//cout << list[i].toString() << endl;
	}
}

string	WebPage::get_value(string key)
{
	for(int i = 0; i < qn; i++)
		if(key == list[i].key)
			return list[i].value;
	return "";
}

void	WebPage::set_qs(string qs)
{
	this->qs = qs;
}
void	WebPage::set_qn(int qn)
{
	this->qn = qn;
}
string	WebPage::get_qs()
{
	return qs;
}
int		WebPage::get_qn()
{
	return qn;
}
void	WebPage::print_footer()
{
	cout << "</body></html>";
}

