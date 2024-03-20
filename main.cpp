#include <iostream>
#include<vector>
#include <cstdint>

using namespace std;

class Policy {
protected:
    bool isChecked;
public:
    virtual void check(const string &parola) = 0;

    bool getCheck() const {
        return isChecked;
    }
    virtual string test()=0;
};

class LengthPolicy : public Policy {
private:
    uint16_t minLength, maxLength;
public:
    LengthPolicy(uint16_t min) {
        minLength = min;
        maxLength = 255;
    }

    LengthPolicy(uint16_t min, uint16_t max) {
        minLength = min;
        maxLength = max;
    }

    void check(const string &parola) override {
        if (parola.size() >= minLength && parola.size() <= maxLength) {
            isChecked = true;
        } else isChecked = false;
    }
    string test(){return "length";}
};

class ClassPolicy : public Policy {
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t ClassCount) {
        minClassCount = ClassCount;
    }
    string test(){return "class";}
    void check(const string &parola) override {
        int litera_mare = 0, litera_mica = 0, cifre = 0, alte_caractere = 0;
        for (int i = 0; i < parola.size(); i++) {
            if (isupper(parola[i]))
                litera_mare = 1;
            else if (islower(parola[i]))
                litera_mica = 1;
            else if (isdigit(parola[i]))
                cifre = 1;
            else alte_caractere = 1;
        }
        int nr_clase = 0;
        if (litera_mare == 1) nr_clase++;
        if (litera_mica == 1) nr_clase++;
        if (cifre == 1) nr_clase++;
        if (alte_caractere == 1) nr_clase++;
        if (nr_clase >= minClassCount)
            isChecked = true;
        else isChecked = false;
    }
};

class IncludePolicy : public Policy {
private:
    char characterType;
public:
    IncludePolicy(char c) {
        characterType = c;
    }
    string test(){return "include";}
    void check(const string &parola) override {
        int ok = 0;
        if (characterType == 'a') {
            for (int i = 0; i < parola.size(); i++) {
                if (islower(parola[i])) {
                  //  cout<<parola<<" true\n";
                    isChecked=true;
                    return;
                }
            }
        } else if (characterType == 'A') {
            for (int i = 0; i < parola.size(); i++) {
                if (isupper(parola[i])) {
                    isChecked=true;
                    return;
                }
            }
        } else if (characterType == '0') {
            for (int i = 0; i < parola.size(); i++) {
                if (isdigit(parola[i])) {
                    isChecked=true;
                    return;
                }
            }
        } else if (characterType == '$') {
            for (int i = 0; i < parola.size(); i++) {
                if (!isalnum(parola[i])) {


                    isChecked=true;
                    return;
                }
            }
        }
        isChecked=false;

    }
};


class NotIncludePolicy : public Policy {
private:
    char characterType;
public:
    NotIncludePolicy(char c) {
        characterType = c;
    }
    string test(){return "notinclude";}
    void check(const string &parola) override {
        int ok = 0;
        if (characterType == 'a') {
            for (int i = 0; i < parola.size(); i++) {
                if (islower(parola[i])) {
                    isChecked=false;
                    return;
                }
            }
        } else if (characterType == 'A') {
            for (int i = 0; i < parola.size(); i++) {
                if (isupper(parola[i])) {
                    isChecked=false;
                    return;
                }
            }
        } else if (characterType == '0') {
            for (int i = 0; i < parola.size(); i++) {
                if (isdigit(parola[i])) {
                    isChecked=false;
                    return;
                }
            }
        } else if (characterType == '$') {
            for (int i = 0; i < parola.size(); i++) {
                if (!isalnum(parola[i])) {
                    isChecked=false;
                    return;
                }
            }
        }
        isChecked=true;
    }
};

class RepetitionPolicy : public Policy {
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t Count) {
        maxCount = Count;
    }
    string test(){return "repetition";}

        void check(const string &parola) override {

        int i = 1, nr_repetari = 1, ok = 0;
        while (i < parola.size()) {
            if (parola[i] == parola[i-1]) {
                nr_repetari++;
                i++;
            } else {
                if (nr_repetari > maxCount) {
                    ok = 1;
                    break;
                } else {
                    nr_repetari=1;
                    i++;
                }
            }
        }
        if (ok == 0) isChecked = true;
        else isChecked = false;
    }

};

class ConsecutivePolicy : public Policy {
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t Count) {
        maxCount = Count;
    }
    string test(){return "consecutive";}
    void check(const string &parola) override {
        int i = 0, nr_consecutive = 1, ok = 0;
        while (i < parola.size()-1) {
            if (parola[i] == parola[i + 1] - 1) {
                nr_consecutive++;
                i++;
            } else {
                if (nr_consecutive > maxCount) {
                    ok = 1;
                    break;
                } else {
                    nr_consecutive=1;
                    i++;
                }
            }
        }
        if (ok == 0) isChecked = true;
        else isChecked = false;
    }

};

string checkPassword(string parola, vector<Policy *> cerinte) {
    for (int i = 0; i < cerinte.size(); i++) {
        cerinte[i]->check(parola);
        if (cerinte[i]->getCheck() == false) {
            //cout<<parola<<" false ->"<<cerinte[i]->test()<<endl;
            return "NOK";
        }
        /*else
            cout<<parola<<" true ->"<<cerinte[i]->test()<<endl;*/
    }
    return "OK";
}

int main() {

    int n;
    cin >> n;
    string regula;
    uint16_t minl,maxl;
    uint16_t minClassCount;
    char characterTypeINCLUDE;
    char characterTypeNOINCLUDE;
    uint16_t repetition, consecutive;
    vector<Policy*> pol;
    for (int i = 0; i < n; i++) {
        cin>>regula;
        if(regula=="length"){
           cin>>minl;

           if(getchar() ==' '){
               cin>>maxl;
               pol.push_back(new LengthPolicy(minl,maxl));
           }
           else
               pol.push_back(new LengthPolicy(minl));

        } else if(regula=="class"){
            cin>>minClassCount;
            pol.push_back(new ClassPolicy(minClassCount));
        } else if(regula=="include"){
            cin>>characterTypeINCLUDE;
            pol.push_back(new IncludePolicy(characterTypeINCLUDE));
        } else if(regula=="ninclude"){
            cin>>characterTypeNOINCLUDE;
            pol.push_back(new NotIncludePolicy(characterTypeNOINCLUDE));
        } else if(regula=="repetition"){
            cin>>repetition;
            pol.push_back(new RepetitionPolicy(repetition));
        } else if(regula=="consecutive"){
            cin>>consecutive;
            pol.push_back(new ConsecutivePolicy(consecutive));
        }
    }
    string parola;
    while(cin>>parola){
        checkPassword(parola, pol);
        if(checkPassword(parola,pol)=="OK")
            cout<<"OK"<<endl;
        else cout<<"NOK"<<endl;
        checkPassword(parola,pol);
    }
    return 0;
}