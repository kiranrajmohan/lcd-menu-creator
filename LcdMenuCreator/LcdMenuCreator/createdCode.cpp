struct LineStatus{
  
		char showCursor,					
		currentLine,						
		currentPosIndex,					
		numLines,							
		lineCursorList[3],
lineIndicatorList[3],
lineStart[3],
navOn[2] 
};

void printLineIndicator(LineStatus &i)
{
	lcd_gotoxy(0,i.currentLine);
	if( i.lineIndicatorList[i.currentLine]==1){
		if( i.lineList[i.currentLine] == 1 ){
			lcd_puts_P( "->" ); 
		}else{
			lcd_puts_P( "* " ); 
		}
	}
} 

void navManager( LineStatus &i X)
{
	if( !i.navOn[0] && !i.navOn[1]){ //nav is off
		return;  
	}
	
	if( i.navOn[0] && horizPosInLine[i.currentLine]>1 ) //left/right nav is on & there are horiz pos's in this line
	{
		if( ((RIGHT_OPORT& (1<<RIGHT_PORT)) == 0) )
		{
				if( i.currentPosIndex < horizPosInLine[i.currentLine]-1 ){
					i.currentPosIndex++;
				}else{
					i.currentPosIndex=0;
				}
		}else if( ((LEFT_OPORT& (1<<LEFT_PORT)) == 0) ){
			if( i.currentPosIndex > 0  ){
				i.currentPosIndex--;
			}else{
				i.currentPosIndex=horizPosInLine[i.currentLine]-1;
			}
		}
	}

	if( i.navOn[1] ) //up/down nav is on
	{
		if( ((UP_OPORT& (1<<UP_PORT)) == 0) )
		{
			do{
				if( i.currentLine < i.numLines-1 ){
					i.currentLine++;
				}else{
					i.currentLine=0;
				}
			}while( i.lineCursorList[ i.currentLine ]==0 && i.currentLine!=curLineTemp ); //2nd condition to prevent infinite loops
			i.currentPosIndex=horizPosInLine[0];
		}
		else if( ((DOWN_OPORT& (1<<DOWN_PORT)) == 0) )
		{
			do{
				if( i.currentLine > 0 ){
					i.currentLine--;
				}else{
					i.currentLine=i.numLines - 1;
				}
			}while( i.lineCursorList[ i.currentLine ]==0 && i.currentLine!=curLineTemp ); //Skip lines without cursor.2nd condition to prevent infinite loops
			i.currentPosIndex=horizPosInLine[0];
		}
	}

}

//-----------------Page function------------------

//----------------RunningDisplay---------------------------
void generatedMenu_RunningDisplay(){
LineStatus i={0,2,2,3,{0,0,1},{0,0,1},{0,0,2},{0,0}};

lcd_gotoxy(0,0);
lcd_puts_P("Now   ");
lcd_gotoxy(9,0);
lcd_puts_P(" ");
lcd_gotoxy(0,1);
lcd_puts_P("Next ");
lcd_gotoxy(2,2);
lcd_puts_P(" Show Menu");

while(1){

printDay( currentTime.day , 6, 0 );
printTime( currentTime.h, currentTime.min, currentTime.s, 10, 0);
if(!mGlobals.newNextRing)
{
printDay( nextRing.day , 5, 1 );
printTime( nextRing.h, nextRing.m, nextRing.s, 9, 1);
resetNewNextRing();
}
 navManager(i);
 if( display.toUpdate){
 	printLineIndicator(i); 
 }
 if( i.currentLine==2){
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_MainMenu() );
	return;
	}

}

}


}

//----------------MainMenu---------------------------
void generatedMenu_MainMenu(){
LineStatus i={0,0,2,3,{1,1,1},{1,1,1},{2,2,2},{0,1}};

lcd_gotoxy(2,0);
lcd_puts_P("Set Time");
lcd_gotoxy(2,1);
lcd_puts_P("Set Time Table");
lcd_gotoxy(2,2);
lcd_puts_P("Pause");

while(1){

 navManager(i);
 if( display.toUpdate){
 	printLineIndicator(i); 
 }
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_RunningDisplay() );
	return;
	}

 if( i.currentLine==0){
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_SetTimeMenu() );
	return;
	}

}

 if( i.currentLine==1){
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_SetTableMenu() );
	return;
	}

}

 if( i.currentLine==2){
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_PauseMenu() );
	return;
	}

}

}


}

//----------------SetTimeMenu---------------------------
void generatedMenu_SetTimeMenu(){
LineStatus i={0,0,0,1,{0},{0},{0},{0,0}};

lcd_gotoxy(0,0);
lcd_puts_P("SetTimeMenu");

while(1){

 navManager(i);
 if( display.toUpdate){
 	printLineIndicator(i); 
 }
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_MainMenu() );
	return;
	}

}


}

//----------------SetTableMenu---------------------------
void generatedMenu_SetTableMenu(){
LineStatus i={0,0,0,1,{0},{0},{0},{0,0}};

lcd_gotoxy(0,0);
lcd_puts_P("SetTableMenu");

while(1){

 navManager(i);
 if( display.toUpdate){
 	printLineIndicator(i); 
 }
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_MainMenu() );
	return;
	}

}


}

//----------------PauseMenu---------------------------
void generatedMenu_PauseMenu(){
LineStatus i={0,0,0,1,{0},{0},{0},{0,0}};

lcd_gotoxy(0,0);
lcd_puts_P("PauseMenu");

while(1){

 navManager(i);
 if( display.toUpdate){
 	printLineIndicator(i); 
 }
	if( ((ENTER_OPORT& (1<<ENTER_PORT)) == 0)){
		LoadMenu( generatedMenu_MainMenu() );
	return;
	}

}


}

//-----------------Page functions over------------------
