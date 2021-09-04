// 10727122 廖奕銘 10727138 游子諭 

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>

using namespace std ;

typedef string *sNamePtr ;



// 公有function 
bool fileExist ( string filename ) ; // 確認這項資料是否存在 

struct Data{
	int		num ; 		// 排序號碼，從1號開始 
	string	sName ;		// 學校名稱
	string	dName ;		// 科系名稱
	string	learn ;		// 進修別**
	string	level ;		// 等級別**
	int		graduate ; 	// 畢業生數
};	// struct Data

typedef vector <struct Data> dataVct ;

struct School{
	dataVct	sData ;
	string	sName ;
	int graduate ;
};

typedef	vector <struct School> schoolVct ;

//--------------------------------------------//

struct DataNode {
	string	small ; 	// 第1筆資料存small 
	string	medium ;	// 第2筆存medium 
	string	big ;		// 最後存big
	
	DataNode	*pre ;	// 前一個節點 
	
	DataNode	*lLeft ;		//  左區的左節點 / 左節點 
	DataNode	*lRight ;	//  左區的右節點 
	DataNode	*rLeft ;		//  右區的左節點 /  
	DataNode	*rRight ;	//  右區的右節點 
};	// struct DataNode

typedef DataNode *DataPtr ;

struct AvlNode {
	int graduate ;
	
	AvlNode *left ;
	AvlNode *right ;
}; // AVLNode

typedef AvlNode *AvlPtr ;

// class Lab02 裡面的function 
void getData ( string filename, int command ) ; // 把所有資料讀進vector

class Lab02{
	schoolVct data ; // 名字取得很爛，但我想不到更好的
	int dataNum = 0 ; // 資料總數
	
	DataPtr root ;
	DataPtr dataNow ;
	
	AvlPtr avlRoot ;
	AvlPtr avlNow ;
	
public:
	char cStr[256] ; // 讀取資料內的東西
	string tool ;
	struct Data input ;
	stringstream ss ;
	int ty = 0 ;
	int count = 0 ;
	
	void getData ( string filename, int command ) {
		char ch ; // 預防file最後有換行字元的狀況
		fstream infile ;
		
		filename = "input" + filename + ".txt" ;
		
		infile.open( filename.c_str(), fstream::in ) ;
		
		data.clear() ; // 初始化Vector
		dataNum = 0 ;
		
		root = new DataNode ;
		initialNode( root ) ;
		
		avlRoot = NULL ;
		
		infile.getline( cStr, 256, '\n' ) ; // skip header1
  		infile.getline( cStr, 256, '\n' ) ; // skip header2
  		infile.getline( cStr, 256, '\n' ) ; // skip column name
  		
		
		while( infile.getline( cStr, 256, '\n' ) ) {
			dataNum++ ;
			
			string buf, cut ;
   			buf.assign( cStr ) ;
   			int fNo = 1 ;
    		int pre = 0 ;
    		int pos = buf.find_first_of( '\t', pre ) ;
    		cut = buf.substr( pre, pos-pre ) ;
			
		    while ( pos > 0 && fNo < 12 ) { // fNo:1-11
			    if ( fNo == 2 )
			    	input.sName = cut ;
			    else if ( fNo == 4 )
			    	input.dName = cut ;
			    else if ( fNo == 5 )
			    	input.learn = cut ;
			    else if ( fNo == 6 )
			    	input.level = cut ;
			  	else if ( fNo == 9 ) {
			  		input.num = dataNum ;
			  		input.graduate = atoi( cut.c_str() ) ; // 上屆畢業人數 9
			  	} // if
				
				pre = pos+1 ;
				pos = buf.find_first_of( '\t', pre ) ;
				cut = buf.substr( pre, pos-pre ) ;
				fNo++ ;	
				
		    } // while 
			count++ ;
			
			getIntoVct ( command ) ;
			
		} // while()
		
		infile.close() ;
	} // getData ()
	
	void getIntoVct ( int command ) {
		if( command == 1 ) { // 新增資料進入2-3樹 
				
			if( !sNameExist() ) {
				struct School newSchool ;
				newSchool.sName = input.sName ;
				newSchool.sData.push_back(input) ;
				newSchool.graduate = input.graduate ;
				data.push_back( newSchool ) ;
				
				dataNow = new DataNode ;
				initialNode( dataNow ) ;
				
				dataNow = searchTree( root, input.sName ) ;
				
				ttTree( dataNow, input.sName ) ;
			
			} // if()
				
			else {
				for( int i = 0 ; i < data.size() ; i++ ) {
					if( data[i].sName == input.sName ) {
						data[i].sData.push_back(input) ;
					
					} // if()
				
				} // for()
			
			} // else
			
		} // if( command == 1 )
		
		else if ( command == 2 ) {
			
			if( !graduateExist() ) {
				struct School newSchool ;
				newSchool.sName = input.sName ;
				newSchool.sData.push_back(input) ;
				newSchool.graduate = input.graduate ;
				data.push_back( newSchool ) ;
				
				
				avlNow = new AvlNode ;
				initialAvlNode( avlNow ) ;
				
				avlNow = insertAVL( avlRoot, input.graduate ) ;
				
				checkBalance( avlNow ) ;
				
			
			} // if()
				
			else {
				for( int i = 0 ; i < data.size() ; i++ ) {
					if( data[i].graduate == input.graduate ) {
						data[i].sData.push_back(input) ;
					
					} // if()
				
				} // for()
			
			} // else
			
		} // else if
		
		else {
			;
		} // else
		
		
	} // getIntoVct
	
	bool pointNothing ( DataPtr now ) {
		
		if ( now->lLeft == NULL && now->lRight == NULL && now->rLeft == NULL && now->rRight == NULL )
			return true ;
		else 
			return false ;
	} // pointNothing()
	
	AvlPtr getAvlParent( AvlPtr walk, AvlPtr now ) {
		
		if ( walk == NULL ) {
			return NULL ;
		} // if
		
		else if ( walk == now ) {
			return NULL ;
		} //else if
		
		else if ( walk->left == now || walk->right == now ) {
			return walk ;
		} //else if
		
		else if ( now->graduate < walk->graduate ) {
			return getAvlParent( walk->left, now ) ;
		} // else if
		
		else {
			return getAvlParent( walk->right, now ) ;
		} // else
			
		
	} // getAvlParent()

	
	void initialNode ( DataPtr now ) {
		
		now->big 		= "" ;
		now->medium 	= "" ;
		now->small 		= "" ;
		
		now->pre		= NULL ;
		
		now->lLeft 		= NULL ;
		now->lRight 	= NULL ;
		now->rLeft 		= NULL ;
		now->rRight 	= NULL ;
		
	} // initialNode()
	
	void initialAvlNode( AvlPtr now ) {
		now->graduate = -1 ;
		
		now->left = NULL ;
		now->right = NULL ;
	} // initialAvlNode()
	
	DataPtr searchTree( DataPtr now, string name ) {
		if ( pointNothing( now ) ) {
			return now ;
			
		} // if()
			
		else if ( now->medium == "" ) {
			if ( name < now->small ) {
				return searchTree( now->lLeft, name ) ;
				
			} // if()
			else {
				
				return searchTree( now->rLeft, name ) ;
			} // else
		} // else if
		
		else {
			if ( name < now->small )
				return searchTree( now->lLeft, name ) ;
				
			else if ( name > now->small && name < now->medium )
				return searchTree( now->lRight, name ) ;
				
			else
				return searchTree( now->rLeft, name ) ;
				
		} // else
			
	} // searchTree()
	
	AvlPtr insertAVL( AvlPtr &now, int graduate ) {
		
		if ( now == NULL ) {
			
			now = new AvlNode ;
			initialAvlNode( now ) ;
			now->graduate = graduate ;
			
			return now ;
			
		} // if
		
		else if ( graduate < now->graduate ) {
			return insertAVL( now->left, graduate ) ;
		} // else if
		
		else {
			return insertAVL( now->right, graduate ) ;
		} // else
		
	} // insertAVL
	
	void checkBalance( AvlPtr &now ) {
		
		int balanceNum = avlTreeHeight( now->left ) - avlTreeHeight( now->right ) ;
		
		AvlPtr temp ;
		
		if ( -1 <= balanceNum && balanceNum <= 1 ) {		// 不需要旋轉
		
			if ( getAvlParent( avlRoot, now ) == NULL ) {						// 檢查到根了 
				return ;
			
			} // if
			else {											// 要繼續往上檢查
				now = getAvlParent( avlRoot, now ) ;
				checkBalance( now ) ;
				return ;
				
			} // else
			
		} // if
		
		else {												// 需要旋轉來平衡 但不用繼續往上檢查 
			AvlPtr pre = getAvlParent( avlRoot, now ) ;
				
			if (		balanceNum == 2 && 
						avlTreeHeight( now->left->left ) - avlTreeHeight( now->left->right ) == 1 ) {
					
					now = rightRotate( now, now->left ) ;
					
					if ( pre == NULL )
						avlRoot = now ;
						
					else {
						if ( now->graduate < pre->graduate ) 
							pre->left = now ;
						
						else 
							pre->right = now ;
						
					} // else
					
			} // if
			
			else if (	balanceNum == -2 && 
				 		avlTreeHeight( now->right->left ) - avlTreeHeight( now->right->right ) == -1 ) {
				 		
				 	now = leftRotate( now, now->right ) ;
				 	
					if ( pre == NULL )
						avlRoot = now ;
						
					else {
						if ( now->graduate < pre->graduate ) 
							pre->left = now ;
						
						else 
							pre->right = now ;
						
					} // else
				 	
			} // else if
			
			else if ( 	balanceNum == 2 && 
				 		avlTreeHeight( now->left->left ) - avlTreeHeight( now->left->right ) == -1 ) {
				 			
				 	now->left = leftRotate( now->left, now->left->right ) ;
				 	
				 	now = rightRotate( now, now->left ) ;
					
					if ( pre == NULL )
						avlRoot = now ;
						
					else {
						if ( now->graduate < pre->graduate ) 
							pre->left = now ;
						
						else 
							pre->right = now ;
						
					} // else
				 	
			} // else if
			
			else if ( 	balanceNum == -2 && 
				 		avlTreeHeight( now->right->left ) - avlTreeHeight( now->right->right ) == 1 ) {
				 		
					now->right = rightRotate( now->right, now->right->left ) ;
					
				 	now = leftRotate( now, now->right ) ;
				 	
				 	if ( pre
					  == NULL )
						avlRoot = now ;
						
					else {
						if ( now->graduate < pre->graduate ) 
							pre->left = now ;
						
						else 
							pre->right = now ;
						
					} // else
					
			} // else if
			return ;
			
		} // else
		
	} // checkBalance()
	
	AvlPtr rightRotate( AvlPtr rootA, AvlPtr pivot ) {
		rootA->left = pivot->right ;
		
		pivot->right = rootA ;
		
		return pivot ;
		
	} // rightRotate()
	
	AvlPtr leftRotate( AvlPtr rootA, AvlPtr pivot ) {
		
		rootA->right = pivot->left ;
		
		pivot->left = rootA ;
		
		return pivot ;
		
	} // leftRotate()
	
	
	void ttTree( DataPtr &now, string name ) {
		
		if ( now->small == "" ) {
			now->small = name ;
			return ;
		} // if
		else if ( now->medium == "" ) {
			now->medium = name ;
			sortNode( now ) ;
			
			return ;
		} // else if
		else {
			now->big = name ;
			sortNode( now ) ;
			
			split( now ) ;
			return ;
		} // else
		
	} // ttTree()
	
	void split( DataPtr &now ) {
		DataPtr splitNode = NULL ;
		DataPtr parentNode = getParent( now ) ;
		
		if ( now->big == "" ) {
			return ;
			
		} // if()
			
		else {
			if ( parentNode == NULL ) {		
				DataPtr newRoot = new DataNode ;
				initialNode( newRoot ) ;
				
				newRoot->small = now->medium ;
				now->medium = "" ;
				
				newRoot -> rLeft = new DataNode ;
				initialNode( newRoot->rLeft ) ;
				newRoot -> rLeft -> small = now -> big ;
				now -> big = "" ;
				
				newRoot -> lLeft = now ;
				
				newRoot -> rLeft -> lLeft = now -> rLeft ;
				
				newRoot -> rLeft -> rLeft = now -> rRight ;
				
				now -> rRight = NULL ;
				
				now -> rLeft = now -> lRight ;
				
				now -> lRight = NULL ;
				
				root = newRoot ;
			
			} // if()
				
			
			else {
				if( parentNode->medium == "" ) { 						// 父節點只有一個數值 
				
					parentNode->medium = now->medium ;
					now->medium = "" ;
					
					sortNode( parentNode ) ;
					
					parentNode->lRight = new DataNode ;
					initialNode( parentNode->lRight ) ;
					splitNode = parentNode->lRight ;
					
					if( now == parentNode->lLeft ) {
						
						splitNode->small = now->big ;
						now->big = "" ;
						
						splitNode->lLeft = now->rLeft ;
						
						splitNode->rLeft = now->rRight ;
						
						now->rLeft = now->lRight ;
						now->lRight = NULL ;
						
						now->rRight = NULL ;
						
						
					} // if()
					
					else if( now == parentNode->rLeft ) {
						
						
						splitNode->small = now->small ;
						now->small = now->big ;
						now->big = "" ;
						
						splitNode->lLeft = now->lLeft ;
						
						now->lLeft = now->rLeft ;
						now->rLeft = now->rRight ;
						now->rRight = NULL ;
						
						splitNode->rLeft = now->lRight ;
						
						now->lRight = NULL ;
						
						
					} // else if
					
					
				} // if()
				
				else if( parentNode->medium != "" ) {											// 父節點已有兩個數值 
					
					parentNode->big = now->medium ;
					now->medium = "" ;
					
					sortNode( parentNode ) ;
					
					
					if( now == parentNode->lLeft ) {				// now是最左邊的子節點 
						
						parentNode->rRight = parentNode->rLeft ;
						parentNode->rLeft = parentNode->lRight ;
						
						parentNode->lRight = new DataNode ;
						initialNode( parentNode->lRight ) ;
						splitNode = parentNode->lRight ;
						
						splitNode->small = now->big ;
						now->big = "" ;
						
						splitNode->lLeft = now->rLeft ;
						
						now->rLeft = now->lRight ;
						now->lRight = NULL ;
						
						splitNode->rLeft = now->rRight ;
						
						now->rRight = NULL ;
						
					} // if()
					
					else if( now == parentNode->lRight ) {		// now是左邊數來第二個子節點
					
						parentNode->rRight = parentNode->rLeft ;
						
						parentNode->rLeft = new DataNode ;
						initialNode( parentNode->rLeft ) ;
						splitNode = parentNode->rLeft ;
						
						splitNode->small = now->big ;
						
						now->big = "" ;
						
						splitNode->lLeft = now->rLeft ;
						
						now->rLeft = now->lRight ;
						now->lRight = NULL ;
						
						splitNode->rLeft = now->rRight ;
						
						now->rRight = NULL ;
						
						
					} // if()
					
					else if ( now == parentNode->rLeft ) {											// now是左邊數來第三個節點 
						
						parentNode->rRight = new DataNode ;
						initialNode( parentNode->rRight ) ;
						splitNode = parentNode->rRight ;
						
						splitNode->small = now->big ;
						
						now->big = "" ;
						
						splitNode->lLeft = now->rLeft ;
						
						now->rLeft = now->lRight ;
						now->lRight = NULL ;
						
						splitNode->rLeft = now->rRight ;
						
						now->rRight = NULL ;
						
						
					} // else if
					
					split( parentNode ) ;
					
					
				} // else
				
			} // else
		} // else
		
	} // split()
	
	int avlTreeHeight( AvlPtr now ) {
		
		if ( now == NULL )
			return 0 ;
			
		else if ( avlTreeHeight( now->left ) > avlTreeHeight( now->right ) )
			return avlTreeHeight( now->left ) + 1 ;
			
		else 
			return avlTreeHeight( now->right ) + 1 ;
		
	} // avlTreeHeight()
	
	int treeHeight( DataPtr now ) {
		
		if ( now == NULL )
			return 0 ;
			
		else {
			
			if ( treeHeight( now->lLeft ) >= treeHeight( now->lRight )	&&
			 	 treeHeight( now->lLeft ) >= treeHeight( now->rLeft )	&&
				 treeHeight( now->lLeft ) >= treeHeight( now->rRight )	 ) {
				 
				return treeHeight( now->lLeft ) + 1 ;
			} // if
			
			else if ( treeHeight( now->lRight ) >= treeHeight( now->rLeft ) &&
					  treeHeight( now->lRight ) >= treeHeight( now->rRight ) ) {
				
				return treeHeight( now->lRight ) + 1 ;
			} // else if
			
			else if ( treeHeight( now->rLeft ) >= treeHeight( now->rRight ) ) {
				
				return treeHeight( now->rLeft ) + 1 ;
			} // else if
			
			else {
				
				return treeHeight( now->rRight ) + 1 ;
			} // else
			
		} // else
			
	} // treeHeight()
	
	int avlNumOfNode( AvlPtr now ) {
		
		if ( now == NULL )
			return 0 ;
			
		else
			return avlNumOfNode( now->left ) + avlNumOfNode( now->right ) + 1 ;
			
	} // avlNumOfNode()
	
	int numOfNode( DataPtr now ) {
		
		if ( now == NULL )
			return 0 ;
			
		else {
			
			return 	numOfNode( now->lLeft ) + numOfNode( now->lRight ) +
					numOfNode( now->rLeft ) + numOfNode( now->rRight ) + 1 ;
					
		} // else
		
	} // numOfNode
	
	void sortNode( DataPtr &now ) {
		
		if( now->big != "" ) {
			if( now->small > now->medium ) {
				swap( now->medium, now->small ) ;
				
			} // if()
			if( now->small > now->big ) {
				swap( now->big, now->small ) ;
				
			} // if()
			if( now->medium > now->big ) {
				swap( now->big, now->medium ) ;
				
			} // if()
				
			
		} // if()
		else if( now->medium != "" ) {
			if( now->small > now->medium ) {
				swap( now->medium, now->small ) ;
				
			} // if()
			
		} // else
		
	} // sortNode()
	
	void swap( string &small, string &big ) {
		string temp ;
		temp = small ;
		small = big ;
		big = temp ;
		
	} // swap
	

	void haveChild( DataPtr &now, DataPtr &nNow ) {
		nNow->lLeft->lLeft = now->lLeft ;
		nNow->lLeft->rLeft = now->lRight ;
		nNow->rLeft->lLeft = now->rLeft ;
		nNow->rLeft->rLeft = now->rRight ;
		
		
		if( now->lLeft != NULL ) {
			nNow->lLeft->lLeft->pre  = nNow->lLeft ;
			nNow->lLeft->rLeft->pre  = nNow->lLeft ;
			nNow->rLeft->lLeft->pre  = nNow->rLeft ;
			nNow->rLeft->rLeft->pre  = nNow->rLeft ;
			
		} // if()
		
	} // haveChild()
	
	bool sNameExist() {
		if( data.empty() ) {
			return false ;
		} // if( data.empty() )
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			if( data[i].sName == input.sName ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // sNameExist()
	
	bool graduateExist() {
		if( data.empty() ) {
			return false ;
		} // if( data.empty() )
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			if( data[i].graduate == input.graduate ) {
				return true ;
				
			} // if()
			
		} // for()
		
		return false ;
		
	} // sNameExist()
	
	void show() {
		int numOfAllData = 1 ;
		
		cout	<<	"Tree height = "	<<	treeHeight( root )	<<	endl	;
		cout	<<	"Number of nodes = "	<<	numOfNode( root )	<<	endl	;
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			if( root->small == data[i].sName ) {
				for( int j = 0 ; j < data[i].sData.size() ; j++ ) {
					cout << numOfAllData << ": [" << data[i].sData[j].num << "] " << data[i].sData[j].sName << ", "
					 	 << data[i].sData[j].dName	<< ", " << data[i].sData[j].learn		<< ", "
					 	 << data[i].sData[j].level	<< ", " << data[i].sData[j].graduate	<< "\n" ;
					
					numOfAllData++ ;
				} // for()
				
			} // if()
			
			if( root->medium != "" && root->medium == data[i].sName ) {
				for( int j = 0 ; j < data[i].sData.size() ; j++ ) {
					cout << numOfAllData << ": [" << data[i].sData[j].num << "] " << data[i].sData[j].sName << ", "
					 	 << data[i].sData[j].dName	<< ", " << data[i].sData[j].learn		<< ", "
					 	 << data[i].sData[j].level	<< ", " << data[i].sData[j].graduate	<< "\n" ;
					
					numOfAllData++ ;
					
				} // for()
				
			} // if()
			
		} // for()
		
	} // show()
	
	void showAVL() {
		int numOfAllData = 1 ;
		
		cout	<<	"Tree height = "		<<	avlTreeHeight( avlRoot )	<<	endl	;
		cout	<<	"Number of nodes = "	<<	avlNumOfNode( avlRoot )		<<	endl	;
		
		for( int i = 0 ; i < data.size() ; i++ ) {
			if( avlRoot->graduate == data[i].graduate ) {
				for( int j = 0 ; j < data[i].sData.size() ; j++ ) {
					cout << numOfAllData << ": [" << data[i].sData[j].num << "] " << data[i].sData[j].sName << ", "
					 	 << data[i].sData[j].dName	<< ", " << data[i].sData[j].learn		<< ", "
					 	 << data[i].sData[j].level	<< ", " << data[i].sData[j].graduate	<< "\n" ;
					
					numOfAllData++ ;
				} // for()
				
			} // if()
			
		} // for()
		
	} // showAVL()
	
	void showAVLTree( AvlPtr now ) {
		if ( now == NULL )
			return ;
		else {
			showAVLTree( now->left ) ;
			cout << now->graduate << endl ;
			showAVLTree( now->right ) ;
			return ;
		} // else
		
	} // showAVLTree()
	
	void DebugShow( DataPtr walk ) { // 00000000000000000000000000000000000
		if ( walk == NULL ) {
			cout << "NULL" << endl ;
		} // if
		
		else {
			cout << walk -> small ;
			if ( walk -> medium != "" ) {
				cout << " " << walk -> medium ;
				cout << endl ;
				DebugShow( walk -> lLeft ) ;
				DebugShow( walk -> lRight ) ;
				DebugShow( walk -> rLeft ) ;
			} // if
			
			else {
				cout << endl ;
				DebugShow( walk -> lLeft ) ;
				DebugShow( walk -> rLeft ) ;
			} // else
		} // else
	} // DebugShow()
	
	DataPtr GetRoot() { // 00000000000000000000000000
	  return root ;
	} // GetRoot
	
		DataPtr getParent( DataPtr now ) {
		bool sign = true ;
		DataPtr walk = root ;
		string name = now->small ;
		DataPtr parent = NULL ;
		
		while( sign ) {
			if( name == walk->small ) {
				sign = false ;
				
			} // if()
			
			else if( pointNothing( walk ) ) {
				sign = false ;
				
			} // if()
			
			else if ( walk->medium == "" ) {
				if ( name < walk->small && !pointNothing( walk ) ) {
					parent = walk ;
					
					walk = walk -> lLeft ;
					
				} // if()
				else if ( name > walk->small && !pointNothing( walk ) ) {
					parent = walk ;
					
					walk = walk -> rLeft ;
					
				} // else if()
				
			} // else if
			
			else {
				if ( name < walk->small && !pointNothing( walk ) ) {
					parent = walk ;
					
					walk = walk -> lLeft ;
					
				} // if()
				else if ( name > walk->small && name < walk->medium && !pointNothing( walk ) ) {
					parent = walk ;
					
					walk = walk -> lRight ;
					
				} // else if()
				else if ( name > walk->medium && !pointNothing( walk ) ) {
					parent = walk ;
					
					walk = walk -> rLeft ;
					
				} // else if()
				
			} // else
			
		} // while()
		
		return parent ;
		
	} // getParent()
	
	
}; // class()

int main() {
	string filename ;
	int command = 1 ;
	Lab02 database ;
	
	while ( command != 0 ) {
		cout << "*** Search Tree Utilities **\n" ;
		cout << "* 0. QUIT                  *\n" ;
		cout << "* 1. Build 2-3 tree        *\n" ;
		cout << "* 2. Build AVL tree        *\n" ;
		cout << "*************************************\n" ;
		cout << "Input a choice(0, 1, 2):" ;
		
		cin >> command ;
		
		if( !cin  ) {
			cout << endl ;
			cout << "Command does not exist!\n\n" ;
			cin.clear();                          
            cin.sync();
        
        	command = 1 ;
		} // if()
		
		else if( command == 1 ) {
			cout << "\nInput a file number ([0] Quit):" ;
				
			cin >> filename ;
			
				
			if( !fileExist( filename ) ) {
				cout << "\n### input" << filename << ".txt does not exist! ###\n\n" ;
				cout << "There is no data!\n\n" ;
				
			} // if()
			
			if( fileExist( filename ) ) {
				
				
				database.getData( filename, command ) ;
			
				database.show() ;
				
				//database.DebugShow( database.GetRoot() ) ;
				
				cout << endl << endl ;
				
			} // else if
			
		} // if()
		
		else if( command == 2 ) {
				
			cout << "\nInput a file number ([0] Quit):" ;
				
			cin >> filename ;
			
				
			if( !fileExist( filename ) ) {
				cout << "\n### input" << filename << ".txt does not exist! ###\n\n" ;
				cout << "There is no data!\n\n" ;
				
			} // if()
			
			if( fileExist( filename ) ) {
				
				
				database.getData( filename, command ) ;
			
			
				database.showAVL() ;
				
				cout << endl << endl ;
				
			} // else if
			
		} // if()
		
		else if( command != 0 ) {
			cout << endl ;
			cout << "Command does not exist!\n" ;
			cout << endl ;
		} // if()
		
	} // while()
	
} // main()

bool fileExist ( string filename ) {
	FILE *infile = NULL ;
		
	if( filename == "0" ) {
		return false ;
	} // if()
		
	filename = "input" + filename + ".txt" ;
	infile = fopen( filename.c_str(), "r" ) ;
		
		
	if( infile == NULL ) {
		return false ;
			
			
	} // if()
		
	else {
		return true ;
	} // else
	
} // fileExist ()
