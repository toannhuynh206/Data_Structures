#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <thread>
#include <chrono>
#include <cmath>
template <typename T>
  class Hashtable {
     public:
        Hashtable(bool debug = false,unsigned int size=11);

        ~Hashtable ();

        int add(std::string k, const T& val);

        void reportAll(std::ostream& f) const;

        const T& lookup (std::string k);  

        void clear();    
    
   private:
    struct Item{
         Item(const T& v,std::string k); //item has a value and a key
         T val;
         std::string key;
     };

   private:
    int curr_size;
    int resize_count;
    unsigned int a_size[17];
    bool debug_x;
    T garb;
    int hash(std::string k) const;
    int max_size;
    void resize();
    int r[5];
    Item** hash_array;
  };

template<typename T>
Hashtable<T>::Item::Item(const T& v,std::string k){
    val=v;
    key=k;
}

template <typename T>
Hashtable<T>::Hashtable(bool debug,unsigned int size){
    resize_count=0;
    curr_size=0;
    srand(time(NULL));
    debug_x=debug;
    a_size[0]=11;
    a_size[1]=23;
    a_size[2]=47; //array of primes to resize
    a_size[3]=97;
    a_size[4]=197;
    a_size[5]=397;
    a_size[6]=797;
    a_size[7]=1597;
    a_size[8]=3203;
    a_size[9]=6421;
    a_size[10]=12853;
    a_size[11]=25717;
    a_size[12]=51437;
    a_size[13]=102877;
    a_size[14]=205759;
    a_size[15]=411527;
    a_size[16]=823117;
    if(size==365){max_size=365;} //this if statement is to help with the collect data portion of the pa
    else if(size==14){max_size=14;}
    else{
        if(size<=a_size[0]){
            max_size=a_size[0]; //round to the nearest prime number
        }
        else{
            for(int i=0;i<=16;i++){
                if( a_size[i] < size && a_size[i+1]>=size){
                    max_size=a_size[i+1];
                }
            }
        } 
    }
    if(!debug_x){ //if debug mode is off create random r values
        r[0]=rand()%max_size;
        r[1]=rand()%max_size;
        r[2]=rand()%max_size;
        r[3]=rand()%max_size;
        r[4]=rand()%max_size;
    }
    else{
        r[0]=983132572;
        r[1]=1468777056;
        r[2]=552714139;
        r[3]=984953261;
        r[4]=261934300;
    }
    hash_array=new Item*[max_size]; //intialize our hash array set each item to null
    for(int i=0;i<max_size;i++){
        hash_array[i]=nullptr;
    }
 }

template<typename T>
Hashtable<T>::~Hashtable (){
    for(int i=0;i<max_size;i++){
        if(hash_array[i]!=nullptr){
            delete hash_array[i];
        }
    }
    delete [] hash_array;
}



template<typename T>
int Hashtable<T>::hash(std::string k) const{
    std::vector<long long> nums;
    std::vector<std::string> seg;
    int temp=0;
    if(k.length()==6){ //case where length is 6
        for(int i=0;i<6;i++){
            int letter_num=(int)k[i]-96;
            temp+=pow(27,6-i-1)*letter_num;
        }
        for(int i=0;i<4;i++){
            nums.push_back(0); //only w5 has a value
        }
        nums.push_back(temp);
    }
    else if(k.length()<6){ //case where length is less than 6
        int diff=6-k.length();
        for(unsigned int i=0;i<k.length();i++){
            int letter_num=(int)k[i]-96;
            temp+=pow(27,5-diff)*letter_num;
            diff+=1;
        }
        for(int i=0;i<4;i++){
            nums.push_back(0);
        }
        nums.push_back(temp); //again only w5 has a value
    }
    else if(k.length()>6){ //case where length is greater than 6
        int segments=ceil(k.length()/6.0); //divide word into segements of 6 chars
        int size=k.length();
        int end=size;
        int start=size-6;
        std::vector<std::string> seg; //this loop breaks the string up into segments of 6 chars
        std::string part="";
        for(int i=0;i<segments;i++){
            part=k.substr(start,end); //get the substring and add it to our segments vector
            k.erase(start,end);
            seg.push_back(part);
            end-=6;
            start-=6;
            if(start<0){
                start=0;
            }
        }
        for(int i=0;i<5-segments;i++){
            seg.push_back(""); 
        }
        reverse(seg.begin(),seg.end()); //reverse the segments because we start from the last 6 words
        for(int i=0;i<5;i++){
             nums.push_back(0);
        }

        for(int i=0;i<5;i++){
            temp=0;
            if(seg[i].length()==0){ //if the segment is empty wi is 0
                nums[i]=0;
            }
            else if(seg[i].length()==6){ //case where the segment has length of 6
                std::string curr_seg=seg[i];
                for(int j=0;j<6;j++){
                    int letter_num=(int)curr_seg[j]-96;
                    temp+=pow(27,6-j-1)*letter_num;
                }
                nums[i]=temp;
            }
            else if(seg[i].length()<6){ //case where the segment is less than 6
                std::string curr_seg=seg[i];
                int diff=6-curr_seg.length();
                for(unsigned int j=0;j<curr_seg.length();j++){
                    int letter_num=(int)curr_seg[j]-96;
                    temp+=pow(27,5-diff)*letter_num;
                    diff+=1;
                   }
                nums[i]=temp;
            }  
        }
    }

    long long sum=r[0]*nums[0]+r[1]*nums[1]+r[2]*nums[2]+r[3]*nums[3]+r[4]*nums[4]; //get sum based on the given equation
    long long hash_val=sum%max_size;
    nums.clear(); //reset the nums and segments vector
    seg.clear();
    return hash_val;
}

template<typename T>
const T& Hashtable<T>::lookup(std::string k){
    int index=hash(k); //get the index
    int curr=index;
    int i=1;
    while(hash_array[curr]!=nullptr){ //loop till we see an empty box
        if(hash_array[curr]->key==k){
            return hash_array[curr]->val; //return if we found our key
        }
        curr=((hash(k))+(i*i))%max_size; //else probe to the next spot
        i++;
    }
    return garb; //return garb not in the list
}


template<typename T>
void Hashtable<T>::resize(){
    srand(time(NULL));
    resize_count++;
    int oldsize=max_size; //get next prime size
    int resize=a_size[resize_count];
    Item** new_hash_array=new Item*[resize]; //intialize bigger array
    for(int i=0;i<resize;i++){
        new_hash_array[i]=nullptr;
    }
    max_size=resize; 
    if(!debug_x){
        r[0]=rand()%max_size;
        r[1]=rand()%max_size; //generate new r values
        r[2]=rand()%max_size;
        r[3]=rand()%max_size;
        r[4]=rand()%max_size;
    }
    for(int i=0;i<oldsize;i++){ //this loop copies over the old array into the new array
        if(hash_array[i]!=nullptr){
            std::string old_string = hash_array[i]->key;
            int newindex=hash(old_string);
            int probe=1;
            if(new_hash_array[newindex]==nullptr){
               new_hash_array[newindex]=new Item(hash_array[i]->val,old_string);
            }
            else{
                while(new_hash_array[newindex]!=nullptr){
                if(new_hash_array[newindex]->key!=old_string){
                    newindex=((hash(old_string))+(probe*probe))%max_size;
                    probe++;
                }  
            }
            new_hash_array[newindex]= new Item(hash_array[i]->val,old_string);
         }
    }
    delete hash_array[i];
    }

    delete [] hash_array; //delete old array
    hash_array=new_hash_array; //now our array points to the new array
}

template<typename T>
int Hashtable<T>::add(std::string k, const T& val){

    if((double)(curr_size+1)/max_size>=.5){
        resize(); //if load factor is above .5 resize
    }
    int curr=hash(k);
    int i=1;
    if(hash_array[curr]==nullptr){
        hash_array[curr]=new Item(val,k);
        curr_size++; //if the first insert is empty return 0
        return 0;
    }
    else{
       while(hash_array[curr]!=nullptr){ //loop until we either find an empty spot or we find a duplicate
            if(hash_array[curr]->key!=k){
                curr=((hash(k))+(i*i))%max_size;
                i++;
            }
            else if(hash_array[curr]->key==k){
                return -1; //if k is already in the list we just return;
            }
        }
        Item* temp= new Item(val,k);
        hash_array[curr]=temp;
        curr_size++;
        return i-1;
   }
}

template<typename T>
void Hashtable<T>::reportAll(std::ostream& f) const{
   for(int i=0;i<max_size;i++){
       if(hash_array[i]!=nullptr){ //print out all items in our hash function to given stream
           f<<hash_array[i]->key<<" "<<hash_array[i]->val<<std::endl;
       }
   }
}

template<typename T>
void Hashtable<T>::clear(){ //helper function to empty out our hash function
    for(int i=0;i<max_size;i++){
        if(hash_array[i]!=nullptr){
            delete hash_array[i];
            hash_array[i]=nullptr;
        }
    curr_size=0;
    }
}





