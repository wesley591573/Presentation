# include <iostream>
# include <fstream>
# include <vector>
# include <string.h>
# include <sstream>
# include <algorithm>
# include <math.h>
# include <cstdlib>

using namespace std ;
 
struct tokenLoc{
	int table ;
	int loc ;
};

struct literal{
	int table ;
	int loc ;
	int loc_mach ; // 在翻譯過後的地址  
	
};

typedef vector<tokenLoc> tokenLocVct ;

// 指令集 
vector <tokenLocVct> data ;
// 原始code 
vector <string> stringList ;
vector <string> stringList_vice ;

// OPCode
vector <string> OPCode ;

// 所有的Table
// instruction 
vector <string> Table1 ;
// pseudo code
vector <string> Table2 ;
// register
vector <string> Table3 ;
// 存所有的Delimiter 
vector <string> Table4 ;
	
// symbol
vector <string> Table5 ;
// integer
vector <string> Table6 ;
// string
vector <string> Table7 ;

/*---------------------------------------------*/

void getTable() ; // 把Table檔讀入

void scanLine() ; // 把每一行的指令看過一遍 

void scanALine() ; // 把一行的指令看過一遍 

/*---------------------------------------------*/

void getData( string fileName ) ; // 讀檔和儲存資料 

void testShow() ; // 確認stringList有沒有確實存入strings

void outputData( string fileName ) ; // 寫檔 

/*---------------------------------------------*/


static int sixteenTo10( string num ) {
		int outputNum = 0 ;
		
		for( int i = 0 ; i < num.size() ; i++ ) {
			
			if( num[i] >= 48 && num[i] <= 57 ) {
				
				outputNum = outputNum + ( num[i] - 48 ) * pow( 16, num.size() - 1 - i ) ;
				
			} // if()
			
			else {
				
				outputNum = outputNum + ( num[i] - 55 ) * pow( 16, num.size() - 1 - i ) ;
				
			} // else
			
		} // for()
		
		return outputNum ;
		
	} // sixteenTo10()

	// 10進位轉16進位 
static string tenTo16( int num ) {
		string tenTo16_res = "" ;
		stringstream ss ;
		
		while( num / 16 != 0 ) {
			ss.str("") ;
			
			if( num % 16 == 10 ) {
				tenTo16_res = "A" + tenTo16_res ;
				
			} // if()
			
			else if( num % 16 == 11 ) {
				tenTo16_res = "B" + tenTo16_res ;
				
			} // else if()
			
			else if( num % 16 == 12 ) {
				tenTo16_res = "C" + tenTo16_res ;
				
			} // else if()
			
			else if( num % 16 == 13 ) {
				tenTo16_res = "D" + tenTo16_res ;
				
			} // else if()
			
			else if( num % 16 == 14 ) {
				tenTo16_res = "E" + tenTo16_res ;
				
			} // else if()
			
			else if( num % 16 == 15 ) {
				tenTo16_res = "F" + tenTo16_res ;
				
			} // else if()
			
			else {
				ss << num % 16 ;
				tenTo16_res = ss.str() + tenTo16_res ;
				
			} // else
			
			num = num / 16 ;
			
		} // while()
		
		ss.str("") ;
		ss << num ;
		
		if( num % 16 == 10 ) {
			tenTo16_res = "A" + tenTo16_res ;
				
		} // if()
			
		else if( num % 16 == 11 ) {
			tenTo16_res = "B" + tenTo16_res ;
				
		} // else if()
			
		else if( num % 16 == 12 ) {
			tenTo16_res = "C" + tenTo16_res ;
				
		} // else if()
			
		else if( num % 16 == 13 ) {
			tenTo16_res = "D" + tenTo16_res ;
				
		} // else if()
			
		else if( num % 16 == 14 ) {
			tenTo16_res = "E" + tenTo16_res ;
				
		} // else if()
			
		else if( num % 16 == 15 ) {
			tenTo16_res = "F" + tenTo16_res ;
				
		} // else if()
		else {
			tenTo16_res = ss.str() + tenTo16_res ;
			
		} // else 
		
		return tenTo16_res ;
		
	} // tenTo16()

class Token{
	tokenLocVct line ;
	
	// 儲存各個指令 
	vector <string> result ;
	
	void scanLine() {
		for( int i = 0 ; i < stringList.size() ; i++ ) {
			scanALine( i ) ;
			
		} // for()
		
	} // scanLine()
	
	void scanALine( int lineNum ) {
		string nowToken = "" ;
		string tokenNum ; // 一整行的token結果
		bool X = false ; // 處理X'FF' 
		
		string returnString ; // 把findTokenNum的值接住 
		
		for( int i = 0 ; i < stringList[lineNum].size() ; i++ ) {
			
			// 是Delimiter 
			if( isDelimiter( stringList[lineNum][i] )  ) {
				
				// 處理String Table 
				
				// 如果碰到引號的處理方法 
				if( strcmp( returnString.c_str(), "(4,9)" ) == 0 && strcmp( nowToken.c_str(), "" ) != 0 ) {
					if( X ) {
						returnString = hashFunction( nowToken, 6 ) ;
					
						tokenNum = tokenNum + returnString ;
					
						nowToken.clear() ;
					
						X = false ;
					
						i-- ;
						
					} // if()
					
					else {
						returnString = hashFunction( nowToken, 7 ) ;
					
						tokenNum = tokenNum + returnString ;
					
						nowToken.clear() ;
					
						i-- ;
						
					} // else()
					
				} // if()
				
				else if( !nowToken.empty() ) {
					if( strcmp( nowToken.c_str(), "X" ) == 0 || strcmp( nowToken.c_str(), "x" ) == 0 ) {
						X = true ;
						
						nowToken.clear() ;
						
						i-- ;
						
					} // if()
					else if( strcmp( nowToken.c_str(), "C" ) == 0 || strcmp( nowToken.c_str(), "c" ) == 0 ) {
						
						nowToken.clear() ;
						
						i-- ;
						
					} // else if()
					
					else {
						returnString =  findTokenNum( nowToken ) ;
						 
						tokenNum = tokenNum + returnString ;
						
						nowToken.clear() ;
						
						i-- ;
						
					} // else
					
				} // else if()
				
				else {
					nowToken = nowToken + stringList[lineNum][i] ;
					
					returnString =  findTokenNum( nowToken ) ;
					
					tokenNum = tokenNum + returnString ;
					
					nowToken.clear() ;
					
					// 處理註解 
					if( strcmp( returnString.c_str(), "(4,10)" ) == 0 ) {
						i = stringList[lineNum].size() ;
						
					} // if()
					
				} // else
				
			} // if()
			
			// 遇到空白
			 
			else if( stringList[lineNum][i] == ' ' || stringList[lineNum][i] == '\t' ) {
				
				if( !nowToken.empty() ) {
					
					returnString =  findTokenNum( nowToken ) ;
					
					tokenNum = tokenNum + returnString ;
					
					nowToken.clear() ;
					
				} // if()
				
			} // else if()
			
			else {
				
				nowToken = nowToken + stringList[lineNum][i] ;
				
			} // else
			
		} // for()
		
		if( !nowToken.empty() ) {
			returnString =  findTokenNum( nowToken ) ;
			
			tokenNum = tokenNum + returnString ;
			
			nowToken.clear() ;
			
		} // if()
		
		result.push_back(tokenNum) ;
		
		data.push_back(line) ;
		
		line.clear() ;
		
	} // scanAline()
	
	bool isDelimiter( char ch ) {
		for( int i = 0 ; i < Table4.size() ; i++ ) {
			if( ch == Table4[i][0] ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // isDelimiter
	
	string findTokenNum( string s ) {
		string result = "" ;
		stringstream ss ;
		string lower = turnToLower( s ) ;
		string upper = turnToUpper( s ) ;
		struct tokenLoc input ;
		
		for( int i = 0 ; i < Table1.size() ; i++ ) {
			if( strcmp( s.c_str(), Table1[i].c_str() ) == 0 || strcmp( lower.c_str(), Table1[i].c_str() ) == 0 ) {
				ss << i + 1 ;
				
				result = ss.str() ;
				
				result = "(1," + result + ")" ;
				
				input.table = 1 ;
				input.loc = i + 1 ;
				
				line.push_back(input) ;
				
				return result ;
				
			} // if()
			
		} // for()
		
		for( int i = 0 ; i < Table2.size() ; i++ ) {
			if( strcmp( s.c_str(), Table2[i].c_str() ) == 0 || strcmp( upper.c_str(), Table2[i].c_str() ) == 0 ) {
				ss << i + 1 ;
				
				result = ss.str() ;
				
				result = "(2," + result + ")" ;
				
				input.table = 2 ;
				input.loc = i + 1 ;
				
				line.push_back(input) ;
				
				return result ;
				
			} // if()
			
		} // for()
		
		for( int i = 0 ; i < Table3.size() ; i++ ) {
			if( strcmp( s.c_str(), Table3[i].c_str() ) == 0 || strcmp( upper.c_str(), Table3[i].c_str() ) == 0 ) {
				ss << i + 1 ;
				
				result = ss.str() ;
				
				result = "(3," + result + ")" ;
				
				input.table = 3 ;
				input.loc = i + 1 ;
				
				line.push_back(input) ;
				
				return result ;
				
			} // if()
			
		} // for()
		
		for( int i = 0 ; i < Table4.size() ; i++ ) {
			if( strcmp( s.c_str(), Table4[i].c_str() ) == 0 ) {
				ss << i + 1 ;
				
				result = ss.str() ;
				
				result = "(4," + result + ")" ;
				
				input.table = 4 ;
				input.loc = i + 1 ;
				
				line.push_back(input) ;
				
				return result ;
				
			} // if()
			
		} // for()
		
		// Interger
		if( s[0] >= 48 && s[0] <= 57 ) {
			
			result = hashFunction( s, 6 ) ;
			
			return result ;
			
		} // if()
		
		// Label
		else {
			
			result = hashFunction( s, 5 ) ;
			
			return result ;
			
		} // else
		
		
	} // findTokenNum()
	
	string turnToUpper( string s ) {
		for( int i = 0 ; i < s.size() ; i++ ) {
			if( s[i] >= 97 && s[i] <= 122 ) {
				s[i] = s[i] - 32 ;
				
			} // if()
			
		} // for()
		
		return s ;
		
	} // turnToUpper
	
	string turnToLower( string s ) {
		for( int i = 0 ; i < s.size() ; i++ ) {
			if( s[i] >= 65 && s[i] <= 90 ) {
				s[i] = s[i] + 32 ;
				
			} // if()
			
		} // for()
		
		return s ;
		
	} // turnToLower
	
	string hashFunction( string s, int tableNum ) {
		int hashNum = 0 ;
		int indexNum = 0 ;
		string result = "" ;
		stringstream ss ;
		string tableNumStr ;
		struct tokenLoc input ;
		
		if( !tableIsFull( tableNum ) ) {
			for( int i = 0 ; i < s.size() ; i++ ) {
				hashNum = hashNum + s[i] ;
				
			} // for()
			
			indexNum = hashNum % 100 ;
			
			while( collision( indexNum, tableNum, s ) ) {
				if( indexNum == 100 ) {
					indexNum = indexNum - 100 ;
					
				} // if()
				
				indexNum = indexNum + 1 ;
				
			} // while()
			
			
			if( tableNum == 5 ) {
				Table5[indexNum] = s ;
				
			} // if()
			
			else if( tableNum == 6 ) {
				string special = turnToUpper( s ) ;
				
				Table6[indexNum] = special ;
				
			} // else if()
			
			else if( tableNum == 7 ) {
				Table7[indexNum] = s ;
				
			} // else if()
			
			
			ss << indexNum ;
					
			result = ss.str() ;
			
			ss.str("") ;
			
			ss << tableNum ;
			
			tableNumStr = ss.str() ;
			
			result = "(" + tableNumStr + "," + result + ")" ;
			
			input.table = tableNum ;
			input.loc = indexNum ;
				
			line.push_back(input) ;
			
			return result ;
			
		} // if()
		
		else {
			ss.str("") ;
			
			ss << tableNum ;
			
			tableNumStr = ss.str() ;
			
			result = "( Table" + tableNumStr + " is full! )" ;
			
			return result ;
			
		} // else
		
	} // hashFunction()
	
	bool collision( int indexNum, int tableNum, string s ) {
		
		if( tableNum == 5 ) {
			
			if( strcmp( Table5[indexNum].c_str(), "-591573" ) == 0 || strcmp( Table5[indexNum].c_str(), s.c_str() ) == 0 ) {
				
				return false ;
				
			} // if()
			else {
				
				return true ;
				
			} // else
			
		} // if()
		
		else if( tableNum == 6 ) {
			// X'F1'和X'f1'相同
			 
			string special = turnToUpper( s ) ;
			
			if( strcmp( Table6[indexNum].c_str(), "-591573" ) == 0 || strcmp( Table6[indexNum].c_str(), special.c_str() ) == 0 ) {
				return false ;
				
			} // if()
			else {
				return true ;
				
			} // else
			
		} // if()
		
		else if( tableNum == 7 ) {
			if( strcmp( Table7[indexNum].c_str(), "-591573" ) == 0 || strcmp( Table7[indexNum].c_str(), s.c_str() ) == 0 ) {
				return false ;
				
			} // if()
			else {
				return true ;
				
			} // else
			
		} // if()
		
	} // collision()
	
	
	bool tableIsFull( int tableNum ) {
		for( int i = 0 ; i < 100 ; i++ ) {
			if( tableNum == 5 ) {
				if( strcmp( Table5[i].c_str(), "-591573" ) == 0 ) {
					return false ;
					
				} // if()
				
			} // if()
			
			else if( tableNum == 6 ) {
				if( strcmp( Table6[i].c_str(), "-591573" ) == 0 ) {
					return false ;
					
				} // if()
				
			} // else if()
			
			else if( tableNum == 7 ) {
				if( strcmp( Table7[i].c_str(), "-591573" ) == 0 ) {
					return false ;
					
				} // if()
				
			} // else if()
			
		} // for()
		
		return true ;
		
	} // tableIsFull()
	
public:
	void getTable() {
		ifstream fin1( "Table1.table" ) ;
		string s ;
		
		while( fin1 >> s ) {
			Table1.push_back( s ) ;
			
			
		} // while()
		
		ifstream fin2( "Table2.table" ) ;
		
		while( fin2 >> s ) {
			Table2.push_back( s ) ;
			
			
		} // while()
		
		ifstream fin3( "Table3.table" ) ;
		
		while( fin3 >> s ) {
			Table3.push_back( s ) ;
			
		} // while()
		
		ifstream fin4( "Table4.table" ) ;
		
		while( fin4 >> s ) {
			Table4.push_back( s ) ;
			
		} // while()
		
	} // getTable()
	
	void getData( string fileName ) {
	
		fileName = fileName + ".txt" ;
		
		ifstream fin( fileName.c_str() ) ;
	    string s;
	    
	    if( fin ) {
	    	while( getline(fin,s) ) {
	        
		        stringList.push_back( s ) ;
		        stringList_vice.push_back( s ) ;
		        
		    } // while()
		    
		    initialTable567() ;
		    
		    scanLine() ;
	    	
		} // if()
		else {
			cout << "There is no such file." << endl ;
			
		} // else
		
		fin.close() ;
		
		
	} // getData ()
	
	
	void testShow() {
		cout << "There are all strings :" << endl ;
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			for( int j = 0 ; j < data[i].size() ; j++ ) {
				cout << "( " << data[i][j].table << ", " << data[i][j].loc << " )" ;
				
			} // for()
			
			cout << endl ;
		} // for()
		
	} // show()
	
	void outputData( string fileName ) {
		fileName = "MyOutput_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		if( outfile ) {
			for( int i = 0 ; i < stringList.size() ; i++ ) {
				outfile << stringList[i] << endl ;
				
				outfile << result[i] << endl ;
				
			} // for()
			
		} // if()
		
		
		outfile.close() ;
		
	} // outputData()
	
	void initialTable567() {
		string str = "-591573" ;
		
		for( int i = 0 ; i < 100 ; i++ ) {
			Table5.push_back( str ) ;
			Table6.push_back( str ) ;
			Table7.push_back( str ) ;
			
		} // for()
		
	} // initialTable()
	
	void initialAll() {
		stringList.clear() ;
		result.clear() ;
		stringList_vice.clear() ;
		
	} // initialAll()
	
}; // class Token

class SIC{
	int nowLoc = 0 ;
	bool END = false ;
	
	vector <int> locate ;
	vector <string> OBCode ;
	
	vector <int> forwardTable ;
	
	void initialLiteral() {
		if( forwardTable.size() != 100 ) {
			for( int i = 0 ; i < 100 ; i++ ) {
				forwardTable.push_back(-591573) ;
				
			} // for()
			
		} // if()
		
		else {
			for( int i = 0 ; i < 100 ; i++ ) {
				forwardTable[i] = -591573 ;
				
			} // for()
			
		} // else
		
	} // initialLiteral()
	
	void makeOPCode() {
		OPCode.push_back( "" ) ;
		OPCode.push_back( "18" ) ;
		OPCode.push_back( "58" ) ;
		OPCode.push_back( "90" ) ;
		OPCode.push_back( "40" ) ;
		OPCode.push_back( "B4" ) ;
		OPCode.push_back( "28" ) ;
		OPCode.push_back( "88" ) ;
		OPCode.push_back( "A0" ) ;
		OPCode.push_back( "24" ) ;
		OPCode.push_back( "64" ) ;
		OPCode.push_back( "9C" ) ;
		OPCode.push_back( "C4" ) ;
		OPCode.push_back( "C0" ) ;
		OPCode.push_back( "F4" ) ;
		OPCode.push_back( "3C" ) ;
		OPCode.push_back( "30" ) ;
		OPCode.push_back( "34" ) ;
		OPCode.push_back( "38" ) ;
		OPCode.push_back( "48" ) ;
		OPCode.push_back( "00" ) ;
		OPCode.push_back( "68" ) ;
		OPCode.push_back( "50" ) ;
		OPCode.push_back( "70" ) ;
		OPCode.push_back( "08" ) ;
		OPCode.push_back( "6C" ) ;
		OPCode.push_back( "74" ) ;
		OPCode.push_back( "04" ) ;
		OPCode.push_back( "D0" ) ;
		OPCode.push_back( "20" ) ;
		OPCode.push_back( "60" ) ;
		OPCode.push_back( "98" ) ;
		OPCode.push_back( "C8" ) ;
		OPCode.push_back( "44" ) ;
		OPCode.push_back( "D8" ) ;
		OPCode.push_back( "AC" ) ;
		OPCode.push_back( "4C" ) ;
		OPCode.push_back( "A4" ) ;
		OPCode.push_back( "A8" ) ;
		OPCode.push_back( "F0" ) ;
		OPCode.push_back( "EC" ) ;
		OPCode.push_back( "0C" ) ;
		OPCode.push_back( "78" ) ;
		OPCode.push_back( "54" ) ;
		OPCode.push_back( "80" ) ;
		OPCode.push_back( "D4" ) ;
		OPCode.push_back( "14" ) ;
		OPCode.push_back( "7C" ) ;
		OPCode.push_back( "E8" ) ;
		OPCode.push_back( "84" ) ;
		OPCode.push_back( "10" ) ;
		OPCode.push_back( "1C" ) ;
		OPCode.push_back( "5C" ) ;
		OPCode.push_back( "94" ) ;
		OPCode.push_back( "B0" ) ;
		OPCode.push_back( "E0" ) ;
		OPCode.push_back( "F8" ) ;
		OPCode.push_back( "2C" ) ;
		OPCode.push_back( "B8" ) ;
		OPCode.push_back( "DC" ) ;
		
	} // makeOPCode()

	
	// 判斷lineIndex這一行有沒有文法錯誤 
	bool isSyntaxError( int lineIndex ) {
		if( data[lineIndex].size() >= 2 && data[lineIndex][0].table == 5 ) {
			if( data[lineIndex][1].table == 1 && data[lineIndex][2].table == 5 ) {
				return false ;
				
			} // if()
			
			else if( data[lineIndex][1].table == 2 && data[lineIndex][2].table == 6 ) {
				return false ;
				
			}  // else if()
			
			else if( data[lineIndex].size() >= 3 && data[lineIndex][1].table == 2 && 
					( data[lineIndex][3].table == 6 || data[lineIndex][3].table == 7) ) {
				return false ;
						
			} // else if()
			
		} // if
		
		else if( data[lineIndex].size() >= 1 && data[lineIndex][0].table == 1 ) {
			if( data[lineIndex].size() == 2 && data[lineIndex][1].table == 5 ) {
				return false ;
				
			} // if()
			
			else if( data[lineIndex].size() == 1 ) {
				return false ;
				
			} // else if()
			
		} // else if()
		
		else if( data[lineIndex].size() >= 1 && data[lineIndex][0].table == 2 ) {
			if( data[lineIndex].size() == 2 && ( data[lineIndex][1].table == 6 || data[lineIndex][1].table == 5 ) ) {
				return false ;
				
			}  // else if()
			
			else if( data[lineIndex].size() == 2 && 
					( data[lineIndex][2].table == 6 || data[lineIndex][2].table == 7) ) {
				return false ;
						
			} // else if()
			
			else if( data[lineIndex].size() == 1 ) {
				return false ;
				
			} // else if()
			
		} // else if()
		
		else {
			return true ;
			
		} // else
		
	} // syntaxError()
	
	void table1( int lineIndex, int tokenIndex, string &inputOBCode ) {
		
		if( data[lineIndex].size() >= 2 && forwardTable[data[lineIndex][tokenIndex + 1].loc] != -591573 ) {
			
			// 有,X的情況 
			if( data[lineIndex].size() >= 4 && 
				( data[lineIndex][tokenIndex + 3].loc == 2 && data[lineIndex][tokenIndex + 3].table == 3 ) ) {
				inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] 
							+ tenTo16( forwardTable[data[lineIndex][tokenIndex + 1].loc] + 32768 ) ;
				
			} // if()
			
			else {
				inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] 
							+ tenTo16( forwardTable[data[lineIndex][tokenIndex + 1].loc] ) ;
				
			} // else
			
			
		} // if()
		
		else if( data[lineIndex].size() == 1 ) {
			inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] + "0000" ;
			
		} // else if()
		
		nowLoc = nowLoc + 3 ;
		
	} // table1()

public:	
	void table2( int lineIndex, int tokenIndex, string &inputOBCode ) {
		// START
		if( data[lineIndex][tokenIndex].loc == 1 ) {
			nowLoc = sixteenTo10( Table6[ data[lineIndex][tokenIndex + 1].loc ] ) ;
			locate.push_back( nowLoc ) ; 
			
		} // if()
		
		// END
		else if( data[lineIndex][tokenIndex].loc == 2 ) {
			END = true ;
			locate.pop_back() ;
			
		} // else if()
		
		// BYTE
		else if( data[lineIndex][tokenIndex].loc == 3 ) {
			
			// integer，兩個hex為一個byte  
			if( data[lineIndex][tokenIndex + 2].table == 6 ) {
				inputOBCode = Table6[ data[lineIndex][tokenIndex + 2].loc ] ;
				
				nowLoc = nowLoc + Table6[ data[lineIndex][tokenIndex + 2].loc ].size() / 2 ;
				
			} // if()
			
			// string，一個字元為一個byte 
			else if( data[lineIndex][tokenIndex + 2].table == 7 ) {
				for( int i = 0 ; i < Table7[ data[lineIndex][tokenIndex + 2].loc ].size() ; i++ ) {
					inputOBCode = inputOBCode + tenTo16( Table7[ data[lineIndex][tokenIndex + 2].loc ][i] ) ;

					
				} // for()
				
				nowLoc = nowLoc + Table7[ data[lineIndex][tokenIndex + 2].loc ].size() ;
				
			} // if()
			
		} // else if()
		
		// WORD
		else if( data[lineIndex][tokenIndex].loc == 4 ) {
			inputOBCode = tenTo16( atoi( Table6[data[lineIndex][tokenIndex+1].loc].c_str() ) ) ;
			
			while( inputOBCode.size() < 6 ) {
				inputOBCode = "0" + inputOBCode ;
				
			} // while()
			
			nowLoc = nowLoc + 3 ;
			
		} // else if()
		
		// RESB
		else if( data[lineIndex][tokenIndex].loc == 5 ) {
			
			nowLoc = nowLoc + atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() )  ;
			
		} // else if()
		
		// RESW
		else if( data[lineIndex][tokenIndex].loc == 6 ) {
			nowLoc = nowLoc + 3 * atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() ) ;
			
		} // else if()
		// EQU
		else if( data[lineIndex][tokenIndex].loc == 7 ) {
			nowLoc = atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() ) ;
			
		} // else if()
		// BASE
		else if( data[lineIndex][tokenIndex].loc == 8 ) {
			
			
		} // else if()
		// LTORG
		else if( data[lineIndex][tokenIndex].loc == 9 ) {
			
			
		} // else if()
		
	} // talbe2
	
	void pass1() {
		// 表示現在正處理到第幾個token 
		string inputOBCode ;
		
		makeOPCode() ;
		initialLiteral() ;
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			inputOBCode = "" ;
			
			if( strcmp( stringList[i].c_str(), "" ) == 0 || ( data[i][0].table == 4 && data[i][0].loc == 10 ) ) {
				if( locate.size() == 0 || END ) {
					locate.push_back( -591573 ) ;
					
				} // if()
				else {
					locate.insert( locate.end() - 1, -591573 ) ;
					
				} // else
				
				OBCode.push_back( "" ) ;
				
			} // if()
			
			else if( strcmp( stringList[i].c_str(), "" ) != 0 && !isSyntaxError( i ) ) {
				for( int j = 0 ; j < data[i].size() ; j++ ) {
					if( data[i][j].table == 1 ) {
						table1( i, j, inputOBCode ) ;
						
						OBCode.push_back( inputOBCode ) ;
						
						locate.push_back( nowLoc ) ;
						
						break ;
						
					} // if()
					
					else if( data[i][j].table == 2 ) {
						table2( i, j, inputOBCode ) ;
						
						OBCode.push_back( inputOBCode ) ;
						
						// END不用幫下一行決定地址 
						if( data[i][j].loc == 2 ) {
							locate.push_back( -591573 ) ;
							
						} // if()
						else {
							locate.push_back( nowLoc ) ;
							
						} // else
						
						break ;
						
					} // else if()
					
					else if( data[i][j].table == 5 ) {
						forwardTable[ data[i][j].loc ] = nowLoc ;
						
						
					} // else if()
					
					
				} // for() 
				
			} // else if()
			
		} // for()
		
	} // pass1()
	
	void pass2() {
		string inputOBCode = "" ;
		
		for( int i = 0 ; i < OBCode.size() ; i++ ) {
			if( strcmp( OBCode[i].c_str(), "" ) == 0 ) {
				
				if( data[i].size() > 0 && data[i][data[i].size() - 1].table == 5 && data[i][data[i].size() - 2].table == 1 ) {
					
					inputOBCode = OPCode[data[i][data[i].size() - 2].loc] 
								  + tenTo16( forwardTable[data[i][data[i].size() - 1].loc] ) ;
					
					OBCode[i] = inputOBCode ;
					
				} // if()
				
			} // if()
			
		} // for()
		
	} // pass2
	
	void testShow() {
		cout << "The all result are : " << endl ;
		
		for( int i = 0 ; i < stringList.size() ; i++ ) {
			if( locate[i] != -591573 ) {
				cout << "[" << i << "] " << "Locate:" << tenTo16( locate[i] ) << endl ;
				
			} // if()
			
			else {
				cout << "" << endl ;
				
			} // else
			
			cout << stringList[i] << endl ;
			
			if( strcmp( OBCode[i].c_str(), "" ) != 0 ) {
				cout << OBCode[i] << endl ;
				
			} // if()
			
			cout << endl ;
			
		} // for()
		
		cout << "There are bugs : " << endl ;
		
		for( int i = 0 ; i < OBCode.size() ; i++ ) {
			cout << OBCode[i] << endl ;
			
		} // for()
		
		cout << locate.size() << endl ;
		cout << stringList.size() << endl ;
		cout << OBCode.size() << endl ;
		
	} // testShow()
	
	void initialAll() {
		nowLoc = 0 ;
		END = false ;
		
		initialLiteral() ;
		locate.clear() ;
		OBCode.clear() ;
		data.clear() ;
		OPCode.clear() ;
		
	} // initial()
	
	void outputData( string fileName ) {
		int lineNum = 5 ;
		
		fileName = "SIC_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		if( outfile ) {
			outfile << "Line\tLoc\tSource statement\t\tObject code" << endl ;
			
			for( int i = 0 ; i < stringList.size() ; i++ ) {
				if( strcmp( stringList[i].c_str(), "" ) != 0 ) {
					outfile << lineNum << "\t" ;
					
					lineNum = lineNum + 5 ;
				
				} // if()
				
				if( locate[i] != -591573 ) {
					outfile << tenTo16( locate[i] ) << "\t" ;
					
				} // if()
			
				outfile << stringList[i] << "\t" ;
				outfile << OBCode[i]<< endl ;
				
			} // for()
			
		} // if()
		
		
		outfile.close() ;
		
	} // outputData()
	
};

class SICXE{
	literal baseRegister ;
	
	vector<int> format ;
	int nowLoc = 0 ;
	bool END = false ;
	
	vector <int> locate ;
	vector <string> locate_str ;
	vector <string> OBCode ;
	
	vector <int> forwardTable ;
	vector <literal> literalTable ;
	vector <string> OPCode ;
	
	void initialLiteral() {
		literal tool ;
		tool.loc = -591573 ;
		tool.loc_mach = -591573 ;
		tool.table = -591573 ;
		
		if( forwardTable.size() != 100 ) {
			for( int i = 0 ; i < 100 ; i++ ) {
				forwardTable.push_back(-591573) ;
				literalTable.push_back( tool ) ;
				
			} // for()
			
		} // if()
		
		else {
			for( int i = 0 ; i < 100 ; i++ ) {
				forwardTable[i] = -591573 ;
				literalTable[i].loc = -591573 ;
				literalTable[i].loc_mach = -591573 ;
				literalTable[i].table = -591573 ;
				
			} // for()
			
		} // else
		
	} // initialLiteral()

	void makeFormat() {
		format.push_back( 0 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 1 ) ;
		format.push_back( 1 ) ;
		format.push_back( 1 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 1 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 2 ) ;
		format.push_back( 1 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		format.push_back( 1 ) ;
		format.push_back( 3 ) ;
		format.push_back( 2 ) ;
		format.push_back( 3 ) ;
		
	} // makeFormat()
	
	void makeOPCode() {
		OPCode.push_back( "" ) ;
		OPCode.push_back( "18" ) ;
		OPCode.push_back( "58" ) ;
		OPCode.push_back( "90" ) ;
		OPCode.push_back( "40" ) ;
		OPCode.push_back( "B4" ) ;
		OPCode.push_back( "28" ) ;
		OPCode.push_back( "88" ) ;
		OPCode.push_back( "A0" ) ;
		OPCode.push_back( "24" ) ;
		OPCode.push_back( "64" ) ;
		OPCode.push_back( "9C" ) ;
		OPCode.push_back( "C4" ) ;
		OPCode.push_back( "C0" ) ;
		OPCode.push_back( "F4" ) ;
		OPCode.push_back( "3C" ) ;
		OPCode.push_back( "30" ) ;
		OPCode.push_back( "34" ) ;
		OPCode.push_back( "38" ) ;
		OPCode.push_back( "48" ) ;
		OPCode.push_back( "00" ) ;
		OPCode.push_back( "68" ) ;
		OPCode.push_back( "50" ) ;
		OPCode.push_back( "70" ) ;
		OPCode.push_back( "08" ) ;
		OPCode.push_back( "6C" ) ;
		OPCode.push_back( "74" ) ;
		OPCode.push_back( "04" ) ;
		OPCode.push_back( "D0" ) ;
		OPCode.push_back( "20" ) ;
		OPCode.push_back( "60" ) ;
		OPCode.push_back( "98" ) ;
		OPCode.push_back( "C8" ) ;
		OPCode.push_back( "44" ) ;
		OPCode.push_back( "D8" ) ;
		OPCode.push_back( "AC" ) ;
		OPCode.push_back( "4C" ) ;
		OPCode.push_back( "A4" ) ;
		OPCode.push_back( "A8" ) ;
		OPCode.push_back( "F0" ) ;
		OPCode.push_back( "EC" ) ;
		OPCode.push_back( "0C" ) ;
		OPCode.push_back( "78" ) ;
		OPCode.push_back( "54" ) ;
		OPCode.push_back( "80" ) ;
		OPCode.push_back( "D4" ) ;
		OPCode.push_back( "14" ) ;
		OPCode.push_back( "7C" ) ;
		OPCode.push_back( "E8" ) ;
		OPCode.push_back( "84" ) ;
		OPCode.push_back( "10" ) ;
		OPCode.push_back( "1C" ) ;
		OPCode.push_back( "5C" ) ;
		OPCode.push_back( "94" ) ;
		OPCode.push_back( "B0" ) ;
		OPCode.push_back( "E0" ) ;
		OPCode.push_back( "F8" ) ;
		OPCode.push_back( "2C" ) ;
		OPCode.push_back( "B8" ) ;
		OPCode.push_back( "DC" ) ;
		
	} // makeOPCode()
	
	// 判斷lineIndex這一行有沒有文法錯誤 
	bool isSyntaxError( int lineIndex ) {
		if( data[lineIndex].size() >= 2 && data[lineIndex][0].table == 5 ) {
			if( data[lineIndex][1].table == 1 && data[lineIndex][2].table == 5 ) {
				return false ;
				
			} // if()
			
			else if( data[lineIndex][1].table == 2 && data[lineIndex][2].table == 6 ) {
				return false ;
				
			}  // else if()
			
			else if( data[lineIndex].size() >= 3 && data[lineIndex][1].table == 2 && 
					( data[lineIndex][3].table == 6 || data[lineIndex][3].table == 7) ) {
				return false ;
						
			} // else if()
			
		} // if
		
		else if( data[lineIndex].size() >= 1 && data[lineIndex][0].table == 1 ) {
			if( data[lineIndex].size() == 2 && data[lineIndex][1].table == 5 ) {
				return false ;
				
			} // if()
			
			else if( data[lineIndex].size() == 1 ) {
				return false ;
				
			} // else if()
			
		} // else if()
		
		else if( data[lineIndex].size() >= 1 && data[lineIndex][0].table == 2 ) {
			if( data[lineIndex].size() == 2 && ( data[lineIndex][1].table == 6 || data[lineIndex][1].table == 5 ) ) {
				return false ;
				
			}  // else if()
			
			else if( data[lineIndex].size() == 2 && 
					( data[lineIndex][2].table == 6 || data[lineIndex][2].table == 7) ) {
				return false ;
						
			} // else if()
			
			else if( data[lineIndex].size() == 1 ) {
				return false ;
				
			} // else if()
			
		} // else if()
		
		else {
			return true ;
			
		} // else
		
	} // syntaxError()
	
	void table1( int lineIndex, int tokenIndex, string &inputOBCode ) {
		stringstream ss ;
		
		// format 1
		if( format[data[lineIndex][tokenIndex].loc] == 1 ) {
			
			inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] ;
			
			nowLoc = nowLoc + 1 ;
			
		} // if()
		
		// format 2
		else if( format[data[lineIndex][tokenIndex].loc] == 2 ) {
			
			if( data[lineIndex][tokenIndex + 1].table == 3 ) {
				ss << data[lineIndex][tokenIndex + 1].loc - 1  ;
			
				inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] + ss.str() ;
				
				ss.str("") ;	
				
			} // if()
			
			else {
			
				inputOBCode = OPCode[data[lineIndex][tokenIndex].loc] + Table6[data[lineIndex][tokenIndex + 1].loc] ;
				
			} // else
			
			// 有第二個register 
			if( data[lineIndex].size() > tokenIndex + 2 && data[lineIndex][tokenIndex + 2].table == 4 
				&& data[lineIndex][tokenIndex + 2].loc == 1 ) {
				ss << data[lineIndex][tokenIndex + 3].loc - 1 ;

				
				inputOBCode = inputOBCode + ss.str() ;
				
				ss.str("") ;	
				
			} // if()
			
			else {
				inputOBCode = inputOBCode + "0" ; 
				
			} // else
			
			nowLoc = nowLoc + 2 ;
			
		} // else if()
		
		// format 4
		else if( format[data[lineIndex][tokenIndex].loc] == 3 && tokenIndex >= 1 
				&& data[lineIndex][tokenIndex-1].table == 4 && data[lineIndex][tokenIndex-1].loc == 2  ) {
			
			int haveSign = 0 ;
			
			// 處理n, i 
			if( haveAt( lineIndex, tokenIndex ) ) {
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "2", 0 ) ;
				
				haveSign++ ;
				
			} // if()
			
			else if( havePoundSign( lineIndex, tokenIndex ) ) {
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "1", 0 ) ;
				
				haveSign++ ;
				
			} // else if()
			
			else {
				
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "3", 0 ) ;
				
				
			} // else
			
			while( inputOBCode.size() < 2 ) {
				inputOBCode = "0" + inputOBCode ;
				
			} // while()
			
			
			// 處理x, b, p, e 
			if( haveX( lineIndex, tokenIndex ) ) {
				inputOBCode = inputOBCode + "9" ;
				
			} // if()
			else {
				inputOBCode = inputOBCode + "1" ;
				
			} // else
			
			// 下一個是backward reference 的Label 
			if( forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] != -591573 && data[lineIndex][tokenIndex + haveSign + 1].table == 5 ) {
				string addr = tenTo16( forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] ) ;
			
				while( addr.size() < 5 ) {
					addr = "0" + addr ;
					
				}  // while
				
				inputOBCode = inputOBCode + addr ;
				
			} // if()
			
			// 下一個是forward reference 的Label 
			else if( forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] == -591573 && data[lineIndex][tokenIndex + haveSign + 1].table == 5 ) {
				inputOBCode = "" ;
				
			} // else if()
			
			// 下一個是Literal 
			else if( data[lineIndex][tokenIndex + 1 + haveSign].table == 4 && data[lineIndex][tokenIndex + 1 + haveSign].loc == 11 ) {
				int addr = findLiteral( data[lineIndex][tokenIndex + 3 + haveSign].table, data[lineIndex][tokenIndex + 3 + haveSign].loc ) ;
				
				
				if( addr != -2 && addr != -1 ) {
					string addr_str = tenTo16( addr ) ;
				
					while( addr_str.size() < 5 ) {
						addr_str = "0" + addr_str ;
						
					}  // while
					
					inputOBCode = inputOBCode + addr_str ;
					
				} // if()
				
				else if( addr == -2 )  {
					insertLiteralTable( data[lineIndex][tokenIndex + 3 + haveSign].table, data[lineIndex][tokenIndex + 3 + haveSign].loc, -1 ) ;
					
					inputOBCode = "" ;
					
				} // else
				else if( addr == -1 ) {
					inputOBCode = "" ;
					
				} // else
				
			} // else if()
			
			// 後面直接接integer 
			else if( data[lineIndex][tokenIndex + 1 + haveSign].table == 6 ) {
				
				string integer = tenTo16( atoi( Table6[data[lineIndex][tokenIndex + 1 + haveSign].loc].c_str() ) ) ;
				
				while( integer.size() < 5 ) {
					integer = "0" + integer ;
					
				} // while()
				
				inputOBCode = inputOBCode + integer ;
				
			} // else if()
			
			// 後面甚麼都沒有 
			else if( tokenIndex == data[lineIndex].size() - 1 || ( data[lineIndex][tokenIndex + 1 + haveSign].table == 4 && data[lineIndex][tokenIndex + 1 + haveSign].loc == 10 ) ) {
				inputOBCode = inputOBCode + "00000" ;
				
			} // else if()
			
			nowLoc = nowLoc + 4 ;
			
		} // else if() // format4
		
		// format 3
		else if( format[data[lineIndex][tokenIndex].loc] == 3 ) {
			int haveSign = 0 ;
			
			// 處理n, i 
			if( haveAt( lineIndex, tokenIndex ) ) {
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "2", 0 ) ;
				
				haveSign++ ;
				
			} // if()
			
			else if( havePoundSign( lineIndex, tokenIndex ) ) {
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "1", 0 ) ;
				
				haveSign++ ;
				
			} // else if()
			
			else {
				inputOBCode = cal16bits( OPCode[data[lineIndex][tokenIndex].loc], "3", 0 ) ;
				
			} // else
			
			
			while( inputOBCode.size() < 2 ) {
				inputOBCode = "0" + inputOBCode ;
				
			} // while()
			
			
			// 處理x,b,p,e和disp 
			if( data[lineIndex][tokenIndex + 1 + haveSign].table == 5 && forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] != -591573 ) {
				int xbpe = 0 ;
				string disp ;
				
				int disp_int = forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] - nowLoc - 3 ;
				int disp_base = forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] - baseRegister.loc_mach ;
				
				if( -2048 <= disp_int && disp_int <= 2047 ) {
					xbpe = xbpe + 2 ;
					
					disp = cal16bits( tenTo16( forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] ), tenTo16( nowLoc + 3 ), 1 ) ;
					
				} // if()
				
				else if( disp_base >= 0 && disp_base <= 4095 ) {
					// cout << "OverFlow" << endl ;
					// cout << "BaseRegister" << tenTo16( baseRegister.loc_mach ) << endl ;
					xbpe = xbpe + 2 * 2 ;
					
					if( baseRegister.loc_mach != -1 ) {
						disp = cal16bits( tenTo16( forwardTable[data[lineIndex][tokenIndex + 1 + haveSign].loc] ), tenTo16( baseRegister.loc_mach ), 1 ) ;
						
					} // if()
					else {
						inputOBCode = "" ;
						
					} // else
					
				} // else if()
				
				if( inputOBCode != "") {
					// 有X 
					if( haveX( lineIndex, tokenIndex ) ) {
						xbpe = xbpe + 8 ;
						
					} // if()
					
					string xbpe_str = tenTo16( xbpe ) ;
					
					while( disp.size() < 3 ) {
						disp = "0" + disp ;
						
					} // while()
					
					inputOBCode = inputOBCode + xbpe_str + disp ;
				
				} // if()
				
			} // if()
			
			// 後面直接接integer  
			else if( data[lineIndex][tokenIndex + 1 + haveSign].table == 6 ) {
				
				string integer = tenTo16( atoi( Table6[data[lineIndex][tokenIndex + 1 + haveSign].loc].c_str() ) ) ;
				
				inputOBCode = inputOBCode + "0" ;
				
				while( integer.size() < 3 ) {
					integer = "0" + integer ;
					
				} // while()
				
				inputOBCode = inputOBCode + integer ;
				
			} // else
			
			// 後面接literal
			else if( data[lineIndex][tokenIndex + 1 + haveSign].table == 4 && data[lineIndex][tokenIndex + haveSign + 1].loc == 11 ) {
				
				//cout << "Literal" << endl ;
				//cout << stringList[lineIndex] << endl ;
				
				int xbpe = 0 ;
				
				int addr = findLiteral( data[lineIndex][tokenIndex + haveSign + 3].table, data[lineIndex][tokenIndex + haveSign + 3].loc ) ;
				
				if( addr == -2 ) {
					insertLiteralTable( data[lineIndex][tokenIndex + haveSign + 3].table, data[lineIndex][tokenIndex + haveSign + 3].loc, -1 ) ;
					
					inputOBCode = "" ;
					
				} // if()
				
				else if( addr != -1 ) {
					string disp = cal16bits( tenTo16( findLiteral( data[lineIndex][tokenIndex + haveSign + 3].table, data[lineIndex][tokenIndex + haveSign + 3].loc ) ), tenTo16( nowLoc + 3 ), 1 ) ;
					
					int disp_int = findLiteral( data[lineIndex][tokenIndex + haveSign + 3].table, data[lineIndex][tokenIndex + haveSign + 3].loc ) - nowLoc - 3 ;
					
					if( -2048 <= disp_int && disp_int <= 2047 ) {
						xbpe = xbpe + 2 ;
						
					} // if()
					
					else {
						xbpe = xbpe + 2 * 2 ;
						
					} // else
					
					// 有X 
					if( haveX( lineIndex, tokenIndex ) ) {
						xbpe = xbpe + 8 ;
						
					} // if()
					
					string xbpe_str = tenTo16( xbpe ) ;
					
					while( disp.size() < 3 ) {
						disp = "0" + disp ;
						
					} // while()
					
					inputOBCode = inputOBCode + xbpe_str + disp ;
					
				} // else
				
				else if( addr == -1 ) {
					inputOBCode = "" ;
					
				} // else if()
				
			} // else if()
			
			// 後面甚麼都沒有 
			else if( tokenIndex == data[lineIndex].size() - 1 || ( data[lineIndex][tokenIndex + 1 + haveSign].table == 4 && data[lineIndex][tokenIndex + 1 + haveSign].loc == 10 ) ) {
				inputOBCode = inputOBCode + "0000" ;
					
			} // else if()
			
			else {
				inputOBCode = "" ;
				
			} // else
			
			nowLoc = nowLoc + 3 ;
			
		} // else if() // format3
		
	} // table1()
	
	string cal16bits( string A, string B, int sign ) {
		int a = sixteenTo10( A ) ;
		int b = sixteenTo10( B ) ;
		
		// 加法 
		if( sign == 0 ) {
			a = a + b ;
			
		} // if()
		
		else if( sign == 1 ) {
			a = a - b ;
			
			if( a < 0 ) {
				a = pow( 16, 3 ) + a ;
				
			} // if()
			
		} // else if()
		
		return tenTo16( a ) ;
		
	} // cal16bits()
	
	bool haveX( int lineNum, int tokenNum ) {
		for( int i = tokenNum ; i < data[lineNum].size() ; i++ ) {
			if( data[lineNum][i].table == 3 && data[lineNum][i].loc == 2 ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // haveX()
	
	// 是否有小老鼠@ 
	bool haveAt( int lineNum, int tokenNum ) {
		for( int i = tokenNum ; i < data[lineNum].size() ; i++ ) {
			if( data[lineNum][i].table == 4 && data[lineNum][i].loc == 13 ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // haveAt()
	
	//是否有井字號# 
	bool havePoundSign( int lineNum, int tokenNum ) {
		for( int i = tokenNum ; i < data[lineNum].size() ; i++ ) {
			if( data[lineNum][i].table == 4 && data[lineNum][i].loc == 12 ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // havePoundSign()
	
public:
	void table2( int lineIndex, int tokenIndex, string &inputOBCode ) {
		// START
		if( data[lineIndex][tokenIndex].loc == 1 ) {
			nowLoc = sixteenTo10( Table6[ data[lineIndex][tokenIndex + 1].loc ] ) ;
			
			locate.push_back( nowLoc ) ; 
			
		} // if()
		
		// END
		else if( data[lineIndex][tokenIndex].loc == 2 ) {
			END = true ;
			locate.pop_back() ;
			locate.push_back(-591573) ;
			
			
			for( int i = 0 ; i < literalTable.size() ; i++ ) {
				
				if( literalTable[i].loc_mach == -1 ) {
					
					locate.push_back( nowLoc ) ;
					OBCode.push_back( inputOBCode ) ;
					
					string newStr = "*\t" ;
					
					if( literalTable[i].table == 7 ) {
						newStr = newStr + "=C'" + Table7[literalTable[i].loc] + "'" ;
						
						for( int j = 0 ; j < Table7[literalTable[i].loc].size() ; j++ ) {
							inputOBCode = inputOBCode + tenTo16( Table7[literalTable[i].loc][j] ) ;
		
							
						} // for()
						
					} // if()
					
					else {
						newStr = newStr + "=X'" + Table6[literalTable[i].loc] + "'" ;
						
						inputOBCode = Table6[literalTable[i].loc] ;
						
					} // else 
					
					stringList_vice.insert( stringList_vice.begin() + lineIndex + definedLiteral() + 1, newStr ) ;
					
					// cout << "///////////////////" << newStr << endl ;
					
					literalTable[i].loc_mach = nowLoc ;
					
					if( literalTable[i].table == 6 ) {
						nowLoc = nowLoc + Table6[literalTable[i].loc].size() / 2 ;
						
					} // if()
					
					else {
						nowLoc = nowLoc + Table7[literalTable[i].loc].size() ;
						
					} // else
					
				} // if()
				
			} // for()
			
		} // else if()
		
		// BYTE
		else if( data[lineIndex][tokenIndex].loc == 3 ) {
			
			// integer，兩個hex為一個byte  
			if( data[lineIndex][tokenIndex + 2].table == 6 ) {
				inputOBCode = Table6[ data[lineIndex][tokenIndex + 2].loc ] ;
				
				nowLoc = nowLoc + Table6[ data[lineIndex][tokenIndex + 2].loc ].size() / 2 ;
				
			} // if()
			
			// string，一個字元為一個byte 
			else if( data[lineIndex][tokenIndex + 2].table == 7 ) {
				for( int i = 0 ; i < Table7[ data[lineIndex][tokenIndex + 2].loc ].size() ; i++ ) {
					inputOBCode = inputOBCode + tenTo16( Table7[ data[lineIndex][tokenIndex + 2].loc ][i] ) ;

					
				} // for()
				
				nowLoc = nowLoc + Table7[ data[lineIndex][tokenIndex + 2].loc ].size() ;
				
			} // if()
			
		} // else if()
		
		// WORD
		else if( data[lineIndex][tokenIndex].loc == 4 ) {
			inputOBCode = tenTo16( atoi( Table6[data[lineIndex][tokenIndex+1].loc].c_str() ) ) ;
			
			while( inputOBCode.size() < 6 ) {
				inputOBCode = "0" + inputOBCode ;
				
			} // while()
			
			nowLoc = nowLoc + 3 ;
			
		} // else if()
		
		// RESB
		else if( data[lineIndex][tokenIndex].loc == 5 ) {
			
			nowLoc = nowLoc + atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() )  ;
			
		} // else if()
		
		// RESW
		else if( data[lineIndex][tokenIndex].loc == 6 ) {
			nowLoc = nowLoc + 3 * atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() ) ;
			
		} // else if()
		// EQU
		else if( data[lineIndex][tokenIndex].loc == 7 ) {
			if( data[lineIndex][tokenIndex + 1].table == 6 ) {
				locate.pop_back() ;
				
				locate.push_back(atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() )) ;
				
				forwardTable[data[lineIndex][tokenIndex - 1].loc] = atoi( Table6[ data[lineIndex][tokenIndex + 1].loc].c_str() ) ;
				
			} // if()
			
			else if( data[lineIndex][tokenIndex + 1].loc == 4 && data[lineIndex][tokenIndex + 1].table == 4 ) {
				
				
			} // else if()
			
			else if( data[lineIndex][tokenIndex + 1].table == 5 ) {
				int loc = nowLoc ;
				
				nowLoc = forwardTable[ data[lineIndex][tokenIndex + 1].loc ] ;
				
				for( int i = tokenIndex + 1 ; i < data[lineIndex].size() ; i++ ) {
					if( data[lineIndex][i].table == 4 ) {
						// +
						if( data[lineIndex][i].loc == 2 ) {
							nowLoc = nowLoc + forwardTable[ data[lineIndex][i + 1].loc ] ;
							
						} // if()
						else if( data[lineIndex][i].loc == 3 ) {
							nowLoc = nowLoc - forwardTable[ data[lineIndex][i + 1].loc ] ;
							
						} // else if()
						
						
					} // if()
				
				} // for()
				
				locate.pop_back() ;
				
				locate.push_back( nowLoc ) ;
				
				forwardTable[data[lineIndex][tokenIndex - 1].loc] = nowLoc ;
				
				nowLoc = loc ;
				
			} // else if()
			
		} // else if()
		
		
		// BASE
		else if( data[lineIndex][tokenIndex].loc == 8 ) {
			baseRegister.loc_mach = findLiteral( data[lineIndex][tokenIndex + 1].table, data[lineIndex][tokenIndex + 1].loc ) ;
			baseRegister.loc = data[lineIndex][tokenIndex + 1].loc ;
			baseRegister.table = data[lineIndex][tokenIndex + 1].table ;
			
			locate.pop_back() ;
				
			locate.push_back( -591573 ) ;
			
		} // else if()
		
		// LTORG
		else if( data[lineIndex][tokenIndex].loc == 9 ) {
			if( undefinedLiteral() != 0 ) {
			
				locate.pop_back() ;
					
				locate.push_back( -591573 ) ;
				
				
				// 計算這一梯次的literal definition的數量 
				for( int i = 0 ; i < literalTable.size() ; i++ ) {
					
					if( literalTable[i].loc_mach == -1 ) {
						
						locate.push_back( nowLoc ) ;
						OBCode.push_back( inputOBCode ) ;
						
						string newStr = "*\t" ;
						
						if( literalTable[i].table == 7 ) {
							newStr = newStr + "=C'" + Table7[literalTable[i].loc] + "'" ;
							
							for( int j = 0 ; j < Table7[literalTable[i].loc].size() ; j++ ) {
								inputOBCode = inputOBCode + tenTo16( Table7[literalTable[i].loc][j] ) ;
			
								
							} // for()
							
						} // if()
						
						else {
							newStr = newStr + "=X'" + Table6[literalTable[i].loc] + "'" ;
							
							inputOBCode = Table6[literalTable[i].loc] ;
							
						} // else 
						
						stringList_vice.insert( stringList_vice.begin() + lineIndex + definedLiteral() + 1, newStr ) ;
						
						//cout << "///////////////////" << newStr << endl ;
						
						literalTable[i].loc_mach = nowLoc ;
						
						nowLoc = nowLoc + 3 ;
						
						
					} // if()
					
				} // for()
			
			} // if()
			
		} // else if()
		
	} // talbe2 
	
	int definedLiteral() {
		int count  = 0 ;
		
		for( int i = 0 ; i < literalTable.size() ; i++ ) {
			if( literalTable[i].loc_mach != -1 && literalTable[i].loc_mach != -591573 ) {
				count++ ;
				
			} // if()
			
		} // for()
		
		return count ;
		
	} // definedLiteral()
	
	int undefinedLiteral() {
		int count  = 0 ;
		
		for( int i = 0 ; i < literalTable.size() ; i++ ) {
			if( literalTable[i].loc_mach == -1 ) {
				count++ ;
				
			} // if()
			
		} // for()
		
		return count ;
		
	} // undefinedLiteral()
	
	void pass1() {
		// 表示現在正處理到第幾個token 
		string inputOBCode ;
		makeFormat() ;
		
		if( OPCode.size() == 0 ) {
			makeOPCode() ;
		} // if()
		
		initialLiteral() ;
		
		//cout << "Pass 1" << endl ;
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			inputOBCode = "" ;
			
			//cout << stringList[i] << endl ;
			
			if( strcmp( stringList[i].c_str(), "" ) == 0 || ( data[i][0].table == 4 && data[i][0].loc == 10 ) ) {
				
				if( locate.size() == 0 || END ) {
					locate.push_back( -591573 ) ;
					
				} // if()
				else {
					locate.insert( locate.end() - 1, -591573 ) ;
					
				} // else
				
				OBCode.push_back( "" ) ;
				
			} // if()
			
			else if( strcmp( stringList[i].c_str(), "" ) != 0 ) {
				
				for( int j = 0 ; j < data[i].size() ; j++ ) {
					
					if( data[i][j].table == 1 ) {
						
						table1( i, j, inputOBCode ) ;
						
						OBCode.push_back( inputOBCode ) ;
						
						locate.push_back( nowLoc ) ;
						
						break ;
						
					} // if()
					
					else if( data[i][j].table == 2 ) {
						table2( i, j, inputOBCode ) ;
						
						OBCode.push_back( inputOBCode ) ;
						
						// END不用幫下一行決定地址 
						if( data[i][j].loc != 2 ) {
							locate.push_back( nowLoc ) ;
							
						} // if()
						
						break ;
						
					} // else if()
					
					// 遇到symbol 
					else if( data[i][j].table == 5 ) {
						forwardTable[ data[i][j].loc ] = nowLoc ;
						
						isBase( i, j ) ;
						
					} // else if() 
					
					// 遇到literal 
					else if( data[i][j].table == 4 && data[i][j].loc == 11 ) {
						insertLiteralTable( data[i][j + 2].table, data[i][j + 2].loc, nowLoc ) ;
						
					} // else if()
					
					
				} // for() 
				
			} // else if()
			
		} // for()
		
	} // pass1()
	
	void pass2() {
		string inputOBCode = "" ;
		int haveDefined = 0 ;
		// cout << "Pass2" << endl ;
		
		for( int i = 0 ; i < stringList_vice.size() ; i++ ) {
			if( strcmp( OBCode[i].c_str(), "" ) == 0 && data[i - haveDefined].size() > 0 
				&& ( data[i - haveDefined][0].table != 4 || data[i - haveDefined][0].loc != 10 ) ) {
				nowLoc = locate[i] ;
				
				for( int j = 0 ; j < data[i - haveDefined].size() ; j++ ) {
					string inputOBCode = "" ;
					
					if( data[i - haveDefined][j].table == 1 ) {
						table1( i - haveDefined, j, inputOBCode ) ;
						
						// cout << "NO. " << i + 1 << "Locate" << locate.size() << endl ;
						
						OBCode[i] = inputOBCode ;
						
						break ;
						
					} // if()
					/*
					else if( data[i][j].table == 2 ) {
						table2( i, j, inputOBCode ) ;
						
						cout << "NO. " << i + 1 << "Locate" << locate.size() << endl ;
						
						OBCode[i] = inputOBCode ;
						
						break ;
						
					} // else if()
					*/
				} // for()
				
			} // if()
			
			if( stringList_vice[i][0] == '*' ) {
				haveDefined ++ ;
				
			} // if()
			
		} // for()
		
		// 把Loc改成4個表示 
		resizeLoc() ;
		
	} // pass2
	
	int findLiteral( int table, int loc ) {
		
		// -2 表示沒找到 
		for( int i = 0 ; i < literalTable.size() ; i++ ) {
			if( literalTable[i].table == table && literalTable[i].loc == loc ) {
				return literalTable[i].loc_mach ;
				
				break ;
			} // if()
			
		} // for()
		
		return -2 ;
		
	} // findLiteral()
	
	void insertLiteralTable( int table, int loc, int loc_mach ) {
		int hash = 1 ;
		
		if( findLiteral( table, loc ) == -2 ) {
			if( table == 6 ) {
				for( int i = 0 ; i < Table6[loc].size() ; i++ ) {
					hash = hash + Table6[loc][i] ;
					
				} // for()
				
				hash = hash % 100 ;
				
			} // if()
			
			else {
				for( int i = 0 ; i < Table7[loc].size() ; i++ ) {
					hash = hash + Table7[loc][i] ;
					
				} // for()
				
				hash = hash % 100 ;
				
			} // else
			
			while( literalTable[hash].loc != -591573 ) {
				hash++ ;
				
				if( hash == 100 ) {
					hash = 0 ;
					
				} // if()
				
			} // while()
			
			literalTable[hash].table = table ;
			literalTable[hash].loc = loc ;
			literalTable[hash].loc_mach = loc_mach ;
		
		} // if()
		
	} // insertLiteralTable()
	
	void testShow() {
		cout << "The all result are : " << endl ;
		
		for( int i = 0 ; i < stringList_vice.size() ; i++ ) {
			if( locate[i] != -591573 ) {
				cout << "[" << i << "] " << "Locate10: " << locate[i] << ", Locate16: " << tenTo16( locate[i] ) << endl ;
				cout << OBCode[i] << endl ;
			} // if()
			
			else {
				cout << "" << endl ;
				
			} // else
			
			cout << stringList_vice[i] << endl ;
			
			if( strcmp( OBCode[i].c_str(), "" ) != 0 ) {
				cout << OBCode[i] << endl ;
				
			} // if()
			
			cout << endl ;
			
		} // for()
		/*
		cout << "There are bugs : " << endl ;
		
		for( int i = 0 ; i < OBCode.size() ; i++ ) {
			cout << OBCode[i] << endl ;
			
		} // for()
		*/
		cout << "There are details : " << endl ;
		cout << "Locate: " << locate.size() << endl ;
		cout << "StringList_vice: "<< stringList_vice.size() << endl ;
		cout << "OBCode: "<< OBCode.size() << endl ;
		cout << "Data: " << data.size() << endl ;
		
	} // testShow()
	
	void outputData( string fileName ) {
		int lineNum = 5 ;
		
		fileName = "SICXE_" + fileName + ".txt" ;
		ofstream outfile( fileName.c_str() ) ;
		
		if( outfile ) {
			outfile << "Line\tLocation\tSource code\t\tObject code" << endl ;
			outfile << "----\t--------\t-------------------------\t\t-----------" << endl ;
			
			for( int i = 0 ; i < stringList_vice.size() ; i++ ) {
				if( strcmp( stringList_vice[i].c_str(), "" ) != 0 && stringList_vice[i][0] != '*' ) {
					outfile << lineNum ;
					
					lineNum = lineNum + 5 ;
				
				} // if()
				
				outfile << "\t" ;
				
				if( locate[i] != -591573 ) {
					outfile << locate_str[i] << "\t" ;
					
				} // if()
			
				outfile << stringList_vice[i] << "\t" ;
				
				outfile << OBCode[i]<< endl ;
					
				
			} // for()
			
		} // if()
		
		outfile.close() ;
		
	} // outputData()
	
	void initialAll() {
		nowLoc = 0 ;
		END = false ;
		
		initialLiteral() ;
		locate.clear() ;
		locate_str.clear() ;
		OBCode.clear() ;
		data.clear() ;
		baseRegister.loc = 0 ;
		baseRegister.loc_mach = 0 ;
		baseRegister.table = 0 ;
		forwardTable.clear() ;
		literalTable.clear() ;
		
	} // initial()
	
	void resizeLoc() {
		for( int i = 0 ; i < locate.size() ; i++ ) {
			locate_str.push_back( tenTo16( locate[i] ) ) ;
			
			while( locate_str[i].size() < 4 ) {
				locate_str[i] = "0" + locate_str[i] ;
				
			} // while()
			
		} // for()
		
	} // resizeLoc()
	
	void isBase( int lineIndex, int tokenIndex ) {
		if( data[lineIndex][tokenIndex].loc == baseRegister.loc 
			&& data[lineIndex][tokenIndex].table == baseRegister.table ) {
		
			baseRegister.loc_mach = forwardTable[baseRegister.loc] ;
		
		} // if()
		
	} // isBase()
	
};

int main() {
	string fileName ;
	string s ;
	int command = 1 ;
	
	Token work ;
			
	work.getTable() ;
			
	while( command != 0 ) {
		cout << "-----------------------------------" << endl ;
		cout << "---  Please input a command?    ---" << endl ;
		cout << "---  Command 0 : Quit           ---" << endl ;
		cout << "---  Command 1 : Token          ---" << endl ;
		cout << "---  Command 2 : SIC            ---" << endl ;
		cout << "---  Command 3 : SIC/XE         ---" << endl ;
		cout << "-----------------------------------" << endl ;
				
		cin >> command ;
				
		cout << endl ; 
		if( command == 1 ) {
			cout << "---   Please input a fileName   ---" << endl ;
			cin >> fileName ;
			cout << "Your fileName is: " << fileName << endl ;
					
			work.getData( fileName ) ;
					
			work.outputData( fileName ) ;
					
			// work.testShow() ;
					
			work.initialAll() ;
					
		} // if()
		else if( command == 2 ) {
			SIC work_SIC ;
					
			cout << "---   Please input a fileName   ---" << endl ;
			cin >> fileName ;
			cout << "Your fileName is: " << fileName << endl ;
					
			work.getData( fileName ) ;
					
			work_SIC.pass1() ;
			
			work_SIC.pass2() ;
			
			// work_SIC.testShow() ;
					
			work_SIC.outputData( fileName ) ;
					
			work_SIC.initialAll() ;
			
			work.initialAll() ;
				
		} // else if()
				
		else if( command == 3 ) {
			SICXE work_SICXE ;
					
			cout << "---   Please input a fileName   ---" << endl ;
			cin >> fileName ;
			cout << "Your fileName is: " << fileName << endl ;
					
			work.getData( fileName ) ;
			
			work_SICXE.pass1() ;
			
			// work_SICXE.testShow() ;
				
			work_SICXE.pass2() ;
					
			// work_SICXE.testShow() ;
					
			work_SICXE.outputData( fileName ) ;
			
			work_SICXE.initialAll() ;
			
			work.initialAll() ;
					
		} // else if()
				
		else if( command != 0 ) {
			cout << "No such command." << endl << endl ;
					
		} // else if()
		
		
		
	} // while()
	
	return 0 ;
	
} // main()
