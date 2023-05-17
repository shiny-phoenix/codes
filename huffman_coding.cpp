#include<bits/stdc++.h>
using namespace std;

map<string, string> huffman_codes;

class node
{
       private :
            string letter;
            int frequency;
            node* left;
            node* right;
        public:  
            node()
            {
                letter = " ";
                frequency = 0;
                this->left = NULL;
                this->right = NULL;
            }
            node(string letter,int freq)
            {
                this->letter = letter;
                this->frequency = freq;
                this->left = NULL;
                this->right = NULL;
            }
            
            friend class huffman_tree;
            friend class compare;
};


class huffman_tree
{
    private:
            node* root;
            string msg;
    public:
            huffman_tree()          {root = NULL;}
            node* getroot()          {return root;}
            void tree_formation();
            void codes(node*, string, map <string, string> &);
            void encode_message();
            void decode_message();
};

class compare{
public:
        bool operator()(node* fs, node* sec){
                return (fs->frequency > sec->frequency);
        }
};

void huffman_tree :: tree_formation()
{
    cout<<"Enter the message to be encoded:"<<endl;
    cin.ignore();
    getline(cin,msg);        
    
    int freq_array[256] = {0};
    for (int i = 0; i < msg.size(); i++)        freq_array[int(msg[i])]++;
   
    priority_queue<node*, vector<node*> , compare> pq;
    
    for (int i =0; i<256; i++)
    {
        if (freq_array[i] )
        {
            char ch = i;
            node* temp = new node(string(1,ch), freq_array[i]);
            pq.push(temp);          
        }
    }
    
    while(pq.size()!=1)
    {
        node* temp = pq.top();
        pq.pop();
        node* temp1 = pq.top();
        pq.pop();
        node* parent = new node(temp->letter + temp1->letter,temp->frequency + temp1->frequency);
        parent->left = temp;
        parent->right = temp1;
        pq.push(parent);
    }
  
    root = pq.top();
     cout<<endl;     
}

void huffman_tree::codes(node* n, string code, map <string, string> & mymap) {
    if (n == nullptr)        return;

    if (n->left == nullptr && n->right == nullptr)
    {
        cout << n->letter << ": " << code << endl;
        mymap[n->letter] = code;
    }

    codes(n->left, code + "0", mymap);
    codes(n->right, code + "1", mymap);
}

void huffman_tree :: encode_message()
{
    tree_formation();

    codes(root, "", huffman_codes);

    string encoded_message = "";
    for (int i = 0; i < msg.size(); i++)
    {
        string code = huffman_codes[string(1, msg[i])];
        encoded_message += code;
    }
    cout << "Encoded message: " << encoded_message << endl;
}

void huffman_tree :: decode_message()
{
    string current_code = "";
    cout<<"Enter the binary string to be decoded:"<<endl;
    cin.ignore();
    getline(cin,current_code);   

    map<string, string> inverted_codes;
    for (auto& pair : huffman_codes) {
        inverted_codes[pair.second] = pair.first;
    }

    string decoded_message = "";
    string temp = "";
    
    for (int i = 0; i < current_code.size(); i++)
    {
        temp += current_code[i];
        if (inverted_codes.find(temp) != inverted_codes.end())
        {
            decoded_message += inverted_codes[temp];
            temp = "";
        }
    }

    cout << "Decoded message: " << decoded_message << endl;
}


int main()
{
    huffman_tree tree;
    int choice;

    do
    {
        cout<<"1. Encode a message"<<endl;
        cout<<"2. Decode a message"<<endl;
        cout<<"Enter choice :",cin>>choice;

        switch(choice)
        {
            case 1:     
                    tree.encode_message();                          
                    break;

            case 2:
                    tree.decode_message();
                    break;
        }
    } while(0 < choice && choice < 3 );

    return 0;
}
