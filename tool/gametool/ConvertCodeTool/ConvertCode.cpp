//
//  main.cpp
//  primer
//
//  Created by huyanfei on 14-10-8.
//  Copyright (c) 2014年 huyanfei. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include <set>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <algorithm>    // std::find
using namespace std;


int main(int argc, const char * argv[]) {
	srand(time(0));
    // insert code here...
    const string strFileName = argv[1];
    int iConverCodeCount  = atoi(argv[2]);
    const  string strVersion = argv[3];
    const  string strGiftCode = argv[4];
    //const  string strClear = argv[5];
    cout<<"  " << strFileName << " | " <<iConverCodeCount <<" | " << strVersion << " | " <<strGiftCode <<endl;
    
    
    const string  strGoldCode = "1234567890asdfghjklqwertyuiopzxcvbnm";
    size_t  iRandMode = strGoldCode.size();
    
    vector<string> converCodeSet;
    
    string commonStr("**********");
    commonStr[1] = strVersion[0];
    commonStr[7] = strVersion[1];
    commonStr[3] = strGiftCode[0];
    commonStr[8] = strGiftCode[1];
    
    int count = 0;
     srand((int)time(0));
    while (converCodeSet.size() != iConverCodeCount) {
      
        string oss= commonStr;
        for (int index = 0; index < 10; ++index) {
            
            if((index == 1) || (index == 7) || (index == 3) || (index == 8)) {
                continue;
                
            }
            
            int Codeindex = rand() % iRandMode;
            const char ch = strGoldCode[Codeindex];
            oss[index] = ch;
            
        }
        count ++;
        cout <<count <<" |convertCode |"<< oss.c_str() <<endl;
		const vector<string>::iterator iter = std::find(converCodeSet.begin(),converCodeSet.end(),oss.c_str());
		if(iter != converCodeSet.end())
		{
			continue;
		}
        converCodeSet.push_back(oss);
		usleep(1);
    }
    
   
    fstream ifs;
	ifs.open(strFileName.c_str(),ios::out|ios::in|ios::binary);
    if(!ifs.good())
	{
		string strTouchFile = string("touch ") + strFileName;
		popen(strTouchFile.c_str(),"w");
		ifs.open(strFileName.c_str(),ios::out|ios::in|ios::binary);
	}
   
    cout<<"======= clear (ConvertCode.txt) Input Y(N) "<<endl;
    string actorInput;
    cin>>actorInput;
    
    while (true) {
       
        if(actorInput == "Y")
        {
            ifs.clear();
            ifs.seekg(0, ios::beg);
            break;
        }
        else if( actorInput == "N")
        {
            ifs.seekg(0, ios::end);
            break;
        }

        else
        {
            cout<<"======= clear (ConvertCode.txt) Input Y(N) "<<endl;
            cin>>actorInput;
        }
        
    }


    for (size_t i = 0; i < converCodeSet.size(); ++i) {
        
         string str = converCodeSet[i];
		str.append("\n");
        ifs.write(str.c_str(),str.size());
        //ifs.write("\n", sizeof("\n"));
       // ifs.w
    }
    
    
    return 0;
}
