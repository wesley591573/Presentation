# include <iostream>
# include <fstream> 
# include <vector>
# include <string>
# include <ctime>
# include <thread>
# include <chrono>
# include <unistd.h>
# include <math.h>
# include <time.h> // clock_gettime ��Ʃһݤ����Y��


#define max 0x3f3f3f3f

using namespace std ;

typedef vector<int> int_vct ;

int_vct allNum ;
vector <int_vct> intVctVct ; // ���ݭn����k�������p�@�ϥ�
vector <int_vct> originalIntVctVct ; //��l�ɮ� 
int_vct intVct ; // ��method1�s�񪺸�Ƶ��c 


struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

void BubbleSort( int_vct &num_vct ) {
  int switchNum ;
    
  for ( int i = 0 ; i < num_vct.size() ; i++ ) {
    for ( int j = i + 1 ; j < num_vct.size() ; j++ ) {
      if ( num_vct[i] > num_vct[j] ) {
        switchNum = num_vct[i] ;
        num_vct[i] = num_vct[j] ;
        num_vct[j] = switchNum ;
          
      } // if()
        
    } // for()
      
  } // for()
    
} // BubbleSort()

void MergeSort( int first, int second ) {
  int firstVct = intVctVct[first].size() ;
  int secondVct = intVctVct[second].size() ;
  int_vct result ;
  int_vct empty ;
  int firstLoc = 0 ; // �Ĥ@��list�ثe�Ҧb��m
  int secondLoc = 0 ;  // �ĤG��list�ثe�Ҧb��m
  
  intVctVct[first].push_back( max ) ;
  intVctVct[second].push_back( max ) ;
  
  /*
  cout << "Merge FirstVct size :" << firstVct << endl ;
  cout << "Merge Second size :" << secondVct << endl ;
  if ( intVctVct.size() == 3 ) {
    cout << "Merge Third size :" << intVctVct[2].size() << endl ;
    
  } // if()
  */
  
  for ( int i = 0 ; i < firstVct + secondVct ; i++ ) {
    if ( intVctVct[first][firstLoc] < intVctVct[second][secondLoc] ) {
      result.push_back( intVctVct[first][firstLoc] ) ;
      firstLoc++ ;
      
    } // if()
    else {
      result.push_back( intVctVct[second][secondLoc] ) ;
      secondLoc++ ;
      
    } // else
    
  } // for()
  
  
  
  intVctVct[first].swap(result) ;
  result.clear() ;
  result.shrink_to_fit() ;
  
  /*
  cout << "Merge Result : " << result.size() << endl ;
  cout << "Test0 : " << intVctVct[0].size() << endl ;
  cout << "Test1 : " << intVctVct[1].size() << endl ;
  if ( intVctVct.size() == 3 ) {
    cout << "Test2 : " << intVctVct[2].size() << endl ;
    
  } // if()
  */
  
} // MergeSort()

class OS {

public:
  bool GetFile( string fileName ) {
    int number ;
    fileName = fileName + ".txt" ;
    
    allNum.clear() ;
    
    ifstream fin( fileName.c_str() ) ;
    if ( !fin ) {
      cout << "Fail" << endl ;
      
      return false ;
      
    } // if()
    
    else {
      cout << "Success" << endl << endl ; 
      
      while ( fin >> number ) {
        allNum.push_back( number ) ;
        
      } // while()
      
      return true ;
      
    } // else
    
    
  } // GetFile()

  // �ھ�cut�Ӭݭn�����X�� 
  void Seperate( int cut ) {
    int_vct eachVct ;
    int nowInt = 0 ; // �����{�b���˨�ĴX��integer 
    
    int intNum = allNum.size() / cut ; // �C�@���ҥ]�t��integer�ƶq 
    
    if ( allNum.size() % cut > 0 ) {
      intNum++ ;
      
    } // if() 
    
    intVctVct.clear() ;
    
    for ( int i = 0 ; i < cut ; i++ ) {
      // ���靈�㰣�����p  
      if ( allNum.size() >= nowInt + intNum && ( i < allNum.size() % cut || allNum.size() % cut == 0 ) ) {
        
        for ( int j = nowInt ; j < nowInt + intNum ; j++ ) {
          eachVct.push_back( allNum[j] ) ;
          
        } // for()
        
        intVctVct.push_back( eachVct ) ;
        
        eachVct.clear() ;
        
        nowInt = nowInt + intNum ;
        
      } // if()
      
      // ����|�����㰣�����p  
      else {
        if ( i == allNum.size() % cut ) {
          intNum-- ;
          
        } // if()
        
        for ( int j = nowInt ; j < nowInt + intNum ; j++ ) {
          eachVct.push_back( allNum[j] ) ;
          
        } // for()
        
        nowInt = nowInt + intNum ;
        
        intVctVct.push_back( eachVct ) ;
        
        eachVct.clear() ;
        
      } // else
      
    } // for()
    
  } // Seperate()
  
  void Thread() {
    vector <thread> threads ;
    vector <thread> empty ; // �Ū�thread vector 
    int_vct empty_int ;
    int intVctVct_size ;
    
    // BubbleSort�����D 
    for ( int i = 0 ; i < intVctVct.size() ; i++ ) {
      threads.push_back( thread( BubbleSort, ref( intVctVct[i] ) ) ) ; 
       
    } // for()
    
    for ( int i = 0 ; i < threads.size() ; i++ ) {
      threads[i].join() ;
      
    } // for()
    
    threads.swap( empty ) ;
    empty.clear() ;
    empty.shrink_to_fit() ;
    
    // Merge������ 
    while ( intVctVct.size() != 1 ) {
      
      for ( int i = 0 ; i + 1 < intVctVct.size() ; i = i + 2 ) {
        threads.push_back( thread( MergeSort, i, i+1 ) ) ;
        
      } // for()
      
      // �@��thread�u����intVctVct��������ơA�Ӥ����ܸ�Ƶ��c�A
      // �קK�o�ͦP�ɦh��thread�ק��Ƶ��c�ɭP�����D 
      for ( int i = 0 ; i < threads.size() ; i++ ) {
        if ( threads[i].joinable() ) {
          threads[i].join() ;
          
        } // if()
        
      } // for()
      
      intVctVct_size = intVctVct.size() ;
      
      // �qintVctVct���A�M���L�Ϊ�int_vct����Ƶ��c 
      for ( int i = intVctVct_size - 1 ; i > 0 ; i = i - 2 ) {
        if ( i == intVctVct_size - 1 ) {
          if ( i % 2 == 0 ) {
            i = i - 1 ;
            
          } // if()
          
        } // if()
        
        intVctVct[i].swap( empty_int ) ;
        intVctVct.erase( intVctVct.begin() + i ) ;
        empty_int.clear() ;
        empty_int.shrink_to_fit() ;
        
      } // for()
      
      threads.swap( empty ) ;
      empty.clear() ;
      empty.shrink_to_fit() ;
      
    } // while()
    
  } // Thread()
  
  void TestShowSep() {
    for ( int i = 0 ; i < intVctVct.size() ; i++ ) {
      for ( int j = 0 ; j < intVctVct[i].size() ; j++ ) {
        cout << intVctVct[i][j] << endl ;
        
      } // for()
      
      cout << "----------------------------------" << endl ;
      
    } // for()
    
  } // TestShowSep()
  
  void TestShowThread() {
    
    for ( int i = 0 ; i < intVctVct.size() ; i++ ) {
      for ( int j = 0 ; j < intVctVct[i].size() ; j++ ) {
        cout << intVctVct.at( i ).at( j ) << endl ;
        
      } // for()
      
      cout << "----------------------------------" << endl ;
      cout << "There is the size " << intVctVct[i].size() << endl ;
      
    } // for()
    
  } // TestShowThread()
  
  bool InputCut( int &cut ) {
    
    cout << "**************************" << endl ;
    cout << "**Please input Cut" << endl ;
    cout << "**************************" << endl ;
    
    cin >> cut ;
    
    if ( cut <= 0 || cut > allNum.size() ) {
      cout << "Input Cut Error" << endl ;
      
      return false ;
      
    } // if()
    
    else {
      return true ;
      
    } // else
    
  } // InputCut()
  
  void SingleProcess() {
    int_vct empty_int ;
    int intVctVct_size ; // �M�����lintVctVct��size 
    
    // BubbleSort()
    for ( int i = 0 ; i < intVctVct.size() ; i++ ) {
      BubbleSort( intVctVct[i] ) ;
      
    } // for()
    
    while ( intVctVct.size() != 1 ) {
    
      // ���վ��Ƶ��c��MergeSort()
      for ( int i = 0 ; i + 1 < intVctVct.size() ; i = i + 2 ) {
        MergeSort( i, i + 1 ) ;
        
      } // for()
      
      intVctVct_size = intVctVct.size() ;
      
      // ��h�l����Ƶ��c���� 
      for ( int i = intVctVct_size - 1 ; i > 0 ; i = i - 2 ) {
        if ( i == intVctVct_size - 1 ) {
          if ( i % 2 == 0 ) {
            i = i - 1 ;
              
          } // if()
            
        } // if()
          
        intVctVct[i].swap( empty_int ) ;
        intVctVct.erase( intVctVct.begin() + i ) ;
        empty_int.clear() ;
        empty_int.shrink_to_fit() ;
          
      } // for()
    
    } // while()
    
  } // singleProcess()
  
  void WriteFile() {
    
    
  } // WriteFile()
  
  void TestShow() {
    for ( int i = 0 ; i < intVct.size() ; i++ ) {
      cout << intVct[i] << endl ;
      
    } // for()
    
  } // TestShow()
  
  void ShowTime( int start, int end ) {
    // ����e�t�Ϊ���e���/�ɶ� 
    time_t now = time(0);

    tm *ltm = localtime(&now);
    
    cout << "CPU Time : " << end - start << " ms" << endl ;
    
    cout << "Output Time : " << 1900 + ltm->tm_year ;
    cout << "-" << 1 + ltm->tm_mon ;
    cout << "-" << ltm->tm_mday << " " ;
    cout << ltm->tm_hour << ":" ;
    cout << ltm->tm_min << ":" ;
    cout << ltm->tm_sec << endl ;
    
  } // ShowTime()
  
  int_vct ReturnVct() {
    return allNum ;
    
  } // returnVct()
  
  void Test() {
    int_vct temp ;
    vector <thread> threads ;
    vector <thread> empty ;
    
    for ( int i = 0 ; i < allNum.size() ; i++ ) {
      temp.clear() ;
      temp.push_back( allNum[i] ) ;
      intVctVct.push_back( temp ) ;
      
    } // for()
    
    int intVctVct_size = intVctVct.size() ;
    
    while ( intVctVct.size() != 1 ) {
      // cout << "Here is a intVctVct_size : " << intVctVct_size << endl ;
      
      for ( int i = 0 ; i + 1 < intVctVct_size ; i = i + 2 ) {
        // cout << i << endl ;
        threads.push_back( thread( MergeSort, i, i+1 ) ) ;
        // cout << "After push back" << endl ;
        
      } // for()
      
      // cout << "Out of for" << endl ;
      
      for ( int i = 0 ; i < threads.size() ; i++ ) {
        // cout << i << endl ;
        threads[i].join() ;
        // cout << "After join" << endl ;
      
      } // for()
      
      threads.swap(empty) ;
      empty.clear() ;
      empty.shrink_to_fit() ;
      
      // cout << "Test" << endl ;
      
      intVctVct_size = intVctVct.size() / 2 ;
    
    } // while()
    
  } // Test()
  
  void OutputFile( string fileName, double time_used, char method ) {
    time_t now = time(0);

    tm *ltm = localtime(&now);
    
		fileName = fileName + "_output" + method + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		if ( method == '1' ) {
		  for ( int i = 0 ; i < intVct.size() ; i++ ) {
		    outfile << intVct.at(i) << endl ;
		    
      } // for()
		  
    } // if()
		
		else {
		  for ( int i = 0 ; i < intVctVct.at(0).size() ; i++ ) {
		    outfile << intVctVct.at(0).at(i) << endl ;
		    
      } // for()
		  
    } // else
		
		outfile << "CPU Time : " << time_used * 1000 << endl ;
		
		outfile << "Output Time : " << 1900 + ltm->tm_year ;
    outfile << "-" << 1 + ltm->tm_mon ;
    outfile << "-" << ltm->tm_mday << " " ;
    outfile << ltm->tm_hour << ":" ;
    outfile << ltm->tm_min << ":" ;
    outfile << ltm->tm_sec << endl ;
		
		outfile.close() ;
		
	} // OutpurFile()
  
  void Initial( int command ) {
    if ( command == 1 ) {
      intVctVct.clear() ;
      intVctVct.shrink_to_fit() ;
      
      intVctVct = originalIntVctVct ;
      
    } // if ()
    
    else if ( command == 2 ) {
      intVct.clear() ;
      intVct.shrink_to_fit() ;
      
    } // else if ()
    
  } // initial()
  
  void MultiProcess() {
    pid_t pid ;
  
    pid = fork() ;
    int_vct empty_int ;
    int intVctVct_size ;
    
    for ( int i = 0 ; i < intVctVct.size() ; i++ ) {
      if ( pid == 0 ) {
        // cout << "Child Process" << endl ;
        
        BubbleSort( intVctVct[i] ) ;
        
        pid = fork() ;
        
      } // if()
      else {
        // cout << "Parent Process" << endl ; 
        
        // BubbleSort( intVctVct[1] ) ;
        exit(0) ;
        
      } // else
      
    } // for()
    
    if ( pid != 0 ) {
      // cout << "Parent Process" << endl ; 
        
      // BubbleSort( intVctVct[1] ) ;
      exit(0) ;
        
    } // if()
    
    while ( intVctVct.size() != 1 ) {
        
        for ( int i = 0 ; i + 1 < intVctVct.size() ; i = i + 2 ) {
          if ( pid == 0 ) {
            // cout << "Child Process" << endl ;
            
            MergeSort( i, i + 1 ) ;
            
            pid = fork() ;
            
          } // if()
          else {
            // cout << "Parent Process" << endl ; 
            
            // BubbleSort( intVctVct[1] ) ;
            exit(0) ;
            
          } // else
          
        } // for()
        
        if ( pid != 0 ) {
          // cout << "Parent Process" << endl ; 
            
          // BubbleSort( intVctVct[1] ) ;
          exit(0) ;
            
        } // if()
        
        
        intVctVct_size = intVctVct.size() ;
        
        // �qintVctVct���A�M���L�Ϊ�int_vct����Ƶ��c 
        for ( int i = intVctVct_size - 1 ; i > 0 ; i = i - 2 ) {
          if ( i == intVctVct_size - 1 ) {
            if ( i % 2 == 0 ) {
              i = i - 1 ;
              
            } // if()
            
          } // if()
          
          intVctVct[i].swap( empty_int ) ;
          intVctVct.erase( intVctVct.begin() + i ) ;
          empty_int.clear() ;
          empty_int.shrink_to_fit() ;
          
        } // for()
        
      } // while()
  
  } // MultiProcess()
  
};

int main() {
  string fileName ;
  OS os ;
  int command = -1 ;
  bool readFile = false ;
  int cut = 0 ; // �ݭn�����X�� 
  struct timespec temp ;
  
  struct timespec start, end;
  long double time_used;
  
  while ( fileName != "0" ) {
    cout << "�п�J�ɮצW�� : " << endl ;
    cout << "( ��J0��ܵ��� )" << endl ; 
    
    cin >> fileName ;
    
    readFile = false ;
    
    if ( fileName != "0" ) {
      readFile = os.GetFile( fileName ) ;
      
    } // if()
    else {
      readFile = false ;
      
      cout << "Quit" << endl ;
      
    } // else
      
    if ( readFile ) {
      // Method 1, 2, 3, 4
      if( os.InputCut( cut ) ) {
        // Method 1
        intVct = os.ReturnVct() ;
        // �p��}�l�ɶ�
        clock_gettime( CLOCK_MONOTONIC, &start ) ;
        BubbleSort( intVct ) ;
        // �p�⵲���ɶ�
        clock_gettime( CLOCK_MONOTONIC, &end ) ;
        
        // �p���ڪ�O�ɶ�
        temp = diff(start, end);
        time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0 ;
              
        os.OutputFile( fileName, time_used, '1' ) ;
        
        os.Initial( 2 ) ;
        
        // Method 2, 3, 4
        os.Seperate( cut ) ;
            
        cout << endl << endl ;
        
        originalIntVctVct = intVctVct ;
        
        // Method 2  
        // �p��}�l�ɶ�
        clock_gettime(CLOCK_MONOTONIC, &start);
        os.Thread() ;
        // �p�⵲���ɶ�
        clock_gettime(CLOCK_MONOTONIC, &end);
            
        // �p���ڪ�O�ɶ�
        temp = diff(start, end);
        time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
            
        os.OutputFile( fileName, time_used, '2' ) ;
            
        os.Initial( 1 ) ;
        
        
        // Method 3
        // �p��}�l�ɶ�
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        
        os.MultiProcess() ;
        
        
        // �p�⵲���ɶ�
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        // �p���ڪ�O�ɶ�
        temp = diff(start, end);
        time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0;
            
        os.OutputFile( fileName, time_used, '3' ) ;
            
        os.Initial( 1 ) ;
        
        // Method 4
        // �p��}�l�ɶ�
        clock_gettime(CLOCK_MONOTONIC, &start);
        os.SingleProcess() ;
        // �p�⵲���ɶ�
        clock_gettime(CLOCK_MONOTONIC, &end);
            
            
        // �p���ڪ�O�ɶ�
        temp = diff(start, end) ;
        time_used = temp.tv_sec + (double) temp.tv_nsec / 1000000000.0 ;
            
        os.OutputFile( fileName, time_used, '4' ) ;
          
        os.Initial( 1 ) ;
          
      } // if()
        
    } // if()
    
  } // while()
  
} // main()
