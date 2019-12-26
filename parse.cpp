#ifndef WEBAPPS_H
#define WEBAPPS_H

#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include "FileApps.h"

using namespace std;

struct FIELDS
{
        string	name;
        string	value;
        string	toString()
        {
			return (name + "=" + value);
		} 
};

class WebApps{
    private:
    int cnt;
    string qs;
    public:
    WebApps();
    void    set_qs(string qs);
    string get_qs();
    void    set_cnt(int cnt);
    int get_cnt();
    void parse(FIELDS *f_name_value_pairs);
    string param(string, FIELDS []);
    int how_many();

};

//*******************************************
//******** Functions begin ******************
//*******************************************
                
//*******************************************
// parse()
// This will separate the name/value pairs found after the ? in
// the URL and populate the name_value_pairs array of structures
//*******************************************
void WebApps::parse (FIELDS *f_name_value_pairs)
{
        string name, value;
        int start_pos = 0, pos;
        for (int counter=0; counter < cnt; counter++) {
                pos = qs.find("=", start_pos);
                name = qs.substr(start_pos, pos - start_pos);
                start_pos = pos + 1;
                pos = qs.find("&", start_pos);
                if (pos == string::npos) {
                        pos = qs.length();
                }
                value = qs.substr(start_pos, pos - start_pos);
                start_pos = pos + 1;
                f_name_value_pairs[counter].name = name;
                f_name_value_pairs[counter].value = value;
        }
}               

//*******************************************
// param()
// This will find the field value based on the
// field name
//*******************************************

string WebApps::param(string lookUp, FIELDS f_name_value_pairs[])
{
        for(int i = 0; i < cnt; i++)
        {
                if(f_name_value_pairs[i].name == lookUp)
                        return f_name_value_pairs[i].value;
        }
        return "";
}
     
WebApps::WebApps()
{
    cout << "Content-type:text/html\n\n"
    << "<html><head><title>Survey Vote</title></head>";
    set_qs(getenv("QUERY_STRING"));
    //cout << "debug with get_qs: " << get_qs();
    set_cnt(how_many());
}
void    WebApps::set_qs(string qs)
{
    this->qs = qs;
}
string  WebApps::get_qs()
{
    return qs;
}
void    WebApps::set_cnt(int cnt)
{
    this->cnt = cnt;
}
int     WebApps::get_cnt()
{
    return cnt;
}
int     WebApps::how_many(){
    int feilds = 0;
    int pos = -1;
    while(qs.find("=", pos+1) != string::npos)
    {
		feilds++;
		pos = qs.find("=", pos+1);
	}
    return feilds;
}

#endif
