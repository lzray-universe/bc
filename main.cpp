#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cctype>
#include<algorithm>
#include<array>

struct N{
	std::string g;
	std::array<int,14>c;
};

std::vector<N>n;

std::string t(const std::string&s){
	size_t a=0;
	while(a<s.size()&&std::isspace((unsigned char)s[a]))a++;
	size_t e=s.size();
	while(e>a&&std::isspace((unsigned char)s[e-1]))e--;
	return s.substr(a,e-a);
}

std::string d;
size_t p=0;
bool r=false;

int x(){
	while(p<d.size()&&std::isspace((unsigned char)d[p])){
		p++;
	}
	if(p>=d.size()||d[p]!='('){
		r=true;
		return-1;
	}
	p++;
	while(p<d.size()&&std::isspace((unsigned char)d[p])){
		p++;
	}
	std::string h;
	for(int i=0;i<4;++i){
		if(p<d.size()&&std::isdigit((unsigned char)d[p])){
			h.push_back(d[p++]);
		}else{
			r=true;
			return-1;
		}
	}
	if(h.size()!=4){
		r=true;
		return-1;
	}
	int j=n.size();
	n.push_back(N());
	n[j].g=h;
	n[j].c.fill(-1);
	
	for(int i=0;i<14;++i){
		while(p<d.size()&&std::isspace((unsigned char)d[p])){
			p++;
		}
		if(p>=d.size()){
			r=true;
			return j;
		}
		if(d[p]==')'){
			r=true;
			return j;
		}
		if(d[p]=='('){
			int k=x();
			if(r)return j;
			n[j].c[i]=k;
		}else if(std::isalpha((unsigned char)d[p])){
			std::string l;
			while(p<d.size()&&std::isalpha((unsigned char)d[p])){
				l.push_back(d[p++]);
			}
			if(l!="nil"){
				r=true;
				return j;
			}
		}else if(std::isdigit((unsigned char)d[p])){
			std::string m;
			for(int o=0;o<4;++o){
				if(p<d.size()&&std::isdigit((unsigned char)d[p])){
					m.push_back(d[p++]);
				}else{
					r=true;
					return j;
				}
			}
			if(m.size()!=4){
				r=true;
				return j;
			}
			if(i==0&&m==h){
				n[j].c[0]=-1;
			}else{
				int q=n.size();
				n.push_back(N());
				n[q].g=m;
				n[q].c.fill(-1);
				n[j].c[i]=q;
			}
		}else{
			r=true;
			return j;
		}
	}
	while(p<d.size()&&std::isspace((unsigned char)d[p])){
		p++;
	}
	if(p>=d.size()||d[p]!=')'){
		r=true;
		return j;
	}
	p++;
	return j;
}

int main(){
	std::ifstream f("answer.all");
	if(!f){
		std::cerr<<"answer.all not found."<<std::endl;
		return 0;
	}
	std::string s;
	std::string u;
	bool v=false;
	while(std::getline(f,s)){
		std::string w=t(s);
		if(!v){
			if(w.size()==4&&std::all_of(w.begin(),w.end(),::isdigit)){
				u=w;
				v=true;
			}
			continue;
		}
		if(w.empty()){
			continue;
		}
		bool y=false;
		if(w!="nil"){
			for(char z:w){
				if(std::isalpha((unsigned char)z)){
					y=true;
					break;
				}
			}
		}
		if(y){
			continue;
		}
		d+=w;
		d.push_back('\n');
	}
	f.close();
	if(!v){
		std::cerr<<"Invalid format: initial guess not found in answer.all."<<std::endl;
		return 0;
	}
	int b=n.size();
	n.push_back(N());
	n[b].g=u;
	n[b].c.fill(-1);
	p=0;
	for(int i=1;i<=13;++i){
		while(p<d.size()&&std::isspace((unsigned char)d[p])){
			p++;
		}
		if(p>=d.size()){
			break;
		}
		if(d[p]=='('){
			int k=x();
			if(r)break;
			n[b].c[i]=k;
		}else if(d.compare(p,3,"nil")==0){
			n[b].c[i]=-1;
			p+=3;
		}else{
			std::string l;
			while(p<d.size()&&!std::isspace((unsigned char)d[p])){
				l.push_back(d[p++]);
			}
			if(l.size()==4&&std::all_of(l.begin(),l.end(),::isdigit)){
				int q=n.size();
				n.push_back(N());
				n[q].g=l;
				n[q].c.fill(-1);
				n[b].c[i]=q;
			}else{
				r=true;
				break;
			}
		}
	}
	if(r){
		std::cerr<<"Error: Failed to parse decision tree from answer.all."<<std::endl;
		return 0;
	}
	
	if(n.empty()){
		return 0;
	}
	std::cout<<n[b].g<<std::endl;
	int m=b;
	std::string fb;
	while(true){
		if(!std::getline(std::cin,fb)){
			break;
		}
		std::string fb2;
		for(char c:fb){
			if(!std::isspace((unsigned char)c)){
				fb2.push_back(std::toupper(c));
			}
		}
		if(fb2.empty()){
			continue;
		}
		size_t posA=fb2.find('A');
		size_t posB=fb2.find('B');
		if(posA==std::string::npos||posB==std::string::npos||posB<posA){
			std::cout<<"Invalid feedback format. Please enter in format XAYB (e.g. 1A2B)."<<std::endl;
			continue;
		}
		int A,B;
		try{
			A=std::stoi(fb2.substr(0,posA));
			B=std::stoi(fb2.substr(posA+1,posB-posA-1));
		}catch(...){
			std::cout<<"Invalid feedback format. Use digits for A and B values."<<std::endl;
			continue;
		}
		if(A<0||A>4||B<0||B>4||A+B>4){
			std::cout<<"Impossible feedback. Please try again."<<std::endl;
			continue;
		}
		if(A==4){
			std::cout<<"Correct! The answer is "<<n[m].g<<"."<<std::endl;
			break;
		}
		int fi=-1;
		if(A==3&&B==0)fi=4;
		else if(A==2&&B==2)fi=1;
		else if(A==2&&B==1)fi=5;
		else if(A==2&&B==0)fi=6;
		else if(A==1&&B==3)fi=2;
		else if(A==1&&B==2)fi=7;
		else if(A==1&&B==1)fi=11;
		else if(A==1&&B==0)fi=10;
		else if(A==0&&B==4)fi=3;
		else if(A==0&&B==3)fi=8;
		else if(A==0&&B==2)fi=12;
		else if(A==0&&B==1)fi=13;
		else if(A==0&&B==0)fi=9;
		else{
			std::cout<<"Impossible feedback. Please try again."<<std::endl;
			continue;
		}
		if(fi<0||fi>=14){
			std::cout<<"Error: feedback index out of range."<<std::endl;
			break;
		}
		int nn=n[m].c[fi];
		if(nn==-1){
			std::cout<<"Error: no decision for feedback "<<A<<"A"<<B<<"B."<<std::endl;
			break;
		}
		m=nn;
		std::cout<<n[m].g<<std::endl;
	}
	return 0;
}
