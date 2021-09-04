# include <iostream>
# include <string.h>
# include <vector>
# include <fstream> 

using namespace std ;

#define max 0x3f3f3f3f

class Page {
  vector < int > schedule ;
  vector < int > frame ;
  vector < vector <int> > record ;
  vector < char > fault_ch ; // �p�G F �A�N��T��o�� fault 
  
  vector <int> fault_output ;
  vector <vector < vector <int> >> record_output ;
  vector <vector < char >> fault_ch_output ;
  vector <int> replace_output ;
  
  int framework ; // ��ܮ�l�j�p 
  int fault = 0 ;
  int replace = 0 ;
  
  int ChToInt( char ch ) {
    return ch - 48 ;
    
  } // ChToInt()
  
  void MakeFrame() {
    for ( int i = 0 ; i < framework ; i ++ ) {
      frame.push_back( -1 ) ;
      
    } // for()
    
  } // MakeFrame()
  
  bool InTheFrame( int now ) {
    for ( int j = 0 ; j < frame.size() ; j++ ) {
      if ( now == frame.at( j ) ) {
        return true ;
        
      } // if()
      
    } // for()
    
    return false ;
    
  } // InTheFrame()
  
  void MoveFrameBackOne() {
    for ( int i = frame.size() - 1 ; i > 0 ; i-- ) {
      frame.at( i ) = frame.at( i - 1 ) ;
      
    } // for()
    
    frame.at( 0 ) = -1 ;
    
  } // MoveFrameBackOne()
  
  // �� now �q frame ������ �A �ç� now ��� frame �e�� 
  void MoveFrame_LRU( int now ) {
    for ( int i = 0 ; i < frame.size() ; i++ ) {
      if ( frame.at( i ) == now ) {
        frame.erase( frame.begin() + i ) ;
        
      } // if()
      
    } // for()
    
    frame.insert( frame.begin(), now ) ;
    
  } // MoveFrame_LRU()
  
public:
  
  void FIFO() {
    int now ; // �{�b�� schedule 
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      
      now = schedule.at( i ) ;
      
      // cout << "Time :" << i << endl ;
      // cout << "Now :" << now << endl ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        // cout << "In the frame" << endl ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        // cout << "Not in the frame" << endl ;
        
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
        } // if()
        
        // �� frame �����e�����Ჾ�@�� 
        MoveFrameBackOne() ;
        
        frame.at( 0 ) = now ;
        
        record.push_back( frame ) ;
        
      } // else
      
      // cout << frame[0] << frame[1] << frame[2] << endl ;
      // cout << frame.size() << endl ;
      
      // cout << endl ;
      
    } // for()
    
  } // FIFO()
  
  void FIFO_Show() {
    cout << "--------------FIFO-----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // FIFO_Show()
  
  void ShowRecord( int now ) {
    for ( int i = 0 ; i < framework ; i++ ) {
      if ( record.at( now ).at( i ) != -1 ) {
        cout << record.at( now ).at( i ) ;
        
      } // if()
      
    } // for()
    
  } // ShowRecord()
  
  bool IsInt( char ch ) {
    if ( ch >= 48 && ch <= 57 ) {
      return true ;
      
    } // if()
    
    return false ;
    
  } // IsInt()
  
  bool ReadFile( string fileName ) {
    FILE *infile = NULL ;
    char ch ; // �C�@�ӼƦr�A�]�� input ���O�s�b�@�_�A �ҥH�n�H�r�����覡Ū�J 
    int number ;  // �C�@�ӼƦr 
    
    fileName = fileName + ".txt" ;
    infile = fopen( fileName.c_str(), "r" ) ;
    
    if ( infile == NULL ) {
      cout << "\n###" << fileName << " does not exist!###\n\n" ;
      
      return false ;
      
    } // if()
    
    else {
      cout << "Success" << endl << endl ; 
      
      fscanf( infile, "%d", &framework ) ;
      
      // cout << "Framework : " << framework << endl ;
      
      while ( !feof(infile) ) {
        fscanf( infile, "%c", &ch ) ;
        
        if ( IsInt( ch ) && !feof(infile)  ) {
          number = ChToInt( ch ) ;
        
          schedule.push_back( number ) ;
          
          // cout << number << endl ;
          
        } // if()
        
      } // while()
      
      MakeFrame() ;
      
      return true ;
      
    } // else
    
  } // ReadFile()
  
  void Initial() {
    record.clear() ;
    fault_ch.clear() ;
    fault = 0 ;
    replace = 0 ;
    frame.clear() ;
    
    MakeFrame() ;
    
  } // Initial()
  
  void TotalInitial() {
    record.clear() ;
    fault_ch.clear() ;
    fault = 0 ;
    replace = 0 ;
    frame.clear() ;
    
    
    schedule.clear() ;
    framework = 0 ;
    
    fault_output.clear() ;
    record_output.clear() ;
    fault_ch_output.clear() ;
    replace_output.clear() ;
    
  } // TotalInitial()
  
  void LRU() {
    int now ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      now = schedule.at( i ) ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        MoveFrame_LRU( now ) ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
        } // if()
        
        // �� frame �����e�����Ჾ�@�� 
        MoveFrameBackOne() ;
        
        frame.at( 0 ) = now ;
        
        record.push_back( frame ) ;
        
      } // else
      
    } // for()
    
  } // LRU()
  
  void LRU_Show() {
    cout << "--------------LRU-----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // LRU_Show()

  void AddCounter_LFU_FIFO( int now, vector <int> &counter ) {
    
    for ( int i = 0 ; i < counter.size() ; i++ ) {
      if ( now == frame.at( i ) ) {
        counter.at( i ) = counter.at( i ) + 1 ;
        
      } // if()
      
    } // for()
    
  } // AddCounter_LFU_FIFO()

  // �q vector ����X�� min ���A�p�G���@�ˤj�N�^��-1 
  // �M��LFU_FIFO�]�p�A�p�G���n�X�ӳ̤p�� schedule 
  // �̫᭱���̤p���n�����A��L�Ҧ��� schedule ���N�� FIFO 
  int FindMin_LFU_FIFO( vector <int> &counter ) {
    int min_num = max ;
    int min_addr = -1 ;
    int same = 1 ;
    int temp ;
    int change ;
    
    for ( int i = counter.size() - 1 ; i > -1 ; i-- ) {
      if ( counter.at( i ) < min_num ) {
        min_num = counter.at( i ) ;
        min_addr = i ;
        
        same = 1 ;
        
      } // if()
      
      else if ( counter.at( i ) == min_num ) {
        same++ ;
        
      } // else if()
      
    } // for()
    
    if ( same == counter.size() ) {
      return -1 ;
      
    } // if()
    
    else {
      // cout << "IN" << endl ;
      // cout << counter.at( min_addr ) << endl ;
      
      frame.erase( frame.begin() + min_addr ) ;
      
      counter.erase( counter.begin() + min_addr ) ;
      
      frame.insert( frame.begin(), -1 ) ;
      
      counter.insert( counter.begin(), 0 ) ;
      
      /*
      cout << "Before" << endl ;
      cout << counter[0] << counter[1] << counter[2] << endl ;
      */
      
      return 0 ;
      
    } // else
    
  } // FindMin()

  // LFU + FIFO
  void LFU_FIFO() {
    int now ;
    vector <int> counter ;
    int min ;
    
    for ( int i = 0 ; i < framework ; i++ ) {
      counter.push_back( 0 ) ;
      
    } // for()
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      now = schedule.at( i ) ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        
        AddCounter_LFU_FIFO( now, counter ) ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        // frame ���� 
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
          min = FindMin_LFU_FIFO( counter ) ;
          
          // �������O�ۦP�� counter 
          if ( min == -1 ) {
            // counter ���Ჾ 
            for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
              counter.at( j ) = counter.at( j - 1 ) ;
              
            } // for()
            
            counter.at( 0 ) = 1 ;
            
            // ���� frame 
            MoveFrameBackOne() ;
          
            frame.at( 0 ) = now ;
            
          } // if()
          
          // ���̤p�� �άO ���ۦP���̤pcounter�u���ֳ��� 
          else {
            counter.at( 0 ) = 1 ;
            
            frame.at( 0 ) = now ;
            
          } // else
          
        } // if()
        
        // frame �S���� 
        else {
          // counter ���Ჾ 
          for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
            counter.at( j ) = counter.at( j - 1 ) ;
            
          } // for()
          
          counter.at( 0 ) = 1 ;
          
          // ���� frame
          MoveFrameBackOne() ;
          
          frame.at( 0 ) = now ;
          
        } // else
        
        record.push_back( frame ) ;
        
      } // else
      
    } // for()
    
    
  } // LFU_FIFO()
    
  void LFU_FIFO_Show() {
    cout << "--------------Least Frequently Used Page Replacement-----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // LFU_FIFO_Show()
  
  // �q vector ����X�� max ���A�p�G���@�ˤj�N�^��-1 
  // �M��MFU_FIFO�]�p�A�p�G���n�X�ӳ̤j�� schedule 
  // �̥k��̤j�������A�ѤU���� FIFO 
  int FindMin_MFU_FIFO( vector <int> &counter ) {
    int max_num = -1 ;
    int max_addr = -1 ;
    int same = 1 ;
    int temp ;
    int change ;
    
    for ( int i = counter.size() - 1 ; i > -1 ; i-- ) {
      if ( counter.at( i ) > max_num ) {
        max_num = counter.at( i ) ;
        max_addr = i ;
        
        same = 1 ;
        
      } // if()
      
      else if ( counter.at( i ) == max_num ) {
        same++ ;
        
      } // else if()
      
    } // for()
    
    if ( same == counter.size() ) {
      return -1 ;
      
    } // if()
    
    else {
      frame.erase( frame.begin() + max_addr ) ;
      
      counter.erase( counter.begin() + max_addr ) ;
      
      frame.insert( frame.begin(), -1 ) ;
      
      counter.insert( counter.begin(), 0 ) ;
      
      return max_addr ;
      
    } // else
    
  } // FindMin_MFU_FIFO()
  
  // MFU + FIFO
  void MFU_FIFO() {
    int now ;
    vector <int> counter ;
    int min ;
    
    for ( int i = 0 ; i < framework ; i++ ) {
      counter.push_back( 0 ) ;
      
    } // for()
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      now = schedule.at( i ) ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        
        AddCounter_LFU_FIFO( now, counter ) ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        // frame ���� 
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
          min = FindMin_MFU_FIFO( counter ) ;
          
          // ���ۦP�� counter 
          if ( min == -1 ) {
            // counter ���Ჾ 
            for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
              counter.at( j ) = counter.at( j - 1 ) ;
              
            } // for()
            
            counter.at( 0 ) = 1 ;
            
            // ���� frame 
            MoveFrameBackOne() ;
          
            frame.at( 0 ) = now ;
            
          } // if()
          
          // ���̤j�� 
          else {
            counter.at( 0 ) = 1 ;
            
            frame.at( 0 ) = now ;
            
          } // else
          
        } // if()
        
        // frame �S���� 
        else {
          // counter ���Ჾ 
          for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
            counter.at( j ) = counter.at( j - 1 ) ;
            
          } // for()
          
          counter.at( 0 ) = 1 ;
          
          // ���� frame
          MoveFrameBackOne() ;
          
          frame.at( 0 ) = now ;
          
        } // else
        
        record.push_back( frame ) ;
        
      } // else
      
    } // for()
    
    
  } // MFU_FIFO()
  
  void MFU_FIFO_Show() {
    cout << "--------------Most Frequently Used Page Replacement -----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // MFU_FIFO_Show()
  
  // LFU+LRU
  void LFU_LRU() {
    int now ;
    vector <int> counter ;
    int min ;
    
    for ( int i = 0 ; i < framework ; i++ ) {
      counter.push_back( 0 ) ;
      
    } // for()
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      now = schedule.at( i ) ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        
        AddCounter_LFU_LRU( now, counter ) ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        // frame ���� 
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
          min = FindMin_LFU_FIFO( counter ) ;
          
          // �������O�ۦP�� counter 
          if ( min == -1 ) {
            // counter ���Ჾ 
            for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
              counter.at( j ) = counter.at( j - 1 ) ;
              
            } // for()
            
            counter.at( 0 ) = 1 ;
            
            // ���� frame 
            MoveFrameBackOne() ;
          
            frame.at( 0 ) = now ;
            
          } // if()
          
          // ���̤p�� �άO ���ۦP���̤pcounter�u���ֳ��� 
          else {
            
            counter.at( 0 ) = 1 ;
            
            frame.at( 0 ) = now ;
            
            
          } // else
          
        } // if()
        
        // frame �S���� 
        else {
          // counter ���Ჾ 
          for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
            counter.at( j ) = counter.at( j - 1 ) ;
            
          } // for()
          
          counter.at( 0 ) = 1 ;
          
          // ���� frame
          MoveFrameBackOne() ;
          
          frame.at( 0 ) = now ;
          
        } // else
        
        record.push_back( frame ) ;
        
      } // else
      
      // cout << counter[0] << counter[1] << counter[2] << endl ;
      // cout << frame[0] << frame[1] << frame[2] << endl << endl  ;
      
    } // for()
    
    
  } // LFU_FIFO()
  
  void AddCounter_LFU_LRU( int now, vector <int> &counter ) {
    
    for ( int i = 0 ; i < counter.size() ; i++ ) {
      if ( now == frame.at( i ) ) {
        
        counter.at( i ) = counter.at( i ) + 1 ;
        
        counter.insert( counter.begin(), counter.at( i ) ) ;
        
        counter.erase( counter.begin() + i + 1 ) ;
        
        frame.insert( frame.begin(), frame.at( i ) ) ;
        
        frame.erase( frame.begin() + i + 1 ) ;
        
      } // if()
      
    } // for()
    
  } // AddCounter_LFU_FIFO()
  
  void LFU_LRU_Show() {
    cout << "--------------Least Frequently Used LRU Page Replacement-----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // MFU_FIFO_Show()
  
  void MFU_LRU() {
    int now ;
    vector <int> counter ;
    int min ;
    
    for ( int i = 0 ; i < framework ; i++ ) {
      counter.push_back( 0 ) ;
      
    } // for()
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      now = schedule.at( i ) ;
      
      // ���b frame �� 
      if ( InTheFrame( now ) ) {
        
        AddCounter_LFU_LRU( now, counter ) ;
        
        record.push_back( frame ) ;
        
        fault_ch.push_back( 'T' ) ;
        
      } // if()
      
      // �S���b frame �� 
      else {
        fault++ ;
        
        fault_ch.push_back( 'F' ) ;
        
        // frame ���� 
        if ( frame.at( frame.size() - 1 ) != -1 ) {
          replace++ ;
          
          min = FindMin_MFU_FIFO( counter ) ;
          
          // ���ۦP�� counter 
          if ( min == -1 ) {
            // counter ���Ჾ 
            for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
              counter.at( j ) = counter.at( j - 1 ) ;
              
            } // for()
            
            counter.at( 0 ) = 1 ;
            
            // ���� frame 
            MoveFrameBackOne() ;
          
            frame.at( 0 ) = now ;
            
          } // if()
          
          // ���̤j�� 
          else {
            counter.at( 0 ) = 1 ;
            
            frame.at( 0 ) = now ;
            
          } // else
          
        } // if()
        
        // frame �S���� 
        else {
          // counter ���Ჾ 
          for ( int j = counter.size() - 1 ; j > 0 ; j-- ) {
            counter.at( j ) = counter.at( j - 1 ) ;
            
          } // for()
          
          counter.at( 0 ) = 1 ;
          
          // ���� frame
          MoveFrameBackOne() ;
          
          frame.at( 0 ) = now ;
          
        } // else
        
        record.push_back( frame ) ;
        
      } // else
      
    } // for()
    
    
  } // MFU_LRU()
  
  void MFU_LRU_Show() {
    cout << "--------------Most Frequently Used LRU Page Replacement -----------------------" << endl ;
    
    for ( int i = 0 ; i < schedule.size() ; i++ ) {
      cout << schedule.at( i ) << "\t" ;
      
      ShowRecord( i ) ;
      
      if ( fault_ch.at( i ) == 'F' ) {
        cout << "\tF" << endl ;
        
      } // if()
      
      else {
        cout << endl ;
        
      } // else
      
    } // for()
    
    cout << "Page Fault = " << fault << "  " ;
    
    cout << "Page Replaces = " << replace << "  " ;
    
    cout << "Page Frames = " << framework << endl << endl ;
    
  } // MFU_LRU_Show()
  
  void SaveData() {
    fault_output.push_back( fault ) ;
    record_output.push_back( record ) ;
    fault_ch_output.push_back( fault_ch ) ;
    replace_output.push_back( replace ) ;
    
  } // SaveData()
  
  void OutputFile_ALL( string fileName ) {
    fileName = "out_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		for ( int j = 0 ; j < 6 ; j++ ) {
		  
		  if ( j == 0 ) {
		    outfile << "--------------FIFO-----------------------" << endl ;
		    
      } // if()
      
      else if ( j == 1 ) {
        outfile << "--------------LRU-----------------------" << endl ;
        
      } // else if()
      
      else if ( j == 2 ) {
        outfile << "--------------Least Frequently Used Page Replacement-----------------------" << endl ;
        
      } // else if()
      
      else if ( j == 3 ) {
        outfile << "--------------Most Frequently Used Page Replacement -----------------------" << endl ;
        
      } // else if()
      
      else if ( j == 4 ) {
        outfile << "--------------Least Frequently Used LRU Page Replacement-----------------------" << endl ;
        
      } // else if()
      
      else if ( j == 5 ) {
        outfile << "--------------Most Frequently Used LRU Page Replacement -----------------------" << endl ;
        
      } // else if()
		    
    
      for ( int i = 0 ; i < schedule.size() ; i++ ) {
        outfile << schedule.at( i ) << "\t" ;
        
        for ( int k = 0 ; k < framework ; k++ ) {
          if ( record_output.at( j ).at( i ).at( k ) != -1 ) {
            outfile << record_output.at( j ).at( i ).at( k ) ;
            
          } // if()
          
        } // for()
        
        if ( fault_ch_output.at( j ).at( i ) == 'F' ) {
          outfile << "\tF" << endl ;
          
        } // if()
        
        else {
          outfile << endl ;
          
        } // else
        
      } // for()
      
      outfile << "Page Fault = " << fault_output.at( j ) << "  " ;
      
      outfile << "Page Replaces = " << replace_output.at( j ) << "  " ;
      
      outfile << "Page Frames = " << framework << endl << endl ;
		  
    } // for()
    
    outfile.close() ;
    
  } // OutputFile_ALL()
  
  
  
}; // Page

int main() {
  string fileName ;
  Page page ;
  
  cout << "Please input file name :" << endl ;
  cout << "( Input 0 to exit. )" << endl ;
  
  cin >> fileName ;
  
  while ( fileName != "0" ) {
    
    page.TotalInitial() ;
    
    if ( page.ReadFile( fileName ) ) {
      
      
      // FIFO
      page.FIFO() ;
      
      // page.FIFO_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      // LRU
      page.LRU() ;
      
      // page.LRU_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      
      // LFU+FIFO
      page.LFU_FIFO() ;
      
      // page.LFU_FIFO_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      
      
      // MFU+FIFO
      page.MFU_FIFO() ;
      
      // page.MFU_FIFO_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      
      
      // LFU+LRU
      page.LFU_LRU() ;
      
      // page.LFU_LRU_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      
      // MFU+LRU 
      page.MFU_LRU() ;
      
      // page.MFU_LRU_Show() ;
      
      page.SaveData() ;
      
      page.Initial() ;
      
      
      page.OutputFile_ALL( fileName ) ;
      
    } // if()
    
    cout << "Please input file name :" << endl ;
    cout << "( Input 0 to exit. )" << endl ;
  
    cin >> fileName ;
    
  } // while()
  
} // main()
