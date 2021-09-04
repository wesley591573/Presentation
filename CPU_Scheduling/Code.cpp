# include <iostream>
# include <string.h>
# include <stdio.h>
# include <vector>
# include <fstream> 

#define max 0x3f3f3f3f

using namespace std ;

int command = -1 ; // 紀錄input檔要我做得事情 
int timeSlice = -1 ;

struct process{
  int id ;
  char id_ch ;
  int burst ;
  int arrival ;
  int priority ;
  bool finished ;
  
} ; // process

struct timeinfo{
  int id ;
  int time ;
  
} ; // timeinfo

struct timeinfo_ch{
  char id_ch ;
  int time ;
  int loc ; // 在AP中的位置 
  
};

// 專門給PPRR排隊Queue用的 
struct PPRRinfo{
  int id ;
  int burst ;
  int priority ;
  int loc ;
  
};

vector <process> AP ; // All Process

class Scheduling {
  vector <char> schedule ;
  vector <timeinfo> waiting ;
  vector <timeinfo> turnAround ;
  int time = 0 ;

public:
  bool GetFile( string fileName ) {
    FILE *infile = NULL ;
    process OP ; // One Process
    char ch ; // 把不重要的資訊讀掉 
    
    fileName = fileName + ".txt" ;
    infile = fopen( fileName.c_str(), "r" ) ;
    
    if ( infile == NULL ) {
      cout << "\n###" << fileName << " does not exist!###\n\n" ;
      
      return false ;
      
    } // if()
    
    else {
      cout << "Success" << endl << endl ; 
      
      fscanf( infile, "%d", &command ) ;
      fscanf( infile, "%d", &timeSlice ) ;
      fscanf( infile, "%c", &ch ) ;
      
      ch = ' ' ;
      
      while( ch != '\n' ) {
				fscanf( infile, "%c", &ch ) ;
			} // while
      
      while ( !feof(infile) ) {
        fscanf( infile, "%d", &OP.id ) ;
        fscanf( infile, "%d", &OP.burst ) ;
        fscanf( infile, "%d", &OP.arrival ) ;
        fscanf( infile, "%d", &OP.priority ) ;
        OP.finished = false ;
        
        AP.push_back( OP ) ;
        
      } // while()
      
      if ( AP.at(AP.size() - 1).id == AP.at(AP.size() - 2).id ) {
        AP.pop_back() ;
        
      } // if()
      
      return true ;
      
    } // else
    
  } // GetFile()
  
  // 因為output檔中，id超出9要用英文字母表示，所以以此function轉換 
  void IDConvert() {
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( AP.at(i).id < 10 ) {
        AP.at(i).id_ch = 48 + AP.at(i).id ;
      	
	    } // if()
	  
	    else {
	      AP.at(i).id_ch = 55 + AP.at(i).id ;
	  	
	    }  // else
      
    } // for()
    
  } // idConVert()
  
  // 製作waiting和turnAround兩個shedule 
  void MakeSch() {
    process temp ;
    timeinfo oneInfo ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      for ( int j = i + 1 ; j < AP.size() ; j++ ) {
        if ( AP.at(i).id > AP.at(j).id ) {
          temp = AP.at(i) ;
          AP.at(i) = AP.at(j) ;
          AP.at(j) = temp ;
          
        } // if()
        
      } // for()
      
    } // for()
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      oneInfo.id = AP.at(i).id ;
      oneInfo.time = 0 ;
      
      waiting.push_back( oneInfo ) ;
      turnAround.push_back( oneInfo ) ;
      
    } // for()
    
  } // MakeSch()
  
  // 是否所有的process都做完了 
  bool AllFinished() {
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( !AP.at(i).finished ) {
        return false ;
        
      } // if()
      
    } // for()
    
    return true ;
    
  } // AllFinished()
  
  // 幫助FCFS找出最優先的process 
  int MinProcess() {
    int minArrival = max ; // 尋找最小的arrival time
    int minProcess = -1 ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( !AP.at(i).finished ) {
        if ( AP.at(i).arrival < minArrival ) {
          minArrival = AP.at(i).arrival ; 
          minProcess = i ;
          
        } // if()
        else if ( AP.at(i).arrival == minArrival ) {
          if ( AP.at(i).id < AP.at(minProcess).id ) {
            minProcess = i ;
            
          } // if()
          
        } // else if()
        
      } // if()
      
    } // for()
    
    return minProcess ;
    
  } // MinProcess()
  
  void FCFS() {
    int min ; // 最優先的process 
    
    while ( !AllFinished() ) {
      min = MinProcess() ;
      
      if ( AP.at(min).arrival > time ) {
        schedule.push_back( '-' ) ;
        time++ ;
        
      } // if()
      
      else {
        waiting.at(min).time = time - AP.at(min).arrival ;
        turnAround.at(min).time = waiting.at(min).time + AP.at(min).burst ;
        
        for ( int i = 0 ; i < AP.at(min).burst ; i++ ) {
          schedule.push_back( AP.at(min).id_ch ) ;
          time++ ;
          
        } // for()
        
        AP.at(min).finished = true ;
        
      } // else
      
    } // while()
    
  } // FCFS()
  
  // 幫助RR找出有相同Arrival Time的數目 
  int SameArrival() {
    int count = 0 ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( AP.at(i).arrival == time ) {
        count++ ;
        
      } // if()
      
    } // for()
    
    return count ;
    
  } // SameArrival()
  
  // 幫助RR找出最優先的process 
  int MinProcess_RR( vector <bool> inTheQueue ) {
    int minArrival = max ; // 尋找最小的arrival time
    int minProcess = -1 ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( !AP.at(i).finished ) {
        if ( AP.at(i).arrival < minArrival && !inTheQueue.at(i) ) {
          minArrival = AP.at(i).arrival ; 
          minProcess = i ;
          
        } // if()
        else if ( AP.at(i).arrival == minArrival ) {
          if ( AP.at(i).id < AP.at(minProcess).id && !inTheQueue.at(i) ) {
            minProcess = i ;
            
          } // if()
          
        } // else if()
        
      } // if()
      
    } // for()
    
    return minProcess ;
    
  } // MinProcess()
  
  void RR() {
    vector <bool> inTheQueue ; // 紀錄每個process是否都進入了queue排隊 
    vector <timeinfo_ch> Queue ; // 排隊列表，分別代表id和burst time 
    int min ;
    timeinfo_ch newProcess ; // 準備要放進Queue的process 
    int slice = timeSlice ;
    
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      inTheQueue.push_back( false ) ;
      
    } // for()
    
    while ( !AllFinished() ) {
      
      // cout << "Time : " << time << endl ;
        
      // AP -> Queue
      // 該process還沒放進Queue中 
      for ( int i = 0 ; i < SameArrival() ; i++ ) {
      
        min = MinProcess_RR( inTheQueue ) ;
        
        // process要放進Queue裡面了 
        if ( AP.at(min).arrival == time ) {
          newProcess.id_ch = AP.at(min).id_ch ;
          newProcess.time = AP.at(min).burst ;
          newProcess.loc = min ;
          Queue.push_back( newProcess ) ;
            
          inTheQueue.at(min) = true ;
          
        } // if()
          
      } // for()
        
      // Queue -> Schedule
      if ( !Queue.empty() ) {
        
        
        if ( slice == 0 ) {
          slice = timeSlice ;
          
          if ( Queue.at(0).time > 0 ) {
            newProcess = Queue.at(0) ;
            Queue.erase( Queue.begin() ) ;
            Queue.push_back( newProcess ) ;
            
          } // if()
          
          else if ( Queue.at(0).time == 0 ) {
            AP.at( Queue.at(0).loc ).finished = true ;
            turnAround.at( Queue.at(0).loc ).time = time - AP.at( Queue.at(0).loc ).arrival ;
            waiting.at( Queue.at(0).loc ).time = turnAround.at( Queue.at(0).loc ).time - AP.at( Queue.at(0).loc ).burst ;
            Queue.erase( Queue.begin() ) ;
            
            if ( Queue.empty() && !AllFinished() ) {
              schedule.push_back( '-' ) ;
              
            } // if()
            
          } // else
          
        } // if()
        
        if ( !Queue.empty() && Queue.at(0).time > 0 ) {
          schedule.push_back( Queue.at(0).id_ch ) ;
          Queue.at(0).time-- ;
            
        } // else if()
        
        else if( !Queue.empty() && Queue.at(0).time == 0 ) {
          AP.at( Queue.at(0).loc ).finished = true ;
          turnAround.at( Queue.at(0).loc ).time = time - AP.at( Queue.at(0).loc ).arrival ;
          waiting.at( Queue.at(0).loc ).time = turnAround.at( Queue.at(0).loc ).time - AP.at( Queue.at(0).loc ).burst ;
          Queue.erase( Queue.begin() ) ;
            
          if ( !Queue.empty() ) {
            slice = timeSlice ;
            
            schedule.push_back( Queue.at(0).id_ch ) ;
            Queue.at(0).time-- ;
            
          } // if()
          else if ( Queue.empty() && !AllFinished() ) {
            slice = timeSlice ;
            
            schedule.push_back( '-' ) ;
            
          } // else if()
            
        } // else
        
        if ( schedule.at( schedule.size() - 1 ) != '-' ) {
          slice-- ;
          
        } // if()
        
      } // if()
      
      else {
        schedule.push_back( '-' ) ;
          
      } // else
        
      time++ ;
      
    } // while()
    
  } // RR()
  
  // 全部都清，大掃除 
  void Initial() {
    time = 0 ;
    schedule.erase( schedule.begin(), schedule.end() ) ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      waiting.at(i).time = 0 ;
      turnAround.at(i).time = 0 ;
      AP.at(i).finished = false ;
      
      
    } // for()
    
    
  } // Initial()
  
  // 全部都清，大掃除
  void BigInitial() {
    time = 0 ;
    schedule.erase( schedule.begin(), schedule.end() ) ;
    waiting.erase( waiting.begin(), waiting.end() ) ;
    turnAround.erase( turnAround.begin(), turnAround.end() ) ;
    AP.erase( AP.begin(), AP.end() ) ;
    
  } // BigInitial()
  
  // 幫助SRTF找出最優先的process 
  int MinProcess_SRTF( vector <timeinfo> record ) {
    int minBurst = max ; // 尋找最小的burst time
    int minArrival = max ; // 尋找最小的arrival time
    int minID = max ; // 尋找最小的id
    int minProcess = -1 ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( time >= AP.at(i).arrival && minBurst > record.at(i).time && !AP.at(i).finished ) {
        minBurst = record.at(i).time ;
        minArrival = AP.at(i).arrival ;
        minID = AP.at(i).id ;
        minProcess = i ;
        
      } // if()
      else if ( time >= AP.at(i).arrival && minBurst == record.at(i).time && !AP.at(i).finished ) {
        if ( minArrival > AP.at(i).arrival ) {
          minArrival = AP.at(i).arrival ;
          minID = AP.at(i).id ;
          minProcess = i ;
          
        } // if()
        
        else if ( minArrival == AP.at(i).arrival ) {
          if ( minID > AP.at(i).id ) {
            minID = AP.at(i).id ;
            minProcess = i ;
            
          } // if()
          
        } // else if()
        
      } // else if()
      
    } // for()
    
    return minProcess ;
    
  } // MinProcess_SRTF()
  
  void SRTF() {
    int min ;
    vector <timeinfo> record ; // 記錄各process的burst還剩多少 
    timeinfo nRecord ;
    
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      nRecord.id = AP.at(i).id ;
      nRecord.time = AP.at(i).burst ;
      
      record.push_back( nRecord ) ;
      
    } // for()
    
    while ( !AllFinished() ) {
      min = MinProcess_SRTF( record ) ;
      // cout << "Time : " << time << endl ;
      
      if ( min == -1 ) {
        schedule.push_back( '-' ) ;
        
      } // if()
      
      else if ( time >= AP.at(min).arrival ) {
        schedule.push_back( AP.at(min).id_ch ) ;
        record.at(min).time -- ;
        
      } // else if()
      
      time ++ ;
      
      if ( min != -1 && record.at(min).time == 0 ) {
        AP.at(min).finished = true ;
          
        turnAround.at(min).time = time - AP.at(min).arrival ;
        waiting.at(min).time = turnAround.at(min).time - AP.at(min).burst ;
        
        min = MinProcess_SRTF( record ) ;
        
      } // if()
      
    } // while()
    
  } // SRTF()
  
  int MinProcess_PPRR( vector <PPRRinfo> &Queue, vector <bool> inTheQueue, int sliceCount ) {
    int minPriority = max ;
    int minProcess = -1 ;
    PPRRinfo newP ; // 要放進Queue的新 
    int count = SameArrival() ;
    
    for ( int j = 0 ; j < count ; j++ ) {
      minPriority = max ;
      minProcess = -1 ;
      
      // 確認是當下所process中priority最小的 
      for ( int i = 0 ; i < AP.size() ; i++ ) {
        if ( time == AP.at(i).arrival && minPriority > AP.at(i).priority && !inTheQueue.at(i) ) {
          minProcess = i ;
          minPriority = AP.at(i).priority ;
          
          newP.id = AP.at(i).id ;
          newP.burst = AP.at(i).burst ;
          newP.priority = AP.at(i).priority ;
          newP.loc = i ;
          
        } // if()
        
      } // for()
      
      inTheQueue.at( minProcess ) = true ;
      
      if ( Queue.size() > 0 ) {
        for ( int i = 0 ; i < Queue.size() ; i++ ) {
          if ( Queue.at(i).priority > newP.priority ) {
            Queue.insert( Queue.begin() + i, newP ) ;
            
            break ;
            
          } // if()
          else if ( i == Queue.size() - 1 ) {
            Queue.push_back( newP ) ;
            
            break ;
            
          } // else if()
          
        } // for()
        
        // 有一個沒做完的被插隊了，他要到隊伍排隊 
        if ( sliceCount != 0 ) {
          for ( int i = 0 ; i < Queue.size() ; i++ ) {
            if ( Queue.at(i).priority > Queue.at(1).priority ) {
              Queue.insert( Queue.begin() + i, Queue.at(1) ) ;
              
              Queue.erase( Queue.begin() + 1 ) ;
              
              break ;
              
            } // if()
            else if ( i == Queue.size() - 1 ) {
              Queue.push_back( Queue.at(1) ) ;
              
              Queue.erase( Queue.begin() + 1 ) ;
              
              break ;
              
            } // else if()
            
          } // for()
          
        } // sliceCount()
        
      } // if()
      else {
        Queue.push_back( newP ) ;
        
      } // else 
      
    } // for()
    
    if ( Queue.size() > 0 ) {
      return Queue.at(0).loc ;
      
    } // if()
    else {
      return -1 ;
      
    } // else
    
  } // MinProcess_PPRR()
  
  void PPRR() {
    int min ;
    bool RR = false ; // 如果有相同priority，就開始執行RR 
    vector <PPRRinfo> Queue ; // 給RR的排隊 
    vector <bool> inTheQueue ; // 各process是否在queue中了 
    int sliceCount = 0 ; 
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      inTheQueue.push_back( false ) ;
      
    } // for()
    
    while ( !AllFinished() ) {
      min = MinProcess_PPRR( Queue, inTheQueue, sliceCount ) ;
      
      if ( min == -1 ) {
        sliceCount = 0 ;
        schedule.push_back( '-' ) ;
        
      } // if()
      
      // 要注意timeSlice 
      else if ( Queue.size() >= 2 && Queue.at(1).priority == AP.at(min).priority ) {
        // 當遇到priority比較高的process插隊時，要把sliceCount重置 
        if ( schedule.size() > 0 && schedule.at( schedule.size() - 1 ) != AP.at(min).id_ch ) {
          sliceCount = 0 ;
          
        } // if()
        
        sliceCount++ ;
        Queue.at(0).burst-- ;
        schedule.push_back( AP.at(min).id_ch ) ;
        
        // timeSlice時間到了，而且process還沒做完 
        if ( sliceCount == timeSlice && Queue.at(0).burst > 0 ) {
          sliceCount = 0 ;
          
          // 把process放到後面排隊 
          for ( int i = 0 ; i < Queue.size() ; i++ ) {
            if ( Queue.at(i).priority > AP.at(min).priority ) {
              Queue.insert( Queue.begin() + i, Queue.at(0) ) ;
              
              Queue.erase( Queue.begin() ) ;
              
              break ;
              
            } // if()
            
            else if ( i == Queue.size() - 1 ) {
              Queue.push_back( Queue.at(0) ) ;
              
              Queue.erase( Queue.begin() ) ;
              
              break ;
              
            } // else if()
            
          } // for()
          
        } // if()
        
        // timeSlice還沒結束，process就做完了 
        else if ( Queue.at(0).burst == 0 ) {
          sliceCount = 0 ;
          
          Queue.erase( Queue.begin() ) ;
          
          AP.at(min).finished = true ;
          
          // +1的目的是因為time是從0開始 
          turnAround.at(min).time = time + 1 - AP.at(min).arrival ;
          waiting.at(min).time = turnAround.at(min).time - AP.at(min).burst ;
          
        } // else if()
        
      } // if()
      
      // 要注意timeSlice 
      else if ( Queue.size() >= 2 && Queue.at(1).priority > AP.at(min).priority ) {
        // 當遇到priority比較高的process插隊時，要把sliceCount重置 
        if ( schedule.size() > 0 && schedule.at( schedule.size() - 1 ) != AP.at(min).id_ch ) {
          sliceCount = 0 ;
          
        } // if()
        
        sliceCount++ ;
        Queue.at(0).burst-- ;
        schedule.push_back( AP.at(min).id_ch ) ;
        
        // process做完了 
        if ( Queue.at(0).burst == 0 ) {
          sliceCount = 0 ;
          
          Queue.erase( Queue.begin() ) ;
          
          AP.at(min).finished = true ;
          
          // +1的目的是因為time是從0開始 
          turnAround.at(min).time = time + 1 - AP.at(min).arrival ;
          waiting.at(min).time = turnAround.at(min).time - AP.at(min).burst ;
          
        } // if()
        
      } // else if()
      
      else if ( Queue.size() == 1 ) {
        sliceCount++ ;
        Queue.at(0).burst-- ;
        schedule.push_back( AP.at(min).id_ch ) ;
        
        // process做完了 
        if ( Queue.at(0).burst == 0 ) {
          sliceCount = 0 ;
          
          Queue.erase( Queue.begin() ) ;
          
          AP.at(min).finished = true ;
          
          // +1的目的是因為time是從0開始 
          turnAround.at(min).time = time + 1 - AP.at(min).arrival ;
          waiting.at(min).time = turnAround.at(min).time - AP.at(min).burst ;
          
        } // if()
        
      } // else if()
      
      time++ ;
      
    } // while()
    
  } // PPRR()
  
  // 幫助HRRN找出最優先的process 
  int MinProcess_HRRN( vector <float> waitingRatio ) {
    float minRatio = -1 ;
    int minArrival = max ;
    int minID = max ;
    int minProcess = -1 ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      if ( time >= AP.at(i).arrival && minRatio < waitingRatio.at(i) && !AP.at(i).finished ) {
        minRatio = waitingRatio.at(i) ;
        minArrival = AP.at(i).arrival ;
        minID = AP.at(i).id ;
        minProcess = i ;
        
      } // if()
      
      else if ( time >= AP.at(i).arrival && minRatio == waitingRatio.at(i) && !AP.at(i).finished ) {
        if ( minArrival > AP.at(i).arrival ) {
          minArrival = AP.at(i).arrival ;
          minID = AP.at(i).id ;
          minProcess = i ;
          
        } // if()
        
        else if ( minArrival == AP.at(i).arrival ) {
          if ( minID > AP.at(i).id ) {
            minID = AP.at(i).id ;
            minProcess = i ;
            
          } // if()
          
        } // else if()
        
      } // else if()
      
    } // for()
    
    return minProcess ;
    
  } // MinProcess_HRRN
  
  void renewRatio( vector <float> &waitingRatio, int min ) {
    // min表示正在CPU的process，因此在waiting中不需要+1 
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      
      if ( time > AP.at(i).arrival && !AP.at(i).finished && i != min  ) {
        waiting.at(i).time ++ ;
        waitingRatio.at(i) = ( (float)waiting.at(i).time + (float)AP.at(i).burst ) / (float)AP.at(i).burst ;
        
      } // if()
      
      else if ( time == AP.at(i).arrival && !AP.at(i).finished && i != min ) {
        waiting.at(i).time = 0 ;
        waitingRatio.at(i) = ( (float)waiting.at(i).time + (float)AP.at(i).burst ) / (float)AP.at(i).burst ;
        
      } // else if()
      
      else if ( !AP.at(i).finished && i != min ) {
        waitingRatio.at(i) = 0 ;
        
      } // else
      
    } // for()
    
  } // renewRatio()
  
  void HRRN() {
    int min ;
    vector <float> waitingRatio ;
    vector <timeinfo> processBurst ;
    timeinfo nProcessBurst ;
    
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      waitingRatio.push_back( 0 ) ;
      
    } // for()
    
    renewRatio( waitingRatio, -1 ) ;
    
    while ( !AllFinished() ) {
      min = MinProcess_HRRN( waitingRatio ) ;
      
      if ( min == -1 ) {
        schedule.push_back( '-' ) ;
        
        time++ ;
        
        renewRatio( waitingRatio, -1 ) ;
        
      } // if()
      
      else {
        for ( int i = 0 ; i < AP.at(min).burst ; i++ ) {
          schedule.push_back( AP.at(min).id_ch ) ;
          
          time++ ;
          
          renewRatio( waitingRatio, min ) ;
          
        } // for()
        
        // cout << AP.at(min).id_ch << ": " << waitingRatio.at(min) << endl ;
        
        turnAround.at(min).time = waiting.at(min).time + AP.at(min).burst ;
        
        AP.at(min).finished = true ;
        
      } // else
      
    } // while()
    
  } // HRRN()
  
  void OutputFile_FCFS( string fileName ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "FCFS" << endl ;
		for ( int i = 0 ; i < schedule.size() ; i++ ) {
		  outfile << schedule.at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    outfile << "waiting" << endl ;
    outfile << "ID	FCFS" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < waiting.size() ; i++ ) {
      outfile << waiting.at(i).id << "\t" << waiting.at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	FCFS" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < turnAround.size() ; i++ ) {
      outfile << turnAround.at(i).id << "\t" << turnAround.at(i).time << endl ;
      
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_FCFS()
  
  void OutputFile_RR( string fileName ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "RR" << endl ;
		for ( int i = 0 ; i < schedule.size() ; i++ ) {
		  outfile << schedule.at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    outfile << "waiting" << endl ;
    outfile << "ID	RR" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < waiting.size() ; i++ ) {
      outfile << waiting.at(i).id << "\t" << waiting.at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	RR" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < turnAround.size() ; i++ ) {
      outfile << turnAround.at(i).id << "\t" << turnAround.at(i).time << endl ;
      
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_RR()
  
  void OutputFile_SRTF( string fileName ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "SRTF" << endl ;
		for ( int i = 0 ; i < schedule.size() ; i++ ) {
		  outfile << schedule.at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    outfile << "waiting" << endl ;
    outfile << "ID	SRTF" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < waiting.size() ; i++ ) {
      outfile << waiting.at(i).id << "\t" << waiting.at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	SRTF" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < turnAround.size() ; i++ ) {
      outfile << turnAround.at(i).id << "\t" << turnAround.at(i).time << endl ;
      
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_SRTF()

  void OutputFile_PPRR( string fileName ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "PPRR" << endl ;
		for ( int i = 0 ; i < schedule.size() ; i++ ) {
		  outfile << schedule.at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    outfile << "waiting" << endl ;
    outfile << "ID	PPRR" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < waiting.size() ; i++ ) {
      outfile << waiting.at(i).id << "\t" << waiting.at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	PPRR" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < turnAround.size() ; i++ ) {
      outfile << turnAround.at(i).id << "\t" << turnAround.at(i).time << endl ;
      
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_PPRR()

  void OutputFile_HRRN( string fileName ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "HRRN" << endl ;
		for ( int i = 0 ; i < schedule.size() ; i++ ) {
		  outfile << schedule.at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    outfile << "waiting" << endl ;
    outfile << "ID	HRRN" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < waiting.size() ; i++ ) {
      outfile << waiting.at(i).id << "\t" << waiting.at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	HRRN" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < turnAround.size() ; i++ ) {
      outfile << turnAround.at(i).id << "\t" << turnAround.at(i).time << endl ;
      
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_HRRN()

  void SaveData( vector < vector <char> > &save_schedule, vector <vector <timeinfo>> &save_waiting, vector <vector <timeinfo>> &save_turnAround ) {
    save_schedule.push_back( schedule ) ;
    save_waiting.push_back( waiting ) ;
    save_turnAround.push_back( turnAround ) ;
    
  } // SaveData()

  void OutputFile_ALL( string fileName, vector < vector <char> > &save_schedule, vector <vector <timeinfo>> &save_waiting, vector <vector <timeinfo>> &save_turnAround ) {
    fileName = "10727138out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		outfile << "All" << endl ; 
		
		outfile << "==        FCFS==" << endl ;
		for ( int i = 0 ; i < save_schedule.at(0).size() ; i++ ) {
		  outfile << save_schedule.at(0).at(i) ;
		  
    } // for()
    
    outfile << endl ;
    
    outfile << "==          RR==" << endl ;
		for ( int i = 0 ; i < save_schedule.at(1).size() ; i++ ) {
		  outfile << save_schedule.at(1).at(i) ;
		  
    } // for()
    
    outfile << endl ;
    
    outfile << "==        SRTF==" << endl ;
		for ( int i = 0 ; i < save_schedule.at(2).size() ; i++ ) {
		  outfile << save_schedule.at(2).at(i) ;
		  
    } // for()
    
    outfile << endl ;
    
    outfile << "==        PPRR==" << endl ;
		for ( int i = 0 ; i < save_schedule.at(3).size() ; i++ ) {
		  outfile << save_schedule.at(3).at(i) ;
		  
    } // for()
    
    outfile << endl ;
    
    outfile << "==        HRRN==" << endl ;
		for ( int i = 0 ; i < save_schedule.at(4).size() ; i++ ) {
		  outfile << save_schedule.at(4).at(i) ;
		  
    } // for()
    
    outfile << endl << "===========================================================" << endl << endl ;
    
    outfile << "waiting" << endl ;
    outfile << "ID	FCFS	RR	SRTF	PPRR	HRRN" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < save_waiting.at(0).size() ; i++ ) {
      outfile << save_waiting.at(0).at(i).id << "\t" << save_waiting.at(0).at(i).time ;
      outfile << "\t" << save_waiting.at(1).at(i).time ;
      outfile << "\t" << save_waiting.at(2).at(i).time ;
      outfile << "\t" << save_waiting.at(3).at(i).time ;
      outfile << "\t" << save_waiting.at(4).at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    outfile << "Turnaround Time" << endl ;
    outfile << "ID	FCFS	RR	SRTF	PPRR	HRRN" << endl ;
    outfile << "===========================================================" << endl ;
    
    for ( int i = 0 ; i < save_turnAround.at(0).size() ; i++ ) {
      outfile << save_turnAround.at(0).at(i).id << "\t" << save_turnAround.at(0).at(i).time ;
      outfile << "\t" << save_turnAround.at(1).at(i).time ;
      outfile << "\t" << save_turnAround.at(2).at(i).time ;
      outfile << "\t" << save_turnAround.at(3).at(i).time ;
      outfile << "\t" << save_turnAround.at(4).at(i).time << endl ;
      
    } // for()
    
    outfile << "===========================================================" << endl << endl ;
    
    outfile.close() ;
    
  } // OutputFile_ALL()

  void TestShow() {
    for ( int i = 0 ; i < AP.size() ; i++ ) {
      cout << AP.at(i).id << "\t" << AP.at(i).arrival << "\t" << AP.at(i).burst << endl ;
      
    } // for()
    
  } // testShow()
  
} ; // Scheduling

int main() {
  string fileName ;
  bool readFile = false ;
  Scheduling sch ;
  vector < vector <char> > save_schedule ;
  vector < vector <timeinfo> > save_waiting ;
  vector < vector <timeinfo> > save_turnAround ;
  
  
  while ( fileName != "0" ) {
    cout << "請輸入檔案名稱 : " << endl ;
    cout << "( 輸入0表示結束 )" << endl ; 
    
    cin >> fileName ;
    
    readFile = false ;
    
    if ( fileName != "0" ) {
      readFile = sch.GetFile( fileName ) ;
      
      if ( readFile ) {
      	sch.IDConvert() ;
      	sch.MakeSch() ;
      	
      	if ( command == 6 ) {
      	  save_schedule.erase( save_schedule.begin(), save_schedule.end() ) ;
      	  save_waiting.erase( save_waiting.begin(), save_waiting.end() ) ;
      	  save_turnAround.erase( save_turnAround.begin(), save_turnAround.end() ) ;
      	  
        } // if()
      	
        // FCFS
        if ( command == 1 || command == 6 ) {
          sch.FCFS() ;
          if ( command == 1 ) {
            sch.OutputFile_FCFS( fileName ) ;
            
          } // if()
          else {
            sch.SaveData( save_schedule, save_waiting, save_turnAround ) ;
            
          } // else
          
          sch.Initial() ;
          
        } // if()
        
        // RR
        if ( command == 2 || command == 6 ) {
          sch.RR() ;
          
          if ( command == 2 ) {
            sch.OutputFile_RR( fileName ) ;
            
          } // if()
          else {
            
            
            sch.SaveData( save_schedule, save_waiting, save_turnAround ) ;
            
          } // else
          
          sch.Initial() ;
          
        } // else if()
        
        // SRTF
        if ( command == 3 || command == 6 ) {
          sch.SRTF() ;
          
          if ( command == 3 ) {
            sch.OutputFile_SRTF( fileName ) ;
            
          } // if()
          else {
            sch.SaveData( save_schedule, save_waiting, save_turnAround ) ;
            
          } // else
          
          sch.Initial() ;
          
        } // else if()
        
        // PPRR
        if ( command == 4 || command == 6 ) {
          sch.PPRR() ;
          
          if ( command == 4 ) {
            sch.OutputFile_PPRR( fileName ) ;
            
          } // if()
          else {
            sch.SaveData( save_schedule, save_waiting, save_turnAround ) ;
            
          } // else
          
          sch.Initial() ;
          
        } // else if()
        
        // HRRN
        if ( command == 5 || command == 6 ) {
          sch.HRRN() ;
          
          if ( command == 5 ) {
            sch.OutputFile_HRRN( fileName ) ;
            
          } // if()
          else {
            sch.SaveData( save_schedule, save_waiting, save_turnAround ) ;
            
            sch.OutputFile_ALL( fileName, save_schedule, save_waiting, save_turnAround ) ;
            
          } // else
          
          sch.Initial() ;
          
        } // else if()
        
        sch.BigInitial() ;
        
      } // if()
      
    } // if()
    else {
      readFile = false ;
      
      cout << "Quit" << endl ;
      
    } // else
    
  } // while()
  
} // main()

