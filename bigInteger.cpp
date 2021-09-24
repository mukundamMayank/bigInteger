#include<iostream>
using namespace std;

string subtarct(string s1, string s2){
	if(s2.length()>s1.length()) {
		string temp=s2;
		s2=s1;
		s1=temp;
	}
	else if (s2.length()==s1.length()){
		for(int i =0;i<s1.length();i++) {
			if(s1[i]<s2[i]){
				string temp = s2;
				s2=s1;
				s1=temp;
				break;
			}
			else if(s1[i]>s2[i])break;
		}
	}
    
	if(s1.length()>s2.length()){
		s2.insert(0,s1.length()-s2.length(),'0');
	}

     
    string ans="";
    int carry =0;
	
	for(int i =s1.length()-1;i>=0;i--) {
	    char temp=s1[i];

	    if(carry == 1){
           	 temp--;
           	 if ((temp-'0')<(s2[i]-'0')) {
           	 	temp+=10;
           	 	carry=1;
           	 }

           	 else carry=0;
           	 
           }
           else {
           	 	if((s1[i]-'0')<(s2[i]-'0')) {
           	 		temp+=10;
           	 		carry =1;
           	 	}
           	 	else carry=0;
           	 }

	    char s=(temp-'0')-(s2[i]-'0')+'0';
	    ans+=s;
	}

	for(int i =0;i<ans.length()/2;i++){
	    char temp = ans[i];
	    ans[i]=ans[ans.length()-1-i];
	    ans[ans.length()-1-i]=temp;
	}

    for(int i =0;i<ans.length();i++){
    	if(ans[i]!='0'){
           break;
    	}

    	if(ans[i]=='0'){
    		ans.erase(ans.begin()+i);
    	}
    }
    
    if(ans.length()==0)ans="0";
	
	return ans;

}

string gcd(string s1, string s2) {
	if(s1 == s2)return s1;
	if(s2.length()>s1.length()) {
		string temp=s2;
		s2=s1;
		s1=temp;
	}
	else if (s2.length()==s1.length()){
		for(int i =0;i<s1.length();i++) {
			if(s1[i]-'0'<s2[i]-'0'){
				string temp = s2;
				s2=s1;
				s1=temp;
				break;
			}
			else if(s1[i]-'0'>s2[i]-'0'){
				break;
			}
		}
	}
	string ans=subtarct(s1,s2);
	if(ans == s2)return ans;
	else return gcd(s2, ans);
	}



string addition(string s1, string s2){
	if(s2.length()>s1.length()) {
		s1.insert(0,s2.length()-s1.length(),'0');
	}
	else if(s1.length()>s2.length()){
		s2.insert(0,s1.length()-s2.length(),'0');
	}

	char carry='0';
	string ans="";

	for(int i =s1.length()-1;i>=0;i--){
		char c=(carry-'0')+(s1[i]-'0')+(s2[i]-'0')+'0';
		if(i!=0) {
			if(c>'9'){
				c-=10;
				carry='1';
			}
			else carry ='0';
		}
		ans+=c;
		if(i==0){
			if(c>'9'){
				c-=10;
				carry='1';
				ans+=carry;
			}
		}
		

	}
	for(int i =0;i<ans.length()/2;i++) {
	    char temp = ans[i];
	    ans[i]=ans[ans.length()-1-i];
	    ans[ans.length()-1-i]=temp;
	}
	
	for(int i =0;i<ans.length();i++){
    	if(ans[i]!='0'){
           break;
    	}

    	if(ans[i]=='0'){
    		ans.erase(ans.begin()+i);
    	}
    }
    
    if(ans.length()==0)ans="0";
	
	return ans;
}

string multiply(string s1, string s2){
	if(s1.length()<s2.length()){
		string temp = s1;
		s1=s2;
		s2=temp;
	}

	string ans ="";
	int k =0;
	for(int i =s2.length()-1;i>=0;i--){
          char carry = '0';
           string temp_ans="";

		for(int j =s1.length()-1;j>=0;j--){
     
			int m= (carry-'0') + ((s1[j]-'0')*(s2[i]-'0'));
            carry=m/10 + '0';
            temp_ans+=(m%10)+'0';
            if(j==0 && carry != '0')temp_ans+=carry;

		}
		for(int p=0;p<temp_ans.length()/2;p++) {
		    char temp=temp_ans[p];
		    temp_ans[p]=temp_ans[temp_ans.length()-1-p];
		    temp_ans[temp_ans.length()-1-p]=temp;
		}
		temp_ans.insert(temp_ans.length(), k, '0');
        ans=addition(ans, temp_ans);
        k++;
	}
	
	for(int i =0;i<ans.length();i++){
    	if(ans[i]!='0'){
           break;
    	}

    	if(ans[i]=='0'){
    		ans.erase(ans.begin()+i);
    	}
    }
    
    if(ans.length()==0)ans="0";
	
	return ans;
}


string exponentiation(string n, string s) {
    int k=0;
    string ans=s;
    while(n!="1"){
       ans=multiply(s,ans);
       n=subtarct(n, "1");
    }
    cout<<ans<<endl;
    return ans;
}

string factorial(string s) {
	string k=s;
	string ans="1";
	while(k!="1") {
		ans=multiply(ans,k);
		k=subtarct(k,"1");
	}
	cout<<ans<<endl;
	return ans;
}


int prec(char oprtr) {
   if(oprtr=='-')return 1;
   else if(oprtr=='+')return 2;
   else if(oprtr == 'x')return 3;
   return 0;
}

void calculator(string s){

	string oprtr="";

	string operands[3000];
	int k = 0;
	int p=0;
	string postfix="";
	string op="";

	for(int i =0;i<s.length();i++){
	   if(s[i]=='-' || s[i]=='+' || s[i]=='x'){
            operands[p++]=op;
            postfix+=op;
            op.erase();
            if(k==0){oprtr+=s[i];}

            else {

            if(prec(oprtr[k-1]) <= prec(s[i])) oprtr+=s[i];
            else if (prec(oprtr[k-1]) > prec(s[i])) {
            	while(prec(oprtr[k-1]) > prec(s[i])) {
            		postfix+=oprtr[k-1];
            		oprtr.erase(oprtr.begin()+k-1);
            		k--;

                   if(k==0)break;
            	}
            	oprtr+=s[i];
            }
        }
            k++;
		}
		else op+=s[i];
		
		if(i == s.length()-1) {
		    operands[p++]=op;
		    postfix+=op;
		    while(oprtr.length()!=0){
		        postfix+=oprtr[k-1];
		        oprtr.erase(oprtr.begin()+k-1);
		        k--;
		    }
		}
	}
	
	int j=0;
	int i =0;
    string calc_value[p];
    int operand_to_be_checked=0;


	while(i<postfix.length()){
		if(postfix[i]!='+' && postfix[i]!='-' && postfix[i]!='x'){
            int n = operands[j].length();
            i=i+n;
            calc_value[operand_to_be_checked++]=operands[j];
            j++;

		}
		else {
           if(postfix[i]=='+'){
           	  calc_value[operand_to_be_checked-2] = addition(calc_value[operand_to_be_checked-1], calc_value[operand_to_be_checked-2]);
           	  operand_to_be_checked--;
           }
           if(postfix[i]=='-'){
           	  calc_value[operand_to_be_checked-2] = subtarct(calc_value[operand_to_be_checked-1], calc_value[operand_to_be_checked-2]);
           	  operand_to_be_checked--;
           }
           if(postfix[i]=='x'){
           	  calc_value[operand_to_be_checked-2] = multiply(calc_value[operand_to_be_checked-1], calc_value[operand_to_be_checked-2]);
           	  operand_to_be_checked--;
           }
           i++;
		}
	}
	cout<<calc_value[0];
}

int main(){
	int operation;
	cin>>operation;

	if(operation == 1){
		string b,e;
		cin>>b>>e;
		exponentiation(b,e);
	}
	if(operation == 2){
		string a,b;
		cin>>a>>b;
		string ans = gcd(a,b);
		cout<<ans<<endl;
    }
    if(operation == 3){
    	string n;
    	cin>>n;
    	factorial(n);
    }
    if(operation==4){
    	string s;
    	cin>>s;
    	calculator(s);
    }
}