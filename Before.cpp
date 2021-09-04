# include <iostream>
# include <vector>
# include <stdlib.h>
# include <stdio.h>
# include <string>
# include <sstream>

using namespace std ;

enum Number {
  DOT = 46, ZERO = 48, ONE, TWO, THREE, FOUR, FIVE, 
  SIX, SEVEN, EIGHT, NINE 
  
};

struct Token {
  string str ;
  string type ;
  
}; // token

// �M����Tree�ϥΪ� 
struct Node {
  string str ;
  string type ;
  Node* left ;
  Node* right ;
  
}; // Node

typedef vector <Token> TokenList ;

typedef Node* NodePtr ;


void SkipAllWhite() ;

bool IsSeparator( char ch ) ;

string TypeDecide( string str ) ;

bool StrIsInt( string str ) ;

bool StrIsFloat( string str ) ;

bool IsT( string str ) ;

bool IsNIL( string str ) ;

void String( char &nowCh, char &nextCh, string &str, bool &doubleQuote ) ;

// �M���B�z�A�������p 
// ���`���pmAllToken���Ĥ@��Token�n�O"(" 
// nowCh == '(' 
// str == ""
void Paren( bool &paren ) ;

// �Ҧ��ؾ𪺹L�{�A�]�t Translate �M Build 
void MakeTree() ;

// ��𪺵��G show �X�ӡA�ݦ��S�����~ 
void TreeShow( NodePtr head ) ;

// ���C��()�̭�����dot 
int TranslateParen_Dot( int locate ) ;

int TranslateParen_Dot_Paren( int locate ) ;

// �Q�� Translate �᪺���e�A�غc�X���㪺�� 
void BuildNodeTree( NodePtr &head, int &locate ) ;

void ParenGrammar( bool &paren ) ; 

// ���F ShowAllToken() �� output space 
void PrintSpace( int count ) ;

// public

// Ū�U�@�Ӧr��æ^�s��tokenList�� 
// �C�@���u�B�z�@��token 
void ReadString() ;

void TestShow() ;

// ��Token show�X�Ӫ��P��
void Show() ;

bool IsEnd() ;

// �r��->token�� 
class Scanner {
  // �x�s�Ҧ���Token 
  TokenList mAllToken ;
  // Tree
  NodePtr mHeadClass ;
  
  bool mError ; // END OF FILE��ERROR 
  bool mError_UT_LP ; // Unexpected Token��Error 
  bool mError_UT_RP ; // Unexpected Token Right Paren�� Error 
  bool mError_NCQ ; // No Closing Quote��Error 
  bool mTokenInSameLine ; // ��@��tokenŪ�i�ӫ᭱�S���F������ťծɡA�u�����Ĥ@��O�q�U�@�Ӷ}�l 
  char mError_UT_char ;
  int mLine ; // ��ܲ{�b�ĴX�� 
  int mColumn ; // ��ܲ{�b�O�Ӧ檺�ĴX�Ӧr�� 
  
  // ���L�Ҧ���white space 
  void SkipAllWhite() {
    char nowCh ;
    char nextCh ;
    
    nextCh = cin.peek() ;
    
    while ( nextCh == ' ' ) {
      nowCh = cin.get() ;
      
      nextCh = cin.peek() ;
      
    } // while()
    
  } // SkipAllWhite()
  
  // �P�_ch�O�_��separator  
  bool IsSeparator( char ch ) {
    if ( ch == ' ' || ch == '(' || ch == ')' || ch == '\'' || ch == '\"' || ch == ';' ) {
      return true ;
      
    } // if()
    
    return false ;
    
  } // IsSeparator()
  
  // �P�_str�����O���� 
  string TypeDecide( string str ) {
    string type = "NULL" ;
    
    if ( str == "(" ) {
      type = "LEFT-PAREN" ;
      
    } // if()
    
    else if ( str == ")" ) {
      type = "RIGHT-PAREN" ;
      
    } // else if()
    
    else if ( str == "." ) {
      type = "DOT" ;
      
    } // else if()
    
    else if ( StrIsInt( str ) ) {
      type = "INT" ;
      
    } // else if()
    
    else if ( StrIsFloat( str ) ) {
      type = "FLOAT" ;
      
    } // else if()
    
    else if ( str == "'" ) {
      type = "QUOTE" ;
      
    } // else if()
    
    else if ( IsT( str ) ) {
      type = "T" ;
      
    } // else if()
    
    else if ( IsNIL( str ) ) {
      type = "NIL" ;
      
    } // else if()
    
    else {
      type = "SYMBOL" ;
      
    } // else
    
    return type ;
    
  } // TypeDecide()
  
  bool StrIsInt( string str ) {
    int check = 0 ; // �}�l�ˬdstr�O�_��integer���}�Y 
    
    if ( str[0] == '+' || str[0] == '-' ) {
      check = 1 ;
      
      if ( str.size() == 1 ) {
        return false ;
        
      } // if()
      
    } // if()
    
    for ( int i = check ; i < str.size() ; i++ ) {
      if ( str[i] != ZERO && str[i] != ONE && str[i] != TWO && str[i] != THREE 
           && str[i] != FOUR && str[i] != FIVE && str[i] != SIX && str[i] != SEVEN
           && str[i] != EIGHT && str[i] != NINE ) {
        return false ;     
        
      } // if()
      
    } // for()
    
    return true ;
    
  } // StrIsInt()
  
  bool StrIsFloat( string str ) {
    int check = 0 ; // �}�l�ˬdstr�O�_��integer���}�Y 
    bool dot = false ; // �ˬddot�O�_���X�{�L 
    
    if ( str[0] == '+' || str[0] == '-' ) {
      check = 1 ;
      
      if ( str.size() <= 2 ) {
        return false ;
        
      } // if()
      
    } // if()
    
    for ( int i = check ; i < str.size() ; i++ ) {
      if ( str[i] == DOT && !dot ) {
        dot = true ;
        
      } // if()
      
      else if ( str[i] != ZERO && str[i] != ONE && str[i] != TWO && str[i] != THREE 
                && str[i] != FOUR && str[i] != FIVE && str[i] != SIX && str[i] != SEVEN
                && str[i] != EIGHT && str[i] != NINE ) {
        return false ;     
        
      } // if()
      
    } // for()
    
    if ( dot ) {
      return true ;
      
    } // if()
    
    return false ;
    
  } // StrIsFloat()
  
  bool IsT( string str ) {
    if ( str.size() == 1 && str == "t" ) {
      return true ;
      
    } // if ()
    
    else if ( str.size() == 2 && str == "#t" ) {
      return true ;
      
    } // else if ()
    
    else {
      return false ;
      
    } // else
    
  } // IsT()
  
  bool IsNIL( string str ) {
    
    if ( str.size() == 2 && str == "#f" ) {
      return true ;
      
    } // if ()
    
    else if ( str.size() == 3 && str == "nil" ) {
      return true ;
      
    } // else if ()
    
    else {
      return false ;
      
    } // else
    
  } // IsNIL()
  
  void String( char &nowCh, char &nextCh, string &str, bool &doubleQuote ) {
    bool escape = false ; // ��ܦ�escape���o�� 
    Token nToken ;
    
    doubleQuote = true ;
    
    while ( doubleQuote ) {
      nowCh = cin.get() ;
      mColumn++ ;
      
      if ( !escape ) {
        str = str + nowCh ;
        
      } // if()
      
      else {
        nowCh = '\0' ;
        
      } // else
      
      escape = false ;
      
      nextCh = cin.peek() ;
      
      // No Closing Quote Error
      if ( nextCh == '\n' ) {
        ChangeTokenInSameLine( true ) ;
        
        str = "" ;
        
        doubleQuote = false ;
        
        mError_NCQ = true ;
        
      } // if()
      
      else if ( nowCh != '\\' && nextCh == '\"' ) {
        nowCh = cin.get() ;
        
        mColumn++ ;
        
        str = str + nowCh ;
        
        doubleQuote = false ;
        
        nToken.str = str ;
        
        nToken.type = "STRING" ;
        
        mAllToken.push_back( nToken ) ;
        
        str = "" ;
        
      } // if()
      
      // escape�����p 
      else if ( nowCh == '\\' ) {
        if ( nextCh == '\\' ) {
          escape = true ; 
          
        } // if()
        
        else if ( nextCh == 'n' ) {
          str = str.assign( str, 0, str.size() - 1 ) ;
          
          str = str + '\n' ;
          
          escape = true ;
          
        } // else if()
        
        else if ( nextCh == '\"' ) {
          str = str.assign( str, 0, str.size() - 1 ) ;
          
          str = str + '\"' ;
          
          escape = true ; 
          
        } // else if()
        
        else if ( nextCh == 't' ) {
          str = str.assign( str, 0, str.size() - 1 ) ;
          
          str = str + '\t' ;
          
          escape = true ;
          
        } // else if()
        
      } // else if
      
    } // while()
    
  } // String()
  
  // �M���B�z�A�������p 
  // ���`���pmAllToken���Ĥ@��Token�n�O"(" 
  // nowCh == '(' 
  // str == ""
  void Paren( bool &paren ) {
    int pair = 0 ;
    Token nToken ;
    bool quote = false ; // �O�_��bool 
    bool makeQuoteTree = false ; // ��quote���ϥΡA���L���D�᭱�O�_�� expression
    bool hadParen = false ; // �� MakeTree() �ݱo�A�]���� '(' �� ')' �~�i�H�}�l�ؾ� 
    
    for ( int i = 0 ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).str == "(" ) {
        pair++ ;
        hadParen = true ; 
        
      } // if()
      
      else if ( mAllToken.at( i ).str == ")" ) {
        pair-- ;
        hadParen = true ;
        
      } // else if()
      
      else if ( mAllToken.at( i ).str == "'" ) {
        quote = true ;
        
        if ( i + 1 < mAllToken.size() && mAllToken.at( i + 1 ).type == "DOT" ) {
          // ERROR
          
        } // if()
        else if ( i + 1 < mAllToken.size() && mAllToken.at( i + 1 ).type != "QUOTE" ) {
          makeQuoteTree = true ;
          
        } // else if()
        
      } // else if()
      
    } // for()
    
    // cout << "mAllToken.size() : " << mAllToken.size() << endl ;
    // cout << mAllToken.at( mAllToken.size() - 1 ).str << endl ;
    
    ParenGrammar( 0, paren ) ;
    
    // cout << "mTokenInSameLine " << mTokenInSameLine << endl ;
    // cout << "After : " << mAllToken.size() << endl ;
    
    if ( paren && pair >= 0 ) {
      // ���() 
      if ( mAllToken.size() >= 2 && mAllToken.at( mAllToken.size() - 2 ).str == "(" 
           && mAllToken.at( mAllToken.size() - 1 ).str == ")" ) {
        mAllToken.pop_back() ;
        mAllToken.pop_back() ;
        
        if ( pair == 0 && !quote ) {
          paren = false ;
          
        } // if()
        
        nToken.str = "nil" ;
        
        nToken.type = "NIL" ;
        
        mAllToken.push_back( nToken ) ;
        
      } // if ()
      
      if ( pair == 0 && quote && makeQuoteTree ) {
        paren = false ;
        
        QuoteTree() ;
        
        MakeTree() ;
      
        ChangeTokenInSameLine( true ) ;
        
      } // if()
      
      else if ( pair == 0 && hadParen ) {
        paren = false ;
        
        MakeTree() ;
        
        ChangeTokenInSameLine( true ) ;
        
      } // else if()
      
    } // if()
    
    // Unexpected Error
    else if ( pair < 0 ) {
      ChangeTokenInSameLine( true ) ;
      
      paren = false ;
      
      mError_UT_LP = true ;
      
      mError_UT_char = ')' ;
      
      // �᭱����skip 
      while ( cin.peek() != '\n' && cin.peek() != EOF ) {
        cin.get() ;
        
        cin.peek() ;
        
      } // while()
      
      if ( cin.peek() == EOF ) {
        mError = true ;
        
      } // if()
      
      mAllToken.clear() ;
      
    } // else if()
    
  } // Paren()
  
  void MakeTree() {
    int locate = 0 ;
    
    // ���� () �����p 
    if ( mAllToken.at( 0 ).type == "NIL" ) {
      
      
    } // if()
    
    else {
      mHeadClass = new Node ;
      mHeadClass -> str = "" ;
      mHeadClass -> type = "" ;
      mHeadClass -> left = NULL ;
      mHeadClass -> right = NULL ;
      
      TranslateParen_Dot( 0 ) ;
      
      TranslateParen_Dot_Paren( 1 ) ;
      
      BuildNodeTree( mHeadClass, locate ) ;
      
    } // else
    
    // TreeShow( head ) ;
    
  } // MakeTree()
  
  void TreeShow( NodePtr head ) {
    if ( head -> left != NULL )
      TreeShow( head -> left ) ;
      
    if ( head -> right != NULL ) 
      TreeShow( head-> right ) ;
      
    if ( head -> str != "" ) {
      cout << head -> str << endl ;
      return ;
      
    } // if()
        
  } // TreeShow()
  
  // ���C��()�̭�����dot 
  int TranslateParen_Dot( int locate ) {
    int nowLocate = locate ;
    bool dot = false ;
    Token nToken ;
    
    for ( int i = nowLocate + 1 ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        
        i = TranslateParen_Dot( i ) ;
        
      } // if()
      
      else if ( mAllToken.at( i ).type == "RIGHT-PAREN" ) {
        if ( !dot ) {
          nToken.str = "." ;
          nToken.type = "DOT" ;
          
          mAllToken.insert( mAllToken.begin() + i, nToken ) ;
          
          nToken.str = "nil" ;
          nToken.type = "NIL" ;
          
          mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
          
          return i + 2 ;
          
        } // if()
        
        return i ;
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" ) {
        dot = true ;
        
      } // else if()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // TranslateParen_Dot()
  
  int TranslateParen_Dot_Paren( int locate ) {
    int rightParenCount = 0 ; // �p��h�s�y�X�Ӫ�right-paren 
    int pair = 0 ;
    Token nToken ;
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      // cout << i << endl ;
      
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        i = TranslateParen_Dot_Paren( i + 1 ) ;
        
      } // if()
      
      if ( mAllToken.at( i + 1 ).type == "RIGHT-PAREN" ) {
        return i + rightParenCount + 1 ;
        
      } // if()
      
      // ���paren��end 
      else if ( mAllToken.at( i + 1 ).type == "DOT" ) {
        i = i + 1 ;
        
      } // else if()
      
      else if ( mAllToken.at( i + 1 ).type != "DOT" || mAllToken.at( i + 2 ).type != "LEFT-PAREN" ) {
        nToken.str = "(" ;
        nToken.type = "LEFT-PAREN" ;
        
        mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
        
        nToken.str = "." ;
        nToken.type = "DOT" ;
        
        mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
        
        pair = 0 ;
        
        for ( int j = i + 1 ; j < mAllToken.size() ; j++ ) {
          if ( mAllToken.at( j ).type == "LEFT-PAREN" ) {
            pair++ ;
            
          } // if()
          else if ( mAllToken.at( j ).type == "RIGHT-PAREN" ) {
            pair-- ;
            
            if ( pair == 0 ) {
              nToken.str = ")" ;
              nToken.type = "RIGHT-PAREN" ;
              
              mAllToken.insert( mAllToken.begin() + j, nToken ) ;
              
              j = mAllToken.size() ;
              
              rightParenCount++ ;
              
            } // if()
            
          } // else if()
          
        } // for()
        
        i = i + 2 ;
        
      } // else if()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // TranslateParen_Dot_Paren()
  
  void BuildNodeTree( NodePtr &head, int &locate ) {
    
    if ( mAllToken.at( locate ).type == "LEFT-PAREN" ) {
      head -> left = new Node ;
      head -> left -> str = "" ;
      head -> left -> type = "" ;
      head -> left -> left = NULL ;
      head -> left -> right = NULL ;
      
      head -> right = new Node ;
      head -> right -> str = "" ;
      head -> right -> str = "" ;
      head -> right -> left = NULL ;
      head -> right -> right = NULL ;
      
      locate++ ;
      
      BuildNodeTree( head -> left, locate ) ;
      BuildNodeTree( head -> right, locate ) ;
      
      // cout << "Locate : " << locate << endl ;
      
    } // if()
    
    else if ( mAllToken.at( locate ).type == "DOT" ) {
      locate++ ;
      
      BuildNodeTree( head, locate ) ;
      
    } // else if()
    
    else if ( mAllToken.at( locate ).type == "RIGHT-PAREN" ) {
      // cout << "Locate : " << locate << endl ;
      
      locate++ ;
      
      BuildNodeTree( head, locate ) ;
      
    } // else if ()
    
    else {
      head -> str = mAllToken.at( locate ).str ;
      head -> type = mAllToken.at( locate ).type ;
      
      locate++ ;
      
    } // else
    
  } // BuildNodeTree()
  
  // �ݨ�U�@�ӬO '(' �A�N�I�s�ۤv�C
  // �^�Ǫ��O��expression���̫�@��token���e�@��
  int ParenGrammar( int locate, bool &paren ) {
    string nowType = "" ;
    string nextType = "" ;
    bool dot = false ; // dot�O�_�w�g�X�{�L 
    bool isExpression = false ; // ��ܬO�_�����j�^�Ǫ� 
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      
      if ( i < mAllToken.size() - 1 ) {
        nowType = mAllToken.at( i ).type ;
        nextType = mAllToken.at( i + 1 ).type ;
      
        if ( nowType == "LEFT-PAREN" ) {
          if ( nextType == "DOT" ) {
            // UT ERROR
            mError_UT_LP = true ;
            
            mError_UT_char = '.' ;
            
            while ( cin.peek() != '\n' && cin.peek() != EOF ) {
              cin.get() ;
              
              cin.peek() ;
              
            } // while()
            
            if ( cin.peek() == EOF ) {
              mError = true ;
              
            } // if()
            
            paren = false ;
            
            mAllToken.clear() ;
            
            ChangeTokenInSameLine( true ) ;
            
            return mAllToken.size() ;
            
          } // if()
          
        } // if()
        
        else if ( nowType == "DOT" ) {
          // cout << "HERE?" << endl ;
          
          if ( !dot ) {
            dot = true ;
            
          } // if()
          
          if ( nextType == "DOT" ) {
            // UT ERROR
            mError_UT_LP = true ;
            
            ChangeTokenInSameLine( true ) ;
            
            mError_UT_char = '.' ;
            
            while ( cin.peek() != '\n' && cin.peek() != EOF ) {
              cin.get() ;
              
              cin.peek() ;
              
            } // while()
            
            if ( cin.peek() == EOF ) {
              mError = true ;
              
            } // if()
            
            paren = false ;
            
            mAllToken.clear() ;
            
            return mAllToken.size() ;
            
          } // if()
          
          else if ( nextType == "RIGHT-PAREN" ) {
            // UT ERROR
            mError_UT_LP = true ;
            
            ChangeTokenInSameLine( true ) ;
            
            mError_UT_char = ')' ;
            
            while ( cin.peek() != '\n' && cin.peek() != EOF ) {
              cin.get() ;
              
              cin.peek() ;
              
            } // while()
            
            if ( cin.peek() == EOF ) {
              mError = true ;
              
            } // if()
            
            paren = false ;
            
            mAllToken.clear() ;
            
            return mAllToken.size() ;
            
          } // else if()
          
        } // else if ()
        
        else if ( nowType == "RIGHT-PAREN" ) {
          if ( !isExpression ) {
            return i ;
            
          } // if()
          
          else if ( isExpression ) {
            isExpression = false ;
            
            if ( dot && nextType != "RIGHT-PAREN" ) {
              // UT ERROR
              mError_UT_RP = true ;
              
              ChangeTokenInSameLine( true ) ;
              
              mError_UT_char = mAllToken.at( i + 1 ).str[0] ;
              
              while ( cin.peek() != '\n' && cin.peek() != EOF ) {
                cin.get() ;
                
                cin.peek() ;
                
              } // while()
              
              if ( cin.peek() == EOF ) {
                mError = true ;
                
              } // if()
              
              paren = false ;
              
              mAllToken.clear() ;
              
              return mAllToken.size() ;
              
            } // if()
            
          } // else if()
          
        } // else if()
        
        // ��Ltype���F�� �A �å]�t���̷|���ͪ� error 
        else {
          if ( nextType != "RIGHT-PAREN" && dot ) {
            // UT ERROR
            mError_UT_RP = true ;
            
            ChangeTokenInSameLine( true ) ;
            
            mError_UT_char = mAllToken.at( i + 1 ).str[0] ;
            
            while ( cin.peek() != '\n' && cin.peek() != EOF ) {
              cin.get() ;
              
              cin.peek() ;
              
            } // while()
            
            if ( cin.peek() == EOF ) {
              mError = true ;
              
            } // if()
            
            paren = false ;
            
            mAllToken.clear() ;
            
            return mAllToken.size() ;
            
          } // if()
          
        } // else
        
        if ( nextType == "LEFT-PAREN" ) {
          // cout << "Test" << endl ;
          
          i = ParenGrammar( i + 1, paren ) ;
          
          // ��ܭ�q Expression �X�� 
          isExpression = true ;
          
          i-- ;
          
        } // if()
      
      } // if()
      
      // ��� .(expression). ���o�� 
      else if ( i == mAllToken.size() - 1 ) {
        if ( mAllToken.at( i ).type == "DOT" && dot ) {
          
          // UT_RIGHT PAREN ERROR
          mError_UT_RP = true ;
          
          ChangeTokenInSameLine( true ) ;
          
          mError_UT_char = '.' ;
          
          while ( cin.peek() != '\n' && cin.peek() != EOF ) {
            cin.get() ;
            
            cin.peek() ;
            
          } // while()
          
          if ( cin.peek() == EOF ) {
            mError = true ;
            
          } // if()
          
          paren = false ;
          
          mAllToken.clear() ;
          
          return mAllToken.size() ;
          
        } // if()
        
      } // else if ()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // ParenGrammar()
  
  // ���F ShowAllToken() �� output space 
  void PrintSpace( int count ) {
    for ( int i = 0 ; i < count ; i++ ) {
      cout << " " ;
      
    } // for()
    
  } // PrintSpace()
  
  // input��locate��ܧA�{�b����m
  // �nreturn�A�̫�s�b����m 
  // �쥻�O���F�� paren �M�ݪ� show�A����ӵo�{���Oparen�]�i�Hshow�X�� 
  // space �b�O���ثe�n�ŴX��
  // sameLine�b�O���e�@�� output token �O�_�� "("�A�ӨM�w�n���n output sapce 
  int ShowAllToken( int locate, int space, bool &sameLine ) {
    int skipRightParen = 0 ; // �J�� ".(" �n�O���A�o�N��n��output�@�� ')' 
    int rightCount = 0 ;
    int input ; // ���� ( space + rightCount ) * 2
    
    // cout << "In Pretty" << endl ;
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        if ( !sameLine ) {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
        } // if()
        
        sameLine = true ;
        
        cout << "( " ;
        
        rightCount++ ;
        
      } // if()
      
      else if ( mAllToken.at( i ).type == "RIGHT-PAREN" ) {
        if ( rightCount != 0 && skipRightParen == 0 ) {
          rightCount-- ;
          
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
          cout << ")" << endl ;
          
          if ( rightCount == 0 ) {
            return i ;
            
          } // if()
          
        } // if()
        
        else if ( skipRightParen > 0 ) {
          skipRightParen-- ;
          
        } // else if()
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" && mAllToken.at( i + 1 ).type == "LEFT-PAREN" ) {
        i++ ;
        skipRightParen ++ ;
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" && mAllToken.at( i + 1 ).type != "LEFT-PAREN" ) {
        if ( mAllToken.at( i + 1 ).type == "NIL" ) {
          i = i + 1 ;
          
        } // if()
        
        else {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
          PrintTokenCorrectly( mAllToken.at( i ) ) ;
          
          cout << endl ;
          
        } // else
        
      } // else if ()
      
      else {
        if ( !sameLine ) {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
        } // if()
        
        sameLine = false ;
        
        PrintTokenCorrectly( mAllToken.at( i ) ) ;
        
        cout << endl ;
        
      } // else
      
      if ( i < mAllToken.size() - 1 && mAllToken.at( i + 1 ).type == "LEFT-PAREN" ) {
        i = ShowAllToken( i + 1, rightCount + space, sameLine ) ;
        
      } // if()
      
    } // for()
    
    return mAllToken.size() - 1 ;
    
  } // ShowAllToken()
  
  // �B�z�@�ǳ·Ъ�token output�A e.g. float, nil... 
  void PrintTokenCorrectly( Token token ) {
    float float_out ;
    int int_out ;
    
    if ( token.type == "LEFT-PAREN" ) {
      cout << "(" ;
      
    } // if()
    
    else if ( token.type == "RIGHT-PAREN" ) {
      cout << ")" ;
      
    } // else if()
    
    else if ( token.type == "FLOAT" ) {
      float_out = atof( token.str.c_str() ) ;
      
      printf( "%.3f", float_out ) ;
      
    } // else if()
    
    else if ( token.type == "NIL" ) {
      cout << "nil" ;
      
    } // else if()
    
    else if ( token.type == "T" ) {
      cout << "#t" ;
      
    } // else if()
    
    else if ( token.type == "INT" ) {
      int_out = atoi( token.str.c_str() ) ;
      
      printf( "%d", int_out ) ;
      
    } // else if()
    
    else if ( token.type == "QUOTE" ) {
      cout << "quote" ;
      
    } // else if()
    
    else {
      cout << token.str ;
      
    } // else
    
  } // PrintTokenCorrectly()
  
  // �C���u��B�z��@��Quote�A���j��Quote�i�H�A���Ƽƪ�Quote���� 
  // �J�� Quote ����O�n���k�䪺expression�ɶ� 
  // �ڨC���^�Ǫ����O��expression���̫�@��token 
  int SingleQuoteTree( int locate ) {
    Token nToken ;
    int pair = 0 ;
    // bool hadParen = false ; // ��ܳo��expression�̭���paren�C(expression) ��O expression 
    
    // cout << "TEST" << endl ;
    // cout << mAllToken.size() << endl ;
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      
      if ( mAllToken.at( i ).type == "QUOTE" ) {
        
        for ( int j = i + 1 ; j < mAllToken.size() ; j++ ) {
          if ( mAllToken.at( j ).type == "QUOTE" ) {
            j = SingleQuoteTree( j ) ;
            
            // ����expression�ڭ̴N��Ū���A�ҥH�n+1 
            // j++ ;
            pair++ ;
            
          } // if()
          
          if ( j < mAllToken.size() && mAllToken.at( j ).type == "LEFT-PAREN" ) {
            // hadParen = true ;
            
            pair++ ;
            
          } // if()
          
          else if ( j < mAllToken.size() && mAllToken.at( j ).type == "RIGHT-PAREN" ) {
            // hadParen = true ;
            
            pair-- ;
            
          } // else if()
          
          if ( pair == 0 ) {
            nToken.str = ")" ;
            nToken.type = "RIGHT-PAREN" ;
            
            if ( j == mAllToken.size() - 1 ) {
              mAllToken.push_back( nToken ) ;
              
            } // if()
            else {
              mAllToken.insert( mAllToken.begin() + j + 1, nToken ) ;
              
            } // else
            
            nToken.str = "(" ;
            nToken.type = "LEFT-PAREN" ;
            
            mAllToken.insert( mAllToken.begin() + i, nToken ) ;
            
            return j + 2 ;
            
          } // if()
          
        } // for()
        
        i = mAllToken.size() ;
        
      } // if()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // SingleQuoteTree()
  
  // �Q��SingleQuoteTree�Ӱ��B�z���expression 
  void QuoteTree() {
    int locate = 0 ;
    
    for ( int i = 0 ; i < mAllToken.size() ; i++ ) {
      i = SingleQuoteTree( i ) ;
    
    } // for()
    
  } // QuoteTree()
  
  // �P�_�{�bmAllToken�����O���O(exit) 
  bool IsExist() {
    string end ;
    
    if ( mAllToken.size() == 5 && mAllToken.at( 3 ).type == "NIL" ) {
      end = mAllToken.at( 0 ).str + mAllToken.at( 1 ).str + mAllToken.at( 4 ).str ;
      
    } // if()
    
    if ( end == "(exit)" ) {
      return true ;
      
    } // if()
    
    return false ;
    
  } // IsExist()
  
public:
  
  // Ū�U�@�Ӧr��æ^�s��tokenList�� 
  // �C�@���u�B�z�@��token 
  void ReadString() {
    char nowCh = '\0' ;
    char nextCh ;
    string str = "" ;
    Token nToken ;
    bool doubleQuote = false ; // ��ܥ��b�B�zstring 
    bool paren = false ; // ��ܥ��b�B�z�A�� 
    bool oneToken = false ; // mAllToken���A�O�_��Token 
    bool comment = false ; // �������M����Ū�J�A���L��@�� 
    
    mLine = 1 ; // ��ܲ{�b�ĴX�� 
    mColumn = 0 ; // ��ܲ{�b�O�Ӧ檺�ĴX�Ӧr�� 
    mError = false ; // End Of File Error
    mError_UT_RP = false ; // Unexpected Token Error Right Paren
    mError_UT_LP = false ; // Unexpected Token Error Left Paren
    mError_NCQ = false ; // No Closing Quote Error
    mError_UT_char = '\0' ;
    mAllToken.clear() ;
    mHeadClass = NULL ; // �C���nŪ�s�� token �N�� head�� ��l�� 
    
    while ( ( !oneToken || paren ) && !mError && !mError_NCQ && !mError_UT_RP && !mError_UT_LP ) {
      
      nextCh = cin.peek() ;
      
      if ( nextCh == EOF ) {
        
        mError = true ;
        
        if ( str != "" ) {
          nToken.str = str ;
            
          nToken.type = TypeDecide( str ) ;
          
          mAllToken.push_back( nToken ) ;
          
          str = "" ;
          
        } // if()
        
      } // if()
      
      else if ( nextCh == '\n' ) {
        
        if ( str != "" ) {
          nToken.str = str ;
            
          nToken.type = TypeDecide( str ) ;
          
          mAllToken.push_back( nToken ) ;
          
          str = "" ;
          
          oneToken = true ;
          
        } // if()
        
        // �U�@��~�}�l��
        else if ( mTokenInSameLine ) {
          ChangeTokenInSameLine( false ) ;
          cin.get() ;
          mLine = 1 ;
          mColumn = 0 ;
          
        } // else if()
        
        else {
          cin.get() ;
          mLine++ ;
          mColumn = 0 ;
          
        } // else
        
      } // else if()
      // ���Ѫ����p 
      else if ( nextCh == ';' ) {
        comment = true ;
        
        if ( str != "" ) {
          nToken.str = str ;
            
          nToken.type = TypeDecide( str ) ;
          
          mAllToken.push_back( nToken ) ;
          
          str = "" ;
          
          oneToken = true ;
          
        } // if()
        
        // ���L�᭱�Ҧ��F�� 
        while ( nextCh != '\n' && nextCh != EOF ) {
          nowCh = cin.get() ;
          
          nextCh = cin.peek() ;
          
        } // while()
        
        if ( nextCh == EOF ) {
          mError = true ;
          
        } // if()
        
      } // else if()
      
      // STRING�����p 
      else if ( nextCh == '\"' && str == "" ) {
        String( nowCh, nextCh, str, doubleQuote ) ;
        
        oneToken = true ;
        
      } // else if()
      
      // ���OSeparator 
      else if ( !IsSeparator( nextCh ) ) {
        nowCh = cin.get() ;
        
        mColumn++ ;
        
        str = str + nowCh ;
        
      } // if()
      
      else if ( IsSeparator( nextCh ) ) {
        // str���F��A�ùJ��seperator 
        if ( str != "" ) {
          nToken.str = str ;
            
          nToken.type = TypeDecide( str ) ;
          
          mAllToken.push_back( nToken ) ;
          
          str = "" ;
          
          oneToken = true ;
          
        } // if()
        
        // str�S���F��A�ùJ��seperator 
        else if ( str == "" ) {
          nowCh = cin.get() ;
          
          mColumn++ ;
          
          // paren
          if ( nowCh == '(' || nowCh == ')' || nowCh == '\'' ) {
            
            paren = true ;
            
            str = str + nowCh ;
          
            nToken.str = str ;
              
            nToken.type = TypeDecide( str ) ;
            
            mAllToken.push_back( nToken ) ;
            
            str = "" ;
            
            oneToken = true ;
            
          } // if()
          
          else if ( nowCh != ' ' ) {
            str = str + nowCh ;
          
            nToken.str = str ;
              
            nToken.type = TypeDecide( str ) ;
            
            mAllToken.push_back( nToken ) ;
            
            str = "" ;
            
            oneToken = true ;
            
          } // if()
          
        } // else if()
        
      } // else if()
      
      if ( mAllToken.size() == 0 ) {
        oneToken = false ;
        
      } // if()
      
      else {
        oneToken = true ;
        
      } // else
      
      if ( oneToken && !mError && !mError_NCQ && !mError_UT_RP && !mError_UT_LP ) {
        ChangeTokenInSameLine( true ) ;
        
        // DOT�����W�X�{�A���D�Oparen == true 
        if ( mAllToken.size() == 1 && mAllToken.at( 0 ).str == "." ) {
          mError_UT_LP = true ;
          
          mError_UT_char = '.' ;
          
          nextCh = cin.peek() ;
          
          // �᭱����skip 
          while ( nextCh != '\n' && nextCh != EOF ) {
            nowCh = cin.get() ;
            
            nextCh = cin.peek() ;
            
            str = "" ;
            
          } // while()
          
          if ( nextCh == EOF ) {
            mError = true ;
            
          } // if()
          
        } // if()
        
      } // if() 
      
      if ( paren ) {
        ChangeTokenInSameLine( false ) ;
        
        // ��paren����k�ˬd 
        Paren( paren ) ;
        
        // ��End of file error �A�Bparen �� true ��ܡA
        // ��� mAllToken ���� �O�����ߪ� expression�A�o�ɭԴN������� 
        if ( mError ) {
          mAllToken.clear() ;
          
        } // if()
        
      } // if()
      
      if ( mError_NCQ || mError_UT_RP || mError_UT_LP ) {
        ChangeTokenInSameLine( true ) ;
        
      } // if()
      
    } // while()
    
    // �p�G�u���@�Ӹ`�I�A�٬O�n�ؾ� 
    if ( mAllToken.size() == 1 && mHeadClass == NULL ) {
      NodePtr walk = NULL ;
      
      mHeadClass = new Node ;
      
      walk = mHeadClass ;
      
      walk -> str = mAllToken.at( 0 ).str ;
      walk -> type = mAllToken.at( 0 ).type ;
      
      walk -> left = NULL ;
      walk -> right = NULL ;
      
    } // if()
    
  } // ReadString()
  
  // ��vector�����eshow�X�� 
  void TestShow() {
    float float_out = 0 ;
    
    for ( int i = 0 ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).type == "FLOAT" ) {
        float_out = atof( mAllToken.at( i ).str.c_str() ) ;
        
        printf( "No.%d %.3f", i + 1, float_out ) ;
        
        printf( " %s\n", mAllToken.at( i ).type.c_str() ) ;
        
      } // if()
      
      else {
        cout << "No." << i + 1 << ": " << mAllToken.at( i ).str << " " << mAllToken.at( i ).type << endl ;
        
      } // else
      
    } // for()
    
  } // TestShow()
  
  // ��Token show�X�Ӫ��P��
  void Show() {
    float float_out = 0 ;
    int int_out = 0 ;
    int leftparen_count = 0 ;
    
    // ��ShowAllToken���ϥΪ� 
    bool sameLine = false ;
    
    if ( mError_UT_LP ) {
      mAllToken.clear() ;
      
      cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " << 
              mLine << " Column " << mColumn << " is >>" << mError_UT_char << "<<" << endl << endl ;
      
      mError_UT_LP = false ;
      
      mAllToken.clear() ;
      
    } // if()
    
    if ( mError_UT_RP ) {
      mAllToken.clear() ;
      
      cout << "ERROR (unexpected token) : ')' expected when token at Line " << 
              mLine << " Column " << mColumn << " is >>" << mError_UT_char << "<<" << endl << endl ;
      
      mError_UT_RP = false ;
      
      mAllToken.clear() ;
      
    } // if()
    
    if ( mError_NCQ ) {
      
      // +1����]�O�]���ڥu���T��Ū�i�Ӥ~�|����column�A�Ӵ���ڬO��peek�� 
      cout << "ERROR (no closing quote) : END-OF-LINE encountered at Line " << mLine 
           << " Column " << mColumn + 1 << endl << endl ;
           
      mError_NCQ = false ;
      
      mAllToken.clear() ;
      
    } // if()
    
  } // Show()
  
  bool IsEnd() {
    string end = "" ;
    
    if ( mAllToken.size() == 5 && mAllToken.at( 3 ).type == "NIL" ) {
      end = mAllToken.at( 0 ).str + mAllToken.at( 1 ).str + mAllToken.at( 4 ).str ;
      
    } // if()
    
    if ( end == "(exit)" ) {
      return true ;
      
    } // if()
    
    return false ;
    
  } // IsEnd()
  
  // true�N��U�@��}�l��
  // false�N��o�@��}�l�� 
  void ChangeTokenInSameLine( bool signal ) {
    mTokenInSameLine = signal ;
    
  } // ChangeTokenInSameLine() 
  
  void Initial() {
    mError = false ;
    mError_NCQ = false ;
    mError_UT_RP = false ;
    mError_UT_LP = false ;
    ChangeTokenInSameLine( false ) ;
    
  } // Initial()
  
  // �bscanner���q�ɴN��error 
  bool HasSyntaxError() {
    if ( !mError_NCQ && !mError_UT_LP && !mError_UT_RP ) {
      return false ;
      
    } // if()
    
    return true ;
    
  } // HasSyntaxError()
  
  // �����\�إX��� 
  bool HasTree() {
    if ( mHeadClass != NULL ) {
      return true ;
      
    } // if()
    else {
      return false ;
      
    } // else
    
  } // HasTree()
  
  NodePtr GetTreeHead() {
    return mHeadClass ;
    
  } // GetTreeHead()
  
  // �p�G input �i�Ӫ��O symbol �B���Q define �L
  // ���n�^�ǵ� main �A����A�^�ǵ� Evaluate 
  bool IsSymbol( string &str ) {
    if ( mAllToken.size() == 1 && mAllToken.at( 0 ).type == "SYMBOL" ) {
      str = mAllToken.at( 0 ).str ;
      
      return true ;
      
    } // if()
    
    else {
      str = "NULL" ;
      
      return false ;
      
    } // else
    
  } // IsSymbol()
   
  void CleanMAllToken() {
    mAllToken.clear() ;
    
  } // CleanMAllToken()
  
  // �ݬO���OEND OF FILE ERROR 
  bool ReturnMError() {
    return mError ;
    
  } // ReturnMError()
  
}; // Scanner

class Evaluate {
  NodePtr mNowHead ; // �ثeŪ�J��Tree 
  NodePtr mOutputHead ; // �n��X��Tree 
  NodePtr mErrorHead ; // Error�o�ͮɡA�ҭn��X��Tree 
  vector <NodePtr> mHeadList ; // ���� define �L�� Tree 
  vector <string> mCommandList ; // command list
  
  bool mError ; // ������ERROR���o�� 
  bool mNonFunctionError ; 
  
  // ���F��Koutput�A�ڷ|���ª�½Ķfunction�h�i��
  // �ӳo�ӬO���U�ǳ� output �X�Ӫ��� 
  TokenList mAllToken ;  
  
  void TranslateTree_mAllToken( NodePtr head, bool end ) {
    Token nToken ;
    
    if ( head -> left != NULL && head -> left -> str == "" ) {
      nToken.str = "(" ;
      nToken.type = "LEFT-PAREN" ;
      mAllToken.push_back( nToken ) ;
      
      // cout << "( " ;
      TranslateTree_mAllToken( head -> left, false ) ;
      
    } // if()
    
    else if ( head -> left != NULL ) {
      TranslateTree_mAllToken( head -> left, false ) ;
      
    } // else if()
    
    if ( head -> right != NULL && head -> right -> left == NULL && head -> right -> right == NULL ) {
      TranslateTree_mAllToken( head -> right, true ) ;
      
    } // if()
    
    else if ( head -> right != NULL ) {
      TranslateTree_mAllToken( head -> right, false ) ;
      
    } // if()
      
    if ( head -> str != "" ) {
      
      if ( end ) {
        nToken.str = "." ;
        nToken.type = "DOT" ;
        mAllToken.push_back( nToken ) ;
        
        nToken.str = head -> str ;
        nToken.type = head -> type ;
        mAllToken.push_back( nToken ) ;
        
        
        nToken.str = ")" ;
        nToken.type = "RIGHT-PAREN" ;
        mAllToken.push_back( nToken ) ;
        
      } // if()
      
      else {
        nToken.str = head -> str ;
        nToken.type = head -> type ;
        mAllToken.push_back( nToken ) ;
        
      } // else
      
      return ;
      
    } // if()
    
  } // TranslateTree_mAllToken()
  
  string GetCommand( NodePtr head ) {
    
    if ( head == NULL ) {
      return "NO-COMMAND" ;
      
    } // if()
    
    else if ( head -> str == "" ) {
      head -> left = Eval( head -> left, false ) ;
      
      if ( head -> left == NULL ) {
        return "ERROR" ;
        
      } // if()
      
      return head -> left -> str ;
      
    } // if()
    
    // �i�Ӫ��i��O�@�ӳQ�w�q�L�� symbol 
    else if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      
      // ��symbol�N�Ofunction 
      for ( int i = 0 ; i < mCommandList.size() ; i++ ) {
        if ( head -> str == mCommandList.at( i ) ) {
          
          return head -> str ;  
          
        } // if()
        
      } // for()
      
      
      if ( IsSymbolDefined( head -> str ) ) {
        return "SYMBOL" ;
        
      } // if()
      
      else {
        // �S���Q�w�q�L�� SYMBOL 
        mError = true ;
        cout << "ERROR (unbound symbol) : " ;
        
        mErrorHead = new Node ;
        mErrorHead -> str = head -> str ;
        mErrorHead -> type = "SYMBOL" ;
        mErrorHead -> right = NULL ;
        mErrorHead -> left = NULL ;
        
        return "NO-COMMAND" ;
        
      } // else
      
    } // else if()
    
    // ��¤@�� atom�A���]�t symbol 
    else if ( head -> type != "" && head -> left == NULL && head -> right == NULL ) {
      return "OUTPUT" ;
      
    } // else if()
    
    return "NO-COMMAND" ;
    
  } // GetCommand()
  
  // �����Q�w�q�� symbol �i�J mHeadList
  // �x�s�i mHeadList �� head�A left ���O symbol�A right -> left �~�O symbol �����e 
  // �]����� input �i�Ӫ��榡�O ( define a (���e) . nil ) 
  // �i�H�b�ۦP symbol �����Ʃw�q 
  // �� Output �@�ӵ��G 
  NodePtr Define( NodePtr head ) {
    NodePtr now_head ;
    NodePtr now ; // �n��i �x�s�C �����Y 
    NodePtr walk ;
    int count = 0 ; // �p��argument���ƶq 
    
    now_head = new Node ;
    
    now = now_head ;
    now -> str = "" ;
    now -> type = "" ;
    
    walk = head -> right ;
    
    if ( head -> str == "define" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      
      if ( walk -> right == NULL ) {
        if ( walk -> type != "NIL" ) {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        else if ( count > 2 ) {
          
          mError = true ;
          
          cout << "ERROR (DEFINE format) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // else if()
        
      } // if()
      
      else if ( walk -> type != "" ) {
        // ERROR
        mError = true ;
        
        if ( walk -> type == "NIL" ) {
          
          mError = true ;
          
          cout << "ERROR (DEFINE format) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        else {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // else
        
      } // else if()
      
      else if ( walk -> type == "" ) {
        count++ ;
        
      } // else if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      // Error
      mError = true ;
    
      cout << "ERROR (DEFINE format) : " ;
      
      mErrorHead = head ;
      
      return head ;
          
    } // if()
    
    
    walk = head -> right ;
    
    now -> left = walk -> left ;
    
    // �ǳƭn�Q�w�q���F�襲��OSYMBOL 
    if ( now -> left -> type != "SYMBOL" || IsCommand( now -> left -> str ) ) {
      // ERROR
      mError = true ;
      
      cout << "ERROR (DEFINE format) : " ;
          
      mErrorHead = head ;
          
      return head ;
      
    } // if()
    
    now -> right = new Node ;
    now = now -> right ;
    
    now -> str = "" ;
    now -> type = "" ;
    
    walk = walk -> right ;
    
    now -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    now -> right = new Node ;
    now = now -> right ;
    
    now -> str = "nil" ;
    now -> type = "NIL" ;
    
    now -> right = NULL ;
    now -> left = NULL ;
    
    // ������i mHeadList
    if ( mHeadList.size() > 0 ) {
      for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
        if ( now_head -> left -> str == mHeadList.at( i ) -> left -> str ) {
          mHeadList.insert( mHeadList.begin() + i, now_head ) ;
          
          mHeadList.erase( mHeadList.begin() + i + 1 ) ;
          
          i = mHeadList.size() ;
          
        } // if()
        
        else if ( i == mHeadList.size() - 1 ) {
          mHeadList.push_back( now_head ) ;
          
          i = mHeadList.size() ;
          
        } // else if()
        
      } // for() 
    
    } // if()
    
    else {
      
      mHeadList.push_back( now_head ) ;
      
    } // else
    
    cout << now_head -> left -> str << " defined" << endl << endl ;
    
    return NULL ;
    
  } // Define()
  
  // ��ثemHeadList���������X 
  void ShowMHeadList() {
    for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
      cout << "Number : " << i + 1 << endl ;
      
      ShowTree( mHeadList.at( i ) -> right -> left ) ;
      
      cout << endl << endl ;
      
    } // for()
    
  } // ShowMHeadList()
  
    // ���C��()�̭�����dot 
  int TranslateParen_Dot( int locate ) {
    int nowLocate = locate ;
    bool dot = false ;
    Token nToken ;
    
    for ( int i = nowLocate + 1 ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        
        i = TranslateParen_Dot( i ) ;
        
      } // if()
      
      else if ( mAllToken.at( i ).type == "RIGHT-PAREN" ) {
        if ( !dot ) {
          nToken.str = "." ;
          nToken.type = "DOT" ;
          
          mAllToken.insert( mAllToken.begin() + i, nToken ) ;
          
          nToken.str = "nil" ;
          nToken.type = "NIL" ;
          
          mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
          
          return i + 2 ;
          
        } // if()
        
        return i ;
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" ) {
        dot = true ;
        
      } // else if()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // TranslateParen_Dot()
  
  int TranslateParen_Dot_Paren( int locate ) {
    int rightParenCount = 0 ; // �p��h�s�y�X�Ӫ�right-paren 
    int pair = 0 ;
    Token nToken ;
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      // cout << i << endl ;
      
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        i = TranslateParen_Dot_Paren( i + 1 ) ;
        
      } // if()
      
      if ( mAllToken.at( i + 1 ).type == "RIGHT-PAREN" ) {
        return i + rightParenCount + 1 ;
        
      } // if()
      
      // ���paren��end 
      else if ( mAllToken.at( i + 1 ).type == "DOT" ) {
        i = i + 1 ;
        
      } // else if()
      
      else if ( mAllToken.at( i + 1 ).type != "DOT" || mAllToken.at( i + 2 ).type != "LEFT-PAREN" ) {
        nToken.str = "(" ;
        nToken.type = "LEFT-PAREN" ;
        
        mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
        
        nToken.str = "." ;
        nToken.type = "DOT" ;
        
        mAllToken.insert( mAllToken.begin() + i + 1, nToken ) ;
        
        pair = 0 ;
        
        for ( int j = i + 1 ; j < mAllToken.size() ; j++ ) {
          if ( mAllToken.at( j ).type == "LEFT-PAREN" ) {
            pair++ ;
            
          } // if()
          else if ( mAllToken.at( j ).type == "RIGHT-PAREN" ) {
            pair-- ;
            
            if ( pair == 0 ) {
              nToken.str = ")" ;
              nToken.type = "RIGHT-PAREN" ;
              
              mAllToken.insert( mAllToken.begin() + j, nToken ) ;
              
              j = mAllToken.size() ;
              
              rightParenCount++ ;
              
            } // if()
            
          } // else if()
          
        } // for()
        
        i = i + 2 ;
        
      } // else if()
      
    } // for()
    
    return mAllToken.size() ;
    
  } // TranslateParen_Dot_Paren()
  
  // input��locate��ܧA�{�b����m
  // �nreturn�A�̫�s�b����m 
  // �쥻�O���F�� paren �M�ݪ� show�A����ӵo�{���Oparen�]�i�Hshow�X�� 
  // space �b�O���ثe�n�ŴX��
  // sameLine�b�O���e�@�� output token �O�_�� "("�A�ӨM�w�n���n output sapce 
  int ShowAllToken( int locate, int space, bool &sameLine ) {
    int skipRightParen = 0 ; // �J�� ".(" �n�O���A�o�N��n��output�@�� ')' 
    int rightCount = 0 ;
    int input ; // ���� ( space + rightCount ) * 2
    
    // cout << "In Pretty" << endl ;
    
    for ( int i = locate ; i < mAllToken.size() ; i++ ) {
      if ( mAllToken.at( i ).type == "LEFT-PAREN" ) {
        if ( !sameLine ) {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
        } // if()
        
        sameLine = true ;
        
        cout << "( " ;
        
        rightCount++ ;
        
      } // if()
      
      else if ( mAllToken.at( i ).type == "RIGHT-PAREN" ) {
        if ( rightCount != 0 && skipRightParen == 0 ) {
          rightCount-- ;
          
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
          cout << ")" << endl ;
          
          if ( rightCount == 0 ) {
            return i ;
            
          } // if()
          
        } // if()
        
        else if ( skipRightParen > 0 ) {
          skipRightParen-- ;
          
        } // else if()
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" && mAllToken.at( i + 1 ).type == "LEFT-PAREN" ) {
        i++ ;
        skipRightParen ++ ;
        
      } // else if()
      
      else if ( mAllToken.at( i ).type == "DOT" && mAllToken.at( i + 1 ).type != "LEFT-PAREN" ) {
        if ( mAllToken.at( i + 1 ).type == "NIL" ) {
          i = i + 1 ;
          
        } // if()
        
        else {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
          PrintTokenCorrectly( mAllToken.at( i ) ) ;
          
          cout << endl ;
          
        } // else
        
      } // else if ()
      
      else {
        if ( !sameLine ) {
          input = ( space + rightCount ) * 2 ;
          
          PrintSpace( input ) ;
          
        } // if()
        
        sameLine = false ;
        
        PrintTokenCorrectly( mAllToken.at( i ) ) ;
        
        cout << endl ;
        
      } // else
      
      if ( i < mAllToken.size() - 1 && mAllToken.at( i + 1 ).type == "LEFT-PAREN" ) {
        i = ShowAllToken( i + 1, rightCount + space, sameLine ) ;
        
      } // if()
      
    } // for()
    
    return mAllToken.size() - 1 ;
    
  } // ShowAllToken()
  
  // �B�z�@�ǳ·Ъ�token output�A e.g. float, nil... 
  void PrintTokenCorrectly( Token token ) {
    float float_out ;
    int int_out ;
    
    if ( token.type == "LEFT-PAREN" ) {
      cout << "(" ;
      
    } // if()
    
    else if ( token.type == "RIGHT-PAREN" ) {
      cout << ")" ;
      
    } // else if()
    
    else if ( token.type == "FLOAT" ) {
      float_out = atof( token.str.c_str() ) ;
      
      printf( "%.3f", float_out ) ;
      
    } // else if()
    
    else if ( token.type == "NIL" ) {
      cout << "nil" ;
      
    } // else if()
    
    else if ( token.type == "T" ) {
      cout << "#t" ;
      
    } // else if()
    
    else if ( token.type == "INT" ) {
      int_out = atoi( token.str.c_str() ) ;
      
      printf( "%d", int_out ) ;
      
    } // else if()
    
    else if ( token.type == "QUOTE" ) {
      cout << "quote" ;
      
    } // else if()
    
    else if ( token.type == "SYMBOL-COMMAND" ) {
      if ( mError && !mNonFunctionError ) {
        cout << token.str ;
        
      } // if()
      
      else {
        cout << "#<procedure " << token.str << ">" ;  
        
      } // else
      
    } // else if()
    
    else {
      cout << token.str ;
      
    } // else
    
  } // PrintTokenCorrectly()
  
  void PrintSpace( int count ) {
    for ( int i = 0 ; i < count ; i++ ) {
      cout << " " ;
      
    } // for()
    
  } // PrintSpace()
  
  NodePtr Cons( NodePtr head ) {
    NodePtr walk = NULL ; 
    NodePtr first = NULL ;
    NodePtr second = NULL ;
    NodePtr combine = new Node ; // combine = first + second
    bool error = false ;
    
    int count = 0 ;
    
    walk = head -> right ;
    
    if ( head -> str == "cons" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> right == NULL ) {
        if ( walk -> type != "NIL" ) {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        else if ( count != 2 ) {
          mError = true ;
          
          NodePtr result = new Node ;
          
          result -> str = "cons" ;
          result -> type = "SYMBOL" ;
          
          result -> right = NULL ;
          result -> left = NULL ;
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // else if()
        
      } // if()
      
      else if ( walk -> type != "" ) {
        // ERROR
        mError = true ;
        
        if ( walk -> type == "NIL" ) {
          NodePtr result = new Node ;
          
          result -> str = "cons" ;
          result -> type = "SYMBOL" ;
          
          result -> right = NULL ;
          result -> left = NULL ;
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // if()
        
        else {
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // else
        
      } // else if()
      
      count++ ;
      
      walk = walk -> right ;
      
    } // while()
    
    
    walk = head -> right ;
    
    first = walk -> left ;
    
    walk = walk -> right ;
    
    second = walk -> left ;
    
    combine -> str = "" ;
    combine -> type = "" ;
    combine -> left = NULL ;
    combine -> right = NULL ;
    
    first = Eval( first, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    second = Eval( second, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    combine -> left = first ;
    combine -> right = second ;
    
    return combine ;
    
  } // Cons()
  
  NodePtr List( NodePtr head ) {
    NodePtr walk = NULL ; // ���b�s���W 
    NodePtr combine = new Node ; // combine = all
    NodePtr combine_head = combine ; // combine ���Y 
    NodePtr now = NULL ; // �s���W���C�Ӥ��e 
    
    if ( head -> str == "list" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    walk = head -> right ;
    
    now = walk -> left ;
    
    combine -> str = "" ;
    combine -> type = "" ;
    combine -> left = NULL ;
    combine -> right = NULL ;
    
    // �k�䪽���O NIL 
    if ( walk -> type == "NIL" ) {
      combine -> str = "nil" ;
      combine -> type = "NIL" ;
      
    } // if()
    
    while ( walk -> type != "NIL" ) {
      
      if ( walk -> right == NULL ) {
        // ERROR
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      now = Eval( now, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      combine -> left = now ;
      combine -> right = new Node ;
      combine = combine -> right ;
      
      combine -> str = "" ;
      combine -> type = "" ;
      combine -> left = NULL ;
      combine -> right = NULL ;
      
      walk = walk -> right ;
      
      now = walk -> left ;
      
    } // while()
    
    combine -> str = "nil" ;
    combine -> type = "NIL" ;
    
    return combine_head ;
    
  } // List()
  
  // �� right part of pair �� output �X�� 
  // cdr �᭱�@�w�n���@�Ӿ� �A�N��J�� quote �L�]�O�@�ӫ��O 
  // �]�� cdr �b�B�z�o�@�����O�@�ӨS�� quote �� tree 
  NodePtr Cdr( NodePtr head ) {
    NodePtr walk = head -> right ; // ���s�� 
    NodePtr rightPart = NULL ;
    
    NodePtr result = NULL ; // ��X error �n output ���� 
    int count = 0 ;
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "cdr" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "cdr" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    
    // �ݦ��S�� command 
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // �̫᭱�� "-> right" �O���V�Ӵʾ𪺥k��  
    rightPart = walk -> left ;
      
    if ( rightPart -> str == "" ) {
      rightPart = rightPart -> right ;
        
    } // if()
    else {
      // ERROR
      mError = true ;
      
      cout << "ERROR (cdr with incorrect argument type) : " ;
      
      mErrorHead = rightPart ;
      
      return rightPart ;
      
    } // else
    
    return rightPart ;
    
  } // Cdr()
  
  // �� left part of pair �� output �X�� 
  // car �᭱�@�w�n���@�Ӿ� 
  NodePtr Car( NodePtr head ) {
    NodePtr walk = head -> right ; // ���s�� 
    NodePtr leftPart = NULL ;
    NodePtr result = NULL ; // ��X error �n output ���� 
    int count = 0 ;
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "car" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "car" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        result -> str = "car" ;
        result -> type = "SYMBOL" ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    
    // �ݦ��S�� command 
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // �̫᭱�� "-> left" �O���V�Ӵʾ𪺥��� 
    leftPart = walk -> left ;
      
    if ( leftPart -> str == "" ) {
      leftPart = leftPart -> left ;
        
    } // if()
    
    else {
      // ERROR
      mError = true ;
      
      cout << "ERROR (car with incorrect argument type) : " ;
      
      mErrorHead = leftPart ;
      
      return leftPart ;
      
    } // else
    
    return leftPart ;
    
  } // Car()
  
  NodePtr IsAtom( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    NodePtr value ;
    NodePtr result = new Node ;
    int count = 0 ;
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "atom?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "atom?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // atom? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    
    // �O Atom 
    else if ( walk -> left -> type == "INT" || walk -> left -> type == "SYMBOL-COMMAND" ||
              walk -> left -> type == "FLOAT" || walk -> left -> type == "STRING" ||
              walk -> left -> type == "NIL" || walk -> left -> type == "T" ) {
      result -> str = "#t" ;
      result -> type = "T" ;
    
    } // else if()
    
    else if ( walk -> left -> type == "SYMBOL" ) {
      if ( IsSymbolDefined( walk -> left -> str ) ) {
        value = GetSymbolTree( walk -> left -> str ) ;
        
        if ( value -> left -> type == "INT" || walk -> left -> type == "SYMBOL-COMMAND" ||
             value -> left -> type == "FLOAT" || value -> left -> type == "STRING" ||
             value -> left -> type == "NIL" || value -> left -> type == "T" ) {
          result -> str = "#t" ;
          result -> type = "T" ;
          
        } // if()
        
        else {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // else
        
      } // if()
      
      else {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // else
      
    } // else if()
    
    // ���O Atom 
    else {
      result -> str = "nil" ;
      result -> type = "NIL" ;
      
    } // else
    
    return result ;
    
  } // IsAtom()
  
  NodePtr IsPair( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    NodePtr value ;
    NodePtr result = new Node ;
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "pair?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "pair?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // �O Atom �A���O Pair 
    if ( walk -> left -> type == "INT" || walk -> left -> type == "SYMBOL-COMMAND" ||
         walk -> left -> type == "FLOAT" || walk -> left -> type == "STRING" ||
         walk -> left -> type == "NIL" || walk -> left -> type == "T" ) {
      result -> str = "nil" ;
      result -> type = "NIL" ;
    
    } // if()
    
    else if ( walk -> left -> type == "SYMBOL" ) {
      if ( IsSymbolDefined( walk -> left -> str ) ) {
        value = GetSymbolTree( walk -> left -> str ) ;
        
        if ( value -> left -> type == "INT" || walk -> left -> type == "SYMBOL-COMMAND" ||
             value -> left -> type == "FLOAT" || value -> left -> type == "STRING" ||
             value -> left -> type == "NIL" || value -> left -> type == "T" ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // if()
        
        else {
          result -> str = "#t" ;
          result -> type = "T" ;
          
        } // else
        
      } // if()
      
      else {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // else
      
    } // else if()
    
    // ���O Atom �A�O Pair 
    else {
      result -> str = "#t" ;
      result -> type = "T" ;
      
    } // else
    
    return result ;
    
  } // IsPair()
  
  NodePtr IsList( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    NodePtr result = new Node ;
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "list?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "list?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // �h "���e" ���ˬd 
    value = walk -> left ;
    
    while ( value != NULL ) {
      
      if ( value -> right == NULL ) {
        if ( value -> type == "NIL" ) {
          result -> str = "#t" ;
          result -> type = "T" ;
          
        } // if()
        else {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // else
        
      } // if()
      
      else {
        if ( value -> type != "" ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          value = NULL ;
          
        } // if()
        
      } // else
      
      value = value -> right ;
      
    } // while()
      
    
    return result ;
    
  } // IsList()
  
  NodePtr IsNull( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    NodePtr result = new Node ;
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "null?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "null?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;    
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Null? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    
    else if ( walk -> left -> type == "NIL" ) {
      result -> str = "#t" ;
      result -> type = "T" ;
      
    } // else if()
    
    else {
      result -> str = "nil" ;
      result -> type = "NIL" ;
      
    } // else
    
    return result ;
    
  } // IsNull()
  
  NodePtr IsInteger( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    
    NodePtr result = new Node ;
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "integer?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "integer?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Integer? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
      mError = true ;
      
    } // if()
    else {
      value = walk -> left ;
      
      if ( value -> type == "INT" ) {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ;
        
      } // else
      
    } // else
    
    return result ;
    
  } // IsInteger()
  
  NodePtr IsReal( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    NodePtr result = new Node ;
    
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    
    if ( GetCommand( head ) == "real" ) {
      result -> str = "real?" ;
      
    } // if()
    
    else {
      result -> str = "number?" ;
      
    } // else
    
    if ( ( head -> str == "real?" || head -> str == "number?" ) && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;  
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Real? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    else {
      value = walk -> left ;
      
      if ( value -> type == "INT" || value -> type == "FLOAT" ) {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ; 
        
      } // else
      
    } // else
    
    return result ;
    
  } // IsReal()
  
  NodePtr IsString( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    NodePtr result = new Node ;
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    result -> str = "string?" ;
    
    if ( head -> str == "string?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ; 
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Real? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    else {
      value = walk -> left ;
      
      if ( value -> type == "STRING" ) {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ;
        
      } // else
      
    } // else
    
    return result ;
    
  } // IsString()
  
  NodePtr IsBoolean( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    
    NodePtr result = new Node ;
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    result -> str = "boolean?" ;
    
    if ( head -> str == "boolean?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Real? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    else {
      value = walk -> left ;
      
      if ( value -> type == "NIL" || value -> type == "T" ) {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ;
        
      } // else
      
    } // else
    
    return result ;
    
  } // IsBoolean()
  
  // �n�� quote 
  NodePtr IsSymbol( NodePtr head ) {
    // �s�� 
    NodePtr walk = head -> right ;
    // "���e" ���Y 
    NodePtr value ;
    NodePtr result = new Node ;
    
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    result -> str = "symbol?" ;
    
    if ( head -> str == "symbol?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ; 
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // Symbol? �᭱���򳣨S�� 
    if ( walk -> left == NULL ) {
      // ERROR 
      
    } // if()
    
    else {
      value = walk -> left ;
      
      if ( value -> type == "SYMBOL" ) {
        result -> str = "#t" ;
        result -> type = "T" ;
        
      } // if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ;
        
      } // else
      
    } // else()
    
    return result ;
    
  } // IsSymbol()
  
  NodePtr Caculate( NodePtr head ) {
    NodePtr result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    
    string command = GetCommand( head ) ;
    
    if ( command == "+" ) {
      result -> str = "+" ;
      
    } // if()
    
    else if ( command == "-" ) {
      result -> str = "-" ;
      
    } // else if()
    
    else if ( command == "*" ) {
      result -> str = "*" ;
      
    } // else if()
    
    else if ( command == "/" ) {
      result -> str = "/" ;
      
    } // else if()
    
    
    if ( ( head -> str == "+" || head -> str == "-" || head -> str == "*" || head -> str == "/" ) && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    
    // �s�� 
    NodePtr walk = head -> right ;
    stringstream ss ;
    
    NodePtr now = walk -> left ; // �s���W���C�Ӥ��e 
    
    NodePtr sum_node = new Node ;
    
    double sum = 0 ; // �`�M 
    double value = 0 ; // �n�Q���p�⪺�Ʀr
    
    int tool = 0 ; // ���Ʀr�ഫ���u�� 
    
    bool flt = false ; // �ݦ��S�����g�X�{�L float 
    
    // cout << "In the functin" << endl ;
    
    
    int count = 0 ;
    
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    sum_node -> left = NULL ;
    sum_node -> right = NULL ;
    
    sum_node -> type = "INT" ;
    sum_node -> str = "0" ;
    
    // ��Ĥ@�ӭȵ� sum 
    // now �O�@�� symbol 
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    now = walk -> left ;
    
    // �N�u�O�Ʀr 
    if ( now -> type == "FLOAT" || now -> type == "INT" ) {
      // cout << now -> str << endl ;
      
      stringstream ss1 ;
      
      ss1 << now -> str ;
      ss1 >> sum ;
      
      // cout << value << endl ;
      
      if ( now -> type == "FLOAT" ) {
        flt = true ;
        
      } // if()
      
    } // if
    
    // �D�Ʀr 
    else {
      // ERROR 
      mError = true ;
      
      if ( command == "+" ) {
        cout << "ERROR (+ with incorrect argument type) : " ;
        
      } // if()
      
      else if ( command == "-" ) {
        cout << "ERROR (- with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "*" ) {
        cout << "ERROR (* with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "/" ) {
        cout << "ERROR (/ with incorrect argument type) : " ;
        
      } // else if()
      
      mErrorHead = now ;
      
      return NULL ;
      
    } // else
    
    walk = walk -> right ;
      
    now = walk -> left ;
    
    while ( walk -> type != "NIL" ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      now = walk -> left ;
      
      // �N�u�O�Ʀr 
      if ( now -> type == "FLOAT" || now -> type == "INT" ) {
        // cout << now -> str << endl ;
        stringstream ss2 ;
        
        ss2 << now -> str ;
        ss2 >> value ;
        
        // cout << value << endl ;
        
        if ( now -> type == "FLOAT" ) {
          flt = true ;
          
        } // if()
        
      } // if
      
      // �D�Ʀr 
      else {
        // ERROR 
        mError = true ;
        
        if ( command == "+" ) {
          cout << "ERROR (+ with incorrect argument type) : " ;
          
        } // if()
        
        else if ( command == "-" ) {
          cout << "ERROR (- with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "*" ) {
          cout << "ERROR (* with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "/" ) {
          cout << "ERROR (/ with incorrect argument type) : " ;
          
        } // else if()
        
        mErrorHead = now ;
        
        return NULL ;
        
      } // else
      
      if ( command == "+" ) {
        // cout << sum << "\t" << value << endl ;
        
        sum = sum + value ;
        
      } // if()
    
      else if ( command == "-" ) {
        
        
        sum = sum - value ;
        
      } // else if()
      
      else if ( command == "*" ) { 
        
        sum = sum * value ;
        
      } // else if ()
      
      else if ( command == "/" ) {
        sum = sum / value ;
        
        if ( value == 0 ) {
          // ERROR
          
          mError = true ;
          
          cout << "ERROR (division by zero) : " ;
          
          mErrorHead = new Node ;
          mErrorHead -> str = "/" ;
          mErrorHead -> type = "SYMBOL" ;
          mErrorHead -> right = NULL ;
          mErrorHead -> left = NULL ;
          
          return NULL ;
          
        } // if()
        
      } // else if()
      
      if ( !flt ) {
        tool = sum ;
        
        sum = tool ;
        
      } // if()
      
      walk = walk -> right ;
      
      now = walk -> left ;
      
    } // while()
    
    stringstream ss3 ;
    
    ss3 << sum ;
    
    ss3 >> sum_node -> str ;
    
    
    if ( flt ) {
      sum_node -> type = "FLOAT" ;
      
    } // if()
    
    return sum_node ;
    
  } // Caculate()
  
  NodePtr Not( NodePtr head ) {
    NodePtr walk = head -> right ;
    
    NodePtr now = NULL ; // �s���W���C�Ӥ��e 
    
    NodePtr result = new Node ;
    
    
    int count = 0 ;
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "not" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "not" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( count > 1 ) {
        mError = true ;
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ; 
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    now = walk -> left ; // �s���W���C�Ӥ��e 
    
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ; 
    
    if ( now -> type == "NIL" ) {
      result -> str = "#t" ;
      result -> type = "T" ;
      
    } // if()
    
    else {
      result -> str = "nil" ;
      result -> type = "NIL" ;
      
    } // else()
    
    return result ;
    
  } // Not()
  
  NodePtr And( NodePtr head ) {
    NodePtr walk = head -> right ;
    
    NodePtr value = NULL ; // �C�@�`�s�������e 
    
    NodePtr result = NULL ;
    
    bool finished = false ;
    
    
    result = new Node ;
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    result -> str = "and" ;
      
    
    if ( head -> str == "and" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    result = NULL ;
    
    walk = head -> right ;
    value = walk -> left ;
    
    
    while ( walk -> type != "NIL" && !finished ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      value = walk -> left ;
      
      if ( value -> type == "NIL" || walk -> right -> type == "NIL" ) {
        finished = true ;
        
        result = value ;
        
      } // if()
      
      walk = walk -> right ;
      
      value = walk -> left ;
      
    } // while()
    
    return result ;
    
  } // And()
  
  NodePtr Or( NodePtr head ) {
    NodePtr walk = head -> right ;
    
    NodePtr value = NULL  ; // �C�@�`�s�������e 
    
    NodePtr result = NULL ;
    
    bool finished = false ;
    
    
    int count = 0 ;
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    result -> str = "and" ;
      
    
    if ( head -> str == "or" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    result = NULL ;
    
    walk = head -> right ;
    
    value = walk -> left ;
    
    while ( walk -> type != "NIL" && !finished ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      value = walk -> left ;
      
      if ( value -> type != "NIL" || walk -> right -> type == "NIL" ) {
        finished = true ;
        
        result = value ;
        
      } // if()
      
      walk = walk -> right ;
      
      value = walk -> left ;
      
    } // while()
    
    return result ;
    
  } // Or()
  
  // �Ʀr��j�p 
  NodePtr IntBigSmall( NodePtr head ) {
    string command = "" ;
    stringstream ss ;
    
    NodePtr walk = head -> right ;
    NodePtr now = NULL ;
    
    NodePtr result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    bool finished = false ;
    
    double num = 0 ; // �n���Ӥ�j�p�Ʀr 
    double contest = 0 ; // num����� 
    
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    
    if ( GetCommand( head ) == ">" ) {
      result -> str = ">" ;
      
    } // if()
    
    else if ( GetCommand( head ) == ">=" ) {
      result -> str = ">=" ;
      
    } // else if()
    
    else if ( GetCommand( head ) == "<" ) {
      result -> str = "<" ;
      
    } // else if()
    
    else if ( GetCommand( head ) == "<=" ) {
      result -> str = "<=" ;
      
    } // else if()
    
    else if ( GetCommand( head ) == "=" ) {
      result -> str = "=" ;
      
    } // else if()
      
    
    if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    now = walk -> left ;
    result = new Node ;
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    command = head -> left -> str ;
    
    // �Ĥ@�ӼƦr 
    walk -> left = Eval( walk -> left, false ) ; 
    
    if ( mError ) {
      return NULL ;
      
    } // if()  
    
    now = walk -> left ;
    
    // �O�Ʀr 
    if ( now -> type == "INT" || now -> type == "FLOAT" ) {
      ss << now -> str ;
      ss >> num ;
      
      walk = walk -> right ;
      
    } // if()
    
    else {
      // ERROR
      finished = true ;
      
      mError = true ;
      
      if ( command == ">" ) {
        cout << "ERROR (> with incorrect argument type) : " ;
        
      } // if()
      
      else if ( command == ">=" ) {
        cout << "ERROR (>= with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "<" ) {
        cout << "ERROR (< with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "<=" ) {
        cout << "ERROR (<= with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "=" ) {
        cout << "ERROR (= with incorrect argument type) : " ;
        
      } // else if()
      
      mErrorHead = now ;
      
      return NULL ;
      
    } // else
    
    while ( walk -> type != "NIL" ) {
      stringstream ss1 ;
      
      walk -> left = Eval( walk -> left, false ) ; 
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      now = walk -> left ;
      
      if ( now -> type == "INT" || now -> type == "FLOAT" ) {
        ss1 << now -> str ;
        ss1 >> contest ;
        
      } // if()
      
      else {
        // ERROR
        finished = true ;
        
        mError = true ;
        
        if ( command == ">" ) {
          cout << "ERROR (> with incorrect argument type) : " ;
          
        } // if()
        
        else if ( command == ">=" ) {
          cout << "ERROR (>= with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "<" ) {
          cout << "ERROR (< with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "<=" ) {
          cout << "ERROR (<= with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "=" ) {
          cout << "ERROR (= with incorrect argument type) : " ;
          
        } // else if()
        
        mErrorHead = now ;
        
        return NULL ;
        
      } // else
      
      if ( command == ">" ) {
        if ( num <= contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // if()
        
      } // if()
      
      else if ( command == ">=" ) {
        if ( num < contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      else if ( command == "<" ) {
        if ( num >= contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      else if ( command == "<=" ) {
        if ( num > contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      else if ( command == "=" ) {
        if ( num != contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // if()
        
      } // else if()
      
      num = contest ;
      
      walk = walk -> right ;
      
    } // while()
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    else if ( result -> str == "" ) {
      result -> str = "#t" ;
      result -> type = "T" ;
      
      return result ;
      
    } // else if ()
    
    else {
      return result ;
      
    } // else
    
  } // IntBigSmall()
  
  // string ��j�p 
  NodePtr StringBigSmall( NodePtr head ) {
    string command = "" ;
    
    NodePtr walk = head -> right ;
    NodePtr now = NULL ;
    
    NodePtr result = new Node ;
    result -> str = "" ;
    result -> type = "STRING" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    bool finished = false ;
    
    string challenge = "" ; // �n���Ӥ�j�p string
    string contest = "" ; // challenge����� 
    
    
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    result -> type = "SYMBOL" ;
    
    if ( GetCommand( head ) == "string-append" ) {
      result -> str = "string-append" ;
      
    } // if()
    
    else if ( GetCommand( head ) == "string>?" ) {
      result -> str = "string>?" ;
      
    } // else if()
    
    else if ( GetCommand( head ) == "string<?" ) {
      result -> str = "string<?" ;
      
    } // else if()
    
    else if ( GetCommand( head ) == "string=?" ) {
      result -> str = "string=?" ;
      
    } // else if()
      
    
    if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count < 2 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    
    result = new Node ;
    result -> str = "" ;
    result -> type = "STRING" ;
    result -> right = NULL ;
    result -> left = NULL ;
    walk = head -> right ;
    now = walk -> left ;
    command = head -> left -> str ;
    
    // �Ĥ@�� string 
    walk -> left = Eval( walk -> left, false ) ; 
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    now = walk -> left ;
    
    if ( now -> type == "STRING" ) {
      challenge = now -> str ;
      
      challenge.erase( challenge.begin() ) ;
      challenge.erase( challenge.length() - 1 ) ;
      
      result -> str = result -> str + challenge ;
      
      walk = walk -> right ;
      
      // cout << "Test" << endl ;
      
    } // if()
    
    else {
      // ERROR
      finished = true ;
      
      mError = true ;
      
      if ( command == "string>?" ) {
        cout << "ERROR (string>? with incorrect argument type) : " ;
        
      } // if()
      
      else if ( command == "string<?" ) {
        cout << "ERROR (string<? with incorrect argument type) : " ;
        
      } // else if()
      
      else if ( command == "string=?" ) {
        cout << "ERROR (string=? with incorrect argument type) : " ;
        
      } // else if()
      
      mErrorHead = now ;
      
      return NULL ;
      
    } // else
    
    while ( walk -> type != "NIL" ) {
      
      walk -> left = Eval( walk -> left, false ) ; 
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      now = walk -> left ;
      
      if ( now -> type == "STRING" ) {
        contest = now -> str ;
        
        contest.erase( contest.begin() ) ;
        contest.erase( contest.length() - 1 ) ;
        
      } // if()
      
      else {
        // ERROR
        finished = true ;
      
        mError = true ;
        
        if ( command == "string-append" ) {
          cout << "ERROR (string-append with incorrect argument type) : " ;
          
        } // if()
        
        else if ( command == "string>?" ) {
          cout << "ERROR (string>? with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "string<?" ) {
          cout << "ERROR (string<? with incorrect argument type) : " ;
          
        } // else if()
        
        else if ( command == "string=?" ) {
          cout << "ERROR (string=? with incorrect argument type) : " ;
          
        } // else if()
        
        mErrorHead = now ;
        
        return NULL ;
        
      } // else
      
      if ( command == "string-append" ) {
        
        result -> str = result -> str + contest ;
        
      } // if()
      
      else if ( command == "string>?" ) {
        if ( challenge <= contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      else if ( command == "string<?" ) {
        if ( challenge >= contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      else if ( command == "string=?" ) {
        if ( challenge != contest ) {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
          
        } // if()
        
      } // else if()
      
      challenge = contest ;
      
      walk = walk -> right ;
      
    } // while()
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    else if ( command == "string-append" ) {
      result -> str = "\"" + result -> str + "\"" ;
      
      return result ;
      
    } // else if()
    
    else if ( result -> type != "NIL" ) {
      result -> str = "#t" ;
      result -> type = "T" ;
      
      return result ;
      
    } // else if()
    
    else {
      return result ;
      
    } // else
    
  } // StringBigSmall()
  
  NodePtr Begin( NodePtr head ) {
    NodePtr walk = head -> right ;
    NodePtr result = NULL ;
    int count = 0 ;
    
    
    result = new Node ;
    result -> right = NULL ;
    result -> left = NULL ;
    result -> str = "begin" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "begin" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      if ( walk -> right == NULL && walk -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    if ( count == 0 ) {
      mError = true ;
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return result ;
      
    } // if()
    
    walk = head -> right ;
    
    walk -> left = Eval( walk -> left, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    NodePtr now = walk -> left ;
    
    while ( walk -> right -> type != "NIL" ) {
      walk = walk -> right ;
      
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      now = walk -> left ;
      
    } // while()
    
    return now ;
    
  } // Begin()
  
  NodePtr Eqv( NodePtr head ) {
    NodePtr walk = head -> right ;
    
    NodePtr result = new Node ;
    NodePtr first = NULL ;
    NodePtr second = NULL ;
    int count = 0 ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    
    result -> str = "eqv?" ;
    result -> type = "SYMBOL" ;
    
    if ( head -> str == "eqv?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> right == NULL ) {
        if ( walk -> type != "NIL" ) {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        else if ( count > 2 ) {
          mError = true ;
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // else if()
        
        else if ( count < 2 ) {
          mError = true ;
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // else if()
        
      } // if()
      
      else if ( walk -> type != "" ) {
        // ERROR
        mError = true ;
        
        if ( walk -> type == "NIL" ) {
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // if()
        
        else {
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // else
        
      } // else if()
      
      count++ ;
      
      walk = walk -> right ;
      
    } // while()
    
    
    walk = head -> right ;
    result -> str = "" ;
    result -> type = "" ;
    
    // �Ĥ@�Ӥ�����F�� 
    if ( walk -> type == "" ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      first = walk -> left ;
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    walk = walk -> right ;
    
    // �ĤG�Ӥ�����F�� 
    if ( walk -> type == "" ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      second = walk -> left ;
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    // �]�����u�঳��� input
    // �ҥH���k��u��O NIL 
    if ( walk -> right -> type == "NIL" ) {
      if ( first -> type != "STRING" && second -> type != "STRING" &&
           first -> type != "" && second -> type != "" ) {
        if ( first -> str == second -> str ) {
          result -> str = "#t" ;
          result -> type = "T" ;
          
        } // if()
        
        else {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // else
        
      } // if()
      
      else if ( ( first -> type == "" && second -> type == "" ) ||
                ( first -> type == "STRING" && second -> type == "STRING" ) ) {
        if ( first == second ) {
          result -> str = "#t" ;
          result -> type = "T" ;
          
        } // if()
        
        else {
          result -> str = "nil" ;
          result -> type = "NIL" ;
          
        } // else
        
      } // else if()
      
      else {
        result -> str = "nil" ;
        result -> type = "NIL" ;
        
      } // else
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    return result ;
    
  } // Eqv()
  
  NodePtr Equal( NodePtr head ) {
    NodePtr walk = head -> right ;
    
    NodePtr result = new Node ;
    NodePtr first = NULL ;
    NodePtr second = NULL ;
    
    int count = 0 ;
    
    result -> str = "equal?" ;
    result -> type = "SYMBOL" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    if ( head -> str == "equal?" && 
         ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    while ( walk != NULL ) {
      if ( walk -> right == NULL ) {
        if ( walk -> type != "NIL" ) {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        else if ( count > 2 ) {
          mError = true ;
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // else if()
        
      } // if()
      
      else if ( walk -> type != "" ) {
        // ERROR
        mError = true ;
        
        if ( walk -> type == "NIL" ) {
          
          cout << "ERROR (incorrect number of arguments) : " ;
          
          mErrorHead = result ;
          
          return result ;
          
        } // if()
        
        else {
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // else
        
      } // else if()
      
      count++ ;
      
      walk = walk -> right ;
      
    } // while()
    
    walk = head -> right ;
    result -> str = "" ;
    result -> type = "" ;
    
    if ( walk -> type == "" ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      first = walk -> left ;
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    walk = walk -> right ;
    
    if ( walk -> type == "" ) {
      walk -> left = Eval( walk -> left, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      second = walk -> left ;
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    if ( walk -> right -> type == "NIL" ) {
      result = CheckTree( first, second ) ;
      
    } // if()
    
    else {
      // ERROR
      
    } // else
    
    return result ;
    
  } // Equal()
  
  NodePtr CheckTree( NodePtr first, NodePtr second ) {
    NodePtr result = new Node ;
    
    result -> right = NULL ;
    result -> left = NULL ;
    
    result -> str = "#t" ;
    result -> type = "T" ;
    
    if ( first == second && first == NULL ) {
      return result ;
      
    } // if()
    
    else if ( first -> str == second -> str ) {
      result = CheckTree( first -> right, second -> right ) ;
      if ( result -> type == "NIL" ) {
        return result ;
        
      } // if()
      
      result = CheckTree( first -> left, second -> left ) ;
      
      return result ;
      
    } // if()
    
    else {
      result -> str = "nil" ;
      result -> type = "NIL" ;
      
      return result ;
      
    } // else
    
  } // CheckTree()
  
  NodePtr If( NodePtr head ) {
    NodePtr original = CopyTree( head ) ;
    NodePtr walk = head -> right ;
    NodePtr condition = NULL ;
    NodePtr yes = NULL ;
    NodePtr no = NULL ;
    NodePtr result = NULL ;
    
    int count = 0 ; // �p�⦳�X��argument
    
    if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    // �u��¬ݦ��S���ŦXargument�Ʀr 
    while ( walk -> type != "NIL" ) {
      
      if ( walk -> right == NULL ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      if ( walk -> type == "" ) {
        count++ ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    walk = head -> right ;
    
    if ( count == 2 ) {
      condition = walk -> left ;
      
      walk = walk -> right ;
      
      yes = walk -> left ;
      
    } // if()
    
    else if ( count == 3 ) {
      condition = walk -> left ;
      
      walk = walk -> right ;
      
      yes = walk -> left ;
      
      walk = walk -> right ;
      
      no = walk -> left ;
      
    } // else if()
    
    else {
      // ERROR
      mError = true ;
      
      result = new Node ;
      result -> str = "if" ;
      result -> type = "SYMBOL" ;
      result -> right = NULL ;
      result -> left = NULL ;
      
      
      cout << "ERROR (incorrect number of arguments) : " ;
      
      mErrorHead = result ;
      
      return NULL ;
      
    } // else
    
    
    walk = head -> right ;
    
    // �p��condition 
    condition = Eval( condition, false ) ;
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    // �̫�A�ݦ��S�� ��L���~ 
    if ( condition -> type == "NIL" ) {
      if ( no != NULL ) {
        no = Eval( no, false ) ;
        
        if ( mError ) {
          return NULL ;
      
        } // if()
        
        return no ;
        
      } // if()
      
      else {
        // ERROR
        mError = true ;
        
        cout << "ERROR (no return value) : " ;
        
        mErrorHead = original ;
        
        return NULL ;
        
      } // else
      
    } // if()
    else {
      yes = Eval( yes, false ) ;
      
      if ( mError ) {
        return NULL ;
      
      } // if()
      
      return yes ;
      
    } // else
    
  } // If()
  
  // �C�Ӥ��e���O ���� + ������ 
  NodePtr Cond( NodePtr head ) {
    NodePtr original = CopyTree( head ) ;
    NodePtr walk = head -> right ;
    NodePtr now = NULL ;
    NodePtr result = NULL ;
    
    if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      head -> type = "SYMBOL-COMMAND" ;
      
      return head ;
      
    } // if()
    
    // (cond)�����p 
    if ( head -> right -> type == "NIL" ) {
      // ERROR
      mError = true ;
      
      cout << "ERROR (COND format) : " ;
      
      mErrorHead = head ;
      
      return head ;
      
    } // if()
    
    // COND format ERROR
    while ( walk -> type != "NIL" ) {
      NodePtr sidewalk = walk -> left ;
      
      if ( walk -> right == NULL ) {
        // ERROR
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
        return head ;
        
      } // if()
      
      // �ڥ��S������i�� 
      else if ( sidewalk -> type != "" ) {
        // ERROR
        mError = true ;
        
        cout << "ERROR (COND format) : " ;
        
        mErrorHead = original ;
        
        return NULL ;
        
      } // else if()
      
      // ������A���O�̭���X�����e�p��1�� 
      if ( sidewalk -> right -> type != "" ) {
         // ERROR
        mError = true ;
        
        cout << "ERROR (COND format) : " ;
        
        mErrorHead = original ;
        
        return NULL ;
        
      } // if()
      
      walk = walk -> right ;
      
    } // while()
    
    walk = head -> right ;
    
    // ����̭����B�� �A�]�]�t no return value ERROR 
    while ( walk -> type != "NIL" ) {
      NodePtr sidewalk = walk -> left ;
      NodePtr result_tool = NULL ;
      
      // �p��C�� sidewalk ������ 
      if ( walk -> right -> type != "NIL" ||  sidewalk -> left -> str != "else" ) {
        sidewalk -> left = Eval( sidewalk -> left, false ) ;
        
        if ( mError ) {
          return NULL ;
      
        } // if()
          
      } // if()
      
      // ���󦨥�
      if ( sidewalk -> left -> type != "NIL" ) {
        
        if ( sidewalk -> right -> type == "" ) {
          // �C�Ӥ��e���n�p��L�A��ERROR���n�^�� 
          while ( sidewalk -> right -> type != "NIL" ) {
            sidewalk = sidewalk -> right ;
            
            result_tool = Eval( sidewalk -> left, false ) ;
            
            if ( mError ) {
              return NULL ;
              
            } // if()
            
          } // while()
          
          if ( result == NULL ) {
            result = result_tool ;
            
            return result ;
            
          } // if()
          
          if ( mError ) {
            
            return NULL ;
      
          } // if()
          
        } // if()
        
      } // if()
      
      // ��F�̫�@�� 
      else if ( walk -> right -> type == "NIL" ) {
        if ( sidewalk -> left -> str == "else" ) {
          
          
          if ( result == NULL ) {
            result = Eval( sidewalk -> right -> left, false ) ;
            
          } // if()
          
          if ( mError ) {
            return NULL ;
      
          } // if()
          
        } // if()
        
        else {
          // ERROR
          mError = true ;
          
          cout << "ERROR (no return value) : " ;
          
          mErrorHead = original ;
          
          return NULL ;
          
        } // else
        
      } // else if()
      
      walk = walk -> right ;
      
    } // while()
    
    return result ;
    
  } // Cond()
  
  bool IsCommand( string str ) {
    for ( int i = 0 ; i < mCommandList.size() ; i++ ) {
      if ( str == mCommandList.at( i ) ) {
        return true ;
        
      } // if()
      
    } // for()
    
    return false ;
    
  } // IsCommand()
  
  NodePtr CopyTree( NodePtr head ) {
    NodePtr result = new Node ;
    result -> str = "" ;
    result -> type = "" ;
    result -> right = NULL ;
    result -> left = NULL ;
    
    result -> str = head -> str ;
    result -> type = head -> type ;
    
    if ( head -> right == NULL && head -> left == NULL ) {
      
      return result ;
      
    } // if()
    
    if ( head -> right != NULL ) {
      result -> right = CopyTree( head -> right ) ;
      
    } // if()
    
    if ( head -> left != NULL ) {
      result -> left = CopyTree( head -> left ) ;
      
    } // if()
    
    return result ;
    
  } // CopyTree() 
  
public:
  
  void GetTree( NodePtr head ) {
    
    mNowHead = head ;
    
  } // GetTree()
  
  void ChangeMError() {
    mError = false ;
    mNonFunctionError = false ;
    
  } // ChangeMError()
  
  // �������]�C�� Tree ���S�� Error ���o�� 
  // return NULL �{�b�N���ο�X�F��A�Ӥ��Oerror( 6/13 ) 
  // firstLevel: ��ܲ{�b�O�_���o�ʾ𪺲Ĥ@�h 
  NodePtr Eval( NodePtr head, bool firstLevel ) {
    NodePtr walk = NULL ;
    NodePtr tool = head ;
    
    // �ˬd non-list 
    if ( tool -> right != NULL && tool -> left != NULL ) {
      while ( tool -> right != NULL ) {
        tool = tool -> right ;
        
      } // while()
      
      if ( tool -> type != "NIL" ) {
        mError = true ;
        
        cout << "ERROR (non-list) : " ;
        
        mErrorHead = head ;
        
      } // if()
      
    } // if()
    
    if ( mError ) {
      return walk ;
      
    } // if()
    
    string command = GetCommand( head ) ;
    
    if ( mError ) {
      return walk ;
      
    } // if()
    
    if ( command == "define" ) {
      if ( mNowHead == head || head -> str == "define" ) {
        walk = Define( head ) ;
        
      } // if()
      
      else {
        // ERROR
        mError = true ;
        
        cout << "ERROR (level of DEFINE)" << endl << endl ;
        
        mErrorHead = NULL ;
        
      } // else
      
      
      // ShowMHeadList() ;
      
    } // if()
    
    else if ( command == "cons" ) {
      walk = Cons( head ) ;
      
    } // else if()
    
    else if ( command == "list" ) {
      
      walk = List( head ) ;
      
    } // else if()
    
    // quote �^�Ǫ��O ���e �A�Ӥ��O��ʾ� 
    else if ( command == "quote" || command == "'" ) {
      
      NodePtr test = NULL ;
      
      test = head -> right ;
      
      if ( ( head -> str == "quote" || head -> str == "'" ) &&
           ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) ) {
      
        if ( head -> type == "SYMBOL" ) {
          head -> type = "SYMBOL-COMMAND" ;
          
        } // if()
        
        return head ;
        
      } // if()
      
      // �ˬdERROR
      while ( test != NULL ) {
        if ( test -> right == NULL && test -> type != "NIL" ) {
          mError = true ;
          
          cout << "ERROR (non-list) : " ;
          
          mErrorHead = head ;
          
          return head ;
          
        } // if()
        
        test = test -> right ;
        
      } // while()
      
      // �ˬdERROR 
      if ( head -> right -> type == "NIL" ) {
        // ERROR
        mError = true ;
        
        NodePtr result = new Node ;
          
        result -> str = "quote" ;
        result -> type = "SYMBOL" ;
          
        result -> right = NULL ;
        result -> left = NULL ;
          
        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = result ;
        
        return result ;
        
      } // if()
      
      else {
        walk = head -> right -> left ;
        
      } // else
      
    } // else if()
    
    
    else if ( command == "car" ) {
      walk = Car( head ) ;
      
    } // else if()
    
    else if ( command == "cdr" ) {
      walk = Cdr( head ) ;
      
    } // else if()
    
    else if ( command == "atom?" ) {
      walk = IsAtom( head ) ;
      
    } // else if()
    
    else if ( command == "pair?" ) {
      walk = IsPair( head ) ;
      
    } // else if()
    
    else if ( command == "list?" ) {
      walk = IsList( head ) ;
      
    } // else if()
    
    else if ( command == "null?" ) {
      walk = IsNull( head ) ;
      
    } // else if()
    
    else if ( command == "integer?" ) {
      walk = IsInteger( head ) ;
      
    } // else if()
    
    else if ( command == "real?" || command == "number?" ) {
      walk = IsReal( head ) ;
      
    } // else if()
    
    else if ( command == "string?" ) {
      walk = IsString( head ) ;
      
    } // else if()
    
    else if ( command == "boolean?" ) {
      walk = IsBoolean( head ) ;
      
    } // else if()
    
    else if ( command == "symbol?" ) {
      walk = IsSymbol( head ) ;
      
    } // else if()
    
    else if ( command == "+" || command == "-" ||
              command == "*" || command == "/" ) {
      
      walk = Caculate( head ) ;
      
      
    } // else if()
    
    else if ( command == "not" ) {
      walk = Not( head ) ;
                
    } // else if()
    
    else if ( command == "and" ) {
      walk = And( head ) ;
      
    } // else if()
    
    else if ( command == "or" ) {
      walk = Or( head ) ;
      
    } // else if()
    
    else if ( command == ">" || command == ">=" || 
              command == "<" || command == "<=" || 
              command == "=" ) {
      walk = IntBigSmall( head ) ;
    
    } // else if()
    
    else if ( command == "string-append" || command == "string>?" ||
              command == "string<?" || command == "string=?" ) {
      walk = StringBigSmall( head ) ;
    
    } // else if()
    
    else if ( command == "eqv?" ) {
      walk = Eqv( head ) ;
      
    } // else if()
    
    else if ( command == "equal?" ) {
      walk = Equal( head ) ;
      
    } // else if()
    
    else if ( command == "begin" ) {
      walk = Begin( head ) ;
      
    } // else if()
    
    else if ( command == "if" ) {
      walk = If( head ) ;
      
    } // else if()
    
    else if ( command == "cond" ) {
      walk = Cond( head ) ;
      
    } // else if()
    
    else if ( command == "clean-environment" ) {
      if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
        head -> type = "SYMBOL-COMMAND" ;
        
        return head ;
        
      } // if()
      
      if ( head -> right -> type == "NIL" ) {
        if ( mNowHead == head ) {
          mHeadList.clear() ;
      
          cout << "environment cleaned" << endl << endl ;
          
        } // if()
        else {
          mError = true ;
          
          cout << "ERROR (level of CLEAN-ENVIRONMENT)" << endl << endl ;
          
          mErrorHead = NULL ;
          
        } // else
        
      } // if()
      
      else {
        NodePtr walk = head ;
        
        // ERROR
        mError = true ;
        
        while ( walk != NULL ) {
          if ( walk -> right == NULL && walk -> type != "NIL" ) {
            cout << "ERROR (non-list) : " ;
            
            mErrorHead = head ;
            
            return head ;
            
          } // if()
          
          walk = walk -> right ;
          
        } // while()
        
        cout << "ERROR (incorrect number of arguments) : " ;
        
        NodePtr result = new Node ;
        result -> str = "clean-environment" ;
        result -> type = "SYMBOL" ;
        result -> left = NULL ;
        result -> right = NULL ;
        
        mErrorHead = result ;
        
      } // else
      
    } // else if()
    
    else if ( command == "SYMBOL" ) {
      walk = GetSymbolTree( head -> str ) ;
      
    } // else if()
    
    // �u���@�Ӹ`�I�A�D SYMBOL 
    // e.g. int, float, string
    else if ( command == "OUTPUT" ) {
      
      walk = head ;
      
    } // else if()
    
    else if ( command == "NO-COMMAND" ) {
      mError = true ;
      
      mNonFunctionError = true ;
      
      cout << "ERROR (attempt to apply non-function) : " ;
      
      mErrorHead = head -> left ;
      
      return head -> left ;
      
    } // else if()
    
    else if ( command == "exit" ) {
      
      if ( head -> type == "SYMBOL" || head -> type == "SYMBOL-COMMAND" ) {
      
        if ( head -> type == "SYMBOL" ) {
          head -> type = "SYMBOL-COMMAND" ;
          
        } // if()
        
        return head ;
        
      } // if()
      
      if ( head != mNowHead ) {
        // ERROR
        mError = true ;
        
        cout << "ERROR (level of EXIT)" << endl << endl ;
        
        mErrorHead = NULL ;
        
      } // if()
      
      else if ( head -> right -> type == "NIL" ) {
        return NULL ;
        
      } // else if()
      
      else {
        // ERROR
        NodePtr walk = head -> right ;
        
        mError = true ;
        
        while ( walk != NULL ) {
          if ( walk -> right == NULL && walk -> type != "NIL" ) {
            cout << "ERROR (non-list) : " ;
            
            mErrorHead = head ;
            
            return head ;
            
          } // if()
          
          walk = walk -> right ;
          
        } // while()

        cout << "ERROR (incorrect number of arguments) : " ;
        
        mErrorHead = new Node ;
        mErrorHead -> str = "exit" ;
        mErrorHead -> type = "SYMBOL" ;
        mErrorHead -> right = NULL ;
        mErrorHead -> left = NULL ;
        
      } // else
      
    } // else if()
    
    // ���򳣤��O�A�]��ܨS��command 
    else {
      
      mError = true ;
      
      mNonFunctionError = true ;
      
      cout << "ERROR (attempt to apply non-function) : " ;
      
      mErrorHead = head -> left ;
      
      return head -> left ;
      
    } // else
    
    if ( mError ) {
      return NULL ;
      
    } // if()
    
    return walk ;
    
  } // Eval()
  
  
  // ��өw�q�L�� symbol output 
  // �p�G symbol �� "���e" �����N�O�@�ӫ��O�A���N����L
  void ShowSymbol( string symbol ) {
    NodePtr head ;
    
    for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
      if ( mHeadList.at( i ) -> left -> str == symbol ) {
        
        ShowTree( mHeadList.at( i ) -> right -> left ) ; 
        
      } // if()
      
    } // for()
    
  } // ShowSymbol()
  
  
  // return symbol �����e 
  NodePtr FindSymbol( string symbol ) {
    for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
      if ( mHeadList.at( i ) -> left -> str == symbol ) {
        return mHeadList.at( i ) -> right -> left ;
        
      } // if()
      
    } // for()
    
    return NULL ;
    
  } // FindSymbol()
  
  // �ݸ� symbol �O�_���Q�w�q�L 
  bool IsSymbolDefined( string symbol ) {
    for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
      if ( mHeadList.at( i ) -> left -> str == symbol ) {
        return true ;
        
      } // if()
      
    } // for()
    
    return false ;
    
  } // IsSymbolDefined()
  
  // �^�Ǹ�symbol�����e 
  NodePtr GetSymbolTree( string symbol ) {
    for ( int i = 0 ; i < mHeadList.size() ; i++ ) {
      if ( mHeadList.at( i ) -> left -> str == symbol ) {
        return mHeadList.at( i ) -> right -> left ;
        
      } // if()
      
    } // for()
    
    return NULL ;
    
  } // GetSymbolTree()
  
  // �s�@�@�� command list 
  void MakeCommand() {
    mCommandList.push_back( "cons" ) ;
    mCommandList.push_back( "list" ) ;
    mCommandList.push_back( "quote" ) ;
    mCommandList.push_back( "'" ) ;
    mCommandList.push_back( "define" ) ;
    mCommandList.push_back( "car" ) ;
    mCommandList.push_back( "cdr" ) ;
    mCommandList.push_back( "atom?" ) ;
    mCommandList.push_back( "pair?" ) ;
    mCommandList.push_back( "list?" ) ;
    mCommandList.push_back( "null?" ) ;
    mCommandList.push_back( "integer?" ) ;
    mCommandList.push_back( "real?" ) ;
    mCommandList.push_back( "number?" ) ;
    mCommandList.push_back( "string?" ) ;
    mCommandList.push_back( "boolean?" ) ;
    mCommandList.push_back( "symbol?" ) ;
    mCommandList.push_back( "+" ) ;
    mCommandList.push_back( "-" ) ;
    mCommandList.push_back( "*" ) ;
    mCommandList.push_back( "/" ) ;
    mCommandList.push_back( "not" ) ;
    mCommandList.push_back( "and" ) ;
    mCommandList.push_back( "or" ) ;
    mCommandList.push_back( ">" ) ;
    mCommandList.push_back( ">=" ) ;
    mCommandList.push_back( "<" ) ;
    mCommandList.push_back( "<=" ) ;
    mCommandList.push_back( "=" ) ;
    mCommandList.push_back( "string-append" ) ;
    mCommandList.push_back( "string>?" ) ;
    mCommandList.push_back( "string<?" ) ;
    mCommandList.push_back( "string=?" ) ;
    mCommandList.push_back( "eqv?" ) ;
    mCommandList.push_back( "equal?" ) ;
    mCommandList.push_back( "begin" ) ;
    mCommandList.push_back( "if" ) ;
    mCommandList.push_back( "cond" ) ;
    mCommandList.push_back( "clean-environment" ) ;
    mCommandList.push_back( "exit" ) ;
    
  } // MakeCommand()
  
  // input �i�ӬO�����H���� head �}�l output
  // �|�Ҽ{ quote �����p�A���i�Ӫ� head ���� symbol �M ���e �n�ۤv�վ� 
  void ShowTree( NodePtr head ) {
    Token nToken ;
    
    // ��ShowAllToken���ϥΪ� 
    bool sameLine = false ;
    
    
    if ( mError ) {
      head = mErrorHead ;
      
    } // if()
    
    
    // �o��ܬƻ򳣤��ο�X
    // �q�`�b�o�̫ݪ�� define �άO environment-clean �A�L�̷|�ۤv��X���G 
    if ( head == NULL ) {
      
      
    } // if()
    
    // �p�G�u���@�ӪF�誺�ܡA���� output �Y�i 
    else if ( head -> str != "" ) {
      nToken.str = head -> str ;
      nToken.type = head -> type ;
      
      PrintTokenCorrectly( nToken ) ;
      
      cout << endl << endl ;
      
    } // if()
    
    else {
      // �ڪ� TranslateTree_mAllToken �| skip ���Ĥ@�� "("
      // �ҥH�o�̭n�ɤW 
      
      nToken.str = "(" ;
      nToken.type = "LEFT-PAREN" ;
      
      mAllToken.push_back( nToken ) ;
      
      TranslateTree_mAllToken( head, false ) ;
      
      // ���� '()�����p 
      if ( mAllToken.size() == 3 && mAllToken.at( 1 ).type == "NIL" ) {
        mAllToken.erase( mAllToken.begin() ) ;
        
        mAllToken.pop_back() ;
        
      } // if()
      
      else {
        TranslateParen_Dot( 0 ) ;
        
        TranslateParen_Dot_Paren( 1 ) ;
        
      } // else
      
      ShowAllToken( 0, 0, sameLine ) ;
      
      mAllToken.clear() ;
    
      cout << endl ;
       
    } // else
    
  } // ShowTree()
  
}; // Evaluate

int main() {
  Scanner scanner ;
  Evaluate evaluate ;
  int testNum ;
  string str = "" ; // �����Ӧ� scanner ��W symbol �� str�A�æ^�ǵ� evaluate 
  NodePtr result ; // Eval �X�Ӫ����G 
  
  evaluate.MakeCommand() ;
  
  cin >> testNum ;
  
  cout << "Welcome to OurScheme!" << endl << endl ;
  
  scanner.Initial() ;
  
  // cout << testNum << endl ;
  
  while ( !scanner.ReturnMError() && !scanner.IsEnd() ) {
    
    cout << "> " ;
    
    scanner.ReadString() ;
    
    evaluate.ChangeMError() ;
    
    
    if ( scanner.HasSyntaxError() ) {
      scanner.Show() ;
      
      if ( scanner.ReturnMError() ) {
        cout << "> " ;
        
      } // if()
      
    } // if()
    
    else if ( !scanner.ReturnMError() ) {
      
      evaluate.GetTree( scanner.GetTreeHead() ) ;
      
      result = evaluate.Eval( scanner.GetTreeHead(), true ) ;
      
      evaluate.ShowTree( result ) ;
      
    } // else if()
    
  } // while()
  
  if ( scanner.ReturnMError() ) {
    cout << "ERROR (no more input) : END-OF-FILE encountered" ;
    
  } // if()
  
  cout  << endl << "Thanks for using OurScheme!" ;
  
} // main()
