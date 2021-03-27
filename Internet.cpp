#include<iostream>
using namespace std;
#include<vector>
//Remember when you define a variable as a class. To access the members within it, you
//just have to use . But if you call a function from another class, you must use ::

class Basic{
private:
    string name;
    string ID;
    string address;
    double time;
    double bandwidth;
    double VAT;
public:
    Basic(){}
    Basic(string name, string ID, string address, double time, double bandwidth, double VAT){
        this->name=name;
        this->ID=ID;
        this->address=address;
        this->time=time;
        this->bandwidth=bandwidth;
        this->VAT=VAT;
    }
    void setName(string name){this->name=name;}
    void setID(string ID){this->ID=ID;}
    void setAddress(string address){this->address=address;}
    void setTime(double time){this->time=time;}
    void setBandwidth(double bandwidth){this->bandwidth=bandwidth;}
    void setVAT(double VAT){this->VAT=VAT;}

    string getName(){return name;}
    string getID(){return ID;}
    string getAddress(){return address;}
    double getTime(){return time;}
    double getBandwidth(){return bandwidth;}
    double getVAT(){return VAT;}
    virtual double computeMobile(){
        return time*1000;
    }
    virtual double computeInternet(){
        return bandwidth*200;
    }
    virtual double computeSum(){
        return Basic::computeMobile()+Basic::computeInternet();
    }
    virtual void displayInfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"ID: "<<ID<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<"Time: "<<time<<endl;
        cout<<"Bandwidth: "<<bandwidth<<endl;
        cout<<"VAT: "<<VAT<<endl;
    }
};

class DataFree: public Basic{
private:
    double freedata;
    double fixedmoney;
public:
    DataFree(){}
    DataFree(string name, string ID, string address,double time, double bandwidth, double VAT, double freedata, double fixedmoney)
    :Basic(name,ID,address,time,bandwidth,VAT){
        this->freedata=freedata;
        this->fixedmoney=fixedmoney;
    }
    double computeInternet(){
        if (DataFree::getBandwidth()<=freedata){return fixedmoney;}
        else{return fixedmoney+Basic::computeInternet();}
    }
    double computeSum(){
        return Basic::computeMobile()+DataFree::computeInternet();
    }
    void displayInfo(){
        Basic::displayInfo();
        cout<<"Free Data: "<<freedata<<endl;
        cout<<"Fixed Money: "<<fixedmoney<<endl;
        cout<<"Sum: "<<DataFree::computeSum()<<endl;
    }
};

class DataFix:public Basic{
public:
    DataFix(string name, string ID, string address,double time, double bandwidth, double VAT)
    :Basic(name,ID,address,time,bandwidth,VAT){}
    double computeMobile(){return Basic::computeMobile()*0.9;}
    double computeInternet(){}
    double computeSum(){
        return DataFix::computeMobile()+1000000;
    }
    void displayInfo(){
        Basic::displayInfo();
        cout<<"Sum: "<<DataFix::computeSum()<<endl;
    }
};

class Family{
private:
    vector<Basic*>list;
public:
    void addEntity(Basic* b){
        list.push_back(b);
    }
    double computeSum(){
        double sum=0;
        for (int i=0; i<list.size(); i++){
            sum+=list[i]->computeSum();
        }
        return sum;
    }
};

int main(){
    Family f;
    Basic s1("Bo Chan","16128","Dinh Hoa", 50, 1000, 100);
    DataFree s2("Mifu","15234","Ho Chi Minh", 40, 500, 100, 700, 20000);
    DataFix s3("Chi Nguyen", "13241","Ha Noi", 45, 1500, 300);
    Basic *m1=&s1;
    Basic *m2=&s2;
    Basic *m3=&s3;
    f.addEntity(m1);
    f.addEntity(m2);
    f.addEntity(m3);
    cout<<f.computeSum()<<endl;
    s1.displayInfo();
    cout<<s1.computeSum()<<endl;
    s2.displayInfo();
    cout<<s2.computeSum()<<endl;
    s3.displayInfo();
    cout<<s3.computeSum()<<endl;
}
