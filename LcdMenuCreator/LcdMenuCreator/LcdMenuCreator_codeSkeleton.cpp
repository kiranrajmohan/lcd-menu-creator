void printLineIndicator(LineStatus &i)
{
	lcd_gotoxy(0,i.currentLine);
	if( i.lineIndicatorList[i.currentLine]==1){
		if( i.lineList[i.currentLine] == 1 ){
			lcd_puts( <ActiveLineIndicator> ); 
		}else{
			lcd_puts( <LineIndicator> ); 
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
		int curPosTemp=i.currentLine;

		if( <right> )
		{
				if( currentPos < horizPosInLine[i.currentLine]-1 ){
					currentPos++;
				}else{
					currentPos=0;
				}
		}else if( <left> ){
			if( currentPos > 0  ){
				currentPos--;
			}else{
				currentPos=horizPosInLine[i.currentLine]-1;
			}
		}
	}

	if( i.navOn[1] ) //up/down nav is on
	{
		int curLineTemp=i.currentLine;
		if( <up> )
		{
			do{
				if( i.currentLine < i.numLines-1 ){
					i.currentLine++;
				}else{
					i.currentLine=0;
				}
			}while( i.lineCursorList[ i.currentLine ]==0 && i.currentLine!=curLineTemp ); //2nd condition to prevent infinite loops
		}
		else if( <down> )
		{
			do{
				if( i.currentLine > 0 ){
					i.currentLine--;
				}else{
					i.currentLine=i.numLines - 1;
				}
			}while( i.lineCursorList[ i.currentLine ]==0 && i.currentLine!=curLineTemp ); //Skip lines without cursor.2nd condition to prevent infinite loops
		}
	}

}