#include <bits/stdc++.h>
#include <bitset>

using namespace std;

string message,tail;
char hip[15],rip[15],hmac[17],rmac[17];
int hp,rp,hp1,rp1,hip1,hip2,hip3,hip4,rip1,rip2,rip3,rip4;

host_mac_ad()
{
    cout<<"Enter Host MAC Address(Example: 07:01:02:01:2C:4B) -> ";
    cin>>hmac;
    cout<<endl;

    cout<<"Enter Receiver MAC Address(Example: 07:01:02:01:2C:4B) -> ";
    cin>>rmac;
    cout<<endl;
}

int main()
{
    cout<<"Enter Your Message -> ";
    cin>>message;
    cout<<endl;

    cout<<"Enter Host Port Address(Within 0 to 65535) -> ";
    cin>>hp;
    cout<<endl;
    bitset<16>host_port(hp);

    cout<<"Enter Receiver Port Address(Within 0 to 65535) -> ";
    cin>>rp;
    cout<<endl;
    bitset<16>receiver_port(rp);

    cout<<"Enter Host IP Address(Example: 192.0.2.235) -> ";
    cin>>hip;
    cout<<endl;
    sscanf(hip, "%d.%d.%d.%d", &hip1, &hip2, &hip3, &hip4);
    bitset<8> bin_hip1(hip1);
    bitset<8> bin_hip2(hip2);
    bitset<8> bin_hip3(hip3);
    bitset<8> bin_hip4(hip4);

    cout<<"Enter Receiver IP Address(Example: 192.0.2.235) -> ";
    cin>>rip;
    cout<<endl;
    sscanf(rip, "%d.%d.%d.%d", &rip1, &rip2, &rip3, &rip4);
    bitset<8> bin_rip1(rip1);
    bitset<8> bin_rip2(rip2);
    bitset<8> bin_rip3(rip3);
    bitset<8> bin_rip4(rip4);

    host_mac_ad();

    cout<<"Enter A Data Link Layer Tail -> ";
    cin>>tail;
    cout<<endl;

    cout<<"So the frame is -> "<<endl;
    cout<<hmac<<" "<<rmac<<" "<<hip<<" "<<rip<<" "<<hp<<" "<<rp<<" "<<message<<" "<<tail<<endl;

    cout<<"After Conversion -> ";
    //using strtok for string breaking then store it in token
    char *token = strtok(hmac, ":");

    while (token != NULL)
    {
        stringstream ss1;
        ss1 << hex << token;
        unsigned n1;
        ss1 >> n1;
        bitset<8> b1(n1);
        cout << b1.to_string() <<"00111010"; //by default ':' value in binary is 00111010
        token = strtok(NULL, ":");
    }
    char *token1 = strtok(rmac, ":");

    while (token1 != NULL)
    {
        stringstream ss;
        ss << hex << token1;
        unsigned n;
        ss >> n;
        bitset<8> b(n);
        cout << b.to_string() <<"00111010";//by default ':' value in binary is 00111010
        token1 = strtok(NULL, ":");
    }

    //the '.' is fixed in IP address so it unnecessary to call function only for dot so I manually did this
    //the '.' is equivalent to 00101110 in binary
    cout<< bin_hip1 <<"00101110"<< bin_hip2 <<"00101110"<< bin_hip3 <<"00101110"<< bin_hip4 <<"00101110";
    cout<< bin_rip1 <<"00101110"<< bin_rip2 <<"00101110"<< bin_rip3 <<"00101110"<< bin_rip4 <<"00101110";
    cout<<host_port;
    cout<<receiver_port;
    for (size_t i = 0; i < message.size(); ++i)
    {
        cout << bitset<8>(message.c_str()[i]);
    }
    for (size_t i = 0; i < tail.size(); ++i)
    {
        cout << bitset<8>(tail.c_str()[i]);
    }

}

